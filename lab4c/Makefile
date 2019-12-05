#Khoi Nguyen
#knguyen99@g.ucla.edu
#804993073

.SILENT:

default:
	gcc -std=c11 -std=gnu99 -lm -lmraa -Wall -Wextra -g lab4c_tcp.c -o lab4c_tcp
	gcc -std=c11 -std=gnu99 -lssl -lcrypto -lm -lmraa -Wall -Wextra -g lab4c_tls.c -o lab4c_tls

clean:
	rm -f lab4c_tls lab4c_tcp *.gz

dist:	
	tar -czf lab4c-804993073.tar.gz lab4c_tcp.c lab4c_tls.c Makefile README 
