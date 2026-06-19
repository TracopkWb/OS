#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#include "../../myLib/logger.h"

// Functions Section
int calculateDivisor(int checkNumber);

int main()
{
    LOG_INFO("Starting FIFO Reader");

    /*
        FIFO from writer -> reader
    */

    char *pipeFromWriter = "toChild";

    LOG_ACTION("Creating input FIFO");

    if (mkfifo(pipeFromWriter, 0666) == -1)
    {
        if (errno != EEXIST)
        {
            LOG_ERROR("Could not create input FIFO");
            return 1;
        }
    }

    LOG_ACTION("Opening input FIFO");

    int processFromWriter = open(pipeFromWriter, O_RDONLY);

    if (processFromWriter == -1)
    {
        LOG_ERROR("Could not open FIFO");
        return 1;
    }

    LOG_ACTION("Reading FIFO");

    int numberSendFromWriter;

    int readingProcess = read(
        processFromWriter,
        &numberSendFromWriter,
        sizeof(numberSendFromWriter));

    if (readingProcess == -1)
    {
        LOG_ERROR("Reading FIFO failed");
        close(processFromWriter);
        return 1;
    }

    LOG_PASS("Read data %d from FIFO", numberSendFromWriter);

    LOG_ACTION("Closing input FIFO");

    close(processFromWriter);

    /*
        Calculate
    */

    LOG_ACTION("Checking if the number is a perfect number");

    int divisorSum = calculateDivisor(numberSendFromWriter);

    LOG_SUCCESS(
        "Calculation completed. Divisor sum is %d",
        divisorSum);

    /*
        FIFO from reader -> writer
    */

    char *pipeToWriter = "toWriter";

    LOG_ACTION("Creating response FIFO");

    if (mkfifo(pipeToWriter, 0666) == -1)
    {
        if (errno != EEXIST)
        {
            LOG_ERROR("Could not create response FIFO");
            return 1;
        }
    }
    else
    {
        LOG_SUCCESS("The pipe %s was created", pipeToWriter);
    }

    LOG_ACTION("Opening response FIFO");

    int processToWriter = open(pipeToWriter, O_WRONLY);

    if (processToWriter == -1)
    {
        LOG_ERROR("Could not open response FIFO");
        return 1;
    }

    LOG_ACTION("Writing result to FIFO");

    if (write(
            processToWriter,
            &divisorSum,
            sizeof(divisorSum)) == -1)
    {
        LOG_ERROR(
            "Error while writing value %d",
            divisorSum);

        close(processToWriter);
        return 1;
    }

    close(processToWriter);

    LOG_SUCCESS(
        "The process has written the value %d in the pipe",
        divisorSum);

    LOG_PASS("The program has sent divisors");

    return 0;
}

int calculateDivisor(int checkNumber)
{
    int divisorSum = 0;

    for (int i = 1; i < checkNumber; i++)
    {
        if (checkNumber % i == 0)
        {
            divisorSum += i;
        }
    }

    return divisorSum;
}