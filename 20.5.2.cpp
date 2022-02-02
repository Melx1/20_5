#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
/*
int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int main() {
    int height, width;
    std::cout << "Enter the height and width of picture: ";
    std::cin >> height >> width;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::string fileName ("..\\pic.txt");
    std::ofstream file (fileName, file.trunc);
    for (int i = 0; i <= height; i++){
        for (int j = 0; j <= width; j++){
            file << getRandomNumber(0,1);
        }
        file << std::endl;
    }

    return 0;
}
 */