#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
/*
int main() {
    std::string bufferStr;
    std::string fileName = "..\\statement.txt";

    //Поведение не соответствует стандарту
    //std::ofstream file(fileName, file.ate);
    //Перезаписывает файл!

    std::ofstream file(fileName, std::ofstream::app);
    if (file.is_open()) {

        //Name
        std::cout << "Enter the name: ";
        std::cin >> bufferStr;
        file << bufferStr << " ";

        //Surname
        std::cout << "Enter the surname: ";
        std::cin >> bufferStr;
        file << bufferStr << " ";

        //Payment
        while (true){
            int buffInt;
            std::cout << "Enter the payment: ";
            std::cin.ignore(32767, '\n');
            std::cin.clear();
            std::cin >> buffInt;
            if (std::cin.fail()){
                std::cout << "Error reading payment, try again.\n";
                continue;
            }
            file << buffInt << " ";
            break;
        }

        //Date

        while (true){
            std::cout << "Enter the date (dd.mm.yyyy): ";
            std::tm buffDate;
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cin >> std::get_time(&buffDate, "%d.%m.%Y");
            if (std::cin.fail()){
                std::cout << "Error reading date, try again.\n";
                continue;
            }
            file << std::put_time(&buffDate, "%d.%m.%Y") << std::endl;
            break;
        }

        file.close();
    }
    else
        std::cout << "File open error!" << std::endl;
    return 0;
}
*/