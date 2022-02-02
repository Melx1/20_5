#include <iostream>
#include <fstream>
/*
int main() {
    std::string targetFish;
    int countFish = 0;

    std::cout << "Enter the species of fish: ";
    std::cin >> targetFish;
    for (char &it: targetFish)
        it = std::tolower(it);

    std::ifstream river ("..\\river.txt");
    if (!river.is_open()){
        std::cout << "File \"river.txt\" open error!\n";
        return -1;
    }

    std::ofstream basket ("..\\basket.txt", std::fstream::app);
    if (!basket.is_open()){
        std::cout << "File \"basket.txt\" open error!\n";
        return -1;
    }

    std::string bufferStr;
    while (std::getline(river, bufferStr)){
        if (targetFish == bufferStr){
            ++countFish;
            basket << bufferStr << '\n';
        }
    }

    river.close();
    basket.close();

    if (countFish > 0)
        std::cout << "Your caught " << countFish << " " << targetFish << "s!" << std::endl;
    else
        std::cout << "Your caught nothing..." << std::endl;

    return 0;
}
*/