#Khoi Nguyen
#804993073
#knguyen99@g.ucla.edu

.SILENT:

default:
	gcc -Wall -Wextra -g lab0.c -o lab0

check: default iotest segtest cattest dumptest badotest badargtest baditest

iotest:
	echo "testing input / output " 
	echo "test 1" > i.txt
	./lab0 --input=i.txt --output=o.txt
	if [[ $$? -ne 0 ]]; then \
	echo "exit code not 0, test failed "; \
	else \
	echo "exit code is 0 "; \
	fi; \
	cmp i.txt o.txt 	
	if [[ $$? -eq 0 ]]; then \
	echo "input / output test passed "; \
	else \
	echo "input / output test failed "; \
	fi; \
	rm -f i.txt o.txt

segtest:
	echo "testing segmentation fault "
	echo "test 2" > i.txt
	./lab0 --input=i.txt --output=o.txt --segfault; \
	if [[ $$? -ne 139 ]]; then \
	echo "test failed. exit code not 139: issue with core dump "; \
	else \
	echo "test passed. exit code is 139 "; \
	fi; \
	rm -f *.txt; 

dumptest:
	echo "testing core dump "; \
	echo "test 3" > i.txt; \
	./lab0 --input=i.txt --output=o.txt --catch --dump-core; \
	if [[ $$? -ne 0 ]]; then \
	echo "test failed. exit code not 0 with --catch --dump-core. "; \
	else \
	echo "test passed. exit code is 0 for --catch --dump-core "; \
	fi; \
	rm -f *.txt

cattest:
	echo "testing catch "; \
	echo "test 4" > i.txt; \
	./lab0 --input=i.txt --output=o.txt --catch --segfault; \
	if [[ $$? -ne 4 ]]; then \
	echo "test failed. exit code not 4 with --catch "; \
	else \
	echo " test 1 passed. exit code is 4 with --catch "; \
	fi; \
	./lab0 --input=i.txt --output=o2.txt --dump-core --catch; \
	if [[ $$? -ne 0 ]]; then \
	echo "test failed. exit code not 0 with --dump-core --catch "; \
	else \
	echo " test 2 passed. exit code is 0 with --dump-core --catch "; \
	fi; \
	rm -f *.txt

badargtest:
	echo "testing bad arguments "
	echo "test 6" | ./lab0 --lol; \
	if [[ $$? -ne 1 ]]; then \
	echo "bad argument test failed. exit code not 3. "; \
	else \
	echo "bad argument test passed. exit code 3. "; \
	fi;

baditest:
	echo "testing bad input "
	echo "test" > i.txt
	chmod -r i.txt
	./lab0 --input=i.txt; \
	if [[ $$? -ne 2 ]]; then \
	echo " bad input test failed. exit code not 1. "; \
	else \
	echo " bad input test passed. exit code is 1. "; \
	fi; \
	rm -f *.txt

badotest:
	echo "testing bad output "
	echo "test" > i.txt
	touch o.txt
	chmod -w o.txt 
	./lab0 --input=i.txt --output=o.txt; \
	if [[ $$? -ne 3 ]]; then \
	echo " bad input test failed. exit code not 2. "; \
	else \
	echo " bad input test passed. exit code is 2. "; \
	fi;
	rm -f *.txt

clean:
	rm -rf lab0 *.o *.txt *.tar.gz
dist:
	tar -czf lab0-804993073.tar.gz lab0.c README Makefile backtrace.png breakpoint.png
