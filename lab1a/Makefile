#Khoi Nguyen
#knguyen99@g.ucla.edu
#804993073

.SILENT:

default:
	gcc -std=c11 -Wall -Wextra -g simpsh.c -o simpsh

check: test1 test2 test3

test1:
	echo "testing input / output ";
	echo "test 1" > i.txt;
	touch o.txt; 
	touch e.txt;
	./simpsh --rdonly i.txt --wronly o.txt --wronly e.txt; \
	if [[ $$? -eq 0 ]]; then \
	echo "exit code 0, test passed"; \
	else \
	echo "exit code not 0, test failed"; \
	fi; \
	rm -f i.txt o.txt e.txt
test2:
	echo "testing command"
	echo "test 2" > i.txt;
	touch o.txt;
	touch e.txt;
	./simpsh --rdonly i.txt --wronly o.txt --wronly e.txt --command 0 1 2 cat; \
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
	echo "testing --verbose"
	echo "--rdonly i.txt" > i.txt;
	touch output.txt
	./simpsh --verbose --rdonly i.txt > output.txt; \
	if [[ $$? -eq 0 ]]; then \
	echo "exit code 0"; \
	else \
	echo "something went wrong, test failed"; \
	fi; \
	diff i.txt output.txt; \
	if [[ $$? -ne 0 ]]; then \
	echo "not right output. test failed."; \
	else \
	echo "test passed"; \
	fi;
	rm -f i.txt output.txt
clean:
	rm -rf simpsh *.o *.tar.gz
dist:
	tar -czf lab1-804993073.tar.gz simpsh.c README Makefile
