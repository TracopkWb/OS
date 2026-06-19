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
// #TITLE#

// Functions Section

// Global Variables
#define MAX_LENGTH 100

// Structure Section
struct package{
    long package_flag;
    char package_data[MAX_LENGTH];
};

int main()
{
    LOG_INFO("Starting Activity 4 - Queue message writer");
    
    int running = 1;
    int packageId;
    struct package packageToSend;
    
    LOG_ACTION("Creating message queue");
    key_t queueHashKey = ftok(".", 'A');

    LOG_ACTION("Opening message queue");
    packageId = msgget(
        queueHashKey,
        IPC_CREAT | 0666
    );

    if (packageId == -1)
    {
        LOG_ERROR("Failed to open message queue");
        exit(EXIT_FAILURE);
    }

    LOG_SUCCESS("Message queue opened with id %d", packageId);

    LOG_ACTION("Getting data from user");

    while (running)
    {
        printf("\tEnter text to send: \n");
        scanf("%s", packageToSend.package_data);
        printf("\tSet priority: \n");
        scanf("%ld", &packageToSend.package_flag);
        if(msgsnd(packageId, &packageToSend, sizeof(struct package) - sizeof(long), 0) == -1)
        {
            LOG_ERROR("Failed to send message");
            exit(EXIT_FAILURE);
        }
    }
    

    

    return 0;
}