//Khoi Nguyen
// 804993073
// knguyen99@g.ucla.edu

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

extern int errno;

void sighand()
{
	fprintf(stderr, "segmentation fault");
	exit(4);
}

int main(int argc, char * argv[])
{

	char* in_file = NULL;
	char* out_file = NULL;
	int catflag = 0;	
	int dflag = 0;	
	int sflag = 0;
	int catflagFirst = 0;	
	static struct option long_options[] = {
		{"input", required_argument, NULL,'i'},
		{"output", required_argument, NULL,'o'},
		{"segfault", no_argument, NULL,'s'},
		{"catch", no_argument, NULL,'c'},
		{"dump-core", no_argument, NULL,'d'},
		{0,0,0,0}
	};

	int r;
	while((r = getopt_long(argc,argv,"i:o:scd",long_options,NULL)) != -1)
	{
		switch(r){
			case 'i':
				in_file = optarg;
				break;
			case 'o':
				out_file = optarg;
				break;
			case 's':
				sflag = 1;
				break;
			case 'c':
				catflag = 1;
				break;
			case 'd':
				if(catflag && !dflag)
				{
					catflagFirst = 1;
				}
				dflag = 1;
				break;
			default:
				fprintf(stderr, "Invalid option. Only --input, --output, --segfault, --catch, and -dump-core allowed. \n");
				exit(1);
		}
	}

	if((catflag && !dflag) || (!catflagFirst && catflag))
        {
                signal(SIGSEGV,sighand);
        }

	if(sflag)
	{
		char* temp = NULL;
		*temp = 'a';
	}
	
	if(in_file)
	{
		int ifd = open(in_file, O_RDONLY);
		if(ifd < 0)
		{
			fprintf(stderr, "Error in opening input %s \n Error: %s", in_file, strerror(errno));
			exit(2);			
		} 
		close(0);
		dup(ifd);
		close(ifd);
	}
	
	if(out_file)
	{
		int ofd = open(out_file, (O_CREAT | O_TRUNC | O_WRONLY), 0666);
		if(ofd < 0)
		{
			fprintf(stderr, "Error in opening output %s \n Error: %s", out_file, strerror(errno));
			exit(3);
		}
		close(1);
		dup(ofd);
		close(ofd);
	}
	
	char buf;
	ssize_t k = read(0,&buf,sizeof(char));
	while(k > 0)
	{
		write(1,&buf,sizeof(char));
		k = read(0,&buf,sizeof(char));
	}  	

	exit(0);
}
