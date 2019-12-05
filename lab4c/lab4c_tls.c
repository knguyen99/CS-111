//Khoi Nguyen
//knguyen99.g.ucla.edu
//804993073

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <sys/time.h>
#include <mraa.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

int exitCode = 0;
int fd = -1;

int run = 1;
int on = 1;
int period = 1;
char scale = 'F';

char* studentID = NULL;
char* host = NULL;
int portNum = -1;
int sockFD = -1;

struct hostent* server;
struct sockaddr_in serverAddr;
SSL* connection;

mraa_aio_context tempSensor;

struct timeval t;
struct tm* endTime;

char readBuffer[256];

float temperature()
{
	//value of the thermistor
	const int b = 4275;

	int a = mraa_aio_read(tempSensor);
	float R = 1023.0/a - 1.0;
	R = 100000*R;
	float temp = 1.0/(log(R/100000)/b+1/298.15)-273.15;
	switch(scale)
	{
		case 'F': return temp*9/5+32;
		default: return temp;
	}
}

int incorrectID(char* id)
{
	if(id == NULL || strlen(id) != 9)
		return 1;
	for(int i = 1; i < 9; i++)
	{
		if(id[i] < '0' || id[i] > '9')
			return 1;
	}
	return 0;
}

void runCommand(char* com)
{
        dprintf(fd,"%s\n",com);
	if(strcmp(com,"OFF") == 0)
	{
		char writeBuffer[256];
        	gettimeofday(&t,0);
        	endTime = localtime(&t.tv_sec);
        	sprintf(writeBuffer,"%02d:%02d:%02d SHUTDOWN\n",endTime->tm_hour, endTime->tm_min, endTime->tm_sec);
		SSL_write(connection,writeBuffer,strlen(writeBuffer));
		dprintf(fd,"%02d:%02d:%02d SHUTDOWN\n",endTime->tm_hour, endTime->tm_min, endTime->tm_sec);
        	on = 0;
	}
        else if(strcmp(com,"STOP") == 0)
                run = 0;
        else if(strcmp(com,"START") == 0)
                run = 1;
        else if(strcmp(com,"SCALE=F") == 0)
                scale = 'F';
	else if(strcmp(com,"SCALE=C") == 0)
                scale = 'C';
	else if(strncmp(com,"PERIOD=",7) == 0)
	{
		int newPeriod = atoi(com+7);
		if(newPeriod != 0)
		{
			period = newPeriod;
		}
		else
		{
			dprintf(STDERR_FILENO,"Invalid period value\n");
			exitCode = 1;
		}
	}
	else if(strncmp(com,"LOG ",4) == 0)
	{
		dprintf(fd,"%s\n",com+4);
	}
}



int readCommands()
{
	int k = SSL_read(connection,readBuffer,256);
	if(k == -1)
	{
		dprintf(STDERR_FILENO, "Error in reading from stdin\n");
		exitCode = 2;
		return 0;
	}

	int index = 0;
	int comIndex = 0;
	char command[256];
	memset(command,0,256);
	while(index<256 && index<k)
	{
		if(readBuffer[index] != '\n')
		{
			command[comIndex] = readBuffer[index];
			comIndex++;
		}
		else
		{
			runCommand(command);
			memset(command,0,256);
			comIndex = 0;
		}
		index++;
	}
	return 1;
}

