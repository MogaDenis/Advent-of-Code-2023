#include <fstream>
#include <iostream>
#include <string>
#include <string.h>

int main()
{
    std::ifstream input("input.txt");

    long sum = 0;

    std::string line;
    while (input >> line)
    {
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

        sum += (first - '0') * 10 + (last - '0');
    }

    std::cout << sum << '\n';

    return 0;
}