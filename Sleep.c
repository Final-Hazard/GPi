#include "Sleep.h"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

//this value is in microseconds and was determined from profiling the running application
const int MIN_SLEEP_TIME = 95;
//Counting zeroes is hard..
const int ONE_MILLION = 1000 * 1000;
//set this to keep performance statistics
const int MONITOR_PERFORMANCE = 1;
const char *SLEEP_PERFORMANCE = "SleepPerformance.txt";
FILE *sleep_file = NULL;

//need to do more actual program profiling to determine the sleep timing
void Sleep(int micros)
{
  if(micros < MIN_SLEEP_TIME)
  {
    fprintf(stderr, "Invalid sleep time of %d requested, %d is minimum sleep time\n", micros, MIN_SLEEP_TIME);
    exit(-5);
  }
  micros -= MIN_SLEEP_TIME;
  struct timespec sleepTime, errorTime, pTime;
  //if there are more than 1,000,000 micros convert them to seconds
  sleepTime.tv_sec = micros / (ONE_MILLION);
  //1000 is number of nanoseconds per microsecond
  sleepTime.tv_nsec = (micros - sleepTime.tv_sec * (ONE_MILLION)) / 1000;
  if(MONITOR_PERFORMANCE)
  {
    if(clock_gettime(CLOCK_MONOTONIC, &pTime))
    {
      fprintf(stderr, "Error of %d returned by clock_gettime (%s)\n", errno, strerror(errno));
    }
  }
  if(nanosleep(&sleepTime, &errorTime))
  {
    fprintf(stderr, "Error of %d returned by nanosleep (%s)\n", errno, strerror(errno));
    int newSleep = errorTime.tv_sec * ONE_MILLION + errorTime.tv_nsec / 1000;
    if(newSleep >= MIN_SLEEP_TIME)
      sleep(newSleep);
  }
  if(MONITOR_PERFORMANCE)
  {
    unsigned long long actual = 0;
    struct timespec endTime;
    if(clock_gettime(CLOCK_MONOTONIC, &endTime))
    {
      fprintf(stderr, "Error of %d returned by clock_gettime (%s)\n", errno, strerror(errno));  
    }
    actual = (endTime.tv_sec - pTime.tv_sec) * ONE_MILLION;
    actual += endTime.tv_nsec - pTime.tv_nsec;
    actual /= 1000;
    
    if(sleep_file == NULL)
      sleep_file = fopen(SLEEP_PERFORMANCE, "a");
    fprintf(sleep_file, "%d %llu\n", micros + MIN_SLEEP_TIME, actual);
  }
  return;
}
