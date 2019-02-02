#include <iostream>
#include <string>
#include <fstream>
#include <random>

int main(void)
{
    uint32_t cityCount;
    uint32_t i;
    std::string fileName;
    std::string id;
    std::ofstream fileStream;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(10.0, 3000.0);

    std::cout << "Filename: ";
    std::cin >> fileName;
    std::cout << "City count: ";
    std::cin >> cityCount;
    std::cout << "ID (y/n): ";
    std::cin >> id;

    fileStream.open(fileName);
    if(!fileStream.good())
    {
        std::cout << "Could not open file" << std::endl;
        return -1;
    }


    fileStream << cityCount << std::endl;
    for(i = 0; i < cityCount; ++i)
    {
        if(id == std::string("y"))
            fileStream << i << " ";
        fileStream << dis(gen);
        fileStream << " ";
        fileStream << dis(gen);
        fileStream << std::endl;
    }

    fileStream.close();
    std::cout << "Generated " << cityCount << " cities." << std::endl;
    return 0;
}
