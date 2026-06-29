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

// Functions 

void getSmallestElement(int*array);
int getSumOfElements(int*array);

// Global Variables
#define SIZE 5
#define REP 100000
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

    getSmallestElement(array);
    getSumOfElements(array);


    if (shmdt(array) == -1)
    {
        perror("shmdt");
        LOG_ERROR("Error while detach from the memory segment");
    }

    LOG_ACTION("Deleting memory shared memory segment");
    // shmctl(shmSegment,IPC_RMID,NULL);

    return 0;
}


void getSmallestElement(int*array){

    LOG_INFO("Finding biggest Element");
    int biggestTemp = array[0];

    for (int i = 1; i < SIZE - 1; i++)
    {
        LOG_INFO("%d) %d\n", i, array[i]);
        if(biggestTemp < array[i]){
            LOG_INFO("New biggest number %d",array[i]);
            biggestTemp = array[i];
        }

        LOG_INFO("Biggest number in the array is: %d",biggestTemp);
    }
}

int getSumOfElements(int*array){
    LOG_INFO("Adding all Elements");
    int sumOfElements = 0;

    for (int i = 0; i < SIZE; i++)
    {
        sumOfElements = sumOfElements + array[0]; 
        
    }
    LOG_INFO("Biggest number in the array is: %d",sumOfElements);
}