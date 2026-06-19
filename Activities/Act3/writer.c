#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#include "../../myLib/logger.h"

// Activity 3 Finding perfect numbers

int main()
{
    LOG_INFO("Starting Activity 3");

    /*
        Parent -> Child FIFO
    */

    LOG_ACTION("Creating input pipe");

    char *pipe2Child = "toChild";

    if (mkfifo(pipe2Child, 0666) == -1)
    {
        if (errno != EEXIST)
        {
            LOG_ERROR("Could not complete mkfifo()");
            return 1;
        }
    }
    else
    {
        LOG_SUCCESS("The pipe %s was created", pipe2Child);
    }

    LOG_ACTION("Getting number from user");

    int number2Send;

    scanf("%d", &number2Send);

    LOG_ACTION("Opening pipe to child");

    int process2Child = open(
        pipe2Child,
        O_WRONLY);

    if (process2Child == -1)
    {
        LOG_ERROR("Could not open pipe");
        return 1;
    }

    LOG_ACTION("Writing to pipe");

    if (write(
            process2Child,
            &number2Send,
            sizeof(number2Send)) == -1)
    {
        LOG_ERROR(
            "Error while writing value %d",
            number2Send);

        close(process2Child);
        return 1;
    }

    close(process2Child);

    LOG_SUCCESS(
        "Sent value %d to child",
        number2Send);

    /*
        Child -> Parent FIFO
    */

    LOG_ACTION("Opening response pipe");

    char *pipeFromChild = "toWriter";

    int processFromChild = open(
        pipeFromChild,
        O_RDONLY);

    if (processFromChild == -1)
    {
        LOG_ERROR("Could not open response pipe");
        return 1;
    }

    LOG_ACTION("Reading result");

    int divisorResult;

    if (read(
            processFromChild,
            &divisorResult,
            sizeof(divisorResult)) == -1)
    {
        LOG_ERROR("Could not read response");
        close(processFromChild);
        return 1;
    }

    close(processFromChild);

    LOG_SUCCESS(
        "Received divisor sum: %d",
        divisorResult);

    if (divisorResult == number2Send)
    {
        LOG_PASS(
            "The number %d is a perfect number",
            number2Send);
    }
    else
    {
        LOG_INFO(
            "The number %d is not a perfect number",
            number2Send);
    }

    return 0;
}