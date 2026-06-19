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
struct familyMember{
    long msgType;
    char name[MAX_LENGTH];
    int fam_Level;
};

int main()
{
    LOG_INFO("Starting Activity 4 - Queue message writer");
    
    int running = 1;
    int queueId;
    struct familyMember member2Send;
    
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

    while (running)
    {
        printf("\tEnter family member name: \n");
        scanf("%s", member2Send.name);
        printf("\tEnter family level: \n");
        scanf("%d", &member2Send.fam_Level);
        member2Send.msgType = member2Send.fam_Level; // Set the message type
        if(msgsnd(queueId, &member2Send, sizeof(member2Send) - sizeof(long), 0) == -1)
        {
            LOG_ERROR("Failed to send message");
            exit(EXIT_FAILURE);
        }
    }
    
    return 0;
}