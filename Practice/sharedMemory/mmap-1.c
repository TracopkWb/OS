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
#include <sys/mman.h>

#include "../../myLib/logger.h"

// Using mmap() to start sharing memory

// Functions Section

// Global Variables
#define SIZE 5

// Structure Section

int main()
{
    LOG_INFO("Starting to work with MMAP()");
    int *mapPtr = mmap(
        NULL,
        SIZE*sizeof(int),
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        0,
        0
    );

    if (mapPtr == MAP_FAILED){
        LOG_ERROR("Memory mapping failed with error: %d",errno);
        return 1;
    }

    LOG_ACTION("Writing data on the mapped memory");
    for(int i = 0; i < SIZE; i++)
        mapPtr[i] = i*10;

    LOG_ACTION("Reading data from the mapped memory");
    for(int i = 0; i < SIZE; i ++)
        LOG_INFO("[%d]",mapPtr[i]);

    LOG_ACTION("Unmapping memory");
    int err = munmap(mapPtr,SIZE*sizeof(int));
    if (err != 0)
    {
        LOG_ERROR("Unmapping failed with error %d",errno);
        return 1;
    }
    LOG_SUCCESS("Mapping memory was successful!");
    return 0;
}