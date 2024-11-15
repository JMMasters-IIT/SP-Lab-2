#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "readfile.h"
#include "workerfunctions.h"

Employee employees[MAXEMPLOYEES];
int employee_count = 0;

void clear_input() { //used to prevent add_emp overflow from first name to last name if there's a space
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void sort_db_by_id() { //Function to sort the db by ID
    for (int i = 0; i < employee_count - 1; i++) {
        for (int j = i + 1; j < employee_count; j++) {
            if (employees[i].id > employees[j].id) {
                Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
}

void load_data(const char *filename){
    if (open_file(filename) == -1) {
        printf("Error: Could not open file %s.\n", filename);
        return;
    }
    Employee temp;
    while (read_int(&temp.id) == 0 &&
           read_string(temp.first_name, MAXNAME) == 0 &&
           read_string(temp.last_name, MAXNAME) == 0 &&
           read_float(&temp.salary) == 0) {

        if (temp.id < 100000 || temp.id > 999999 || temp.salary < 30000 || temp.salary > 150000) {
            printf("Skipping invalid entry: ID=%d, Name=%s %s, Salary=%.0f\n", temp.id, temp.first_name, temp.last_name, temp.salary);
            continue;
        }
        employees[employee_count++] = temp;
        if (employee_count >= MAXEMPLOYEES) {
            printf("Database full; cannot load more employees.\n");
            break;
        }
    }
    close_file();
    sort_db_by_id();
}

void print_db() { //prints the database and count of people
    printf("\n%-15s %-15s %-10s %-10s\n", "First Name", "Last Name", "Salary", "ID");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < employee_count; i++) {
        printf("%-15s %-15s $%-9.0f %-10d\n", 
               employees[i].first_name, employees[i].last_name,
               employees[i].salary, employees[i].id);
    }
    printf("---------------------------------------------------\n");
    printf("Total number of employees: %d\n\n", employee_count); //print number of people in db
}

void lookup_by_id() { //function to lookup a person by their ID
    int id;
    printf("Enter ID to lookup: ");
    scanf("%d", &id);
    //For loop for linear search through db
    for (int i = 0; i < employee_count; i++) {
        if (employees[i].id == id) { //Compare input to each value in db to find a match
            printf("Employee Found: ID: %06d, Name: %s %s, Salary: $%.2f\n", 
                   employees[i].id, employees[i].first_name, 
                   employees[i].last_name, employees[i].salary);
            return;
        }
    }
    printf("Employee with ID %06d not found.\n", id); 
}

void remove_employee() { //Function to remove an employee based on the ID
    int id;
    printf("Enter the ID of the employee you'd like to remove: \n");
    scanf("%d", &id);
    //For loop for linear search through db
    int index = -1; //Used to hold the index of the employee to be removed
    for (int i = 0; i < employee_count; i++) {
        if (employees[i].id == id) { //Compare input to each value in db to find a match
            index = i; //Store index 
            printf("Employee Found: ID: %06d, Name: %s %s, Salary: $%.2f\n", 
                   employees[i].id, employees[i].first_name, 
                   employees[i].last_name, employees[i].salary);
            break;
        }
    }
    if (index==-1){
        printf("Employee %06d not found\n", id);
        return;
    }

    int confirm;
    printf("Are you sure you want to remove this employee? ");
    printf("Enter 1 for yes, 0 for no: ");
    scanf("%d", &confirm);

    if (confirm != 1) {
        printf("Employee was not removed from the db\n");
    }

    for (int i = index; i < employee_count - 1; i++) {
        employees[i] = employees[i + 1];
    }

    employee_count--; //Decrease employee count
    printf("Employee %06d has been removed from the database.\n", id);
}

void salary_between() { //Find all employees between two salaries
    int min;
    int max;
    printf("This function allows you to search for all employees within a salary range.\n");
    do{
        printf("Please enter the minimum salary: \n");
        scanf("%d", &min);
        printf("Please enter the maximum salary: \n");
        scanf("%d", &max);
        if(min > max){
            printf("Error: The minimum salary cannot be greater than the maximum salary.\n");
        }
        if(min < 30000){
            printf("Error: No employees in this database make less than $30,000. Please enter a higher number for the minimum.\n");
        }
        if(max < 30000){
            printf("Error: No employees in this database make less than $30,000. Please enter a higher number for the maximum.\n");
        }
    } while (min > max || min < 30000 || max < 30000);
    
    printf("Employees found: ");
    printf("\n%-15s %-15s %-10s %-10s\n", "First Name", "Last Name", "Salary", "ID");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < employee_count; i++) {
        if (employees[i].salary >= min && employees[i].salary <= max) { //Compare input to each value in db to find matches
            printf("%-15s %-15s $%-9.0f %-10d\n", 
               employees[i].first_name, employees[i].last_name,
               employees[i].salary, employees[i].id);
        }
    }
    printf("---------------------------------------------------\n");
}

void lookup_by_last() { //Function to lookup by last name, it is case sensitive
    char last_name[MAXNAME];
    printf("Enter the employee's last name: ");
    scanf("%s", last_name);
    //For loop for linear search through db
    for (int i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].last_name, last_name) == 0) { //Compare input to each name in db to find a match
            printf("Employee Found: ID: %06d, Name: %s %s, Salary: $%.2f\n", 
                   employees[i].id, employees[i].first_name, 
                   employees[i].last_name, employees[i].salary);
            return;
        }
    }
    printf("Employee with last name %s not found.\n", last_name);
}

