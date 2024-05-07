#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Employee structure
typedef struct {
    const char* name;
    const char* emp_id;
    const char* department;
} Employee;

// Define Manager structure
typedef struct {
    Employee super;
    Employee technician1;
    Employee technician2;
    int under;
} Manager;

// Define Technician structure
typedef struct {
    Employee super;
    const Employee* manager;
} Technician;

// Function to display employee information
void display_info(Employee* emp) {
    printf("Name: %s\n", emp->name);
    printf("Employee ID: %s\n", emp->emp_id);
    printf("Department: %s\n", emp->department);
}

// Function to display team information
void display_team_info(Manager* manager) {
    display_info(&manager->super);
    printf("Technicians under this manager:\n");
    display_info(&manager->technician1);
    printf("\n");
    display_info(&manager->technician2);
    printf("\n");
}

int main() {
    // Creating employees
    Manager manager1;
    manager1.super.name = "John Doe";
    manager1.super.emp_id = "M001";
    manager1.super.department = "Management";
    manager1.technician1.name = "";
    manager1.technician1.emp_id = "";
    manager1.technician1.department = "";
    manager1.technician2.name = "";
    manager1.technician2.emp_id = "";
    manager1.technician2.department = "";
    manager1.under = 0;

    Technician technician1;
    technician1.super.name = "Alice Smith";
    technician1.super.emp_id = "T001";
    technician1.super.department = "IT";
    technician1.manager = &manager1.super;

    Technician technician2;
    technician2.super.name = "Bob Johnson";
    technician2.super.emp_id = "T002";
    technician2.super.department = "IT";
    technician2.manager = &manager1.super;

    Manager manager2;
    manager2.super.name = "Jane Smith";
    manager2.super.emp_id = "M002";
    manager2.super.department = "HR";
    manager2.technician1.name = "";
    manager2.technician1.emp_id = "";
    manager2.technician1.department = "";
    manager2.technician2.name = "";
    manager2.technician2.emp_id = "";
    manager2.technician2.department = "";
    manager2.under = 0;

    Technician technician3;
    technician3.super.name = "Carol Williams";
    technician3.super.emp_id = "T003";
    technician3.super.department = "HR";
    technician3.manager = &manager2.super;

    // Adding technicians to managers
    manager1.technician1 = technician1.super;
    manager1.under = manager1.under + 1;
    manager1.technician2 = technician2.super;
    manager1.under = manager1.under + 1;

    manager2.technician1 = technician3.super;
    manager2.under = manager2.under + 1;

    // Displaying information
    display_team_info(&manager1);
    display_team_info(&manager2);

    return 0;
}
