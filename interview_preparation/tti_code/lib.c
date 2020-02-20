#define GUL_TTI_DEVNAME_PREFIX "gultti"
#define GUL_TTI_DEV0_NAME	"dev0"
#define GUL_TTI_DEV1_NAME	"dev1"

static inline int open_devtti(int modem_id)
{
	char tti_dev_name[50];
	int devtti;
	if (modem_id == 0)
		sprintf(tti_dev_name, "/dev/%s%s", GUL_TTI_DEVNAME_PREFIX,
					GUL_TTI_DEV0_NAME);
	else if (modem_id == 1)
		sprintf(tti_dev_name, "/dev/%s%s", GUL_TTI_DEVNAME_PREFIX,
						GUL_TTI_DEV1_NAME);
	printf("Trying to open device : %s\n", tti_dev_name);
	devtti = open(tti_dev_name, O_RDWR);
	if (devtti < 0) {
		printf("Error(%d): Cannot open %s\n", devtti, tti_dev_name);
		return devtti;
	}
	return devtti;
}

int modem_tti_register(struct tti *tti_t, int modem_id)
{
	int32_t ret = 0;

	/* Register TTI */
	tti_t->dev_tti_handle = open_devtti(modem_id);
	if (tti_t->dev_tti_handle < 0) {
		printf("Unable to open device.\n");
		ret = -2;
		goto err;
	}

	/* IOCTL - register FD with kernel */
	ret = ioctl(tti_t->dev_tti_handle, IOCTL_GUL_MODEM_TTI_REGISTER, tti_t);
	if (ret < 0) {
		printf("IOCTL_GUL_MODEM_TTI_REGISTER failed.\n");
		goto err;
	}

err:
	return ret;
}


static inline int close_devtti(int dev_tti_handle)
{
	return close(dev_tti_handle);
}

int modem_tti_deregister(struct tti *tti_t)
{
	int32_t ret = 0;

	/* Free IRQs */
	ret = ioctl(tti_t->dev_tti_handle, IOCTL_GUL_MODEM_TTI_DEREGISTER,
				tti_t);
	if (ret < 0) {
		printf("IOCTL_GUL_MODEM_TTI_DEREGISTER failed.\n");
		goto err;
	}

	/* Close Dev TTI File */
	ret = close_devtti(tti_t->dev_tti_handle);
	if (ret < 0) {
		printf("Error closing TTI device.\n");
		goto err;
	}
err:
	return ret;
}
