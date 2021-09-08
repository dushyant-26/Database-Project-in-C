#include "deleteOperations.h"

void deleteTable(Table* table) {
    char* command = (char*)malloc(100);
    strcpy(command, "rm ");
    strcat(command,dbName);
    system(command);
    system("clear");
    exit(1);
}

void truncate(Table* table) {
    header();
    if(rows == 0) {
        printf("\nDatabase Empty!\n");
        backToDashboard();
        return;
    }
    FILE* file = fopen("temp", "w+");
    rewind(table->file);
    table->file = file;
    writeHeaders(table);

    char* command1 = (char*)malloc(100);
    strcpy(command1, "mv ");
    strcat(command1,"temp ");
    strcat(command1,dbName);
    system(command1);

    rows = 0;
    updateRow(table);
    header();
    printf("\nData deleted Successfully!\n");
    backToDashboard();
}

void deleteData(Table* table) {
    header();
    if(rows == 0) {
        printf("\nDatabase Empty!\n");
        backToDashboard();
        return;
    }
    char constraint[50];
    printf("\nOn the basis of which constraint, do you want to delete the entries(Enter * for deleting each entry)\n");
    scanf(" %s",constraint);

    if(strcmp(constraint,"*") == 0) {
        truncate(table);
        return;
    }
    rewind(table->file);
    Table* temp = (Table*)malloc(sizeof(Table));
    temp->file = (FILE*)malloc(sizeof(FILE));
    temp->file = fopen("temp", "w+");
    writeHeaders(temp);


    int attributePos = attributeNum(change_to_uppercase(constraint));
    if(attributePos == -1) {
        header();
        printf("\nNo such attribute in database!\n");
        backToDashboard();
        return;
    }
    printf("Enter value for constraint\n");
    columns constraintVal;
    scanData(attributePos, &constraintVal);
    moveToData(table);

    int deleted = 0;
    columns entry[cols];
    for(int i = 0; i < rows; i++) {
        fread(&entry,sizeof(columns),cols,table->file);
        if(isDataEqual(attributePos, &entry[attributePos], &constraintVal) == 0) {
            fwrite(&entry,sizeof(columns),cols, temp->file);
        }
        else {
            deleted++;
        }
    }
    if(deleted == 0) {
        header();
    }
    char* command1 = (char*)malloc(100);
    strcpy(command1, "mv ");
    strcat(command1,"temp ");
    strcat(command1,dbName);
    system(command1);

    rows = rows - deleted;
    table->file = temp->file;
    free(temp);
    updateRow(table);
    header();
    if(deleted == 0) {
        printf("\nNo data present with this constraint!\n");
    }
    else {
        printf("\nData deleted Successfully!\n");
    }
    backToDashboard();
}
