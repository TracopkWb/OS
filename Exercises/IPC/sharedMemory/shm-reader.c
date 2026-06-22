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
#include <sys/shm.h>
#include <sys/msg.h>

#include "../../../myLib/logger.h"


// Shared Memory Reader - 1

// Functions Section

// Global Variables
#define SIZE 5 
// Structure Section

int main()
{
    key_t shmSpaceId;
    int shmId;
    int *array;

    shmSpaceId = ftok(".", 'A');

    if (shmSpaceId == -1)
    {
        perror("shm - ftok()");
        LOG_ERROR("Error while creating the shared memory");
        exit(1);
    }
    
    shmId =  shmget(shmSpaceId,SIZE*sizeof(int),0666);

    if(shmId == -1){
        perror("shmget");
        LOG_ERROR("Error while connecting to the shared memory");
        exit(1);
    }

    array = (int *) shmat(shmSpaceId,NULL,0);

    if(array == (int *) (-1)){
        perror("shmat");
        LOG_ERROR("Error while reading the shared memory");
        exit(1);
    }

    LOG_ACTION("Reading array from the shared memory");

    for (int i = 0; i < SIZE; i++)
    {
        LOG_INFO("%d) %d\n", i, array[i]);
    }
    
    if (shmdt(array) == -1)
    {
        perror("shmdt");
        LOG_ERROR("Error while detach from the memory segment");
    }
    
    LOG_ACTION("Deleting memory shared memory segment");
    shmctl(shmSpaceId,IPC_RMID,NULL);

    return 0;
}