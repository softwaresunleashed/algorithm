#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// struct for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message;

#define FTOK_PATH_FILENAME	"progfile"	// could be anything
#define FTOK_UNIQUE_ID		65		// could be anything

int main()
{
	key_t key;
	int msgid;

	// ftok to generate unique key
	key = ftok(FTOK_PATH_FILENAME, FTOK_UNIQUE_ID);

	// msgget() creates a message queue
	// and returns identifier
	msgid = msgget(key, IPC_CREAT | 0666);
	message.mesg_type = 1;		// set the message type to categorize the message
	printf("Write Data to send : ");
	gets(message.mesg_text);

	// msgsnd() to send message
	msgsnd(msgid, &message, sizeof(message), 0);

	// display the message
	printf("Data send is : %s \n", message.mesg_text);

	return 0;

}




