#include "createOperations.h"
Table* createTable(Table* table, char* table_name) {
    table->file = fopen(table_name, "w+");

    char input[100];
    printf("Enter the number of attributes\n");
    scanf(" %s", input);

    if(isInteger(input) == 0) {
        printf("\nInvalid Data(Expected INTEGER)\n");
        char command[100];
        copyString(command, "rm ");
        strcat(command,dbName);
        system(command);
        exit(1);
    }
    cols = convert_to_int(input);

    rows = 0;
    c_name = (char**)malloc(sizeof(char*) * cols);
    datatype = (int*)malloc(sizeof(int) * cols);
    for(int i = 0; i < cols; i++) {
        c_name[i] = (char*)malloc(50);
        printf("\nEnter the name of attribute no. %d\n", i + 1);
        scanf("%s",c_name[i]);
        printf("\nEnter number to tell datatype of this attribute(0 for int,1 for char, 2 for string,3 for double)\n");
        scanf(" %s",input);

        if(isInteger(input) == 0) {
            printf("\nInvalid Data(Expected INTEGER)\n");
            char command[100];
            copyString(command, "rm ");
            strcat(command,dbName);
            system(command);
            exit(1);
        }
        datatype[i] = convert_to_int(input);

    }

    writeHeaders(table);

    return table;
}

Table* openTable() {
    char* table_name = (char*)malloc(50);
    printf("\nEnter the database name\n");
    scanf("%s",table_name);

    dbName = table_name;
    Table* table = (Table*)malloc(sizeof(Table));
    table->file = (FILE*)malloc(sizeof(FILE));
    table->file = fopen(table_name, "r+");

    if(table->file == NULL) {
        return createTable(table,table_name);
    }

    fscanf(table->file,"%d",&cols);
    fscanf(table->file,"%d",&rows);
    datatype = (int*)malloc(sizeof(int) * cols);
    for(int i = 0; i < cols; i++) {
        fscanf(table->file,"%d",&datatype[i]);
    }
    c_name = (char**)malloc(sizeof(char*) * cols);
    for(int i = 0; i < cols; i++) {
        c_name[i] = (char*)malloc(50);
        fscanf(table->file,"%s",c_name[i]);
    }

    return table;
}

void insertData(Table* table) {
    header();
    columns entry[cols];
    fseek(table->file, 0, SEEK_END);

    for(int i = 0; i < cols; i++) {
        printf("Enter the data for %s\n",c_name[i]);
        int correctDatatype = scanData(i,&entry[i]);
        if(correctDatatype == -1) {
            backToDashboard();
            return;
        }
    }
    fwrite(&entry, sizeof(columns),cols, table->file);
    rows++;
    updateRow(table);
    header();
    printf("\nData Inserted Successfully!\n");
    backToDashboard();
}
