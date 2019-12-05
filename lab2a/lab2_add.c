//Khoi Nguyen
//knguyen99@g.ucla.edu
//804993073
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <pthread.h>
#include <sched.h>

int numThreads = 1;
int numIterations = 1;
long long counter = 0;
pthread_mutex_t pmutex;
char sOpt = 'a';
int slock = 0;

int opt_yield;

void add(long long *pointer, long long value) {
	long long sum = *pointer + value;
	if (opt_yield)
		sched_yield();
	*pointer = sum;
}

void mutexAdd(long long *pointer,long long value){
	pthread_mutex_lock(&pmutex);
        long long sum = *pointer + value;
        if (opt_yield)
                sched_yield();
        *pointer = sum;
	pthread_mutex_unlock(&pmutex);
}

void spinAdd(long long *pointer,long long value){
	while(__sync_lock_test_and_set(&slock,1));
        long long sum = *pointer + value;
        if (opt_yield)
                sched_yield();
        *pointer = sum;
	__sync_lock_release(&slock);
}

void compAdd(long long value){
	long long old;
	long long new;
	do{
		old = counter;
		new = old + value;
		if(opt_yield)
			sched_yield();
	}while(__sync_val_compare_and_swap(&counter,old,new) != old);
}

void* function(){
	int i =0;
	for (; i < numIterations; i++)
	{
		switch(sOpt)
		{
			case 'a':
				{
					add(&counter,1);
					break;
				}
			case 'm':
				{
					mutexAdd(&counter,1);
					break;
				}
			case 's':
                                {
					spinAdd(&counter,1);
                                        break;
                                }
			case 'c':
                                {
					compAdd(1);
                                        break;
                                }
		}
	}
	for(; i>0; i--)
	{
                switch(sOpt)
                {
                        case 'a':
                                {
                                        add(&counter,-1);
                                        break;
                                }
                        case 'm':
                                {
                                        mutexAdd(&counter,-1);
                                        break;
                                }
                        case 's':
                                {
                                        spinAdd(&counter,-1);
                                        break;
                                }
                        case 'c':
                                {
                                        compAdd(-1);
                                        break;
                                }
                }
	}
	return 0;
}

int main(int argc, char* argv[])
{
	struct timespec start;
	struct timespec end;
	char* testName = "add-none";

	static struct option long_options[] = {
		{"threads", required_argument, NULL, 't'},
		{"iterations", required_argument, NULL, 'i'},
		{"yield", no_argument, NULL, 'y'},
		{"sync", required_argument, NULL, 's'}
	};
	int option_index = 0;
	int r;
	opterr = 0;
	while((r = getopt_long(argc, argv, "", long_options, &option_index)) != -1)
	{
		switch(r)
		{
			case 't':
				{
					int threads = atoi(optarg);
					if(threads > 1)
						numThreads = threads;
					break;
				}
			case 'i':
				{
					int iter = atoi(optarg);
					if(iter > 1)
						numIterations = iter;
					break;
				}
			case 'y':
				{
					opt_yield = 1;
					if(sOpt == 'a')
					{
						testName = "add-yield-none";
					}
					break;
				}
			case 's':
				{
					sOpt = *optarg;
					switch(*optarg)
					{
						case 'm':
							{
								if(opt_yield)
									testName = "add-yield-m";
								else
									testName = "add-m";
								break;
							}
						case 's':
                                                        {
                                                                if(opt_yield)
                                                                        testName = "add-yield-s";
                                                                else
                                                                        testName = "add-s";
                                                                break;
                                                        }
						case 'c':
                                                        {
                                                                if(opt_yield)
                                                                        testName = "add-yield-c";
                                                                else
                                                                        testName = "add-c";
                                                                break;
                                                        }
					}
					break;
				}
			default:
				{
					fprintf(stderr, "Invalid option\n");
					exit(1);
				}
		}
	}
        pthread_t threads[numThreads];
        if((clock_gettime(CLOCK_MONOTONIC,&start)) == -1)
        {
                fprintf(stderr, "Error in starting time\n");
                exit(1);
        }
        int i = 0;
        for(; i < numThreads; i++)
        {
        	if(pthread_create(&threads[i],NULL, function, NULL) != 0)
		{
			fprintf(stderr, "Error in creating thread\n");
			exit(1);
		}
        }
	int j = 0;
	for(; j < numThreads; j++)
	{
		if(pthread_join(threads[j],NULL) != 0)
		{
			fprintf(stderr, "Error in joining threads\n");
			exit(0);
		}
	}
		
	if((clock_gettime(CLOCK_MONOTONIC, &end)) == -1)
	{
		fprintf(stderr, "Error in ending time\n");
		exit(1);
	}
	
	int operations = numThreads * numIterations * 2;
	long totalTime = ((end.tv_sec - start.tv_sec)*1000000000) + (end.tv_nsec - start.tv_nsec);
	long avgTime = totalTime/operations;
	printf("%s,%i,%i,%i,%li,%li,%lli\n", testName, numThreads, numIterations, operations, totalTime, avgTime,counter);
	exit(0);
}
