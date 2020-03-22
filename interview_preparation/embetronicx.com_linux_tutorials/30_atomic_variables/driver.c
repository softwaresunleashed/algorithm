#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>		//kmalloc()
#include <linux/uaccess.h>	// copy_to/from_user()

#include <linux/kthread.h>	// kernel threads
#include <linux/sched.h>	// task_struct		
#include <linux/delay.h>


atomic_t etx_global_variable = ATOMIC_INIT(0);	// Atomic variable declaration & initialization
unsigned int etc_bit_check = 0;

dev_t dev = 0;

// Driver variables should be declared 'static' since they should be visible only to the filed.
static struct class *dev_class;		// struct for device class
static struct cdev etx_cdev;		// struct for character device

static int __init etx_driver_init(void);	// module init function
static void __exit etx_driver_exit(void);	// module exit function

// Thread structures
static struct task_struct * etx_thread1;	// thread 1 tcb
static struct task_struct * etx_thread2;	// thread 2 tcb

// Driver file operations functions
static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t len,loff_t * off);
static ssize_t etx_write(struct file *filp, 
                const char *buf, size_t len, loff_t * off);


int thread_function1(void *pv)
{
    unsigned int prev_value = 0;

    while(!kthread_should_stop()) {
        atomic_inc(&etx_global_variable);
        prev_value = test_and_change_bit(1, (void*)&etc_bit_check);
        printk(KERN_INFO "Function1 [value : %u] [bit:%u]\n", atomic_read(&etx_global_variable), prev_value);
        //printk("T1...\n");
	msleep(5000);
    };
    return 0;
}

int thread_function2(void *pv)
{
    unsigned int prev_value = 0;
    while(!kthread_should_stop()) {
        atomic_inc(&etx_global_variable);
        prev_value = test_and_change_bit(1,(void*) &etc_bit_check);
        printk(KERN_INFO "Function2 [value : %u] [bit:%u]\n", atomic_read(&etx_global_variable), prev_value);
        //printk("T2...\n");
	msleep(5000);
    };
    return 0;
}

static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = etx_read,
        .write          = etx_write,
        .open           = etx_open,
        .release        = etx_release,
};
 
static int etx_open(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Device File Opened...!!!\n");
        return 0;
}
 
static int etx_release(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Device File Closed...!!!\n");
        return 0;
}

static ssize_t etx_read(struct file *filp,
                char __user *buf, size_t len, loff_t *off)
{
        printk(KERN_INFO "Read function\n");

        return 0;
}

static ssize_t etx_write(struct file *filp,
                const char __user *buf, size_t len, loff_t *off)
{
        printk(KERN_INFO "Write Function\n");
        return len;
}

static int __init etx_driver_init(void)
{
	// 1. Allocating Major Number
	if((alloc_chrdev_region(&dev, 0, 1, "etx_dev")) < 0)
	{
		printk(KERN_INFO "Cannot allocate major number\n");
		return -1;
	}
	printk(KERN_INFO "Major = %d Minor = %d \n", MAJOR(dev), MINOR(dev));

	// 2. Creating Character device
	cdev_init(&etx_cdev, &fops);

	// 3. Adding character device to the system
	if((cdev_add(&etx_cdev, dev, 1)) < 0)
	{
		printk(KERN_INFO "Cannot add the device to the system\n");
		goto r_class;
	}

	// 4. Creating class struct
	if((dev_class = class_create(THIS_MODULE, "etx_class")) == NULL)
	{
		printk(KERN_INFO "Cannot create the struct class\n");
		goto r_class;
	}

	// 5. Creating device node /dev/etx_device
	if((device_create(dev_class, NULL, dev, NULL, "etx_device")) == NULL)
	{
		printk(KERN_INFO "Cannot create the device\n");
		goto r_device;
	}
	
	// 6. Creating Thread 1
	etx_thread1 = kthread_run(thread_function1, NULL, "etx_1_thread");
	if(etx_thread1)
	{
		printk(KERN_INFO "Kthread1 created successfully...\n");
	}
	else
	{
		printk(KERN_INFO "Cannot create kthread1\n");
		goto r_device;
	}

	// 7. Creating Thread 2
	etx_thread2 = kthread_run(thread_function2, NULL, "etx_2_thread");
	if(etx_thread2)
	{
		printk(KERN_INFO "Kthread2 created successfully...\n");
	}
	else
	{
		printk(KERN_INFO "Cannot create kthread2\n");
		goto r_device;
	}
	
	printk(KERN_INFO "Device Driver Insert...Done!!!\n");
	return 0;

r_device:
	class_destroy(dev_class);

r_class:
	unregister_chrdev_region(dev, 1);	// unregister character device region
	cdev_del(&etx_cdev);			// delete character device	
	return -1;
}

void __exit etx_driver_exit(void)
{
	// Stop running threads
	kthread_stop(etx_thread1);
	kthread_stop(etx_thread2);

	// destroy device
	device_destroy(dev_class, dev);

	// destroy device node
	class_destroy(dev_class);

	// delete character device
	cdev_del(&etx_cdev);

	// finally unregister character device region
	unregister_chrdev_region(dev, 1);

	printk(KERN_INFO "Device Driver Removed...Done!!!\n");
}


module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sudhanshu Gupta <cool.sudhanshu@gmail.com>");
MODULE_DESCRIPTION("A simple device driver - Atomic Variables");
MODULE_VERSION("1.27");
