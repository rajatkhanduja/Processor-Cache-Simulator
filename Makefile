SRC=src
OBJ=obj
INC=include
BIN=bin

all: ${OBJ}/file_reading.o ${OBJ}/main.o ${OBJ}/cache.o
	g++ ${OBJ}/file_reading.o ${OBJ}/main.o ${OBJ}/cache.o -o ${BIN}/cache_simulator

${OBJ}/file_reading.o: ${SRC}/file_reading.cpp
	g++ -c -g ${SRC}/file_reading.cpp -o ${OBJ}/file_reading.o

${OBJ}/main.o: ${SRC}/main.cpp
	g++ -c -g ${SRC}/main.cpp -o ${OBJ}/main.o

${OBJ}/cache.o: ${SRC}/cache.cpp
	g++ -c -g ${SRC}/cache.cpp -o ${OBJ}/cache.o


clean:
	rm -f ${OBJ}/* ${BIN}/*
