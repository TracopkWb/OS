#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// #TITLE#

// Functions Section

// Global Variables

// Structure Section

int main()
{
    // Starts the process (parent)
    int itsID = getpid();
    printf("I am the parent, PID = %d\n", itsID);

    int numberOfChildren = 0;
    // Creation of the children
    for (int i = 0; i < 3; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            printf("I am child %d, PID = %d\n", i + 1, getpid());
            return 0;
        }
        else if (pid > 0)
        {
            numberOfChildren++;
        }
    }

    //Waiting for all the children
    for (int i = 0; i < 3; i++)
    {
        wait(NULL);
    }

    printf("The parent with id %d, has %d children\n",itsID, numberOfChildren);
    return 0;
}