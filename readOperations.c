#include "readOperations.h"
void readData(Table* table) {
    header();
    if(rows == 0) {
        printf("\nDatabase Empty!\n");
        backToDashboard();
        return;
    }
    char constraint[50];
    printf("\nOn the basis of which constraint, do you want to read the entries(Enter * for reading each entry)\n");
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
    columns entry[cols];
    moveToData(table);

    header();
    printf("\n");
    for(int i = 0; i < cols; i++) {
        printf("%s\t",c_name[i]);
        format((void*)c_name[i]);
    }
    printf("\n");
    int numsPrinted = 0;
    for(int i = 0; i < rows; i++) {
        fread(&entry,sizeof(columns),cols,table->file);
        if(selectAll == 0) {
            if(datatype[attributePos] == 2) {
                if(isStringPresentAtStart(entry[attributePos].string,constraintVal.string) == 0) {
                    continue;
                }
            }
            else {
                if(isDataEqual(attributePos, &entry[attributePos], &constraintVal) == 0) {
                    continue;
                }
            }
        }
        printf("\n");
	numsPrinted++;
        for(int j = 0; j < cols; j++) {
            printData(j, &entry[j]);
        }
        printf("\n");
    }
    if(numsPrinted == 0) {
        header();
	printf("\nNo data found with this constraint!\n");
    }
    backToDashboard();
}

void readTableStructure(Table* table) {
    header();
    printf("\nDatabase Name - %s\n",dbName);
    printf("\nAttribute\t");
    printf("Datatype\n");
    for(int i = 0; i < cols; i++) {
        printf("\n%s\t",c_name[i]);
	format(c_name[i]);
	printf("%s\n",getDatatype(i));
    }
    backToDashboard();
}
