//Khoi Nguyen
//knguyen99.g.ucla.edu
//804993073

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <mraa.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

int exitCode = 0;
int fd = -1;
int run = 1;
int on = 1;
mraa_aio_context tempSensor;
mraa_gpio_context button;
char scale = 'F';
struct timeval time;

char buffer[256];

float temperature()
{
	//value of the thermistor
	const int b = 4275 

	int a = mraa_aio_read(tempSensor);
	float R = 1023.0/a - 1.0;
	R = 100000*R;
	float temp = 1.0/(log(R/100000)/b+1/298.15)-273.15;
	if(scale == 'F')
		return temp * 9/5+32
	return temp;
}

int runCommand(char* com)
{
	fprintf(stdout,com);
	if(com == "START")
		run = 1;
	else if(com == "STOP")
		run = 0;
	else if(com == "OFF")
		on = 0;
	else if(com == "SCALE=F")
		scale = 'F';
	else if(com == "SCALE=C")
		scale = 'C';
})

int readCommands()
{
	int i = read(STDIN_FILENO,&buffer, 256);
	if(i == -1)
	{
		fprintf(stderr, "Error in reading from stdin\n");
		exitCode = 2;
	}
	else if(i == 0)
		return 0;
	int index = 0;
	int comIndex = 0;
	char* command;
	while(buffer[i] != '\0')
	{
		if(buffer[i] != '\n')
		{
			command[comIndex] = buffer[i];
			comIndex++
		}
		else
		{
			runCommand(command);			
			command = "";
			comIndex = 0;
		}
	}
}

void main(int argc, char* argv[])
{
	char* option
	static struct option long_options[] = {
		{"SCALE",required_argument,NULL,'s'},
		{"PERIOD",required_argument,NULL,'p'},
		//{"STOP",no_argument,NULL,'o'},
		//{"START",no_argument,NULL,'a'},
		{"LOG",required_argument,NULL,'l'}
		{0,0,0,0}
	};
	int period = 1;
	int option_index = 0;
	int logFlag = 0;
	int r;
	opterr = 0;

	//read initial command line options
	while((r = getopt_long(argc, argv, "", long_options, &option_index)) != -1){
		switch(r){
			case 's':
				scale = *optarg;
				if(scale != 'F' && scale != 'C')
				{
					fprintf(stderr,"Invalid scale option\n");
					scale = 'F';
					exitCode = 1;
				}
				break;
			case 'p':
				period = atoi(optarg);
				if(period <= 0)
				{
					fprintf(stderr, "Invalid Period Option\n");
					period = 1;
					exitCode = 1;
				}
				break;
			case 'l':
				logFlag = 1;
				fd = open(*optarg,O_CREAT | O_TRUNC | O_RDWR, 0666);
				if(!logFile)
				{
					fprintf(stderr,"Error in creating log file\n");
					exitCode = 2;
				}		
				break;
			default:
				fprintf(stderr, "Invalid command option\n");
				exitCode = 1;
				break;
		}
	}

	//initialize button and temp sensor on beaglebone
	tempSensor = mraa_aio_init(1);
	button = mraa_gpio_init(60);
	
	//set button as input
	mraa_gpio_dir(button, MRAA_GPIO_IN);
		
	//set up poll
	struct pollfd polls[1];
	polls[0].fd = STDIN_FILENO;
	polls[0].events = POLLIN | POLLHUP | POLLERR;
	polls[0].revents = 0;

	time_t nextTime = 0;
	struct tm* endTime;

	while(on)
	{
		//if button got pressed
		int buttonPress = mraa_gpio_read(button);
		if(buttonPress > 0)
		{
			gettimeofday(&time,0);
			endTime = localtime(&time.tv_sec);
			fprintf(stdout,"%02d:%02d:%02d  SHUTDOWN",endTime->tm_hour, endTime->tm_min, endTime->tm_sec);
			if(logFlag)
				fprintf(fd,"%02d:%02d:%02d  SHUTDOWN",endTime->tm_hour, endTime->tm_min, endTime->tm_sec);
		}
		else if (buttonPress == -1)
		{
			fprintf(stderr, "Error in reading button press\n");
			exitCode = 2;
		}
				
                //get time of temperature read
                gettimeofday(&time,0);
		float temp = temperature();

		//print temp if supposed to
		if(run && time.tv_sec >= nextTime)
		{
			endTime = localtime(&time.tv_sec);
			fprintf(stdout,"%02d:%02d:%02d %.1f",endTime->tm_hour, endTime->tm_min, endTime->tm_sec, temp);
			if(logFlag)
				fprintf(fd,"%02d:%02d:%02d %.1f",endTime->tm_hour, endTime->tm_min, endTime->tm_sec, temp);
			nextTime = time.tv_sec + period;
		}

		int ret = poll(polls,1,0);
		if(ret == -1)
		{
			fprintf(stderr, "Error in polling\n");
			exitCode = 2;
		}

		if((polls[0].revents & POLLIN)
		{
			readCommands();
		}

	}
	mraa_gpio_close(button);
	mraa_aio_close(tempSensor);
	exit(exitCode);
}
