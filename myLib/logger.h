#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define RED    "\033[1;31m"
#define GREEN  "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE   "\033[1;34m"
#define CYAN   "\033[1;36m"
#define RESET  "\033[0m"


#define LOG_ACTION(fmt, ...)                                      \
do                                                                \
{                                                                 \
    printf(" [%s:%d - %s()] : " BLUE "[ACTION] " fmt RESET "\n",  \
           __FILE__, __LINE__, __func__, ##__VA_ARGS__);          \
    fflush(stdout);                                               \
} while (0)


#define LOG_INFO(fmt, ...)                                        \
do                                                                \
{                                                                 \
    printf(" [%s:%d - %s()] : " CYAN "[INFO] " fmt RESET "\n",    \
           __FILE__, __LINE__, __func__, ##__VA_ARGS__);          \
    fflush(stdout);                                               \
} while (0)


#define LOG_SUCCESS(fmt, ...)                                     \
do                                                                \
{                                                                 \
    printf(" [%s:%d - %s()] : " GREEN "[SUCCESS] " fmt RESET "\n",\
           __FILE__, __LINE__, __func__, ##__VA_ARGS__);          \
    fflush(stdout);                                               \
} while (0)


#define LOG_PASS(fmt, ...)                                        \
do                                                                \
{                                                                 \
    printf(" [%s:%d - %s()] : " GREEN "[PASSED] " fmt RESET "\n", \
           __FILE__, __LINE__, __func__, ##__VA_ARGS__);          \
    fflush(stdout);                                               \
} while (0)


#define LOG_WARNING(fmt, ...)                                      \
do                                                                \
{                                                                 \
    printf(" [%s:%d - %s()] : " YELLOW "[WARNING] " fmt RESET "\n",\
           __FILE__, __LINE__, __func__, ##__VA_ARGS__);          \
    fflush(stdout);                                               \
} while (0)


#define LOG_ERROR(fmt, ...)                                        \
do                                                                \
{                                                                 \
    fprintf(stderr, " [%s:%d - %s()] : " RED "[ERROR] " fmt RESET "\n", \
            __FILE__, __LINE__, __func__, ##__VA_ARGS__);          \
    fflush(stderr);                                                \
} while (0)


#endif