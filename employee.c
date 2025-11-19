#include "employee.h"
#include <string.h>
#include <stdio.h>

static Employee employees[MAX_EMPLOYEES];
static int employeeCount = 0;
static int nextId = 1;

// Initialize the employee system
void initEmployeeSystem(void) {
    employeeCount = 0;
    nextId = 1;
}

// Add a new employee
int addEmployee(const char* name, const char* position, float salary) {
    // Check if we have space for more employees
    if (employeeCount >= MAX_EMPLOYEES) {
        return 0;
    }

    // Create new employee
    employees[employeeCount].id = nextId;
    strncpy(employees[employeeCount].name, name, 49);
    employees[employeeCount].name[49] = '\0'; // Make sure string ends
    strncpy(employees[employeeCount].position, position, 49);
    employees[employeeCount].position[49] = '\0';
    employees[employeeCount].salary = salary;

    // Increase counters
    employeeCount++;
    nextId++;

    return 1; // Success
}

// Get total number of employees
int getEmployeeCount(void) {
    return employeeCount;
}

// Get employee at specific index
Employee* getEmployee(int index) {
    if (index < 0 || index >= employeeCount) {
        return NULL; // Invalid index
    }
    return &employees[index];
}

// Clear all employees
void clearAllEmployees(void) {
    employeeCount = 0;
    nextId = 1;
}
