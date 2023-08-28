CC=gcc
CFLAGS= -c -g -Wall $(INCLUDES)

all: myprogram myprogramOG

myprogram: functions.o main.o
	gcc -o myprogram functions.o main.o

myprogramOG: functionsOriginal.o main.o
	gcc -o myprogramOG functionsOriginal.o main.o

functions.o: functions.c myheader.h
	gcc -c functions.c

functionsOriginial.o: functionsOriginial.c myheaderOG.h
	gcc -c functionsOriginial.c

main.o: main.c myheader.h
	gcc -c main.c -o main.o

clean : 
	rm -v myprogram $(OBJECT_FILES)
