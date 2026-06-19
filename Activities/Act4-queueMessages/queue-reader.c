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
    long fam_Level;
    char name[MAX_LENGTH];
};

int main()
{
    LOG_INFO("Starting Activity 4 - Queue message reader");
    

    return 0;
}