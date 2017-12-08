CC = gcc
FLAGS = -Wall 

all: rec transu

recv: rec.c
	$(CC) rec.c -lc -o rec $(FLAGS) 

sender: transu.c 
	$(CC) transu.c -lc -o transu $(FLAGS) 

clean:
	rm *.o *.exe



