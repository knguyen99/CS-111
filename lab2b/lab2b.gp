#! /usr/bin/gnuplot
#
# purpose:
#	 generate data reduction graphs for the multi-threaded add project
#
# input: lab2b_list.csv
#	1. test name
#	2. # threads
#	3. # iterations per thread
#	4. # lists
#	5. # operations performed (threads x iterations x (ins + lookup + delete))
#	6. run time (ns)
#	7. run time per operation (ns)
#	8. total time to acquire locks
# output:
#	lab2_add-1.png ... threads and iterations that run (unprotected) w/o failure

# general plot parameters
set terminal png
set datafile separator ","

#Throughput graph
set title "Throughput (operations/second) vs Threads"
set xlabel "Threads"
set xrange [0.75:]
set logscale x 2
set ylabel "Operations per Second"
set logscale y 10
set output 'lab2b_1.png'

plot \
	"< grep list-none-m lab2b_list.csv | grep 1000,1," using ($2):(1000000000/($7)) \
	title 'Mutex synchronized list operations' with points lc rgb 'blue', \
	"< grep list-none-s lab2b_list.csv | grep 1000,1," using ($2):(1000000000/($7)) \
	title 'Spin-lock synchronized list operations' with points lc rgb 'violet', \

#Timing Mutex Waits graph
set title "Wait-For-Lock Time and Average Time Per Operation vs Threads"
set xlabel "Threas"
set xrange [0.75:]
set logscale x 2
set ylabel "Wait-For-Lock Time and Average Time"
set logscale y 10
set output 'lab2b_2.png'

plot \
	"< grep list-none-m lab2b_list.csv | grep 1000" using ($2):($7) \
	title 'Mutex synchronized Average Time per operations' with points lc rgb 'blue', \
	"< grep list-none-m lab2b_list.csv | grep 1000" using ($2):($8) \
	title 'Mutex synchronized Average Wait-For-Lock time' with points lc rgb 'green', \

#Correctness of list option
set title "Correctness of Unprotected and Protected Threads'
set xlabel "Threads"
set xrange [0.75:]
set logscale x 2
set ylabel "Successful Iterations"
set logscale y 10
set output 'lab2b_3.png'

plot \
	"< grep list-id-none lab2b_list.csv | grep 1,4," using ($2):($3) \
	title 'Unprotected' with points lc rgb 'red', \
	"< grep list-id-none lab2b_list.csv | grep 2,4," using ($2):($3) \
	title '' with points lc rgb 'red', \
	"< grep list-id-none lab2b_list.csv | grep 4,4," using ($2):($3) \
	title '' with points lc rgb 'red', \
	"< grep list-id-none lab2b_list.csv | grep 8,4," using ($2):($3) \
	title '' with points lc rgb 'red', \
	"< grep list-id-none lab2b_list.csv | grep 16,4," using ($2):($3) \
	title '' with points lc rgb 'red', \
	"< grep list-id-m lab2b_list.csv | grep 10,4," using ($2):($3) \
	title 'Mutex protected' with points lc rgb 'blue', \
	"< grep list-id-m lab2b_list.csv | grep 20,4," using ($2):($3) \
	title '' with points lc rgb 'blue', \
	"< grep list-id-m lab2b_list.csv | grep 40,4," using ($2):($3) \
	title '' with points lc	rgb 'blue', \
	"< grep list-id-m lab2b_list.csv | grep 80,4," using ($2):($3) \
	title '' with points lc rgb 'blue', \
	"< grep list-id-s lab2b_list.csv | grep 10,4," using ($2):($3) \
	title 'Spin Lock protected' with points lc rgb 'green', \
	"< grep list-id-s lab2b_list.csv | grep 20,4," using ($2):($3) \
	title '' with points lc rgb 'green', \
	"< grep list-id-s lab2b_list.csv | grep 40,4," using ($2):($3) \
	title '' with points lc rgb 'green', \
	 "< grep list-id-s lab2b_list.csv | grep 80,4," using ($2):($3) \
	title '' with points lc rgb 'green', \

#Mutex Throughput vs Threads
set title "Throughput vs Threads"
set xlabel "Threads"
set xrange [0.75:]
set logscale x 2
set ylabel "Operations per Second"
set logscale y 10
set output 'lab2b_4.png'

plot \
	"< grep list-none-m lab2b_list.csv | grep 1000,1," using ($2):(1000000000/($7)) \
	title 'One List' with linespoints lc rgb 'blue', \
	"< grep list-none-m lab2b_list.csv | grep 1000,4" using ($2):(1000000000/($7)) \
	title 'Four Lists' with linespoints lc rgb 'green', \
	"< grep list-none-m lab2b_list.csv | grep 1000,8" using ($2):(1000000000/($7)) \
	title 'Eight Lists' with linespoints lc rgb 'red', \
	"< grep list-none-m lab2b_list.csv | grep 1000,16," using ($2):(1000000000/($7)) \
	title 'Sixteen List' with linespoints lc rgb 'violet' \

#Spin Lock Throughput vs Threads
set title "Throughput vs Threads"
set xlabel "Threads"
set xrange [0.75:]
set logscale x 2
set ylabel "Operations per Second"
set logscale y 10
set output 'lab2b_5.png'

plot \
	"< grep list-none-s lab2b_list.csv | grep ,1000,1," using ($2):(1000000000/($7)) \
	title 'One List' with linespoints lc rgb 'blue', \
	"< grep list-none-s lab2b_list.csv | grep 1000,4" using ($2):(1000000000/($7)) \
	title 'Four Lists' with linespoints lc rgb 'green', \
	"< grep list-none-s lab2b_list.csv | grep 1000,8" using ($2):(1000000000/($7)) \
	title 'Eight Lists' with linespoints lc rgb 'red', \
	"< grep list-none-s lab2b_list.csv | grep 1000,16," using ($2):(1000000000/($7)) \
	title 'Sixteen List' with linespoints lc rgb 'violet' \

