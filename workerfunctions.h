#ifndef WORKERFUNCTIONS_H
#define WORKERFUNCTIONS_H

#include <stdbool.h>

#define MAXEMPLOYEES 1024
#define MAXNAME 64

// Define the Employee struct
typedef struct {
    int id;
    char first_name[MAXNAME];
    char last_name[MAXNAME];
    float salary;
} Employee;

// Declare the employees array and employee_count as extern
extern Employee employees[MAXEMPLOYEES];
extern int employee_count;

// Function prototypes
void clear_input();
void sort_db_by_id();
void load_data(const char *filename);
void print_db();
void lookup_by_id();
void lookup_by_last();
void add_employee();
int nextID();
void remove_employee();
void salary_between();
void update_employee();
void print_highest_salaries();

#endif // WORKERFUNCTIONS_H