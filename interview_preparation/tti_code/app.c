#define GUL_TTI_MAGIC   'T'

#define IOCTL_GUL_MODEM_TTI_REGISTER	_IOWR(GUL_TTI_MAGIC, 1, struct tti *)
#define IOCTL_GUL_MODEM_TTI_DEREGISTER	_IOWR(GUL_TTI_MAGIC, 2, struct tti *)


#define MAX_TTI_COUNT	2	/* Number of TTI instances */

struct tti {
	uint32_t	efd;
	uint32_t	ttid;
	int32_t	dev_tti_handle;
};

int modem_tti_register(struct tti *tti_t, int modem_id);
int modem_tti_deregister(struct tti *tti_t);
#define GUL_TTI_MAGIC   'T'

#define IOCTL_GUL_MODEM_TTI_REGISTER	_IOWR(GUL_TTI_MAGIC, 1, struct tti *)
#define IOCTL_GUL_MODEM_TTI_DEREGISTER	_IOWR(GUL_TTI_MAGIC, 2, struct tti *)


#define MAX_TTI_COUNT	2	/* Number of TTI instances */

struct tti {
	uint32_t	efd;
	uint32_t	ttid;
	int32_t	dev_tti_handle;
};

int modem_tti_register(struct tti *tti_t, int modem_id);
int modem_tti_deregister(struct tti *tti_t);


#define MODEM_INSTANCE_0	0

/* Every modem can have two TTI IDs */
#define MODEM_TTI_INSTANCE_0	0
#define MODEM_TTI_INSTANCE_1	1

typedef struct tti_stats {
	suseconds_t micro_sec;
	uint32_t tti_id;
} tti_stats_t;

static int modem_id = 0;
static int tti_id = 0;
static int tti_count = 0;


#define MAX_MODEM_INSTANCES	1
#define MAX_TTI_ID		2
#define MAX_COUNT		10
#define	GUL_RFIC_SCHED_PRIORITY	99

void print_usage_message(void) {
	printf("Usage : ./app_name [options] modem_id tti_id tti_count_max\n");
	printf("\n");
	printf("options:\n");
	printf("\tnone\n");
	printf("\n");
	printf("mandatory:\n");
	printf("\tmodem_id         -- decimal |	0..(MAX_MODEM_INSTANCES-1)\n");
	printf("\ttti_id           -- decimal |	0..(MAX_TTI_ID)\n");
	printf("\ttti_count_max	 -- decimal |	0..(MAX_COUNT-1)\n");
	printf("\nSupported MAX Values:\n");
	printf("\nMAX_MODEM_INSTANCES=%d \tMAX_TTI_ID=%d \tMAX_COUNT=%d\n",
				MAX_MODEM_INSTANCES, MAX_TTI_ID, MAX_COUNT);
	fflush(stdout);

	exit(EXIT_SUCCESS);
}

void validate_cli_args(int argc, char *argv[]) {
	if ((strcmp(argv[1], "-h") == 0)  || 
			(strcmp(argv[1], "-H") == 0))
		print_usage_message();

	/* Check Total Argument count */
	if (argc == 4) {		 
		modem_id	= atoi(argv[1]);
		tti_id		= atoi(argv[2]);
		tti_count	= atoi(argv[3]);
	} else {
		print_usage_message();
	}
}

struct sched_param param = { .sched_priority = GUL_RFIC_SCHED_PRIORITY };
int main(int argc, char *argv[])
{
	struct tti tti_t;
	ssize_t bytes_read;
	struct timeval tv;
	uint64_t eftd_ctr;
	int ret = 0;
	int index = 0;
	tti_stats_t *stats_arr;
	/* Validate CLI Args */
	validate_cli_args(argc, argv);
	/* Raise app priority to RT */
	/*sched_setscheduler(current, SCHED_FIFO, &param);*/
	sched_setscheduler(0, SCHED_FIFO, &param);

	/* Register modem=0 and TTI=0 */
	stats_arr = (tti_stats_t *)malloc(tti_count * sizeof(tti_stats_t));
	if (!stats_arr) {
		printf("OOM while allocating stats array...\n");
		goto error;
	}

	/* Register Modem & TTI as per command line params supplied */
	tti_t.ttid = tti_id;
	ret = modem_tti_register(&tti_t, modem_id);
	if(ret < 0) {
		printf("%s failed...\n", __func__);
		goto error;
	}

	for (index = 0; index < tti_count; index++) {
		bytes_read = read(tti_t.dev_tti_handle, &eftd_ctr,
					sizeof(uint64_t));
		if (bytes_read != sizeof(uint64_t)) {
			printf("Read error. Exiting...\n");
			goto error;
		} else {
		/* Extract timestamp in usecs and populate the data structure */
			gettimeofday(&tv, NULL);
			stats_arr[index].micro_sec = tv.tv_usec;
			stats_arr[index].tti_id = tti_t.ttid;
			fflush(stdout);
		}
	}
	for (index = 0; index < tti_count; index++)
		printf("\nTTI_ID=%d \t\t TIMESTAMP=%ld usec\t tti_count=%d\n",
			stats_arr[index].tti_id, stats_arr[index].micro_sec,
			index);
	/* Deregister TTI */
	modem_tti_deregister(&tti_t);
	free(stats_arr);
	exit(EXIT_SUCCESS);
	return 0;

error:
	if(stats_arr) {
		free(stats_arr);
		stats_arr = NULL;
	}
	exit(EXIT_FAILURE);
}
