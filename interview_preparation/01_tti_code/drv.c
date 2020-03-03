/* tti driver */

static int gul_tti_dev_open(struct inode *inode, struct file *filp)
{
	struct gul_tti_device_data *tti_dev = NULL;

	tti_dev = container_of(inode->i_cdev, struct gul_tti_device_data, cdev);
	filp->private_data = tti_dev;
	return 0;
}

static int gul_tti_dev_release(struct inode *inode, struct file *filp)
{
	filp->private_data = NULL;
	return 0;
}

static ssize_t gul_tti_dev_read(struct file *filp, char __user *buf,
				size_t count, loff_t *offset)
{
	int rc = 0;
	DECLARE_SWAITQUEUE(wait);
	struct gul_tti_device_data *tti_dev = NULL;

	tti_dev = filp->private_data;
	raw_spin_lock(&tti_dev->gul_dev->tti_priv_t->wq_lock);
	prepare_to_swait(&tti_dev->gul_dev->tti_priv_t->tti_wq, &wait,
						TASK_INTERRUPTIBLE);
	raw_spin_unlock(&tti_dev->gul_dev->tti_priv_t->wq_lock);

	/*Now wait here, tti notificaion will wakeup*/
	schedule();

	raw_spin_lock(&tti_dev->gul_dev->tti_priv_t->wq_lock);
	finish_swait(&tti_dev->gul_dev->tti_priv_t->tti_wq, &wait);
	raw_spin_unlock(&tti_dev->gul_dev->tti_priv_t->wq_lock);

	rc = put_user(tti_dev->gul_dev->tti_priv_t->tti_count, (int *)buf);
	if (!rc)
		rc = sizeof(tti_dev->gul_dev->tti_priv_t->tti_count);
	return rc;
}

#ifdef HAVE_UNLOCKED_IOCTL
static long gul_tti_dev_ioctl(struct file *filp, unsigned int cmd,
			unsigned long arg)
#else
static int gul_tti_dev_ioctl(struct inode *inode, struct file *filp,
			unsigned int cmd, unsigned long arg)
#endif
{
	int ret = 0;
	struct tti tti_t = {0};
	struct gul_tti_device_data *tti_dev = NULL;
	struct gul_dev *gul_dev = NULL;

	tti_dev = (struct gul_tti_device_data *)filp->private_data;
	gul_dev = tti_dev->gul_dev;

	switch (cmd) {
	case IOCTL_GUL_MODEM_TTI_REGISTER:
		ret = copy_from_user(&tti_t, (struct tti *)arg,
						sizeof(struct tti));
		if (ret != 0)
			return -EFAULT;
		ret = tti_register_irq(gul_dev, &tti_t);
		break;

	case IOCTL_GUL_MODEM_TTI_DEREGISTER:
		ret = copy_from_user(&tti_t, (struct tti *)arg,
						sizeof(struct tti));
		if (ret != 0)
			return -EFAULT;
		tti_deregister_irq(gul_dev, &tti_t);
		break;

	default:
		ret = -ENOTTY;
	}
	return ret;
}


/* TTI initialize file_operations */
static const struct file_operations gul_tti_dev_fops = {
	.owner		= THIS_MODULE,
	.open		= gul_tti_dev_open,
	.release	= gul_tti_dev_release,
	.read		= gul_tti_dev_read,
#ifdef HAVE_UNLOCKED_IOCTL
	.unlocked_ioctl = gul_tti_dev_ioctl,
#else
	.ioctl = gul_tti_dev_ioctl,
#endif
#ifdef CONFIG_COMPAT
	.compat_ioctl = gul_tti_dev_ioctl,
#endif
};

#define MAX_DEV 2

static struct class *gul_tti_dev_class;
static dev_t tti_dev_number;
static int tti_dev_major;
static struct gul_tti_device_data *tti_dev_data[MAX_DEV];

