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
void swap(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {

        // Last i elements are already in place, so the loop will only num n - i - 1 times
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr, j, j + 1);
        }
    }
}

// Global Variables
#define SIZE 5
// Structure Section

int main()
{
    key_t hashKey;
    int shmSegment;
    int *array;

    hashKey = ftok(".", 'A');

    if (hashKey == -1)
    {
        perror("shm - ftok()");
        LOG_ERROR("Error while creating the shared memory");
        exit(1);
    }

    shmSegment = shmget(hashKey, SIZE * sizeof(int), 0666);

    if (shmSegment == -1)
    {
        perror("shmget");
        LOG_ERROR("Error while connecting to the shared memory");
        exit(1);
    }

    array = (int *)shmat(shmSegment, NULL, 0);

    if (array == (int *)(-1))
    {
        perror("shmat");
        LOG_ERROR("Error while reading the shared memory");
        exit(1);
    }

    LOG_ACTION("Reading array from the shared memory");

    for (int i = 0; i < SIZE; i++)
    {
        LOG_INFO("%d) %d\n", i, array[i]);
    }

    bubbleSort(arr, SIZE);

    if (shmdt(array) == -1)
    {
        perror("shmdt");
        LOG_ERROR("Error while detach from the memory segment");
    }

    LOG_ACTION("Deleting memory shared memory segment");
    // shmctl(shmSegment,IPC_RMID,NULL);

    return 0;
}
