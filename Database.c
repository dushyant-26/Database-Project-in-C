#include "utilities.h"
#include "createOperations.h"
#include "readOperations.h"
#include "updateOperations.h"
#include "deleteOperations.h"

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
