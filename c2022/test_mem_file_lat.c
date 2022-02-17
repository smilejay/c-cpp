#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define TEST_TIMES 100000

int time_substract(struct timespec *result, struct timespec *begin, struct timespec *end)
{
    if(begin->tv_sec > end->tv_sec)    return -1;
    if((begin->tv_sec == end->tv_sec) && (begin->tv_nsec > end->tv_nsec))    return -2;
    result->tv_sec = (end->tv_sec - begin->tv_sec);
    result->tv_nsec = (end->tv_nsec - begin->tv_nsec);

    if(result->tv_nsec < 0)
    {
        result->tv_sec--;
        result->tv_nsec += 1000000000;
    }
    return 0;
}

void check_mem_file_exist(struct timespec *diff)
{
    struct timespec time_start={0, 0},time_end={0, 0};
    clock_gettime(CLOCK_REALTIME, &time_start);
    access("/var/run/test_mem_file", F_OK);
    clock_gettime(CLOCK_REALTIME, &time_end);
    time_substract(diff, &time_start, &time_end);
    // result.tv_sec = time_end.tv_sec-time_start.tv_sec;
    // result.tv_nsec = time_end.tv_nsec-time_start.tv_nsec;
}

int average(int array[TEST_TIMES])
{
    int i = 0;
    int avg;
    long sum = 0;
    for (i = 0; i < TEST_TIMES; i++)
    {
        sum += array[i];
    }
    avg = sum / TEST_TIMES;
    return avg;
}

int main(int argc, char **argv)
{
    struct timespec results[TEST_TIMES];
    int ns_results[TEST_TIMES];
    int avg_ns;
    int i = 0, j = 0;
    for (i = 0; i < TEST_TIMES; i++)
    {
        check_mem_file_exist(&results[i]);
    }
    for (j = 0; j < TEST_TIMES; j++)
    {
        ns_results[j] = results[j].tv_sec * 1000000000 + results[j].tv_nsec;
        // printf("duration: %lluns\n", ns_results[j]);
    }
    avg_ns = average(ns_results);
    printf("average: %d ns\n", avg_ns);
}