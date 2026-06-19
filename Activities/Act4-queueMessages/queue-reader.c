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

// Activity 4 - Queue messages

// Functions Section

// Global Variables
#define MAX_LENGTH 100

// Structure Section
struct familyMember
{
    long fam_Level;
    char name[MAX_LENGTH];
};

int main()
{
    struct familyMember receivedMember;
    struct familyMember members[100];
    struct msqid_ds queueInfo;

    LOG_INFO("Starting Activity 4 - Queue message reader");

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

    errno = 0;

    while (1)
    {
        if (msgrcv(queueId, &receivedMember, sizeof(receivedMember) - sizeof(long), 0, IPC_NOWAIT) == -1)
        {
            LOG_ERROR("Failed to receive message");
            exit(EXIT_FAILURE);
        }
        LOG_INFO("Received family member: %s, Level: %ld \n",
                 receivedMember.name,
                 receivedMember.fam_Level);
        }
    }

    if (errno != ENOMSG)
    {
        LOG_ERROR("msgrcv failed");
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Received %d messages from the queue", numberOfMembers);

    for (int j = 0; j < numberOfMembers; j++)
    {
        LOG_INFO("Family member: %s, Level: %ld",
                 members[j].name,
                 members[j].fam_Level);
    }

    return 0;
}