int nextID() { //Used in add_emp(). Checks for the highest ID currently in the db and increments by 1 for new ID
    int max_id = 100000;  //start at lowest possible ID
    for (int i = 0; i < employee_count; i++) {
        if (employees[i].id > max_id) {
            max_id = employees[i].id;
        }
    }
    //If 999999 is reached, then return -1
    if (max_id >= 999999) {
        return -1;
    }
    return max_id + 1;  //Return highest ID+1 for new ID
}

void update_employee() {//Function to update any variable of an employee
    int id;
    printf("Enter the ID of the employee you'd like to update: ");
    scanf("%d", &id);
    //For loop for linear search through db
    int index = -1; //used to hold the index of the employee to be updated
    for (int i = 0; i < employee_count; i++) {
        if (employees[i].id == id) { //Compare input to each value in db to find a match
            index = i; //store index 
            printf("Employee Found: ID: %06d, Name: %s %s, Salary: $%.2f\n", 
                   employees[i].id, employees[i].first_name, 
                   employees[i].last_name, employees[i].salary);
            break;
        }
    }
    if (index==-1){
        printf("Employee %06d not found\n", id);
        return;
    }

    int update_choice;
    do {
        printf("Employee update menu: \n");
        printf("1. Update employee ID: \n");
        printf("2. Update employee first name: \n");
        printf("3. Update employee last name: \n");
        printf("4. Update employee salary: \n");
        printf("5. Return to main menu. \n");
        printf("Enter your choice: ");
        scanf("%d", &update_choice);

        if (update_choice == 1){
            int new_id;
            bool valid_id = false;
            
            do { //CHeck that new ID is in range
                printf("Enter new employee ID (100000 - 999999): ");
                scanf("%d", &new_id);

                if (new_id < 100000 || new_id > 999999) {
                    printf("Error: Employee ID must be between 100000 and 999999.\n");
                } 
                else { //Check if the new ID already exists
                    bool id_exists = false;
                    for (int i = 0; i < employee_count; i++) {
                        if (i != index && employees[i].id == new_id) {
                            id_exists = true;
                            break;
                        }
                    }

                    if (id_exists) {
                        printf("Error: An employee with ID %06d already exists.\n", new_id);
                    } 
                    else {
                        valid_id = true; //The ID is valid if it’s within range and unique
                    }
                }
            } while (!valid_id);

            //Update the employee ID after successful validation
            employees[index].id = new_id;
            printf("Employee ID updated.\n");

            //Sort the database after ID update to maintain order
            sort_db_by_id();
        }
        else if (update_choice == 2){
            char new_first_name[MAXNAME];
            bool valid_name = false;
            do {
                printf("Enter new first name for employee: ");
                scanf("%63s", new_first_name);
                clear_input(); //Clear any extra input left

                if (strchr(new_first_name, ' ') != NULL) {
                    printf("Error: First name cannot contain spaces.\n");
                } 
                else {
                    valid_name = true;
                    strcpy(employees[index].first_name, new_first_name);
                    printf("First name updated.\n");
                }
            } while (!valid_name);
        }
        else if (update_choice == 3){
            char new_last_name[MAXNAME];
            bool valid_name = false;
            do {
                printf("Enter new last name for employee: ");
                scanf("%63s", new_last_name);
                clear_input(); //Clear any extra input left

                if (strchr(new_last_name, ' ') != NULL) {
                    printf("Error: Last name cannot contain spaces.\n");
                } 
                else {
                    valid_name = true;
                    strcpy(employees[index].last_name, new_last_name);
                    printf("Last name updated.\n");
                }
            } while (!valid_name);
        }
        else if (update_choice == 4){
            int new_salary;
            do{
                printf("Enter the employee's new salary (30000 to 150000): ");
                scanf("%d", &new_salary);

                if (new_salary < 30000 || new_salary > 150000) {
                    printf("Please enter a number between 30,000 and 150,000.\n");
                } 
                else {
                    employees[index].salary = new_salary;
                    printf("Salary updated.\n");
                }
            }while (new_salary < 30000 || new_salary > 150000);
        } 
        else if (update_choice == 5){
            break;
        }
        else{
            printf("That's not right. Please try again...\n");
        }
    } while (update_choice != 5);
}

