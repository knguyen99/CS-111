//Khoi Nguyen
//804993073
//knguyen99@g.ucla.edu
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/time.h>

int fdArr[100];
int processsize = 10;
pid_t processArr[100];

char** comlist;

int processIndex = 0;
int fdIndex = 0;
int signalCaught = 0;
int highestSignal = 0;

void resizeArray()
{
	if(processsize == processIndex)
	{
		processsize *=2;
		comlist = realloc(comlist,processsize*sizeof(char*));
	}	
}	

void sighand(int n)
{
	fprintf(stderr, "%i caught",n);
	exit(n); 
}

int main(int argc, char* argv[])
{
	comlist = malloc(processsize*sizeof(char*));
	static int verbose_flag = 0;
	static int pro_flag = 0;
	int fileflag = 0;
	int exitFlag = 0;

	struct rusage rstruct;
        struct timeval usertime;
        struct timeval systime;
	struct timeval childusertime;
	struct timeval childsystime;

	static struct option long_options[] = {
		//file flags
		{"append", no_argument, NULL, O_APPEND},
		{"cloexec", no_argument, NULL, O_CLOEXEC},
                {"creat", no_argument,	NULL, O_CREAT},
                {"directory", no_argument,NULL, O_DIRECTORY},
                {"dsync", no_argument,	NULL, O_DSYNC},
                {"excl", no_argument,	NULL, O_EXCL},
                {"nofollow", no_argument,NULL, O_NOFOLLOW},
                {"nonblock", no_argument,NULL, O_NONBLOCK},
                {"rsync", no_argument,	NULL, O_RSYNC},
                {"sync", no_argument,	NULL, O_RSYNC},
                {"trunc", no_argument,	NULL, O_TRUNC}, 

		//file opening options
		{"rdonly",required_argument,NULL,'r'},
		{"wronly",required_argument,NULL,'w'},
		{"rdwr", required_argument,NULL, 'd'},
		{"pipe", no_argument, NULL, 'p'},

		//subcommand options
		{"command", required_argument,NULL,'c'},
		{"wait", no_argument, NULL, 't'},
		
		//miscellaneous options
		{"close", required_argument, NULL, 'l'},
		{"verbose", no_argument, &verbose_flag,1},
		{"profile", no_argument, &pro_flag, 1},
		{"abort", no_argument, NULL, 'a'},
		{"catch", required_argument,NULL, 'h'},
		{"ignore", required_argument,NULL, 'i'},
		{"default", required_argument,NULL, 'e'},
		{"pause", no_argument, NULL, 'u'},
		{0,0,0,0}
	};

	int option_index = 0;
	int r;
	opterr = 0;
	while((r = getopt_long(argc, argv, "", long_options, &option_index)) != -1){
                if(pro_flag)
                {
                        getrusage(RUSAGE_SELF, &rstruct);
                        usertime = rstruct.ru_utime;
                        systime = rstruct.ru_stime;
                }
		switch(r){
			//file flags
			case O_APPEND:
			case O_CLOEXEC:
			case O_CREAT:
                        case O_DIRECTORY:
                        case O_DSYNC:
                        case O_EXCL:
                        case O_NOFOLLOW:
                        case O_NONBLOCK:
                        case O_RSYNC:
                        case O_TRUNC:
				
				if(verbose_flag)
				{
					printf("%s\n", argv[optind-1]);
					fflush(stdout);	
				}
				fileflag = (fileflag | r);;
				break;
				
			//rdonly
			case 'r':{
				if(optarg == NULL || (optarg[0] == '-' && optarg[1] == '-')){
					if(verbose_flag)
					{
						printf("--rdonly\n");
						fflush(stdout);
					}
					fprintf(stderr,	"Invalid argument for --rdonly option");
					if(exitFlag < 1)
						exitFlag = 1;
					break;
				}     	
				else if(verbose_flag)
				{
					printf("--rdonly %s\n", optarg);
					fflush(stdout);
				}
				int fd = open(optarg, O_RDONLY | fileflag , 0666);
				fdArr[fdIndex] = fd;
				fdIndex++;
				fileflag = 0;
				if(fd == -1){
					fprintf(stderr, "Error: cannot open file. fd = %i %i %s\n", fd,errno,optarg);
					
					if(exitFlag < 1)
						exitFlag = 1;
					break;
				}
				break;
				}

			//wronly
			case 'w':{
				if(optarg == NULL || (optarg[0] == '-' && optarg[1] == '-')){
					if(verbose_flag)
					{
						printf("--wronly\n");
						fflush(stdout);
					}
					fprintf(stderr, "Invalid argument for --wronly option");
					if(exitFlag < 1)
						exitFlag = 1;
					break;
				}
				else if(verbose_flag)
				{
					printf("--wronly %s\n", optarg);
					fflush(stdout);
				}
				int fd = open(optarg,O_WRONLY | fileflag, 0666);
				fdArr[fdIndex] = fd;
				fdIndex++;
				fileflag = 0;
				if(fd == -1){
					fprintf(stderr, "Error: cannot open file");
					if(exitFlag < 1)
						exitFlag = 1;
                                        break;
                                }
				break;}

			//rdwr
			case 'd':
				{
					if(optarg == NULL || (optarg[0] == '-' && optarg[1] == '-')){
						if(verbose_flag)
						{
							printf("--rdwr\n");
							fflush(stdout);
						}
						fprintf(stderr, "Invalid argument for --rdwr option");
                                        	if(exitFlag < 1)
							exitFlag = 1;
						break;
					}
					else if(verbose_flag)
					{
						printf("--rdwr %s\n", optarg);
						fflush(stdout);
					}
					int fd = open(optarg,O_RDWR | fileflag,0666);
					fdArr[fdIndex] = fd;
					fdIndex++;
					fileflag = 0;
					if(fd == -1){
						fprintf(stderr, "Error: cannot open file with read and write permission");
                                        	if(exitFlag < 1)
							exitFlag = 1;
						break;
					}
					break;
				}
			
			//pipe
			case 'p': {
				if(verbose_flag)
				{
					printf("--pipe\n");
					fflush(stdout);
				}
				int pipeArr[2];
				if((pipe(pipeArr)) == -1)
				{
					fprintf(stderr, "Error in creating pipe");
					if(exitFlag < 1)
						exitFlag = 1;
					fdArr[fdIndex] = -1;
					fdArr[fdIndex+1] = -1;
					fdIndex += 2;
					break;
				}
				fdArr[fdIndex] = pipeArr[0];
				fdArr[fdIndex+1] = pipeArr[1];
				fdIndex+=2; 				
				break;
			}

			//command
			case 'c':{
				int in = atoi(optarg);
				int ou = atoi(argv[optind]);
				int er = atoi(argv[optind+1]);
				if(fdIndex == 0 || in >= fdIndex || ou >= fdIndex || er >= fdIndex)
				{
					fprintf(stderr, "Error: File descriptor does not exist");
                                        if(exitFlag < 1)
						exitFlag = 1;
					break;
				}

				if(fdArr[in] == -1 || fdArr[ou] == -1 || fdArr[er] == -1)
				{
					fprintf(stderr, "Error: File descriptor could not be opened");
                                        if(exitFlag < 1)
						exitFlag = 1;
					//break;
				}
				int comcount = 1;
				int j = optind+2;
				for(; j < argc; j++){
					if(argv[j][0] == '-' && argv[j][1] == '-')
					{
						break;			
					}
					comcount++;					
				}
				if(comcount == 1)
				{
					fprintf(stderr, "Error: no command");
                                        if(exitFlag < 1)
						exitFlag = 1;
					break;
				}
				char* comarr[comcount];
				int k = 0;
				int charcount = 0;
				for(; k < comcount-1; k++)
					comarr[k] = argv[optind+2+k];
				optind = j;
				char* comstring;
				comstring = malloc(sizeof(char*));
				comarr[comcount-1] = NULL;
				if(verbose_flag)
				{
					printf("--command %i %i %i ", in, ou, er);
					fflush(stdout);
				}
				int m = 0;
				for(; m < comcount-1; m++)
				{
					int q = 0;
					while(comarr[m][q] != '\0')
					{
						comstring = realloc(comstring,(charcount+1)*sizeof(char*));
						comstring[charcount] = comarr[m][q];
						charcount++;
						q++;
					}
					comstring = realloc(comstring, (charcount+1)*sizeof(char*));
					comstring[charcount] = ' ';
					charcount++;
				}
				
				comstring[charcount] = '\0';
				if(verbose_flag)
					printf("%s\n", comstring);
				fflush(stdout);
				pid_t p = fork();
				resizeArray();
				comlist[processIndex] = comstring;
				if( p < 0){
					fprintf(stderr, "Error in creating subprocess");
                                        if(exitFlag < 1)
						exitFlag = 1;
					break;
				}
				if(p == 0){
					dup2(fdArr[in],STDIN_FILENO);
					dup2(fdArr[ou],STDOUT_FILENO);
					dup2(fdArr[er],STDERR_FILENO);
					int closeChildIndex = 0;
					for(; closeChildIndex < fdIndex; closeChildIndex++)
						close(fdArr[closeChildIndex]);
					if(execvp(comarr[0], comarr) == -1)
						{
						fprintf(stderr, "Error in running a command");
						_Exit(exitFlag);
						}
					}
				if(p>0){
					resizeArray();
					processArr[processIndex] = p;
					processIndex++;
					}
					break;
				}

			//wait
			case 't':
				{
					if(verbose_flag)
					{
						printf("--wait\n");
						fflush(stdout);
					}
					int waitIndex = 0;
					for(;waitIndex < processIndex; waitIndex++)
					{
						int status;
						if(pro_flag)
						{
						  getrusage(RUSAGE_CHILDREN, &rstruct);
						  childusertime = rstruct.ru_utime;
						  childsystime = rstruct.ru_stime;
						}
						pid_t id = waitpid(processArr[waitIndex], &status,0);
						if(WIFSIGNALED(status))
						{
							signalCaught = 1;
							if(WTERMSIG(status) > highestSignal)
								highestSignal = WTERMSIG(status);
						}
						if(WEXITSTATUS(status) > exitFlag)
							exitFlag = WEXITSTATUS(status);
						if(processArr[waitIndex] == id)
						{
							if(WIFSIGNALED(status))
								printf("signal %i ", WTERMSIG(status));
							else
								printf("exit %i ", WEXITSTATUS(status));
							fflush(stdout);
							printf("%s\n", comlist[waitIndex]);
						}
						if(pro_flag){
						  getrusage(RUSAGE_CHILDREN, &rstruct);
						  double ut = ((double)rstruct.ru_utime.tv_sec - (double)childusertime.tv_sec) + (((double)rstruct.ru_utime.tv_usec - (double)childusertime.tv_usec)*0.000001);
						  double st = ((double)rstruct.ru_stime.tv_sec - (double)childsystime.tv_sec) + (((double)rstruct.ru_stime.tv_usec - (double)childsystime.tv_usec)*0.000001);
						  printf("Child User time: %fs seconds | System time: %fs \n",  ut, st);
						  fflush(stdout);
						}
						fflush(stdout);
					}	
					break;
				}
			//close
			case 'l':
				{
					if(optarg == NULL || (optarg[0] == '-' && optarg[1] == '-')){
                                        	if(verbose_flag)
						{
                                                	printf("--close\n");
							fflush(stdout);
						}
                                        	fprintf(stderr, "Invalid argument for --close option");
                                        	if(exitFlag < 1)
                                        		exitFlag = 1;
                                        	break;
                                	}
					else if(verbose_flag)
					{
						printf("--close %s\n", optarg);
						fflush(stdout);
					}
					int n = atoi(optarg);
					if(n >= fdIndex)
					{
						fprintf(stderr, "Error: File descriptor does not exist");
                                        	if(exitFlag < 1)
							exitFlag = 1;
						break;
					}
					if(fdArr[n] == -1)
					{
						fprintf(stderr, "Error: File descriptor cannot be closed or is already closed");
                                        	if(exitFlag < 1)
							exitFlag = 1;
						break;
					}
					else if(close(fdArr[n]) == -1)
					{
						fprintf(stderr, "Error in closing file %i %i", errno, n);
                                        	if(exitFlag < 1)
							exitFlag = 1;
						fdArr[n] = -1;
						break;
					}
					fdArr[n] = -1;
					break;
				}
			//abort
			case 'a':
				{	if(verbose_flag)
					{
						printf("--abort\n");
						fflush(stdout);
					}
					char *temp = NULL;
					*temp = 'a';
					break;
				}
			//catch
			case 'h':
				{
                                if(optarg == NULL || (optarg[0] == '-' && optarg[1] == '-')){
                                        if(verbose_flag){
                                                printf("--catch\n");
						fflush(stdout);
					}
                                        fprintf(stderr, "Invalid argument for --default option");
                                        if(exitFlag < 1)
	                                        exitFlag = 1;
                                        break;
                                }
				else if(verbose_flag)
				{
					printf("--catch %s\n",optarg);
					fflush(stdout);
				}
				int sig = atoi(optarg);
				struct sigaction new_action;
				new_action.sa_handler = sighand;
				sigaction(sig, &new_action, NULL);
				break;
				}
			//ignore
			case 'i':
				{
				if(optarg == NULL || (optarg[0] == '-' && optarg[1] == '-')){
                                        if(verbose_flag){
                                                printf("--ignore\n");
						fflush(stdout);
					}
                                        fprintf(stderr, "Invalid argument for --ignore option");
                                        if(exitFlag < 1)                                        
						exitFlag = 1;
                                        break;
                                }
                                else if(verbose_flag){
                                        printf("--ignore %s\n",optarg);
					fflush(stdout);}	
				int sig = atoi(optarg);
				struct sigaction new_action;
				new_action.sa_handler = SIG_IGN;
				sigaction(sig, &new_action, NULL);
				break;
				}

			//default
			case 'e':
				{
                                if(optarg == NULL || (optarg[0] == '-' && optarg[1] == '-')){
                                        if(verbose_flag){
                                                printf("--default\n");
						fflush(stdout);}
                                        fprintf(stderr, "Invalid argument for --default option");
                                        if(exitFlag < 1)
	                                        exitFlag = 1;
                                        break;
                                }
				else if(verbose_flag){
					printf("--default %s\n",optarg);
					fflush(stdout);}
				int sig = atoi(optarg);
				struct sigaction new_action;
				new_action.sa_handler = SIG_DFL;
				sigaction(sig, &new_action, NULL);
				break;
				}
			
			//pause
			case 'u':
				{
					if(verbose_flag){
						printf("--pause");
						fflush(stdout);}
					pause();
					break;
				}
	
			//invalid option
			case '?':{
				fprintf(stderr, "Invalid option or missing argument for option");
                                if(exitFlag < 1)
					exitFlag = 1;
				break;
			}
		}
                if(pro_flag && r){
                        getrusage(RUSAGE_SELF, &rstruct);
                        double ut = ((double)rstruct.ru_utime.tv_sec - (double)usertime.tv_sec) + (((double)rstruct.ru_utime.tv_usec - (double)usertime.tv_usec)*0.000001);
                        double st = ((double)rstruct.ru_stime.tv_sec - (double)systime.tv_sec) + (((double)rstruct.ru_stime.tv_usec - (double)systime.tv_usec)*0.000001);
                        printf("--%s User time: %fs seconds | System time: %fs \n", long_options[option_index].name, ut, st);
                        fflush(stdout);
                }
	}
	free(comlist);
	fflush(stdout);
	if(signalCaught)
	{
		signal(highestSignal,SIG_DFL);
		raise(highestSignal);
	}
	exit(exitFlag);
}


