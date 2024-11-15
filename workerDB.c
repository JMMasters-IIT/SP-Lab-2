#include <stdio.h>
#include "readfile.h"
#include "workerfunctions.h"

//Jack Miller 11.13.2024
//This program is designed to input a file from the command line when it's run
//and build a database with the data from the input file. It will skip any entry that has a space
//in the first or last name field, and skip any line that has a salary <30000 and >150000.
//It can read out and count the number of entries it imported. Search for someone based on ID.
//Search for someone based on the last name. And, finally, it will add an entry into the db
//by prompting the user for the first name, last name, and salary and perform the same data validation
//techniques mentioned above. It will then auto assign an ID based on the highest ID number
//in the db and increment by 1 from there for each additional entry.
//Added function to allow updating any value of an employee.
//Added function to allow removing any employee
//Added function to find salaries between two values (must be between 30000 and 150000)
//Added function to find the M highest salaries where M is the input from the user



int main(int argc, char *argv[]) { //Main function for displaying options
    if (argc != 2) {
        printf("Usage: %s <employee_data_file>\n", argv[0]);
        return 1;
    }
    load_data(argv[1]); //Load data from file passed as command line argument

    int choice;
    do {
        printf("\nEmployee Database Menu\n"); //Print menu of options
        printf("1. Print the Database\n");
        printf("2. Lookup employee by ID\n");
        printf("3. Lookup employee by last name\n");
        printf("4. Add an employee\n");
        printf("5. Remove an employee\n");
        printf("6. Update an employee\n");
        printf("7. Print highest salaries\n");
        printf("8. Find employees between a range of salaries\n");
        printf("9. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (getchar() != '\n') {
                printf("That's not right. Please try again...\n"); //Error if it's a string
                clear_input(); //Clear the input
                continue;
        }

        if (choice == 1) {
            print_db();
        }
        else if (choice == 2){
            lookup_by_id();
        }
        else if (choice == 3){
            lookup_by_last();
        }
        else if (choice == 4){
            add_employee();
        }
        else if (choice == 5){
            remove_employee();            
        }
        else if (choice == 6){
            update_employee();
        }
        else if (choice == 7){
            print_highest_salaries();
        }
        else if (choice == 8){
            salary_between();
        }
        else if (choice == 9){
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("That's not right. Please try again...\n"); 
        }
    } while (choice != 9);

    return 0;
}
