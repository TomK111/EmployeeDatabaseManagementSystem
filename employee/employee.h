//
// Created by tomislav on 3/21/21.
//

#ifndef EMS_EMPLOYEE_H
#define EMS_EMPLOYEE_H

class Employee {
private:
    char employee_name[50]{};
    int identification_number{};
    int contact_number{};
    std::string email{};
    std::string position{};
    std::string department{};
    bool flag{};
public:
    Employee();
    void get_data();
    void show_data();
    int get_identification_number() const;
    void write_employee_record_in_file();
    void show_employee_record(int);
    void update_employee_record(int);
    void delete_employee_record(int);
    static void delete_from_duplicate_file(int);
    void check_for_duplication_in_file();
};

void display_all();

#endif //EMS_EMPLOYEE_H
