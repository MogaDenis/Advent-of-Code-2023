#include <vector>
#include <string>
#include <fstream>
#include <iostream>

void replaceLiteralsWithDigits(std::string& line, std::vector<std::string>& digits)
{
    int count = 1;
    for (std::string digit : digits)
    {
        std::string::size_type index = 0;
        std::string replacement = digit[0] + std::to_string(count) + digit[digit.length() - 1];

        while ((index = line.find(digit, index)) != std::string::npos)
        {
            line.replace(index, digit.size(), replacement);
            index += replacement.size();
        }

        count++;
    }
}

int main()
{
    std::vector<std::string> digits = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    std::ifstream input("input.txt");

    long sum = 0;

    std::string line;
    while (input >> line)
    {
        replaceLiteralsWithDigits(line, digits);

        char first = '.';
        char last = '.';

        for (char letter : line)
        {
            if (!isdigit(letter))
                continue;

            if (first == '.')
                first = letter;

            last = letter;
        }

        int value = (first - '0') * 10 + (last - '0');

        sum += value;
    }

    std::cout << sum << '\n';

    return 0;
}