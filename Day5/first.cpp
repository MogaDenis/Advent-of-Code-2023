#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

typedef struct 
{
    long long destinationStart;
    long long sourceStart;
    long long rangeLength;
} tuple;

tuple create_tuple(long long destinationStart, long long sourceStart, long long rangeLength)
{
    tuple newTuple;

    newTuple.destinationStart = destinationStart;
    newTuple.sourceStart = sourceStart;
    newTuple.rangeLength = rangeLength;

    return newTuple;
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

std::vector<long long> vector_of_string_to_vector_of_long(std::vector<std::string>& vector)
{
    std::vector<long long> newVector{};

    for (std::string text : vector)
        newVector.push_back((long long)atol(text.c_str()));

    return newVector;
}

std::vector<long long> get_vector_long_from_string(std::string& text)
{
    std::vector<std::string> splitText = split(text, ' ');

    return vector_of_string_to_vector_of_long(splitText);
}

long long get_value_from_tuple_vector(std::vector<tuple>& vector, long long key)
{
    for (tuple& currentTuple : vector)
    {
        if (key >= currentTuple.sourceStart && key < currentTuple.sourceStart + currentTuple.rangeLength)
            return currentTuple.destinationStart + (key - currentTuple.sourceStart);
    }

    return key;
}

int main()
{
    std::ifstream input("input.txt");

    std::vector<tuple> seedToSoil{};
    std::vector<tuple> soilToFertilizer{};
    std::vector<tuple> fertilizerToWater{};
    std::vector<tuple> waterToLight{};
    std::vector<tuple> lightToTemperature{};
    std::vector<tuple> temperatureToHumidity{};
    std::vector<tuple> humidityToLocation{};

    long long emptySpaceCount = 0;

    char lineChar[250];
    input.getline(lineChar, 250);
    std::string line{lineChar};

    std::string seedsString = split(line, ':')[1];
    seedsString = seedsString.substr(1, seedsString.size() - 1);

    std::vector<long long> seeds = get_vector_long_from_string(seedsString);

    while (input.getline(lineChar, 250))
    {
        std::string line{lineChar};

        if (line.empty())
        {
            emptySpaceCount++;
            continue;
        }

        if (!isdigit(line[0]))
            continue;

        std::vector<long long> values = get_vector_long_from_string(line);

        long long destinationStart = values[0];
        long long sourceStart = values[1];
        long long rangeLength = values[2];

        if (emptySpaceCount == 1)
            seedToSoil.push_back(create_tuple(destinationStart, sourceStart, rangeLength));
        else if (emptySpaceCount == 2)
            soilToFertilizer.push_back(create_tuple(destinationStart, sourceStart, rangeLength));
        else if (emptySpaceCount == 3)
            fertilizerToWater.push_back(create_tuple(destinationStart, sourceStart, rangeLength));
        else if (emptySpaceCount == 4)
            waterToLight.push_back(create_tuple(destinationStart, sourceStart, rangeLength));
        else if (emptySpaceCount == 5)
            lightToTemperature.push_back(create_tuple(destinationStart, sourceStart, rangeLength));
        else if (emptySpaceCount == 6)
            temperatureToHumidity.push_back(create_tuple(destinationStart, sourceStart, rangeLength));
        else if (emptySpaceCount == 7)
            humidityToLocation.push_back(create_tuple(destinationStart, sourceStart, rangeLength));
    }

    bool foundMin = false;
    long long minimumLocation = -1;

    for (int index = 0; index < (int)seeds.size(); index += 2)
    {
        long long start = seeds[index];
        long long range = seeds[index + 1];

        std::cout << "Starting: " << start << '\n';

        for (long long offset = 0; offset < range; offset++)
        {
            long long currentSeed = start + offset;

            long long soil = get_value_from_tuple_vector(seedToSoil, currentSeed);
            long long fertilizer = get_value_from_tuple_vector(soilToFertilizer, soil);
            long long water = get_value_from_tuple_vector(fertilizerToWater, fertilizer);
            long long ligth = get_value_from_tuple_vector(waterToLight, water);
            long long temperature = get_value_from_tuple_vector(lightToTemperature, ligth);
            long long humidity = get_value_from_tuple_vector(temperatureToHumidity, temperature);
            long long location = get_value_from_tuple_vector(humidityToLocation, humidity);

            if (!foundMin)
            {
                minimumLocation = location;
                foundMin = true;
                continue;
            }

            if (location < minimumLocation)
                minimumLocation = location;
        }

        std::cout << "Done: " << start << "\n\n";
    }

    std::cout << minimumLocation << '\n';

    return 0;
}