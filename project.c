#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int cols;
int rows;
int* datatype;
char** c_name;
char* dbName;

typedef union data {
    int integer;
    char character;
    char string[50];
    double decimal;
} columns;

typedef struct table {
    FILE* file;
} Table;

void header() {
    system("clear");
    printf("==============================================================================================================================\n");
    printf("      *******************************************[ Welcome to your Database]********************************************      \n");
    printf("==============================================================================================================================\n");
}

void copyString(char* dest, char* src) {
    if(src[0] >= 97 && src[0] <= 122) {
        src[0] -= 32;
    }
    int i;
    for(i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

char* change_to_uppercase(char* str) {
    for (int i = 0; str[i]!='\0'; i++) {
        if(str[i] >= 'a' && str[i] <= 'z') {
           str[i] = str[i] -32;
        }
    }
    return str;
}

int isStringPresentAtStart(char* firstVal, char* secondVal) {
    if(strlen(secondVal) > strlen(firstVal)) {
        return 0;
    }
    char string[50];
    copyString(string,firstVal);
    change_to_uppercase(string);
    change_to_uppercase(secondVal);

    for(int i = 0; secondVal[i] != '\0'; i++) {
        if(secondVal[i] != string[i]) {
	    return 0;
	}
    }
    return 1;
}

int isInteger(char* input) {
    for(int i = 0; input[i] != '\0'; i++) {
        if(input[i] < 48 || input[i] > 57) {
	    return 0;
	}
    }
    return 1;
}

int isCharacter(char* input) {
    if(strlen(input) == 1) {
        return 1;
    }
    return 0;
}

int isDouble(char* input) {
    for(int i = 0; input[i] != '\0'; i++) {
	if(input[i] == '.' && input[i + 1] != '\0') {
	    continue;
	}
        if(input[i] < 48 || input[i] > 57) {
            return 0;
        }
    }
    return 1;
}

int convert_to_int(char* input) {
    int result = 0;
    for(int i = 0; input[i] != '\0'; i++) {
        result = result * 10 + (input[i] - 48);
    }
    return result;
}

double convert_to_double(char* input) {
    int result = 0;
    int decimalPos = -1;
    for(int i = 0; input[i] != '\0'; i++) {
	if(input[i] == '.') {
	    decimalPos = i;
	    continue;
	}
        result = result * 10 + (input[i] - 48);
    }

    if(decimalPos == -1) {
        return result;
    }
    int len = strlen(input);

    int decimal = 1;
    for(int i = 0; i < len - decimalPos - 1; i++) {
        decimal *= 10;
    }
    return (result * 1.0 / decimal);
}

void backToDashboard() {
    printf("\nPress 1 to return to dashboard or 0 to exit\n");
    int temp;
    scanf("%d",&temp);
    if(temp == 0) {
	system("clear");
        exit(1);
    }
}

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

void format(void* str) {
    if(strlen((char*)str) < 8) {
        printf("\t");
    }
}

int attributeNum(char* constraint) {
    for(int i = 0; i < cols; i++) {
        if(strcmp(c_name[i],constraint) == 0) {
	    return i;
	}
    }
    return -1;
}

int scanData(int pos, columns* input) {
    char val[100];
    scanf(" %[^\n]s",val);
    header(); 
    switch(datatype[pos]) {
            case 0:
		if(isInteger(val) == 0) {
		    printf("\nInvalid Data(Expected INTEGER)\n");
		    return -1;
		}
		input->integer = convert_to_int(val);
                break;
            case 1:
		if(isCharacter(val) == 0) {
		    printf("\nInvalid Data(Expected CHARACTER)\n");
		    return -1;
		}
		input->character = val[0];
                break;
            case 2:
		copyString(input->string,val);
                break;
            case 3:
		if(isDouble(val) == 0) {
		    printf("\nInvalid Data(Expected Double)\n");
		    return -1;
		}
		input->decimal = convert_to_double(val);
                break;
    }
    return 1;
}

void printData(int pos, columns* input) {
    switch(datatype[pos]) {
                case 0:
                    printf("%d\t",input->integer);
                    format((void*)(&input->integer));
                    break;
                case 1:
                    printf("%c\t",input->character);
                    format((void*)(&input->character));
                    break;
                case 2:
                    printf("%s\t",input->string);
                    format((void*)(input->string));
                    break;
                case 3:
                    printf("%lf\t",input->decimal);
                    format((void*)(&input->decimal));
                    break;
    }
}

int isDataEqual(int pos, columns* firstVal, columns* secondVal) {
    char string[50];
    switch(datatype[pos]) {
            case 0:
                return (firstVal->integer == secondVal->integer);
            case 1:
                return (firstVal->character == secondVal->character);                
	    case 2:
		copyString(string,firstVal->string);
		change_to_uppercase(string);
		change_to_uppercase(secondVal->string);
                return (strcmp(string,secondVal->string) == 0);
            case 3:
                return (firstVal->decimal == secondVal->decimal);
    }
}

void writeHeaders(Table* table) {
    fprintf(table->file, "%d\t%d    \n",cols,rows);
    for(int i = 0; i < cols - 1; i++) {
        fprintf(table->file, "%d\t", datatype[i]);
    }
    fprintf(table->file, "%d\n",datatype[cols-1]);

    for(int i = 0; i < cols - 1; i++) {
        fprintf(table->file,"%s\t", change_to_uppercase(c_name[i]));
    }
    fprintf(table->file, "%s\n",change_to_uppercase(c_name[cols-1]));
}


void updateRow(Table* table) {
    int temp;	
    rewind(table->file);
    fscanf(table->file, "%d\t", &temp);
    fprintf(table->file, "%d",rows);
}

void moveToData(Table* table) {
    char temp[100];
    rewind(table->file);
    fgets(temp,100,table->file);
    fgets(temp,100,table->file);
    fgets(temp,100,table->file);
}

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
        for(int j = 0; j < cols; j++) {
            printData(j, &entry[j]);
        }
        printf("\n");
    }
    backToDashboard();
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
    printf("\n On the basis of which constraint, do you want to delete the entries(Enter * for deleting each entry)\n");
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
    printf("\nData deleted Successfully!\n");
    backToDashboard();
}

void dashboard(Table* table) {
    while(1) {
        int choice = 0;
        int num = 0;

        header();
    
        printf("\nWhich operation do you want to do?\n");
        printf("1. Insert operation\n");
        printf("2. Read operation\n");
        printf("3. Delete operation\n");
        printf("4. Truncate operation\n");
	printf("5. Update operation\n");
        printf("Enter any other key to exit the Program\n\n");

        scanf("%d",&choice);

        switch(choice) {
            case 1:
                insertData(table);               
 		break;
            case 2:
                readData(table);
                break;
            case 3:
                deleteData(table);
                break;
            case 4:
                truncate(table);
                break;
	    case 5:
		updateData(table);
		break;
            default:
		system("clear");
                exit(1);
        }
    }

}

int main() {
    system("clear");
    Table* table = openTable();

    dashboard(table);
}

