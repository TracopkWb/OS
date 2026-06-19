#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "../../myLib/logger.h"


int main()
{
    int dataFromFifoFile;

    LOG_INFO("Starting FIFO reader");

    LOG_ACTION("Opening FIFO file");

    int fd = open("myFifo1", O_RDONLY);

    if(fd == -1)
    {
        LOG_ERROR("Could not open FIFO");
        return 1;
    }


    LOG_ACTION("Reading FIFO");

    int readingProcess = read(
        fd,
        &dataFromFifoFile,
        sizeof(dataFromFifoFile)
    );


    if(readingProcess == -1)
    {
        LOG_ERROR("Reading failed");
        perror("read");
        return 1;
    }


    if(readingProcess > 0)
    {
        printf(
            CYAN "[INFO] " RESET
            "Data received: %d\n",
            dataFromFifoFile
        );
    }


    LOG_ACTION("Closing FIFO");

    close(fd);

    LOG_PASS("Reading was successful!");

    return 0;
}