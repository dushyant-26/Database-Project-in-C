//All the utility functions aree included in utilities.h
#include "updateOperations.h"

//updates the data entries in table with given constraint
//params:
//Table* table: pointer to structure containing file
void updateData(Table* table) {
    header();
    if(rows == 0) {
        printf("\nDatabase Empty!\n");
        backToDashboard();
        return;
    }

    char constraint[50];
    printf("\nOn the basis of which constraint, do you want to update the entries(Enter * for updating each entry)\n");
    scanf(" %s",constraint);

    columns constraintVal;
    int attributePos;
    int selectAll = (strcmp(constraint, "*") == 0); 

    if(selectAll == 0) {
        attributePos = attributeNum(change_to_uppercase(constraint));
        if(attributePos == -1) {
            header();
            printf("\nNo such attribute in database!\n");
            backToDashboard();
            return;
        }
        printf("\nEnter value for constraint\n");
        scanData(attributePos, &constraintVal);
    }
    Table* temp = (Table*)malloc(sizeof(Table));
    temp->file = (FILE*)malloc(sizeof(FILE));
    temp->file = fopen("temp", "w+");
    writeHeaders(temp);

    char updateAttr[50];
    columns updatedVal;
    int attrPos;
    printf("\nOn which attribute, do you want to perform the update operation\n");
    scanf(" %s",updateAttr);

    attrPos = attributeNum(change_to_uppercase(updateAttr));
    if(attrPos == -1) {
        header();
        printf("\nNo such attribute in database!\n");
        backToDashboard();
        return;
    }
    printf("\nEnter the new updated value for %s \n",updateAttr);
    scanData(attrPos, &updatedVal);

    int updated = 0;
    columns entry[cols];
    moveToData(table);
    for(int i = 0; i < rows; i++) {
        fread(&entry,sizeof(columns),cols,table->file);
        if(selectAll == 1 || isDataEqual(attributePos, &entry[attributePos], &constraintVal) == 1) {
            updateEntry(attrPos,&entry[attrPos], &updatedVal);
	    updated++;
        }
        fwrite(&entry, sizeof(columns),cols, temp->file);
    }
    char* command1 = (char*)malloc(100);
    strcpy(command1, "mv ");
    strcat(command1,"temp ");
    strcat(command1,dbName);
    system(command1);

    table->file = temp->file;
    free(temp);
    header();
    if(updated == 0) {
        printf("\nNo Data Found with this constraint!\n");
    }
    else{
        printf("\nData updated Successfully!\n");
    }
    backToDashboard();
}



