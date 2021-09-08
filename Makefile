Database: utilities.c createOperations.c readOperations.c updateOperations.c deleteOperations.o Database.c
	gcc -c utilities.c
	gcc -c createOperations.c
	gcc -c readOperations.c
	gcc -c updateOperations.c
	gcc -c deleteOperations.c
	ar -cvr libDb.a utilities.o createOperations.o readOperations.o updateOperations.o deleteOperations.o
	gcc -o Database Database.c -L. -lDb
