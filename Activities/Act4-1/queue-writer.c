//Standard C
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

//File System & Permissions
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> // FIFO pipes

// System V IPC 
#include <sys/ipc.h>
#include <sys/msg.h>

#include "../../myLib/logger.h"


// Activity 4 - Queue messages

// Functions Section

// Global Variables
#define MAX_LENGTH 100

// Structure Section
struct message{
    long type;
    char text[MAX_LENGTH];
};
 
int main()
{
    LOG_INFO("Starting Activity 4 - Queue message writer");
    
    int queueId;
    struct message msg2Send;
    
    LOG_ACTION("Creating message queue");
    key_t queueHashKey = ftok(".", 'A');

    LOG_ACTION("Opening message queue");
    queueId = msgget(
        queueHashKey,
        IPC_CREAT | 0666
    );

    if (queueId == -1)
    {
        LOG_ERROR("Failed to open message queue");
        exit(EXIT_FAILURE);
    }

    LOG_SUCCESS("Message queue opened with id %d", queueId);

    LOG_ACTION("Getting data from user");

    while (1)
    {
        printf("\tEnter Text: \n");
        scanf("%s", msg2Send.text);
        printf("\tEnter message type: \n");
        scanf("%ld", &msg2Send.type);
        if(msgsnd(queueId, &msg2Send, sizeof(msg2Send) - sizeof(long), 0) == -1)
        {
            LOG_ERROR("Failed to send message");
            exit(EXIT_FAILURE);
        }
        LOG_SUCCESS("Sent: %s, Level: %ld", msg2Send.text, msg2Send.type);
    }
    
    return 0;
}