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

// Shared Memory Writer 1 

// Functions Section

// Global Variables
#define SIZE 5

// Structure Section

int main()
{
    key_t key;
    int idMemory;
    int *array;

    key = ftok(".", 'A');
    
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    idMemory = shmget(key, 1024, IPC_CREAT | 0666);

    if (idMemory == -1)
    {
        perror("shmget");
        LOG_ERROR("Failed to create shared memory segment");
        exit(1);
    }

    array = (int *)shmat(idMemory, NULL, 0);

    if (array == (int *)(-1))
    {
        perror("shmat");
        LOG_ERROR("Failed to attach shared memory segment");
        exit(1);
    }

    LOG_SUCCESS("Shared memory segment created and attached successfully");

    LOG_ACTION("Submit the array of integers to the shared memory segment");

    for (int i = 0; i < SIZE; i++)
    {
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &array[i]);
    }

    LOG_INFO("Array of integers submitted to shared memory segment");

    shmdt(array);

    //LOG_ACTION("Deleting the shared memory segment");
    //shmctl(key,IPC_RMID,NULL);
    return 0;
}