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

int fdArr[100];
int fdIndex = 0;

int main(int argc, char* argv[])
{
	static int verbose_flag = 0;
	int exitFlag = 0;
	static struct option long_options[] = {
		{"rdonly",required_argument,NULL,'r'},
		{"wronly",required_argument,NULL,'w'},
		{"command", required_argument,NULL,'c'},
		{"verbose", no_argument, NULL,'v'},
		{0,0,0,0}
	};

	int option_index = 0;
	int r;
	opterr = 0;
	while((r = getopt_long(argc, argv, "r:w:c:v", long_options, &option_index)) != -1){
		switch(r){
			case 'r':{
				if(optarg == NULL || (optarg[0] == '-' && optarg[1] == '-')){
					if(verbose_flag)
						printf("--rdonly\n");
					fprintf(stderr,	"Invalid argument for --rdonly option");
					exitFlag = 1;
					break;
				}     	
				else if(verbose_flag)
					printf("--rdonly %s\n", optarg);
				int fd = open(optarg,O_RDONLY);
				fdArr[fdIndex] = fd;
				fdIndex++;
				if(fd == -1){
					fprintf(stderr, "Error: cannot open file");
					exitFlag = 1;
					break;
				}
				break;}
			case 'w':{
				if(optarg == NULL || (optarg[0] == '-' && optarg[1] == '-')){
					if(verbose_flag)
						printf("--wronly\n");
					fprintf(stderr, "Invalid argument for --wronly option");
					exitFlag = 1;
					break;
				}
				else if(verbose_flag)
					printf("--wronly %s\n", optarg);
				int fd = open(optarg,O_WRONLY);
				fdArr[fdIndex] = fd;
				fdIndex++;
				if(fd == -1){
					fprintf(stderr, "Error: cannot open file");
					exitFlag = 1;
                                        break;
                                }
				break;}
			case 'c':{
				int ioearr[3];
				int in = atoi(optarg);
				int ou = atoi(argv[optind]);
				int er = atoi(argv[optind+1]);
				if(fdIndex == 0 || in >= fdIndex || ou >= fdIndex || er >= fdIndex)
				{
					fprintf(stderr, "Error: File descriptor does not exist");
					exitFlag = 1;
					break;
				}

				if(fdArr[in] == -1 || fdArr[ou] == -1 || fdArr[er] == -1)
				{
					fprintf(stderr, "Error: File descriptor could not be opened");
					exitFlag = 1;
					break;
				}
				ioearr[0] = fdArr[in];
				ioearr[1] = fdArr[ou];
				ioearr[2] = fdArr[er];
				int comcount = 1;
				int j = optind+2;
				for(; j < argc; j++){
					if(argv[j][0] == '-' && argv[j][1] == '-')
					{
						break;			
					}
					comcount++;					
				}
				char* comarr[comcount];
				int k = 0;
				for(; k < comcount-1; k++)
					comarr[k] = argv[optind+2+k];
				optind = j;
				comarr[comcount-1] = NULL;
				if(verbose_flag){
					printf("--command %i %i %i ", in, ou, er);
					int m = 0;
					for(; m < comcount-1; m++)
						printf("%s ",comarr[m]);
					printf("\n");
				}
				pid_t p = fork();
				if( p < 0){
					fprintf(stderr, "Error in creating subprocess");
					exitFlag = 1;
					break;
				}
				if(p == 0){
					dup2(ioearr[0],STDIN_FILENO);
					dup2(ioearr[1],STDOUT_FILENO);
					dup2(ioearr[2],STDERR_FILENO);
					if(execvp(comarr[0], comarr) == -1)
						fprintf(stderr, "Error in running a command");
					}
					break;
				}
			case 'v':
				verbose_flag = 1;
				break;
			default:{
				fprintf(stderr, "Invalid option.");
				exitFlag = 1;
			}
		}
	}
	exit(exitFlag);
}


