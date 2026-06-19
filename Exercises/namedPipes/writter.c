#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#include "../../myLib/logger.h"


// Activity #3

// Functions Section


int main()
{
    LOG_INFO("Hi Tracopk!\n \
        Let's start working with namedPipes");

    // Creating pipe and checking its existence
    LOG_ACTION("Creating the fifo file");
    if (mkfifo("myFifo1", 0666) == -1)
    {
        if (errno != EEXIST)
        {
            LOG_ERROR("Could not complete mkfifo()");
            return 1;
        }
    }
    else
    {
        LOG_SUCCESS("The fifo file was created");
    }

    // Opening fifo
    LOG_ACTION("Opening fifo");
    int fd = open("myFifo1",O_WRONLY);
    
    LOG_ACTION("Writing in the fifo file");
    int x = 31;

    if(write(fd,&x,sizeof(int)) == -1){

        LOG_ERROR("There has been an error while writing the value");
        return 1;
    }
    LOG_SUCCESS("The process has written the value %d",x);
    LOG_PASS("The process has written the value %d",x);
    LOG_ACTION("Closing the fifo");
    close(fd);
    
    return 0;
}