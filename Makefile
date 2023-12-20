.SUFFIXES: .c .o
CCFLAGS = -std=c99 -pedantic -Wall
OBJS = radixTrie.o func.o
EXEC = radixTrie 
OPTIONS = -g

build: ${OBJS}
	gcc ${CCFLAGS} ${OPTIONS} -o ${EXEC} ${OBJS}
	
radixTrie.o: radixTrie.c func.h
	gcc ${CCFLAGS} ${OPTIONS} -c radixTrie.c
	
func.o: func.c func.h
	gcc ${CCFLAGS} ${OPTIONS} -c func.c
	
run: ${EXEC}
	./${EXEC}
	
clean:
	rm -f ${EXEC} ${OBJS}

valgrind:
	#valgrind --tool=memcheck --leak-check=full ./${EXEC}
	valgrind --track-origins=yes --leak-check=full ./${EXEC}
	
