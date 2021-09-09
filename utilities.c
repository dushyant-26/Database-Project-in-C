#include <stdio.h>
#include<stdlib.h>
#include<string.h>

//Global variables for structure information of table.
int cols;
int rows;
int* datatype;
char** c_name;
char* dbName;

//union for storing different types of data
typedef union data {
    int integer;
    char character;
    char string[50];
    double decimal;
} columns;

//structure containing FILE*
typedef struct table {
    FILE* file;
} Table;

//copies the string from src into dest.
//params:
//char* dest: the string where src is copied 
//char* src: the string which is copied
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

//updates the input param with the updatedVal
//params:
//int pos: attribute number
//columns* input: input entry which need to be updated
//columns* updatedVal: copies data of updatedVal into input
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

//returns datatype of the attributes.
//params:
//int pos:position of given attribute
//return char*: datatype of attribute
char* getDatatype(int pos) {
    char* str = (char*)malloc(10);
    switch(datatype[pos]) {
        case 0:
	    copyString(str,"INTEGER");
	    break;
	case 1:
	    copyString(str,"CHARACTER");
	    break;
	case 2:
	    copyString(str,"STRING");
	    break;
	case 3:
	    copyString(str,"DOUBLE");
	    break;
        default:
	    printf("ERROR\n");
	    exit(1);
    }
    return str;
}

//change the string to uppercase
//params:
//char* str: input string
//returns char*: updated string
char* change_to_uppercase(char* str) {
    for (int i = 0; str[i]!='\0'; i++) {
        if(str[i] >= 'a' && str[i] <= 'z') {
           str[i] = str[i] -32;
        }
    }
    return str;
}

//prints the table structure data into table->file
//params:
//Table* table: pointer to structure containing the file.
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

//prompts the user to return to dashboard or exit the database
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

//checks if secondVal is present at start of firstVal.
//params:
//char* firstVal: given string
//char* secondVal: the string which we need to check at start of first string
//return int: return 1,if secondVal present at start of firstVal else return 0.
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

//checks whether given string is integer or not.
int isInteger(char* input) {
    for(int i = 0; input[i] != '\0'; i++) {
        if(input[i] < 48 || input[i] > 57) {
            return 0;
        }
    }
    return 1;
}

//checks whether given string is a character or not.
int isCharacter(char* input) {
    if(strlen(input) == 1) {
        return 1;
    }
    return 0;
}

//checks whether given string is double or not
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

//convert given string to integer
int convert_to_int(char* input) {
    int result = 0;
    for(int i = 0; input[i] != '\0'; i++) {
        result = result * 10 + (input[i] - 48);
    }
    return result;
}

//convert given string to double
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

//format the data while printing
void format(void* str) {
    if(strlen((char*)str) < 8) {
        printf("\t");
    }
}

//return the attribute number corresponding to given attribute name
int attributeNum(char* constraint) {
    for(int i = 0; i < cols; i++) {
        if(strcmp(c_name[i],constraint) == 0) {
            return i;
        }
    }
    return -1;
}

//take input from the user
//params:
//int pos: attribute number of attribute to be scanned.
//columns* input: union variable in which data is scanned. 
//return int:return -1,if scanned data is not of required datatype, else return 0.
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
		change_to_uppercase(val);
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

//prints the data on the screen
//params:
//int pos: attribute number of attribute to be scanned.
//columns* input: data which need to be printed. 
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
                    break;
    }
}

//checks whether data of both the given union variables is equal or not.
//params:
//int pos: attribute number of attribute to be scanned.
//columns* firstVal: first data input.
//columns* secondVal: second data input.
//return int: return 1, if equal else return 0. 
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

//updates the number of rows in table 
void updateRow(Table* table) {
    int temp;
    rewind(table->file);
    fscanf(table->file, "%d\t", &temp);
    fprintf(table->file, "%d",rows);
}

//move the file pointer to the data entries i.e ahead of table structure data.
void moveToData(Table* table) {
    char temp[100];
    rewind(table->file);
    fgets(temp,100,table->file);
    fgets(temp,100,table->file);
    fgets(temp,100,table->file);
}

