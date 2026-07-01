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

// Shared Memory Reader - 1

// Functions Section

// Global Variables
#define SIZE 5
#define REP 100000
// Structure Section

int main()
{
    key_t hashId;
    int shmId, semId;
    int *array;
    struct sembuf operation;

    hashId = ftok(".", 'A');

    if (hashId == -1)
    {
        perror("shm - ftok()");
        LOG_ERROR("Error while creating the shared memory");
        exit(1);
    }

    shmId = shmget(hashId, SIZE * sizeof(int), 0666);

    if (shmId == -1)
    {
        perror("shmget");
        LOG_ERROR("Error while connecting to the shared memory");
        exit(1);
    }

    // Connect to the semaphore set
    semId = semget(hashId, 1, 0666);
    if (semId == -1)
    {
        perror("semget");
        LOG_ERROR("Error while connecting to the semaphore set");
        exit(1);
    }


    array = (int *)shmat(shmId, NULL, 0);

    if (array == (int *)(-1))
    {
        perror("shmat");
        LOG_ERROR("Error while reading the shared memory");
        exit(1);
    }

    LOG_ACTION("Reading array from the shared memory");

    // Set up the semaphore operation to wait (decrement)

    for (int r = 0; r<REP;r++)
    {
        operation.sem_num = 0; // Semaphore index
        operation.sem_op = -1; // Wait (decrement)
        operation.sem_flg = 0;  // No special flags
        semop(semId, &operation, 1); // Perform the operation

        for (int i = 0; i < SIZE; i++)
        {
            array[i] =+ 1;
            LOG_INFO("%d) %d\n", i, array[i]);
        }

        operation.sem_op = 1; // Signal (increment)
        semop(semId, &operation, 1); // Perform the operation
        
    }

    if (shmdt(array) == -1)
    {
        perror("shmdt");
        LOG_ERROR("Error while detach from the memory segment");
    }

    LOG_ACTION("Deleting memory shared memory segment");
    // shmctl(shmId,IPC_RMID,NULL);

    return 0;
}