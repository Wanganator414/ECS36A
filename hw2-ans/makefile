CC=gcc
CFLAGS= -ansi -Wall -pedantic
RM='*.exe'
TARGET=hw1_3

$(TARGET): 
	gcc $(CFLAGS) -o $(TARGET) $(TARGET).c

listAll:
	ls -la

vis:
	gcc $(CFLAGS) -o vis.exe vis.c

hw1ex:
	gcc $(CFLAGS) -o hw1ex.exe hw1ex.c

csif28:
	ssh ewang414@pc28.cs.ucdavis.edu

permute:
	gcc $(CFLAGS) -o permute.exe permute.c

life:
	gcc $(CFLAGS) -o life.exe life.c

weird:
	gcc $(CFLAGS) -o weird.exe weird.c

pi:
	gcc $(CFLAGS) -o pi.exe pi.c


clean:
	rm *.exe
