#include "updateOperations.h"

void updateEntry(int pos,columns* input,columns* updatedVal) {
    switch(datatype[pos]) {
            case 0:
                input->integer = updatedVal->integer;
                break;
            case 1:
                input->character = updatedVal->character;
                break;
            case 2:
                copyString(input->string,updatedVal->string);
                break;
            case 3:
                input->decimal = updatedVal->decimal;
                break;
    }
}

void updateData(Table* table) {
    header();
    if(rows == 0) {
        printf("\nDatabase Empty!\n");
        backToDashboard();
        return;
    }
    char constraint[50];
    printf("\n On the basis of which constraint, do you want to update the entries(Enter * for updating each entry)\n");
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
        printf("Enter value for constraint\n");
        scanData(attributePos, &constraintVal);
    }
    Table* temp = (Table*)malloc(sizeof(Table));
    temp->file = (FILE*)malloc(sizeof(FILE));
    temp->file = fopen("temp", "w+");
    writeHeaders(temp);

    char updateAttr[50];
    columns updatedVal;
    int attrPos;
    printf("\n On which attribute, do you want to perform the update operation\n");
    scanf(" %s",updateAttr);

    attrPos = attributeNum(change_to_uppercase(updateAttr));
    if(attrPos == -1) {
        header();
        printf("\nNo such attribute in database!\n");
        backToDashboard();
        return;
    }
    printf("Enter the new updated value for %s \n",updateAttr);
    scanData(attrPos, &updatedVal);

    columns entry[cols];
    moveToData(table);
    for(int i = 0; i < rows; i++) {
        fread(&entry,sizeof(columns),cols,table->file);
        if(isDataEqual(attributePos, &entry[attributePos], &constraintVal) == 1) {
            updateEntry(attrPos,&entry[attrPos], &updatedVal);
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
    printf("\nData updated Successfully!\n");
    backToDashboard();
}



