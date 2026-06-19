#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("Parent (PID=%d)\n", getpid());

    for (int i = 1; i <= 2; i++)
    {
        pid_t child = fork();

        if (child == 0)
        {
            printf("    Child %d (PID=%d)\n", i, getpid());

            for (int j = 1; j <= 2; j++)
            {
                pid_t grandchild = fork();

                if (grandchild == 0)
                {
                    printf("        Grandchild %d (PID=%d)\n",
                           j, getpid());

                    sleep(30);
                    return 0;
                }
            }

            // wait for grandchildren
            for (int j = 0; j < 2; j++)
            {
                wait(NULL);
            }

            sleep(30);
            return 0;
        }
    }

    // wait for children
    for (int i = 0; i < 2; i++)
    {
        wait(NULL);
    }

    return 0;
}