#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED
#define MAX_EMPLOYEES 100

typedef struct {
    int id;
    char name[50];
    char position[50];
    float salary;
} Employee;

void initEmployeeSystem(void);

int addEmployee(const char* name, const char* position, float salary);

int getEmployeeCount(void);

Employee* getEmployee(int index);

void clearAllEmployees(void);

#endif // EMPLOYEE_H_INCLUDED
