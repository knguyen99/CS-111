#Khoi Nguyen
#knguyen99@g.ucla.edu
#804993073

.SILENT:

default:
	gcc -std=c11 -std=gnu99 -Wall -Wextra -g simpsh.c -o simpsh

check: test1 test2 test3 

test1:
	echo "testing input / output and wait";
	echo "test 1" > i.txt;
	touch o.txt; 
	touch e.txt;
	./simpsh --rdonly i.txt --wronly o.txt --wronly e.txt --wait; \
	if [[ $$? -eq 0 ]]; then \
	echo "exit code 0, test passed"; \
	else \
	echo "exit code not 0, test failed"; \
	fi; \
	rm -f i.txt o.txt e.txt
test2:
	echo "testing command pipe wait and close"
	echo "test 2" > i.txt;
	touch o.txt;
	touch e.txt;
	./simpsh --rdonly i.txt --wronly o.txt --wronly e.txt --pipe --command 0 1 3 cat --verbose --ignore; \
	if [[ $$? -eq 0 ]]; then \
	echo "exit code 0"; \
	else \
	echo "something went wrong, test failed"; \
	fi; 
	diff i.txt o.txt; \
	if [[ $$? -ne 0 ]] && [[ -s e.txt ]]; then \
	echo "input and output not the same, test failed" ; \
	else \
	echo "test passed"; \
	fi;
	rm -f i.txt o.txt e.txt
test3:
	echo "testing --verbose --catch --abort"
	echo "--rdonly i.txt" > i.txt;
	touch output.txt
	./simpsh --verbose --rdonly i.txt --catch 11 --abort > output.txt; \
	if [[ $$? -eq 11 ]]; then \
	echo "exit code 11 test passed"; \
	else \
	echo "something went wrong, test failed"; \
	fi; \
	rm -f i.txt output.txt
clean:
	rm -rf simpsh *.o *.tar.gz
dist:
	tar -czf lab1-804993073.tar.gz simpsh.c README Makefile
