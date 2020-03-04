#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// struct for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message;

#define FTOK_PATH_FILENAME	"progfile"	// could be anything but same as writer
#define FTOK_UNIQUE_ID		65		// could be anything but same as writer

int main()
{
	key_t key;
	int msgid;

	// ftok to generate unique key
	key = ftok(FTOK_PATH_FILENAME, FTOK_UNIQUE_ID);

	// msgget() creates a message queue
	// and returns identifier
	msgid = msgget(key, IPC_CREAT | 0666);

	// msgrcv to receive message
	msgrcv(msgid, &message, sizeof(message), 1, 0);

	// display the message
	printf("Data Received is : %s \n", message.mesg_text);
	
	// to destroy the message queue
	msgctl(msgid, IPC_RMID, NULL);


	return 0;

}




