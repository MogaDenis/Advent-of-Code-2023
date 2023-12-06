#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <assert.h>

typedef struct 
{
    uint64_t time;
    uint64_t distance;
} race;

inline race create_race(uint64_t time, uint64_t distance)
{
    race newRace;
    newRace.time = time;
    newRace.distance = distance;

    return newRace;
}

std::vector<std::string> split(std::string str, char separator) 
{
    std::vector<std::string> strings = std::vector<std::string>{};

    uint64_t startIndex = 0, endIndex = 0;
    for (uint64_t i = 0; i <= (uint64_t)str.size(); i++) {
        
        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == (uint64_t)str.size()) {
            endIndex = i;
            std::string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }

    return strings;
}

inline void remove_empty(std::vector<std::string>& vector)
{
    std::remove_if(vector.begin(), vector.end(), [](const std::string& text){return text.empty();});
}

void remove_leading_whitespaces(std::string& text)
{
    while (text[0] == ' ')
        text = text.substr(1, text.size() - 1);
}

inline uint64_t calculate_distance(uint64_t startTime, uint64_t raceTime, uint64_t speed)
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

    int index = 0;

    std::string totalTimeString = "";
    std::string totalDistanceString = "";

    while (times[index].empty() == false && distances[index].empty() == false)
    {
        totalTimeString += times[index];
        totalDistanceString += distances[index];

        index++;
    }

    uint64_t totalTime = atol(totalTimeString.c_str());
    uint64_t totalDistance = atol(totalDistanceString.c_str());

    race bigRace = create_race(totalTime, totalDistance);

    uint64_t firstWinningTime = 0;
    uint64_t lastWinningTime = totalTime;

    uint64_t currentTime = 0;
    do 
    {
        
        uint64_t distanceCovered = calculate_distance(currentTime, bigRace.time, currentTime);

        if (distanceCovered > bigRace.distance)
            firstWinningTime = currentTime;

        currentTime++;
    } 
    while (firstWinningTime == 0);

    currentTime = totalTime;
    bool stop = false;
    do 
    {
        uint64_t distanceCovered = calculate_distance(currentTime, bigRace.time, currentTime);

        if (distanceCovered <= bigRace.distance)
            lastWinningTime = currentTime - 1;    
        else
            stop = true;

        currentTime--;
    } 
    while (!stop);

    std::cout << lastWinningTime - firstWinningTime + 1 << '\n';

    return 0;
}