#include <fstream>
#include <iostream>
#include "employee.h"

int identification_number_to_be_updated = 0;

void Employee::get_data() {
    flag = false;
    std::cout << "\nEnter Employee Identification Number: ";
    std::cin >> identification_number;
    if (identification_number_to_be_updated != identification_number) {
        check_for_duplication_in_file();
    }

    if (flag) {
        std::cout << "Error: Duplicate Record" << std::endl;
        return;
    }

    std::cout << "\n\nEnter Employee Name: ";
    std::cin.ignore();
    std::cin.getline(employee_name, 50);


    std::cout << "\n\nEnter Employee Position: ";
    std::cin >> position;

    std::cout << "\n\nEnter Employee Department: ";
    std::cin >> department;

    std::cout << "\n\nSalary: ";
    std::cin >> salary;

}

void display_all(){
    Employee em;
    std::ifstream inFile;
    inFile.open("employee.dat", std::ios::binary);
    if(!inFile) {
        std::cout << "File could not be opened. Press any key to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::cout << "\n\n\n\t\tDISPLAY ALL RECORDS\n\n";
    while(inFile.read(reinterpret_cast<char *> (&em), sizeof(Employee))){
        em.show_data();
        std::cout << "\n\n====================================\n";
    }

    inFile.close();
    std::cin.ignore();
    std::cin.get();
}

void Employee::show_data() {
    std::cout << "Employee ID: " << identification_number;
    std::cout << "\nEmployee Name: " << employee_name;
    std::cout << "\nEmployee Department: " << department;
    std::cout << "\nEmployee Position: " << position;
    std::cout << "\nEmployee Salary: " << salary;
}

Employee::Employee() {
    std::ofstream outFile;
    outFile.open("employee.dat", std::ios::binary|std::ios::app);
    outFile.close();
    std::ofstream outDFile;
    outDFile.open("DuplicateCheckingFile.txt", std::ios::app);
    outDFile.close();
}

void Employee::write_employee_record_in_file() {
    std::ofstream outFile;
    outFile.open("employee.dat", std::ios::binary|std::ios::app);

    get_data();

    if(!flag){
        outFile.write(reinterpret_cast<char *>(this), sizeof(Employee));
        outFile.close();
        std::cout << "\n\n Employee Record has been created.";
    }

    if(flag) {
        std::cout << "Record could not be created due to duplication.";
        outFile.close();
    }

    std::cin.ignore();
    std::cin.get();
}

void Employee::update_employee_record(int n) {
    identification_number_to_be_updated = n;
    bool found = false;
    std::fstream File;
    File.open("employee.dat", std::ios::binary|std::ios::in|std::ios::out);
    if(!File) {
        std::cout << "File could not open. Press any key to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    while(!File.eof() && !found) {
        File.read(reinterpret_cast<char *>(this), sizeof(Employee));
        if(get_identification_number() == n){
            show_data();
            std::cout << "\n\nPlease enter the new details of the employee" << std::endl;
            get_data();
            if(!flag){
                int pos=(-1)*static_cast<int>(sizeof(*this));
                File.seekp(pos, std::ios::cur);
                File.write(reinterpret_cast<char *>(this), sizeof(Employee));
            }
            found = true;
        }
    }
    File.close();

    if(flag){
        std::cout << "Could not update because this ID already exists";
    }

    if(!found) {
        std::cout << "\n\n Record Not Found.";
    }

    std::cin.ignore();
    std::cin.get();

    if(!flag && found && identification_number_to_be_updated != n) {
        delete_from_duplicate_file(n);
    }
    identification_number_to_be_updated=0;
}

void Employee::delete_employee_record(int n) {
    std::ifstream inFile;
    inFile.open("employee.dat", std::ios::binary);
    if(!inFile){
        std::cout << "\n File could not be opened...press any key to continue";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::ofstream outFile;
    outFile.open("Temp.dat", std::ios::out);
    inFile.seekg(0, std::ios::beg);
    while(inFile.read(reinterpret_cast<char *>(this), sizeof(Employee))){
        if(get_identification_number() != n){
            outFile.write(reinterpret_cast<char *>(this), sizeof(Employee));
        }
    }

    outFile.close();
    inFile.close();
    remove("employee.dat");
    rename("Temp.dat", "employee.dat");
    std::cout << "\n\nRecord deleted...press any key to continue.";
    std::cin.ignore();
    std::cin.get();
    delete_from_duplicate_file(n);
}

int Employee::get_identification_number() const {
    return identification_number;
}

void Employee::show_employee_record(int n) {
    std::ifstream inFile;
    inFile.open("employee.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "File could not be opened. Press any key to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    bool flag = false;
    while (inFile.read(reinterpret_cast<char *>(this), sizeof(Employee))) {
        if (get_identification_number() == n) {
            show_data();
            flag = true;
        }
    }

    inFile.close();
    if (!flag) {
        std::cout << "\n\nRecord does not exist.";
    }
    std::cin.ignore();
    std::cin.get();
}

void Employee::check_for_duplication_in_file() {
    int current_identification_number = 0;
    flag = false;
    std::ifstream infile("DuplicateCheckingFile.txt");
    while(!infile.eof()){
        infile >> current_identification_number;
        if(current_identification_number == identification_number) {
            flag = true;
        }
    }
    infile.close();
    if(!flag){
        std::ofstream outfile("DuplicateCheckingFile.txt", std::ios::app);
        outfile << "\n" << identification_number;
        outfile.close();
    }
}

void Employee::delete_from_duplicate_file(int n) {
    int current_identification_number;
    std::ifstream  InFile("DuplicateCheckingFile.txt");
    std::ofstream OutFile("TempFile.txt");
    InFile.seekg(0, std::ios::beg);
    while(!InFile.eof()){
        InFile >> current_identification_number;
        if (current_identification_number != n) {
            OutFile << "\n" << current_identification_number;
        }
    }

    InFile.close();
    OutFile.close();
    remove("DuplicateCheckingFile.txt");
    rename("TempFile.txt", "DuplicateCheckingFile.txt");
    std::cin.ignore();
    std::cin.get();
}


