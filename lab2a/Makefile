#Khoi Nguyen
#knguyen99@g.ucla.edu
#804993073

.SILENT:

default:
	gcc -std=c11 -std=gnu99 -pthread -Wall -Wextra -g lab2_add.c -o lab2_add
	gcc -std=c11 -std=gnu99 -pthread -Wall -Wextra -g SortedList.c lab2_list.c -o lab2_list

tests:	default
	./lab2_add --iterations=100 --threads=2 >> lab2_add.csv 
	./lab2_add --iterations=100 --threads=4	>> lab2_add.csv 
	./lab2_add --iterations=100 --threads=8	>> lab2_add.csv 
	./lab2_add --iterations=100 --threads=12>> lab2_add.csv 
	./lab2_add --iterations=1000 --threads=2>> lab2_add.csv 
	./lab2_add --iterations=1000 --threads=4>> lab2_add.csv 
	./lab2_add --iterations=1000 --threads=8>> lab2_add.csv 
	./lab2_add --iterations=1000 --threads=12>> lab2_add.csv 
	./lab2_add --iterations=10000 --threads=2>> lab2_add.csv 	
	./lab2_add --iterations=10000 --threads=4>> lab2_add.csv 
	./lab2_add --iterations=10000 --threads=8>> lab2_add.csv 
	./lab2_add --iterations=10000 --threads=12>> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=2>> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=4>> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=8>> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=12>> lab2_add.csv 
	./lab2_add --yield --iterations=100 --threads=2 >> lab2_add.csv 
	./lab2_add --yield --iterations=100 --threads=4 >> lab2_add.csv 
	./lab2_add --yield --iterations=100 --threads=8 >> lab2_add.csv 
	./lab2_add --yield --iterations=100 --threads=12>> lab2_add.csv 
	./lab2_add --yield --iterations=1000 --threads=2>> lab2_add.csv 
	./lab2_add --yield --iterations=1000 --threads=4>> lab2_add.csv 
	./lab2_add --yield --iterations=1000 --threads=8>> lab2_add.csv 
	./lab2_add --yield --iterations=1000 --threads=12>> lab2_add.csv 
	./lab2_add --yield --iterations=10000 --threads=2>> lab2_add.csv 
	./lab2_add --yield --iterations=10000 --threads=4>> lab2_add.csv 
	./lab2_add --yield --iterations=10000 --threads=8>> lab2_add.csv 
	./lab2_add --yield --iterations=10000 --threads=12>> lab2_add.csv 
	./lab2_add --yield --iterations=100000 --threads=2>> lab2_add.csv 
	./lab2_add --yield --iterations=100000 --threads=4>> lab2_add.csv 
	./lab2_add --yield --iterations=100000 --threads=8>> lab2_add.csv 
	./lab2_add --yield --iterations=100000 --threads=12>> lab2_add.csv 
	./lab2_add --yield --iterations=100000 --threads=2 --sync=m >> lab2_add.csv 
	./lab2_add --yield --iterations=100000 --threads=4 --sync=m >> lab2_add.csv 
	./lab2_add --yield --iterations=100000 --threads=8 --sync=m >> lab2_add.csv 
	./lab2_add --yield --iterations=100000 --threads=12 --sync=m >> lab2_add.csv 
	./lab2_add --yield --iterations=100000 --threads=2 --sync=c >> lab2_add.csv 
	./lab2_add --yield --iterations=100000 --threads=4 --sync=c >> lab2_add.csv 
	./lab2_add --yield --iterations=100000 --threads=8 --sync=c >> lab2_add.csv 
	./lab2_add --yield --iterations=100000 --threads=12 --sync=c >> lab2_add.csv 
	./lab2_add --yield --iterations=1000 --threads=2 --sync=s >> lab2_add.csv 
	./lab2_add --yield --iterations=1000 --threads=4 --sync=s >> lab2_add.csv 
	./lab2_add --yield --iterations=1000 --threads=8 --sync=s >> lab2_add.csv 
	./lab2_add --yield --iterations=1000 --threads=12 --sync=s >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=1 --sync=m >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=2 --sync=m >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=4 --sync=m >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=8 --sync=m >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=12 --sync=m >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=1 --sync=c >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=2 --sync=c >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=4 --sync=c >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=8 --sync=c >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=12 --sync=c >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=1 --sync=s >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=2 --sync=s >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=4 --sync=s >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=8 --sync=s >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=12 --sync=s >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=1 >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=2 >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=4 >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=8 >> lab2_add.csv 
	./lab2_add --iterations=100000 --threads=12 >> lab2_add.csv 
	./lab2_add --iterations=100 --threads=1 >> lab2_add.csv 
	./lab2_add --iterations=1000 --threads=1 >> lab2_add.csv 
	./lab2_add --iterations=10000 --threads=1 >> lab2_add.csv 
	./lab2_list --iterations=10 >> lab2_list.csv 
	./lab2_list --iterations=100 >> lab2_list.csv 
	./lab2_list --iterations=1000 >> lab2_list.csv 
	./lab2_list --iterations=10000 >> lab2_list.csv 
	./lab2_list --iterations=20000 >> lab2_list.csv 
	-./lab2_list --iterations=10 --threads=2 >> lab2_list.csv 
	-./lab2_list --iterations=100 --threads=2 >> lab2_list.csv
	-./lab2_list --iterations=1000 --threads=2 >> lab2_list.csv
	-./lab2_list --iterations=10 --threads=4 >> lab2_list.csv
	-./lab2_list --iterations=100 --threads=4 >> lab2_list.csv
	-./lab2_list --iterations=1000 --threads=4 >> lab2_list.csv
	-./lab2_list --iterations=10 --threads=8 >> lab2_list.csv 
	-./lab2_list --iterations=100 --threads=8 >> lab2_list.csv 
	-./lab2_list --iterations=1000 --threads=8 >> lab2_list.csv 
	-./lab2_list --iterations=10 --threads=12 >> lab2_list.csv 
	-./lab2_list --iterations=100 --threads=12 >> lab2_list.csv 
	-./lab2_list --iterations=1000 --threads=12 >> lab2_list.csv
	-./lab2_list --iterations=2 --threads=2 --yield=i >>lab2_list.csv 
	-./lab2_list --iterations=2 --threads=4	--yield=i >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=8	--yield=i >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=12 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=2 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=4 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=8 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=12 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=2 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=4 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=8 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=12 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=2 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=4 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=8 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=12 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=2 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=4 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=8 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=12 --yield=i >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=2 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=4 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=8 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=12 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=2 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=4 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=8 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=12 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=2 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=4 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=8 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=12 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=2 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=4 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=8 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=12 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=2 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=4 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=8 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=12 --yield=d >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=2 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=4 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=8 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=12 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=2 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=4 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=8 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=12 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=2 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=4 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=8 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=12 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=2 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=4 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=8 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=12 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=2 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=4 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=8 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=12 --yield=il >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=2 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=4 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=8 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=2 --threads=12 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=2 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=4 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=8 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=4 --threads=12 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=2 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=4 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=8 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=8 --threads=12 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=2 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=4 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=8 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=16 --threads=12 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=2 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=4 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=8 --yield=dl >>lab2_list.csv
	-./lab2_list --iterations=32 --threads=12 --yield=dl >>lab2_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=i --sync=m >>lab2_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=d --sync=m >>lab2_list.csv	
	./lab2_list --iterations=32 --threads=12 --yield=il --sync=m >>lab2_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=dl --sync=m >>lab2_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=i --sync=s >>lab2_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=d --sync=s >>lab2_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=il --sync=s >>lab2_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=dl --sync=s >>lab2_list.csv
	./lab2_list --iterations=1000 >> lab2_list.csv
	./lab2_list --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=2 --sync=m >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=4 --sync=m >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=8 --sync=m >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=12 --sync=m >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=16 --sync=m >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=24 --sync=m >> lab2_list.csv
	./lab2_list --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=2 --sync=s >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=4 --sync=s >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=8 --sync=s >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=12 --sync=s >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=16 --sync=s >> lab2_list.csv
	-./lab2_list --iterations=1000 --threads=24 --sync=s >> lab2_list.csv

graphs: clean tests
	./lab2_add.gp
	./lab2_list.gp	

clean:
	rm -f lab2_add lab2_list *.o *.gz

dist:	clean graphs
	tar -czf lab2a-804993073.tar.gz lab2_list.c lab2_add.c SortedList.c SortedList.h Makefile README lab2_list.csv lab2_add.csv lab2_add.gp lab2_add-1.png  lab2_add-2.png lab2_add-3.png lab2_add-4.png lab2_add-5.png lab2_list.gp lab2_list-1.png lab2_list-2.png lab2_list-3.png lab2_list-4.png

