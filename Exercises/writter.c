#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>


// #TITLE#

// Functions Section

// Global Variables

// Structure Section

int main()
{
    printf("Hi Tracopk! Let's start working with named Pipes\n");

    // Creating pipe and checking its existence

    if (mkfifo("myFifo1", 0666) == -1)
    {
        if (errno != EEXIST)
        {
            perror("mkfifo");
            return 1;
        }
    }
    else
    {
        printf("FIFO created successfully\n");
    }

    // Opening fifo
    printf("<ACTION> - Opening fifo\n");
    int fd = open("myFifo1",O_WRONLY);
    
    printf("<ACTION> - Writing in the fifo\n");
    int x = 30;

    if(write(fd,&x,sizeof(int)) == -1){
        printf("<ERROR> - There has been an error while writing the value %d",x);
        return 2;
    }
    printf("<PASSED> - The process has written the value %d\n",x);
    printf("<ACTION> - Closing the fifo\n");

    close(fd);
    
    return 0;
}