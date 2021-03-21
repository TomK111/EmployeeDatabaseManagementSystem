#include <iostream>
#include "employee/employee.h"

void entry_menu(){
    char ch;
    int num;
    Employee employee;
    std::cout << "\n\n\n\t\t\tEMPLOYEE DATABASE MANAGEMENT SYSTEM MENU";
    std::cout<<"\n\n\n\t\t\t\t1. CREATE EMPLOYEE RECORD";
    std::cout<<"\n\n\n\t\t\t\t2. SHOW RECORDS OF ALL EMPLOYEES";
    std::cout<<"\n\n\n\t\t\t\t3. SEARCH EMPLOYEE RECORD";
    std::cout<<"\n\n\n\t\t\t\t4. UPDATE EMPLOYEE RECORD";
    std::cout<<"\n\n\n\t\t\t\t5. DELETE EMPLOYEE RECORD";
    std::cout<<"\n\n\n\t\t\t\t6. EXIT";
    std::cout<<"\n\n\n\n\t\t\tPlease Enter Your Choice (1-6):  ";
    std::cin >>ch;
    switch(ch){
        case '1':
            employee.write_employee_record_in_file();
            break;
        case '2':
            display_all();
            break;
        case '3':
            std::cout << "\n\n\t Please enter the employee identification number: ";
            std::cin >> num;
            employee.show_employee_record(num);
            break;
        case '4':
            std::cout << "\n\n\t Please enter the employee identification number: ";
            std::cin >> num;
            employee.update_employee_record(num);
        case '5':
            std::cout << "\n\n\t Please enter the employee identification number: ";
            std::cin >> num;
            employee.delete_employee_record(num);
            break;
        case '6':
            exit(0);
            break;
        default:
            std::cout << "\a";entry_menu();
            break;
    }
}
int main() {

    return 0;
}
