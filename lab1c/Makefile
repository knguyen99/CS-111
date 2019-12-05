#Khoi Nguyen
#knguyen99@g.ucla.edu
#804993073

.SILENT:

default:
	gcc -std=c11 -std=gnu99 -Wall -Wextra -g simpsh.c -o simpsh

check: test1 test2 test3

test1:
	echo "test 1"
	echo "test 1" > i.txt;
	./simpsh --profile --creat --append --rdwr i.txt --creat --wronly e.txt --pipe --command 0 0 1 echo lol --command 0 3 1 factor 100 --command 2 0 1 cat --creat --wronly o.txt --command 0 4 1 wc -l > t1.txt
	if [[ $$? -eq 0 ]]; then \
	echo "exit code 0"; \
	echo "test passed"; \
	else \
	echo "test failed"; \
	fi;
	rm i.txt o.txt e.txt 

test2:
	echo "testing 2"
	./simpsh --profile --creat --append --rdwr o.txt --creat --wronly e.txt --pipe --pipe --command 0 3 1 echo cs 111 --command 2 0 1 wc -c --command 0 0 1 date > t2.txt 
	if [[ $$? -eq 0 ]] && wc -l o.txt | grep -q "2"; then \
	echo "exit code 0 test passed"; \
	else \
	echo " something went wrong, test failed"; \
	fi; 
	rm -f o.txt e.txt line.txt
test3:
	echo "testing input / output with multiple commands and wait"
	./simpsh --profile --creat --rdwr o.txt --creat --wronly err.txt --pipe --pipe --pipe --command 0 3 1 ls --command 2 5 1 sort --command 4 7 1 tr [:lower:] [:upper:] --command 6 0 1 grep '8' > t3.txt; \
	if [[ $$? -eq 0 ]]; then \
	echo "exit code 0 test passed"; \
	else \
	echo "something went wrong, test failed"; \
	fi; \
	rm -f err.txt t1.txt t2.txt t3.txt o.txt
clean:
	rm -rf simpsh *.o *.tar.gz
dist:
	tar -czf lab1-804993073.tar.gz simpsh.c README Makefile pg98.txt report.pdf

