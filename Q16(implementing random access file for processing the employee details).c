#include <stdio.h>
#include <stdlib.h>
struct Employee {
    int id;
    char name[50];
    float salary;
};
void addEmployee(FILE *file);
void displayAllEmployees(FILE *file);
void updateEmployee(FILE *file);
void deleteEmployee(FILE *file);
int main() {
    FILE *employeeFile;
    int choice;
    employeeFile = fopen("employee.dat", "rb+");
    if (employeeFile == NULL) {
        employeeFile = fopen("employee.dat", "wb+");
    }
    if (employeeFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    do {
        printf("\nEmployee Database\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
   switch (choice) {
            case 1:
                addEmployee(employeeFile);
                break;
            case 2:
                displayAllEmployees(employeeFile);
                break;
            case 3:
                updateEmployee(employeeFile);
                break;
            case 4:
                deleteEmployee(employeeFile);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
       fclose(employeeFile);
    return 0;
}
void addEmployee(FILE *file) {
    struct Employee employee;
    fseek(file, 0, SEEK_END);
    printf("Enter employee ID: ");
    scanf("%d", &employee.id);
    printf("Enter employee name: ");
    scanf("%s", employee.name);
    printf("Enter employee salary: ");
    scanf("%f", &employee.salary);
    fwrite(&employee, sizeof(struct Employee), 1, file);
    printf("Employee added successfully.\n");
}
void displayAllEmployees(FILE *file) {
    struct Employee employee;
    fseek(file, 0, SEEK_SET);
    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", employee.id, employee.name, employee.salary);
    }
}
void updateEmployee(FILE *file) {
    struct Employee employee;
    int targetID;
    printf("Enter the ID of the employee to update: ");
    scanf("%d", &targetID);
    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        if (employee.id == targetID) {
            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            printf("Enter new name: ");
            scanf("%s", employee.name);
            printf("Enter new salary: ");
            scanf("%f", &employee.salary);
       fwrite(&employee, sizeof(struct Employee), 1, file);

            printf("Employee updated successfully.\n");
            return;
        }
    }
    printf("Employee with ID %d not found.\n", targetID);
}
void deleteEmployee(FILE *file) {
    struct Employee employee, temp;
    int targetID;
    printf("Enter the ID of the employee to delete: ");
    scanf("%d", &targetID);
    FILE *tempFile = fopen("temp.dat", "wb");
    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        if (employee.id == targetID) {
            continue;
        }
        fwrite(&employee, sizeof(struct Employee), 1, tempFile);
    }
    fclose(file);
    fclose(tempFile);
    remove("employee.dat");
    rename("temp.dat", "employee.dat");
    file = fopen("employee.dat", "rb+");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("Employee with ID %d deleted successfully.\n", targetID);
}
