#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int getRandomNumber(int min, int max)
{
    rand();
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

class ATM {
private:
    std::string atm_saveFileName{"..\\ATM.bin"};
    unsigned long atm_banknoteDenomination[6] {100, 200, 500, 1000, 2000, 5000}; // long for implicit conversion
    int atm_fileIntSize; //first byte of file (recorded at char type)
    int atm_banknoteCount[6] {0,0,0,0,0,0}; //other bytes of file
    const int maxBanknoteCount = 1000;

public:
    explicit ATM(){
        if (!read()) {
            atm_fileIntSize = sizeof(int);
            refill();
        }
    }

    bool read(){
        std::ifstream atmFile (atm_saveFileName, std::ifstream::binary);
        char bufferCh;
        if (atmFile.is_open()){
            atmFile.read(&bufferCh, 1);
            atmFile.seekg(1, std::ios_base::cur);
            atm_fileIntSize = bufferCh - '0';
            for (int & it : atm_banknoteCount){
                atmFile.read(reinterpret_cast<char*> (&it), atm_fileIntSize);
                atmFile.seekg(atm_fileIntSize, std::ios_base::cur);
            }
            atmFile.close();
            return true;
        }
        return false;
    }

    bool save(){
        std::ofstream atmFile (atm_saveFileName, std::ofstream::binary | std::ofstream::trunc);
        if (atmFile.is_open()){
            char bufferCh = atm_fileIntSize + '0';
            atmFile.write(&bufferCh, 1);
            atmFile.seekp(1, std::ios_base::cur);
            for (int & it : atm_banknoteCount){
                atmFile.write(reinterpret_cast<char*> (&it), atm_fileIntSize);
                atmFile.seekp(atm_fileIntSize, std::ios_base::cur);
            }
            atmFile.close();
            return true;
        }
        return false;
    }

    void refill(){
        int allBanknoteCount = 0;
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        for (int i = 0; i < 5; ++i){
            atm_banknoteCount[i] = getRandomNumber(0, maxBanknoteCount - allBanknoteCount);
            allBanknoteCount += atm_banknoteCount[i];
        }
        atm_banknoteCount[5] = maxBanknoteCount - allBanknoteCount;
    }

    unsigned long allCash () {
        unsigned long allCash = 0;
        for (int i = 0; i < 6; ++i){
            allCash += atm_banknoteDenomination[i] * atm_banknoteCount[i];
        }
        return allCash;
    }

    int withdrawal (const unsigned long &amount){
        if (amount > allCash())
            return -2; //atm cash fault

        int withdrawalBanknoteCount[6] {0, 0, 0, 0, 0, 0};
        unsigned long balance = amount;
        int i = 5;
        while (balance > 0 and i >= 0){
            if (balance / atm_banknoteDenomination[i] <= atm_banknoteCount[i])
                withdrawalBanknoteCount[i] = balance / atm_banknoteDenomination[i];
            else
                withdrawalBanknoteCount[i] = atm_banknoteCount[i];
            balance -= withdrawalBanknoteCount[i] * atm_banknoteDenomination[i];
            i--;
        }


        if (balance > 0)
            return -1; //atm banknote fault

        //change atm
        for (int j = 0; j < 6; ++j)
            atm_banknoteCount[j] -= withdrawalBanknoteCount[j];
        save();
        return 0;
    }

    void showSaveFile (){
        std::ifstream atmFile (atm_saveFileName, std::ifstream::binary);
        char bufferCh;
        if (atmFile.is_open()){
            atmFile.read(&bufferCh, 1);
            atmFile.seekg(1, std::ios_base::cur);
            atm_fileIntSize = bufferCh - '0';
            std::cout << "atm_fileIntSize = " << atm_fileIntSize << "\n";
            for (int i = 0; i < 6; i++) {
                int bufferInt;
                atmFile.read(reinterpret_cast<char*>(&bufferInt), atm_fileIntSize);
                atmFile.seekg(atm_fileIntSize, std::ios_base::cur);
                std::cout << bufferInt << " ";
            }
            std::cout << std::endl;
            atmFile.close();
            return;
        }
        std::cout << "File open error." << std::endl;
    }
};


int main() {
    ATM atm;
    char operationCode; // '+' refill, '-' withdrawal

    while (true){
        std::cout << R"(Refill\withdrawal of cash from the ATM. Enter "+" or "-": )";
        std::cin >> operationCode;
        if (std::cin.fail() or !(operationCode == '+' or operationCode == '-')){
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Entered fault.\n";
            std::cout << "Try again.\n";
            continue;
        }
        break;
    }

    switch (operationCode) {
        case '+': {
            atm.refill();
            atm.save();
            break;
        }
        case '-': {
            unsigned long amount;
            while (true){
                std::cout << "Enter the withdrawal amount of cash in multiples of 100.\n"
                          << "Withdrawal amount no more - " << atm.allCash() << " RUB.\n";
                std::cin >> amount;
                if (amount == 0)
                    break;
                if (std::cin.fail() or amount % 100 != 0){
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    std::cout << "Entered fault.\n";
                    std::cout << "Try again or enter '0' for exit.\n";
                    continue;
                }
                if (!atm.withdrawal(amount)) {
                    std::cout << "Take your money.\n";
                    break;
                }
                else {
                    std::cout << "Requested amount could not be issued.\n";
                    std::cout << "Try again or enter '0' for exit.\n";
                    continue;
                }

            }
            break;
        }
    }

    atm.save();

    return 0;
}