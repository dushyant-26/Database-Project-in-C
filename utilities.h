#ifndef utilities
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern int cols;
extern int rows;
extern int* datatype;
extern char** c_name;
extern char* dbName;

typedef union data {
    int integer;
    char character;
    char string[50];
    double decimal;
} columns;

typedef struct table {
    FILE* file;
} Table;
void copyString(char* dest, char* src);
char* change_to_uppercase(char* str);
int isStringPresentAtStart(char* firstVal, char* secondVal);
int isInteger(char* input);
int isCharacter(char* input);
int isDouble(char* input);
int convert_to_int(char* input);
double convert_to_double(char* input);
void format(void* str);
int attributeNum(char* constraint);
int scanData(int pos, columns* input);
void printData(int pos, columns* input);
int isDataEqual(int pos, columns* firstVal, columns* secondVal);
void updateRow(Table* table);
void header();
void writeHeaders(Table* table);
void backToDashboard();
void moveToData(Table* table);
char* getDatatype(int pos);

#define utilities
#endif
