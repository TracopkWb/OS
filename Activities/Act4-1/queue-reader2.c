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
#include <sys/msg.h>

#include "../../myLib/logger.h"

// Activity 4 - Queue Reader 2
// Show the number of consonant nad Uppercase letters in the message queue

// Functions Section
void checkForLowerAndBlankSpaces(char *text);

// Global Variables
#define MAX_LENGTH 100

// Structure Section
struct message
{
    long type;
    char text[MAX_LENGTH];
};

int main()
{
    struct message receivedMessage;
    struct message members[100];
    struct msqid_ds queueInfo;

    LOG_INFO("Starting Activity 4 - Queue message reader 2");

    LOG_ACTION("Creating message queue");
    key_t queueHashKey = ftok(".", 'A');

    LOG_ACTION("Opening message queue");
    int queueId = msgget(
        queueHashKey,
        IPC_CREAT | 0666);

    if (queueId == -1)
    {
        LOG_ERROR("Failed to open message queue");
        exit(EXIT_FAILURE);
    }

    LOG_SUCCESS("Message queue opened with id %d", queueId);

    LOG_ACTION("Getting data from message queue");

    while (1)
    {
        if (msgrcv(queueId,
                   &receivedMessage,
                   sizeof(receivedMessage) - sizeof(long),
                   2,
                   0) == -1)
        {
            LOG_ERROR("msgrcv failed");
            exit(EXIT_FAILURE);
        }

        LOG_INFO("Received: %s, Level: %ld",
                 receivedMessage.text,
                 receivedMessage.type);
    }

    return 0;
}

void checkForLowerAndBlankSpaces(char *text)
{
    int numConsonants = 0;
    int numUppercase = 0;
    ;

    for (int i = 0; text[i] != '\0'; i++)
    {

        if ((text[i] >= 'A' && text[i] <= 'Z'))
        {
            numUppercase++;
        }
        else if (!((text[i] == 'a' || text[i] == 'e' || text[i] == 'i' || text[i] == 'o' || text[i] == 'u')))
        {

            numConsonants++;
        }
    }
    LOG_PASS("Number of consonants: %d", numConsonants);
    LOG_PASS("Number of uppercase letters: %d", numUppercase);
}