void connectToServer()
{
	//initialize scket
	sockFD = socket(AF_INET,SOCK_STREAM,0);
	if(sockFD ==  -1)
	{
		dprintf(STDERR_FILENO, "Error in creating socket\n");
		exit(2);
	}

        //initialize SSL
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        SSL_load_error_strings();

        const SSL_METHOD* method = TLSv1_client_method();
        SSL_CTX* context = SSL_CTX_new(method);
        if(context == NULL)
        {
                dprintf(STDERR_FILENO, "Error in creating context\n");
                exit(2);
        }
        connection = SSL_new(context);
        if(connection == NULL)
        {
                dprintf(STDERR_FILENO, "Error in creating framework for connection data\n");
                exit(2);
        }
	//identify target structure / host port
	server = gethostbyname(host);
	if(server == NULL)
	{
		dprintf(STDERR_FILENO, "Error in getting host by name\n");
		SSL_shutdown(connection);
        	SSL_free(connection);
		exit(1);
	}

	//intialize for connecting
	bzero((char*) &serverAddr, sizeof(serverAddr));
	bcopy((char*)server->h_addr, (char*)&serverAddr.sin_addr.s_addr, server->h_length);
	serverAddr.sin_port = htons(portNum);
	serverAddr.sin_family = AF_INET;

	//connect
	if((connect(sockFD,(struct sockaddr*)&serverAddr, sizeof(serverAddr))) != 0)
	{
		dprintf(STDERR_FILENO,"Error in connecting\n");
	        SSL_shutdown(connection);
	        SSL_free(connection);
		exit(2);
	}

        //set up communicaton between ssl and socket fd
        if((SSL_set_fd(connection,sockFD)) != 1)
        {
                dprintf(STDERR_FILENO, "Error in establishing communication between SSL and socket fd\n");
	        SSL_shutdown(connection);
	        SSL_free(connection);
                exit(2);
        }

	if((SSL_connect(connection)) != 1)
	{
		dprintf(STDERR_FILENO, "Error in SSL connection\n");
	        SSL_shutdown(connection);
	        SSL_free(connection);
		exit(2);
	}

        //print id
	char writeBuffer[256];
        sprintf(writeBuffer,"ID=%s\n",studentID);
	SSL_write(connection,writeBuffer,strlen(writeBuffer));
        dprintf(fd,"ID=%s\n",studentID);
}

int main(int argc, char* argv[])
{
	static struct option long_options[] = {
		{"scale",required_argument,NULL,'s'},
		{"period",required_argument,NULL,'p'},
		{"log",required_argument,NULL,'l'},
		{"id",required_argument,NULL,'i'},
		{"host",required_argument,NULL,'h'},
		{0,0,0,0}
	};
	int option_index = 0;
	int r;
	opterr = 0;
	memset(readBuffer,0,256);

	//read initial command line options
	while((r = getopt_long(argc, argv, "", long_options, &option_index)) != -1){
		switch(r){
			case 's':
				scale = *optarg;
				if(scale != 'F' && scale != 'C')
				{
					dprintf(STDERR_FILENO,"Invalid scale option\n");
					scale = 'F';
					exitCode = 1;
				}
				break;
			case 'p':
				period = atoi(optarg);
				if(period <= 0)
				{
					dprintf(STDERR_FILENO, "Invalid Period Option\n");
					period = 1;
					exitCode = 1;
				}
				break;
			case 'l':
				fd = open(optarg,O_CREAT | O_TRUNC | O_RDWR, 0666);
				if(fd == -1)
				{
					dprintf(STDERR_FILENO,"Error in creating log file\n");
					exitCode = 2;
				}
				break;
			case 'i':
				studentID = optarg;
				break;
			case 'h':
				host = optarg;
				break;
			default:
				dprintf(STDERR_FILENO, "Invalid command option\n");
				exit(1);
				break;
		}
	}

	if(optind < argc)
		portNum = atoi(argv[optind]); 

	if( fd == -1 || incorrectID(studentID) || host == NULL || portNum <= 0)
	{
		dprintf(STDERR_FILENO,"Error invalid mandatory parameter\n");
		exit(1);
	}
	connectToServer();


	//initialize temp sensor on beaglebone
	tempSensor = mraa_aio_init(1);

	//set up poll
	struct pollfd polls[1];
	polls[0].fd = sockFD;
	polls[0].events = POLLIN | POLLHUP | POLLERR;
	polls[0].revents = 0;

	time_t nextTime = 0;

	while(on)
	{
                //get time of temperature read
                gettimeofday(&t,0);
		float temp = temperature();

		//print temp if supposed to
		if(run && t.tv_sec >= nextTime)
		{
			char writeBuffer[256];
			endTime = localtime(&t.tv_sec);
			sprintf(writeBuffer,"%02d:%02d:%02d %.1f\n",endTime->tm_hour, endTime->tm_min, endTime->tm_sec, temp);
			SSL_write(connection,writeBuffer,strlen(writeBuffer));
			dprintf(fd,"%02d:%02d:%02d %.1f\n",endTime->tm_hour, endTime->tm_min, endTime->tm_sec, temp);
			nextTime = t.tv_sec + period;
		}

		//poll
		int ret = poll(polls,1,0);
		if(ret == -1)
		{
			dprintf(STDERR_FILENO, "Error in polling\n");
			exitCode = 2;
		}

		if(polls[0].revents & POLLIN)
		{
			readCommands();
		}

	}
	close(fd);
	close(sockFD);
	SSL_shutdown(connection);
	SSL_free(connection);
	mraa_aio_close(tempSensor);
	exit(exitCode);
}