int create_tti_cdevs(struct gul_tti_device_data **tti_dev_data)
{
	int i, err, rc = 0;
	/*Allocating chardev region and assigning Major number*/
	err = alloc_chrdev_region(&tti_dev_number, 0, MAX_DEV, "gulttidev");
	/* Device Major number*/
	tti_dev_major = MAJOR(tti_dev_number);
	/*sysfs class creation */
	gul_tti_dev_class = class_create(THIS_MODULE, "gulttidev");
	for (i = 0; i < MAX_DEV; i++) {
		cdev_init(&tti_dev_data[i]->cdev, &gul_tti_dev_fops);
		tti_dev_data[i]->cdev.ops = &gul_tti_dev_fops;
		tti_dev_data[i]->cdev.owner = THIS_MODULE;
		/* Adding a device to the system:i-Minor number of new device*/
		cdev_add(&tti_dev_data[i]->cdev, MKDEV(tti_dev_major, i), 1);
		device_create(gul_tti_dev_class, NULL, MKDEV(tti_dev_major, i),
					NULL, "gulttidev%d", i);
	}
	return rc;
}

void remove_tti_cdevs(void)
{
	int i;

	for (i = 0; i < MAX_DEV; i++) {
		cdev_del(&tti_dev_data[i]->cdev);
		device_destroy(gul_tti_dev_class, MKDEV(tti_dev_major, i));
	}
	class_unregister(gul_tti_dev_class);
	class_destroy(gul_tti_dev_class);
	unregister_chrdev_region(tti_dev_number, MAX_DEV);
}

#define SIGNAL_TO_USERSPACE	1

/* TTI IRQ Handler */
static irqreturn_t tti_irq_handler(int irq, void *data)
{
	struct tti_priv *tti_priv_t = (struct tti_priv *)data;
	/* Send signal to User space */
	if (tti_priv_t) {
		raw_spin_lock(&tti_priv_t->wq_lock);
		swake_up_all_locked(&tti_priv_t->tti_wq);
		raw_spin_unlock(&tti_priv_t->wq_lock);
	}
	return IRQ_HANDLED;
}

int tti_register_irq(struct gul_dev *gul_dev, struct tti *tti_t)
{
	int ret = 0;
	int tti_interrupt_flags = IRQF_NO_THREAD | IRQF_TRIGGER_RISING;
	struct tti_priv *tti_priv_t = NULL;

	tti_priv_t = &gul_dev->tti_priv_t[tti_t->ttid];
	tti_priv_t->tti_id = tti_t->ttid;
	if (tti_priv_t->irq != 0) {
	/* IRQ request */
		ret = request_irq(tti_priv_t->irq, tti_irq_handler,
				tti_interrupt_flags, "tti_handler", tti_priv_t);
		if (ret < 0) {
			dev_err(gul_dev->dev, "%s request irq err - %d\n",
							__func__, ret);
			goto err;
		}
	} else {
		dev_err(gul_dev->dev, "%s IRQ is invalid\n", __func__);
		ret = -EINVAL;
		goto err;
	}

err:
	return ret;
}

void tti_deregister_irq(struct gul_dev *gul_dev, struct tti *tti_t)
{
	struct tti_priv *tti_priv_t = &gul_dev->tti_priv_t[tti_t->ttid];

	if (tti_priv_t != NULL) {
		/* IRQ request */
		free_irq(tti_priv_t->irq, tti_priv_t);
	}

	return;
}

void init_tti(void)
{
	/* TTI Interrupt Number extraction from device node */
	dn_modem_tti = of_find_node_by_name(NULL, "modem_tti");
	if (!dn_modem_tti) {
		dev_info(gul_dev->dev, "Error:modem_tti Node missing in DTB\n");
		return -ENODEV;
	}
	gul_dev->tti_priv_t[0].irq = of_irq_get(dn_modem_tti, 0);
	gul_dev->tti_priv_t[1].irq = of_irq_get(dn_modem_tti, 1);
	for (i = 0; i < MAX_DEV; i++) {
		tti_dev_data[i] = kmalloc(sizeof(struct gul_tti_device_data),
						GFP_KERNEL);
		tti_dev_data[i]->gul_dev = gul_dev;
	}
	rc = create_tti_cdevs(tti_dev_data);
	if (rc) {
		dev_err(gul_dev->dev, "Failed to create char devs\n");
		goto out;
	}
	for (i = 0; i < MAX_DEV; i++) {
		/*simple wait queue init*/
		init_swait_queue_head(&gul_dev->tti_priv_t[i].tti_wq);
		/*raw spinlock init for TTI module*/
		raw_spin_lock_init(&gul_dev->tti_priv_t[i].wq_lock);
	}
}
