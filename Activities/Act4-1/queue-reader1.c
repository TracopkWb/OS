// Standard C
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

// File System & Permissions
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> // FIFO pipes

// System V IPC
#include <sys/ipc.h>
#include <sys/msg.h>

#include "../../myLib/logger.h"

// Activity 4 - Queue Reader 1
// Show the messages in the message queue

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
    struct message receivedMessage;
    struct message members[100];
    struct msqid_ds queueInfo;

    LOG_INFO("Starting Activity 4 - Queue message reader 1");

    LOG_ACTION("Creating message queue");
    key_t queueHashKey = ftok(".", 'A');

    LOG_ACTION("Opening message queue");
    int queueId = msgget(
        queueHashKey,
        IPC_CREAT | 0666);

    if (queueId == -1)
    {
        LOG_ERROR("Failed to open message queue");
        exit(EXIT_FAILURE);
    }

    LOG_SUCCESS("Message queue opened with id %d", queueId);

    LOG_ACTION("Getting data from message queue");

    while (1)
    {
        if (msgrcv(queueId,
           &receivedMessage,
           sizeof(receivedMessage) - sizeof(long),
           2,
           0) == -1)
        {
            LOG_ERROR("msgrcv failed");
            exit(EXIT_FAILURE);
        }

        LOG_INFO("Received: %s, Level: %ld",
                 receivedMessage.text,
                 receivedMessage.type);
    }

    return 0;
}