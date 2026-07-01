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

#include "../../myLib/logger.h"

// Shared Memory Writer 1 

// Functions Section

// Global Variables
#define SIZE 5

// Structure Section

// Union Section
union semun {
    int val;                // Value for SETVAL
    struct semid_ds *buf;   // Buffer for IPC_STAT, IPC_SET
    unsigned short *array;  // Array for GETALL, SETALL
};

int main()
{
    key_t key;
    int idMemory, idSemaphore;
    int *array;
    union semun arg;

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

    // Create a semaphore set with 1 semaphore
    idSemaphore = semget(key, 1, IPC_CREAT | 0666);

    if (idSemaphore == -1)
    {
        perror("semget");
        LOG_ERROR("Failed to create semaphore set");
        exit(1);
    }

    // Initialize the semaphore to 1 (unlocked)
    arg.val = 1;

    int r = semctl(idSemaphore, 0, SETVAL, arg);
    if (r == -1)
    {
        perror("semctl");
        LOG_ERROR("Failed to initialize semaphore");
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

    LOG_ACTION("Deleting the shared memory segment");
    //shmctl(key,IPC_RMID,NULL);
    return 0;
}