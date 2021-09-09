Database: utilities.c createOperations.c readOperations.c updateOperations.c deleteOperations.o Database.c
	gcc -c utilities.c createOperations.c readOperations.c updateOperations.c deleteOperations.c
	ar -cvr libDb.a utilities.o createOperations.o readOperations.o updateOperations.o deleteOperations.o
	gcc -o Database Database.c -L. -lDb
