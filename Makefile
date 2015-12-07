all: 	
	gcc -c Cshell.c Cshell.h
	gcc -g -o myshell Cshell.c
run:	
	./c
clean:
	-rm -rf myshell *~ *.o *.gch
	clear
