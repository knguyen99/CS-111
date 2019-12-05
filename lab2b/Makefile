#Khoi Nguyen
#knguyen99@g.ucla.edu
#804993073

.SILENT:

default:
	gcc -std=c11 -std=gnu99 -lpthread -Wno-parentheses -Wall -Wextra -lprofiler -g SortedList.c lab2_list.c -o lab2_list

tests:	default
	./lab2_list --iterations=10 >> lab2b_list.csv 
	./lab2_list --iterations=100 >> lab2b_list.csv 
	./lab2_list --iterations=1000 >> lab2b_list.csv 
	./lab2_list --iterations=10000 >> lab2b_list.csv 
	./lab2_list --iterations=20000 >> lab2b_list.csv 
	-./lab2_list --iterations=10 --threads=2 >> lab2b_list.csv 
	-./lab2_list --iterations=100 --threads=2 >> lab2b_list.csv
	-./lab2_list --iterations=1000 --threads=2 >> lab2b_list.csv
	-./lab2_list --iterations=10 --threads=4 >> lab2b_list.csv
	-./lab2_list --iterations=100 --threads=4 >> lab2b_list.csv
	-./lab2_list --iterations=1000 --threads=4 >> lab2b_list.csv
	-./lab2_list --iterations=10 --threads=8 >> lab2b_list.csv 
	-./lab2_list --iterations=100 --threads=8 >> lab2b_list.csv 
	-./lab2_list --iterations=1000 --threads=8 >> lab2b_list.csv 
	-./lab2_list --iterations=10 --threads=12 >> lab2b_list.csv 
	-./lab2_list --iterations=100 --threads=12 >> lab2b_list.csv 
	-./lab2_list --iterations=1000 --threads=12 >> lab2b_list.csv
	-./lab2_list --iterations=2 --threads=2 --yield=i >>lab2b_list.csv 
	-./lab2_list --iterations=2 --threads=4	--yield=i >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=8	--yield=i >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=12 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=2 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=4 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=8 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=12 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=2 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=4 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=8 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=12 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=2 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=4 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=8 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=12 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=2 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=4 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=8 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=12 --yield=i >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=2 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=4 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=8 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=12 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=2 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=4 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=8 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=12 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=2 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=4 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=8 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=12 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=2 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=4 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=8 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=12 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=2 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=4 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=8 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=12 --yield=d >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=2 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=4 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=8 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=12 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=2 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=4 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=8 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=12 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=2 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=4 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=8 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=12 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=2 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=4 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=8 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=12 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=2 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=4 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=8 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=12 --yield=il >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=2 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=4 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=8 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=2 --threads=12 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=2 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=4 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=8 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=4 --threads=12 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=2 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=4 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=8 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=8 --threads=12 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=2 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=4 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=8 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=16 --threads=12 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=2 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=4 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=8 --yield=dl >>lab2b_list.csv
	-./lab2_list --iterations=32 --threads=12 --yield=dl >>lab2b_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=i --sync=m >>lab2b_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=d --sync=m >>lab2b_list.csv	
	./lab2_list --iterations=32 --threads=12 --yield=il --sync=m >>lab2b_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=dl --sync=m >>lab2b_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=i --sync=s >>lab2b_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=d --sync=s >>lab2b_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=il --sync=s >>lab2b_list.csv
	./lab2_list --iterations=32 --threads=12 --yield=dl --sync=s >>lab2b_list.csv
	./lab2_list --iterations=1000 >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=2 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=4 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=8 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=12 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=16 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=24 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=2 --sync=s >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=4 --sync=s >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=8 --sync=s >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=12 --sync=s >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=16 --sync=s >> lab2b_list.csv
	-./lab2_list --iterations=1000 --threads=24 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=1 --threads=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=1	--threads=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=1	--threads=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=1	--threads=12 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=1	--threads=16 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=2	--threads=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=2 --threads=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=2 --threads=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=2 --threads=12 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=2 --threads=16 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=4	--threads=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=4 --threads=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=4 --threads=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=4 --threads=12 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=4 --threads=16 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=8 --threads=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=8 --threads=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=8 --threads=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=8 --threads=12 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=8 --threads=16 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=16 --threads=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=16 --threads=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=16 --threads=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=16 --threads=12 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --iterations=16 --threads=16 >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=10 --threads=1 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=10 --threads=4 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=10 --threads=8 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=10 --threads=12 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=10 --threads=16 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=20 --threads=1 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=20 --threads=4 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=20 --threads=8 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=20 --threads=12 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=20 --threads=16 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=40 --threads=1 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=40 --threads=4 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=40 --threads=8 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=40 --threads=12 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=40 --threads=16 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=80 --threads=1 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=80 --threads=4 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=80 --threads=8 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=80 --threads=12 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=80 --threads=16 --sync=m >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=10 --threads=1 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=10 --threads=4 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=10 --threads=8 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=10 --threads=12 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=10 --threads=16 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=20 --threads=1 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=20 --threads=4 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=20 --threads=8 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=20 --threads=12 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=20 --threads=16 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=40 --threads=1 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=40 --threads=4 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=40 --threads=8 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=40 --threads=12 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=40 --threads=16 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=80 --threads=1 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=80 --threads=4 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=80 --threads=8 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=80 --threads=12 --sync=s >> lab2b_list.csv
	./lab2_list --yield=id --lists=4 --iterations=80 --threads=16 --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --iterations=1000 --threads=1 --sync=m >> lab2b_list.csv
	./lab2_list --lists=8 --iterations=1000 --threads=1 --sync=m >> lab2b_list.csv
	./lab2_list --lists=16 --iterations=1000 --threads=1 --sync=m >> lab2b_list.csv
	./lab2_list --lists=1 --iterations=1000 --threads=2 --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --iterations=1000 --threads=2 --sync=m >> lab2b_list.csv
	./lab2_list --lists=8 --iterations=1000 --threads=2 --sync=m >> lab2b_list.csv
	./lab2_list --lists=16 --iterations=1000 --threads=2 --sync=m >> lab2b_list.csv
	./lab2_list --lists=1 --iterations=1000 --threads=4 --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --iterations=1000 --threads=4 --sync=m >> lab2b_list.csv
	./lab2_list --lists=8 --iterations=1000 --threads=4 --sync=m >> lab2b_list.csv
	./lab2_list --lists=16 --iterations=1000 --threads=4 --sync=m >> lab2b_list.csv
	./lab2_list --lists=1 --iterations=1000 --threads=8 --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --iterations=1000 --threads=8 --sync=m >> lab2b_list.csv
	./lab2_list --lists=8 --iterations=1000 --threads=8 --sync=m >> lab2b_list.csv
	./lab2_list --lists=16 --iterations=1000 --threads=8 --sync=m >> lab2b_list.csv
	./lab2_list --lists=1 --iterations=1000 --threads=12 --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --iterations=1000 --threads=12 --sync=m >> lab2b_list.csv
	./lab2_list --lists=8 --iterations=1000 --threads=12 --sync=m >> lab2b_list.csv
	./lab2_list --lists=16 --iterations=1000 --threads=12 --sync=m >> lab2b_list.csv
	./lab2_list --lists=1 --iterations=1000 --threads=1 --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --iterations=1000 --threads=1 --sync=s >> lab2b_list.csv
	./lab2_list --lists=8 --iterations=1000 --threads=1 --sync=s >> lab2b_list.csv
	./lab2_list --lists=16 --iterations=1000 --threads=1 --sync=s >> lab2b_list.csv
	./lab2_list --lists=1 --iterations=1000 --threads=2 --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --iterations=1000 --threads=2 --sync=s >> lab2b_list.csv
	./lab2_list --lists=8 --iterations=1000 --threads=2 --sync=s >> lab2b_list.csv
	./lab2_list --lists=16 --iterations=1000 --threads=2 --sync=s >> lab2b_list.csv
	./lab2_list --lists=1 --iterations=1000 --threads=4 --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --iterations=1000 --threads=4 --sync=s >> lab2b_list.csv
	./lab2_list --lists=8 --iterations=1000 --threads=4 --sync=s >> lab2b_list.csv
	./lab2_list --lists=16 --iterations=1000 --threads=4 --sync=s >> lab2b_list.csv
	./lab2_list --lists=1 --iterations=1000 --threads=8 --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --iterations=1000 --threads=8 --sync=s >> lab2b_list.csv
	./lab2_list --lists=8 --iterations=1000 --threads=8 --sync=s >> lab2b_list.csv
	./lab2_list --lists=16 --iterations=1000 --threads=8 --sync=s >> lab2b_list.csv
	./lab2_list --lists=1 --iterations=1000 --threads=12 --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --iterations=1000 --threads=12 --sync=s >> lab2b_list.csv
	./lab2_list --lists=8 --iterations=1000 --threads=12 --sync=s >> lab2b_list.csv
	./lab2_list --lists=16 --iterations=1000 --threads=12 --sync=s >> lab2b_list.csv

graphs: clean tests
	./lab2b.gp

profile:
	LD_PRELOAD=/usr/lib64/libprofiler.so CPUPROFILE=profile.gperf ./lab2_list --iterations=1000 --threads=12 --sync=s
	pprof --text ./lab2_list ./profile.gperf > profile.out
	pprof --list=function ./lab2_list ./profile.gperf >> profile.out
clean:
	rm -f lab2_list *.gz 

dist:	clean graphs profile
	tar -czf lab2b-804993073.tar.gz lab2_list.c SortedList.c SortedList.h Makefile README lab2b_list.csv profile.out lab2b_1.png lab2b_2.png lab2b_3.png lab2b_4.png lab2b_5.png lab2b.gp profile.gperf

