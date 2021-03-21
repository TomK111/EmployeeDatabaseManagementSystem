#include <iostream>
#include <iomanip>
#include "entry_menu/menu.h"


int main()
{
    char ch;
    std::cout.setf(std::ios::fixed|std::ios::showpoint);
    std::cout<<std::setprecision(2);
    do
    {
        std::cout<<"\n\n\n\t\t\t\tHOME SCREEN\n\n\n";
        std::cout<<"\n\n\t1. Employee Database Management System";
        std::cout<<"\n\n\t2. Exit";
        std::cout<<"\n\n\n\tPlease Select Your Option (1-2):";
        std::cin>>ch;
        switch(ch)
        {
            case '1':
                entry_menu();
                break;
            case '2':
                break;
            default: std::cout<<"\a";
        }
    }while(ch!='3');
    system("pause");
    return 0;
}