void print_highest_salaries() {
    int m;

    while (1) {
        printf("Enter the number of top salaries to display: ");
        scanf("%d", &m);

        if (m <= 0) { //Check that m is a positive number
            printf("That's not right. Please enter a positive number.\n"); //Error if it's negative
            clear_input(); //Clear the input
        } 
        else {
            if (getchar() != '\n') {
                printf("That's not right. Please enter a positive number.\n"); //Error if it's a string
                clear_input(); //Clear the input
            } 
            else {
                break; //Input is okay, continue
            }
        }
    }

    if (m > employee_count) { //If they request more than what's in the db, it limits it to the number in db
        m = employee_count;
    }

    Employee temp_salary[m]; //Temp array to hold values
    int temp_count = 0; //Tracks the number of employees in the temp_salary array

    for (int i = 0; i < employee_count; i++) {
        Employee current = employees[i];

        if (temp_count < m) { //If no one is in the temp, then add directly (can't compare against nothing)
            temp_salary[temp_count++] = current;
        } 
        else {
            int min_salary = 0; //Holds index of whomever has the lowest salary in temp array
            for (int j = 1; j < m; j++) {
                if (temp_salary[j].salary < temp_salary[min_salary].salary) {
                    min_salary = j;
                }
            }

            //If current employee's salary is higher than the lowest in temp_salary, replace it
            if (current.salary > temp_salary[min_salary].salary) {
                temp_salary[min_salary] = current;
            }
        }
    }

    //Sort temp_salary by salary in descending order
    for (int i = 0; i < temp_count - 1; i++) {
        for (int j = i + 1; j < temp_count; j++) {
            if (temp_salary[i].salary < temp_salary[j].salary) {
                Employee temp = temp_salary[i];
                temp_salary[i] = temp_salary[j];
                temp_salary[j] = temp;
            }
        }
    }

    //Print the top M employees by salary
    printf("\nTop %d Employees by Salary:\n", m);
    printf("%-15s %-15s %-10s %-10s\n", "First Name", "Last Name", "Salary", "ID");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < temp_count; i++) {
        printf("%-15s %-15s $%-9.0f %-10d\n", 
               temp_salary[i].first_name, temp_salary[i].last_name,
               temp_salary[i].salary, temp_salary[i].id);
    }
    printf("---------------------------------------------------\n");
}

void add_employee() { //Function to add an employee, validates inputs, asks for confirmation
    if (employee_count >= MAXEMPLOYEES) {
        printf("Unfortunately no more employees can be added to the database.\n");
        return;
    }
    Employee new_employee;
    int next_ID = nextID();
    if (next_ID == -1) { //If we are already at the highest ID then we can't add any new employees
        printf("Cannot add more employees. Maximum employee ID (999999) reached.\n");
        return;
    }
    new_employee.id = next_ID;

    do {
        printf("Enter the first name of the employee: ");
        scanf("%63s", new_employee.first_name);
        clear_input(); //Clear any extra input left
        //This will ignore any spaces in the name and only capture what comes before the space
    } while (strchr(new_employee.first_name, ' ') != NULL);

    do {
        printf("Enter the last name of the employee: ");
        scanf("%63s", new_employee.last_name);
        clear_input(); //Clear any extra input left
        //This will ignore any spaces in the name and only capture what comes before the space
    } while (strchr(new_employee.last_name, ' ') != NULL);

    do {
        printf("Enter employee's salary (30000 to 150000): ");
        scanf("%f", &new_employee.salary);
        if (new_employee.salary != (int)new_employee.salary || //Check that salary is a whole number and between 30000 and 150000
            new_employee.salary < 30000 || new_employee.salary > 150000) {
            printf("Please enter a number between 30,000 and 150,000.\n"); 
        }
    } while (new_employee.salary != (int)new_employee.salary || 
             new_employee.salary < 30000 || new_employee.salary > 150000);

    int confirm;
    //Print out employee to ask if they're sure they want to add them
    printf("\nDo you want to add the following employee to the DB?\n");
    printf("%s %s, Salary: $%.0f\n", new_employee.first_name, new_employee.last_name, new_employee.salary);
    printf("Enter 1 for yes, 0 for no: ");
    scanf("%d", &confirm);

    //Depending on choice it will either add employee to the end of the db or print out they weren't added
    if (confirm == 1) {
        employees[employee_count++] = new_employee;
    } 
    else {
        printf("Employee was not added to the db\n");
    }
}