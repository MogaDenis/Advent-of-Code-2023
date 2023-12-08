#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <unistd.h>

std::vector<std::string> split(std::string str, char separator) 
{
    std::vector<std::string> strings = std::vector<std::string>{};

    long long startIndex = 0, endIndex = 0;
    for (long long i = 0; i <= (long long)str.size(); i++) {
        
        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == (long long)str.size()) {
            endIndex = i;
            std::string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }

    return strings;
}

int main()
{
    std::ifstream input("input.txt");

    std::map<std::string, std::pair<std::string, std::string>> directions{};
    std::vector<std::string> startingPoints{};

    char lineChar[300];
    input.getline(lineChar, 300);
    std::string instructions{lineChar};

    input.getline(lineChar, 300);

    while (input.getline(lineChar, 300))
    {
        std::string line{lineChar};

        std::vector<std::string> step = split(line, ' ');

        std::string currentLocation = step[0];

        if (currentLocation[currentLocation.size() - 1] == 'A')
            startingPoints.push_back(currentLocation);
        
        std::string left = step[2];
        std::string rigth = step[3];

        left = left.substr(1, left.size() - 2);
        rigth = rigth.substr(0, rigth.size() - 1);

        directions[currentLocation] = std::pair<std::string, std::string>{left, rigth};
    }

    int index = 0;
    int stepsCount = 0;

    std::string currentLocation = "AAA";
    std::string destination = "ZZZ";

    while (currentLocation != destination)
    {
        char leftOrRigth = instructions[index];

        if (leftOrRigth == 'L')
            currentLocation = directions[currentLocation].first;
        else if (leftOrRigth == 'R')
            currentLocation = directions[currentLocation].second;

        index++;
        stepsCount++;

        if (index >= (int)instructions.size())
            index = 0;
    }
    
    std::cout << "Steps: " << stepsCount << '\n';

    return 0;
}