#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <unistd.h>
#include <numeric>

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

uint64_t get_number_of_steps(std::map<std::string, std::pair<std::string, std::string>>& directions, 
                            std::string& instructions, std::string& currentLocation)
{
    uint64_t index = 0;
    uint64_t stepsCount = 0;

    while (currentLocation[currentLocation.size() - 1] != 'Z')
    {
        char leftOrRigth = instructions[index];

        if (leftOrRigth == 'L')
            currentLocation = directions[currentLocation].first;
        else if (leftOrRigth == 'R')
            currentLocation = directions[currentLocation].second;

        index++;
        stepsCount++;

        if (index >= (uint64_t)instructions.size())
            index = 0;        
    }

    return stepsCount;
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

    uint64_t result = 1;

    for (std::string& currentLocation : startingPoints)
    {
        result = std::lcm(result, get_number_of_steps(directions, instructions, currentLocation));
    }

    std::cout << result << '\n';

    return 0;
}