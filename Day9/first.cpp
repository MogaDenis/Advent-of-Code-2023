#include <vector>
#include <fstream>
#include <iostream>
#include <string>
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

std::vector<int64_t> to_int_from_strings(std::vector<std::string>& strings)
{
    std::vector<int64_t> numbers{};

    for (std::string& text : strings)
        numbers.push_back(atol(text.c_str()));

    return numbers;
}

bool all_zeroes(const std::vector<int64_t>& numbers)
{
    for (const int64_t& number : numbers)
        if (number != 0)
            return false;

    return true;
}

std::vector<int64_t> get_difference_values(std::vector<int64_t>& values)
{
    std::vector<int64_t> differences{};

    for (int64_t i = 0; i < (int64_t)values.size() - 1; i++)
        differences.push_back(values[i + 1] - values[i]);

    return differences;
}

int main()
{
    std::ifstream input("input.txt");

    char lineChar[200];

    int64_t totalSum = 0;

    while (input.getline(lineChar, 200))
    {
        std::vector<int64_t> last{};
        
        std::string line{lineChar};

        std::vector<std::string> valuesStrings = split(line, ' ');
        std::vector<int64_t> numbers = to_int_from_strings(valuesStrings);

        last.push_back(numbers[numbers.size() - 1]);

        std::vector<int64_t> differences{};
        do
        {
            differences = get_difference_values(numbers);

            numbers = differences;

            int64_t differencesCount = (int64_t)differences.size();

            last.push_back(differences[differencesCount - 1]);
        }
        while (!all_zeroes(differences));

        int64_t sumBottomUp = 0;
        for (int64_t& number : last)
            sumBottomUp += number;

        totalSum += sumBottomUp;
    }

    std::cout << totalSum << '\n';

    return 0;
}