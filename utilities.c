#include "utilities.h"

char* change_to_uppercase(char* str) {
    for (int i = 0; str[i]!='\0'; i++) {
        if(str[i] >= 'a' && str[i] <= 'z') {
           str[i] = str[i] -32;
        }
    }
    return str;
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

void backToDashboard() {
    printf("\nPress 1 to return to dashboard or 0 to exit\n");
    int temp;
    scanf("%d",&temp);
    if(temp == 0) {
        system("clear");
        exit(1);
    }
}

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

