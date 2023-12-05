#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <string.h>

std::vector<std::string> split(std::string str, char separator) 
{
    std::vector<std::string> strings = std::vector<std::string>{};

    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= (int)str.size(); i++) {
        
        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == (int)str.size()) {
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
    long powersSum = 0;

    std::ifstream input("input.txt");
    
    char lineChar[200];
    while (input.getline(lineChar, 200))
    {
        std::string line{lineChar};

        std::vector<std::string> gameAndSets = split(line, ':'); 

        std::vector<std::string> sets = split(gameAndSets[1], ';');

        int maxBlue = 0;
        int maxGreen = 0;
        int maxRed = 0;
        
        for (auto& set : sets)
        {
            std::vector<std::string> pairs = std::vector<std::string>{};
            for (auto& pair : split(set, ','))
                pairs.push_back(pair.substr(1, pair.length() - 1));

            int blue = 0;
            int green = 0;
            int red = 0;

            for (auto& pair : pairs)
            {
                std::vector<std::string> countAndColour = split(pair, ' ');

                std::string count = countAndColour[0];
                std::string colour = countAndColour[1];

                int countInt = atoi(count.c_str());

                if (colour == "blue")
                    blue += countInt;
                if (colour == "green")
                    green += countInt;
                if (colour == "red")
                    red += countInt;
            }

            if (red > maxRed)
                maxRed = red;
            
            if (green > maxGreen)
                maxGreen = green;

            if (blue > maxBlue)
                maxBlue = blue;
        }

        powersSum += maxBlue * maxGreen * maxRed;
    }

    std::cout << powersSum << '\n';

    return 0;
}