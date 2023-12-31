#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <assert.h>

typedef struct 
{
    int time;
    int distance;
} race;

inline race create_race(int time, int distance)
{
    race newRace;
    newRace.time = time;
    newRace.distance = distance;

    return newRace;
}

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

void remove_empty(std::vector<std::string>& vector)
{
    std::remove_if(vector.begin(), vector.end(), [](const std::string& text){return text.empty();});
}

void remove_leading_whitespaces(std::string& text)
{
    while (text[0] == ' ')
        text = text.substr(1, text.size() - 1);
}

inline int calculate_distance(int startTime, int raceTime, int speed)
{
    return speed * (raceTime - startTime);
}

int main()
{
    std::ifstream input("input.txt");

    std::string timesString = "-1";
    std::string distancesString = "-1";

    char lineChar[100];
    while (input.getline(lineChar, 100))
    {
        std::string line{lineChar};

        if (timesString == "-1")
        {
            timesString = split(line, ':')[1];
            remove_leading_whitespaces(timesString);
        }
        else if (distancesString == "-1")
        {
            distancesString = split(line, ':')[1];
            remove_leading_whitespaces(distancesString);
        }
    }

    std::vector<std::string> times = split(timesString, ' ');
    for (std::string& time : times)
        remove_leading_whitespaces(time);

    std::vector<std::string> distances = split(distancesString, ' ');
    for (std::string& distance : distances)
        remove_leading_whitespaces(distance);

    remove_empty(times);
    remove_empty(distances);

    std::vector<race> races{};
    int index = 0;
    while (times[index].empty() == false && distances[index].empty() == false)
    {
        race newRace = create_race(atoi(times[index].c_str()), atoi(distances[index].c_str()));

        races.push_back(newRace);

        index++;
    }

    int totalWays = 1;

    for (race& currentRace : races)
    {
        int waysToWinCurrent = 0;
        for (int start = 1; start < currentRace.time; start++)
        {
            int distanceCovered = calculate_distance(start, currentRace.time, start);

            if (distanceCovered > currentRace.distance)
                waysToWinCurrent++;
        }

        totalWays *= waysToWinCurrent;
    }

    std::cout << totalWays << '\n';

    return 0;
}