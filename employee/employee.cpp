//
// Created by tomislav on 3/21/21.
//

#include <fstream>
#include <iostream>
#include "employee.h"

int identification_number_to_be_updated = 0;

void Employee::get_data() {
    flag = false;
    std::cout << "\nEnter Employee Identification Number: ";
    std::cin >> identification_number_to_be_updated;
    if(identification_number_to_be_updated != identification_number)
        check_for_duplication_in_file();

    if(flag) {
        std::cout << "Error: Duplicate Record" << "\n";
        return;
    }

    std::cout << "\n\nEnter Employee Name: ";
    std::cin.ignore();
    std::cin.getline(employee_name, 50);

    std::cout << "\n\nEnter Employee Position: ";
    std::cin >> position;

    std::cout << "\nEnter Employee Department: ";
    std::cin >> department;

    std::cout << "\nEnter Employee Email: ";
    std::cin >> email;

    std::cout << "\nEnter Employee Phone Number: ";
    std::cin >> contact_number;
}

void display_all(){
    Employee employee;
    std::ifstream inFile;
    inFile.open("employee.dat", std::ios::binary);
    if(!inFile) {
        std::cout << "File could not be opened. Press any key to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::cout << "\n\n\n\t\tDISPLAY ALL RECORDS\n\n";
    while(inFile.read(reinterpret_cast<char *> (&employee), sizeof(Employee))){
        employee.show_data();
        std::cout << "\n\n====================================\n";
    }

    inFile.close();
    std::cin.ignore();
    std::cin.get();
}

void Employee::check_for_duplication_in_file() {
    int current_identification_number = 0;
    flag = false;
    std::ifstream infile("DuplicateCheckingFile.txt");
    while(!infile.eof()){
        infile>>current_identification_number;
        if(current_identification_number == identification_number){
            flag = true;
        }
    }
    infile.close();
    if(!flag) {
        std::ofstream outfile("DuplicateCheckingFile.txt", std::ios::app);
        outfile<<"\n"<<identification_number;
        outfile.close();
    }
}

void Employee::show_data() {
    std::cout << "Employee ID: " << identification_number;
    std::cout << "\nEmployee Name: " << employee_name;
    std::cout << "\nEmployee Email: " << email;
    std::cout << "\nEmployee Phone Number: " << contact_number;
    std::cout << "\nEmployee Department: " << department;
}

Employee::Employee() {
    std::ofstream outfile;
    outfile.open("employee.dat", std::ios::binary|std::ios::app);
    outfile.close();
    std::ofstream outDFile;
    outDFile.open("DuplicateCheckingFile.txt", std::ios::app);
    outDFile.close();
}

void Employee::write_employee_record_in_file() {
    std::ofstream outFile;
    outFile.open("student.dat", std::ios::binary|std::ios::app);

    get_data();

    if(!flag){
        outFile.write(reinterpret_cast<char *>(this), sizeof(Employee));
        outFile.close();
        std::cout << "\n\n Employee Record has been created.";
    }

    else {
        std::cout << "Record has not been created due to duplication.\n";
        outFile.close();
    }

    std::cin.ignore();
    std::cin.get();
}

void Employee::update_employee_record(int n) {
    identification_number_to_be_updated = n;
    bool found = false;
    std::fstream File;
    File.open("student.dat", std::ios::binary|std::ios::in|std::ios::out);
    if(!File) {
        std::cout << "File could not open. Press any key to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
}