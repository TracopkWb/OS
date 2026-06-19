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
    for (int i = 0; i < 2; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {

            printf("I am child %d, PID = %d my parent id: %d\n", i + 1, getpid(), itsID);
            for (int j = 1; j <= 2; j++)
            {
                pid_t grandChildrenId = fork();

                if (grandChildrenId == 0)
                {
                    printf("I am grandChildren %d, PID = %d\n", j + 1, getpid());
                    return 0;
                }
            }

            return 0;
        }
    }
    return 0;
}