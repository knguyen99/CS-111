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
#include "SortedList.h"
#include <string.h>

int numThreads = 1;
int numIterations = 1;
pthread_mutex_t pmutex;
int slock = 0;
SortedList_t* list;
SortedListElement_t* elements;
int opt_yield = 0;
int yArg = 0;
char sOpt = 'n';
int numElements;




void* function(void* arg){
	int tid = *(int*)arg;
	for(int i = tid; i < numElements; i += numThreads)
	{
		switch(sOpt)
		{
			case 'm':
			{
				pthread_mutex_lock(&pmutex);
				SortedList_insert(list, &elements[i]);
				pthread_mutex_unlock(&pmutex);
				break;
			}
			case 's':
			{
				while(__sync_lock_test_and_set(&slock,1));
                                SortedList_insert(list, &elements[i]);
        			__sync_lock_release(&slock);
				break;
			}
			default:
				SortedList_insert(list, &elements[i]);
				break;
		}
	}
	switch(sOpt)
	{
		case 'm':
			pthread_mutex_lock(&pmutex);
                        if(SortedList_length(list) == -1)
                        {
                                fprintf(stderr, "Error in list length\n");
                                exit(1);
                        }
                        pthread_mutex_unlock(&pmutex);
			break;
		case 's':
                       	while(__sync_lock_test_and_set(&slock,1));
                       	if(SortedList_length(list) == -1)
                       	{
                               	fprintf(stderr, "Error in list length\n");
                               	exit(1);
                        }
                        __sync_lock_release(&slock);
			break;
		default:
			if(SortedList_length(list) == -1)
			{
				fprintf(stderr, "Error in list length\n");
				exit(1);
			}
			break;
	}
	for(int i = tid; i < numElements; i += numThreads)
	{
		SortedListElement_t* e;
		switch(sOpt)
		{
		case 'm':
			pthread_mutex_lock(&pmutex);
                         e = SortedList_lookup(list,elements[i].key);
                        if(e == NULL)
                        {
                                fprintf(stderr, "Error in lookup\n");
                                exit(1);
                        }
                        if(SortedList_delete(e))
                        {
                                fprintf(stderr, "Error in delete\n");
                                exit(1);
                        }
			pthread_mutex_unlock(&pmutex);
                        break;
		case's':
			while(__sync_lock_test_and_set(&slock,1));
                        e = SortedList_lookup(list,elements[i].key);
                        if(e == NULL)
                        {
                                fprintf(stderr, "Error in lookup\n");
                                exit(1);
                        }
                        if(SortedList_delete(e))
                        {
                                fprintf(stderr, "Error in delete\n");
                                exit(1);
                        }
			__sync_lock_release(&slock);
                        break;
		default:
			 e = SortedList_lookup(list,elements[i].key);
			if(e == NULL)
			{
				fprintf(stderr, "Error in lookup\n");
				exit(1);
			}	
			if(SortedList_delete(e))
			{
				fprintf(stderr, "Error in delete\n");
				exit(1);
			}
			break;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	struct timespec start;
	struct timespec end;
	char* testName = "list-";
	char* yieldName = "none-";
	char* syncName = "none";
	static struct option long_options[] = {
		{"threads", required_argument, NULL, 't'},
		{"iterations", required_argument, NULL, 'i'},
		{"yield", required_argument, NULL, 'y'},
		{"sync", required_argument,NULL,'s'}
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
					for(size_t k = 0; k < strlen(optarg); k++)
					{
						switch(optarg[k])
						{
							case 'i':
							{
								opt_yield |= INSERT_YIELD;
								yArg += 1;
								break;
							}
                                                        case 'd':
                                                        {
								opt_yield |= DELETE_YIELD;
								yArg += 2;
								break;
                                                        }
                                                        case 'l':
                                                        {
								opt_yield |= LOOKUP_YIELD;
								yArg += 4;
								break;
                                                        }
							default:
							{
								fprintf(stderr, "Invalid option for yield");
								exit(1);
							}
						}
					}
					break;
				}
			case 's':
			{
				sOpt = *optarg;
				switch(*optarg)
				{
					case 'm':pthread_mutex_init(&pmutex,NULL);break;
					case 's':break;
					default: fprintf(stderr, "Invalid sync option");
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
	list = malloc(sizeof(SortedList_t));
	list->prev = list;
	list->next = list;
	list->key = NULL;
	
	numElements = numThreads * numIterations;
	elements = malloc(sizeof(SortedListElement_t)*numElements);
	
	srand(time(NULL));
	for(int l = 0; l < numElements; l++)
	{
		char* key = malloc(sizeof(char)*5);
		for(int q = 0; q < 4; q++)
		{
			key[q] = (char)((rand()%27)+39);
		}
		key[4] = '\0';
		elements[l].key = key;
	}
        pthread_t threads[numThreads];
	int tids[numThreads];
        if((clock_gettime(CLOCK_MONOTONIC,&start)) == -1)
        {
                fprintf(stderr, "Error in starting time\n");
                exit(1);
        }

        int i = 0;
        for(; i < numThreads; i++)
        {
		tids[i] = i;
        	if(pthread_create(&threads[i],NULL, function, &tids[i]) != 0)
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
	if(SortedList_length(list) != 0)
	{
		fprintf(stderr, "Error in list length = 0 \n");
		exit(1);
	}
		
	if((clock_gettime(CLOCK_MONOTONIC, &end)) == -1)
	{
		fprintf(stderr, "Error in ending time\n");
		exit(1);
	}
	free(elements);

	int numLists = 1;
	switch(yArg)
	{
		case 1: yieldName = "i-"; break;
		case 2: yieldName = "d-"; break;
		case 3: yieldName = "id-"; break;
		case 4: yieldName = "l-"; break;
		case 5: yieldName = "il-"; break;
		case 6: yieldName = "dl-"; break;
		case 7: yieldName = "idl-"; break;
		default: yieldName = "none-"; break;
	}
	if(sOpt == 'n')
		syncName = "none";
	else if(sOpt == 'm')
		syncName = "m";
	else
		syncName = "s";
	int operations = numThreads * numIterations * 3;
	long totalTime = ((end.tv_sec - start.tv_sec)*1000000000) + (end.tv_nsec - start.tv_nsec);
	long avgTime = (totalTime/operations);
	printf("%s%s%s,%i,%i,%i,%i,%li,%li\n", testName, yieldName,syncName,numThreads, numIterations, numLists,operations, totalTime, avgTime);
	exit(0);
}
