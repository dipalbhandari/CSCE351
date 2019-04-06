output:  monitor.c sleepingStylistMon.c monitor.o
	gcc sleepingStylistMon.c  monitor.c -o result -lpthread
monitor.o: monitor.c
	gcc -c monitor.c 
clean: 
	rm *.o result