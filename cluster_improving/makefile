FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

all: cluster
clean:
	rm -rf *.o cluster

cluster: main.o SparseMatrix.o Utility.o Common.o ModularityGroupsDivision.o Algorithm2.o B.o ModularityMaximization.o vector.o
	gcc main.o SparseMatrix.o Utility.o Common.o ModularityGroupsDivision.o Algorithm2.o B.o ModularityMaximization.o vector.o -o cluster $(LIBS)
main.o:  main.c ModularityGroupsDivision.h SparseMatrix.h Common.h Utility.h
	gcc $(FLAGS) -c main.c
	
SparseMatrix.o: SparseMatrix.c SparseMatrix.h Common.h
	gcc $(FLAGS) -c SparseMatrix.c
	
Utility.o: Utility.c Utility.h SparseMatrix.h Common.h
	gcc $(FLAGS) -c Utility.c
	
Common.o: Common.c Common.h
	gcc $(FLAGS) -c Common.c
	
ModularityGroupsDivision.o: ModularityGroupsDivision.c ModularityGroupsDivision.h B.h Algorithm2.h ModularityMaximization.h
	gcc $(FLAGS) -c ModularityGroupsDivision.c

Algorithm2.o: Algorithm2.c Algorithm2.h Common.h B.h SparseMatrix.h vector.h
	gcc $(FLAGS) -c Algorithm2.c
	
B.o: B.c B.h Common.h SparseMatrix.h vector.h 
	gcc $(FLAGS) -c B.c

ModularityMaximization.o: ModularityMaximization.c ModularityMaximization.h SparseMatrix.h
	gcc $(FLAGS) -c ModularityMaximization.c

vector.o: vector.c vector.h 
	gcc $(FLAGS) -c vector.c
