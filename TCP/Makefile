CC = g++
FLAGS = -Wall 

all: cliente servidor

servidor: testesrv.cpp
	$(CC) testesrv.cpp -o servidor $(FLAGS) 

cliente: testecli.cpp 
	$(CC) testecli.cpp -o cliente $(FLAGS) 

clean:
	rm *.o *.exe




