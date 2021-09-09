#include "createOperations.h"
#include "readOperations.h"
#include "updateOperations.h"
#include "deleteOperations.h"

void databaseHeader() {
    system("clear");
    printf("==============================================================================================================================\n");
    printf("      *******************************************[ Welcome to your Database]********************************************      \n");
    printf("==============================================================================================================================\n");
}

void dashboard(Table* table) {
    while(1) {
        int choice = 0;
        int num = 0;

        databaseHeader();

        printf("\nWhich operation do you want to do?\n");
        printf("1. Insert operation\n");
        printf("2. Read operation\n");
        printf("3. Delete operation\n");
        printf("4. Truncate operation\n");
        printf("5. Update operation\n");
	printf("6. Read table structure\n");
	printf("7. Delete the table(WARNING: This will make database loose all the data)\n");
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
	    case 6:
		readTableStructure(table);
		break;
	    case 7:
		deleteTable(table);
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
