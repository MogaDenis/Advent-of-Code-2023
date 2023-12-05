#include <fstream>
#include <iostream>
#include <vector>
#include <map>

bool is_number(std::string& text)
{
    for (char character : text)
        if (!isdigit(character))
            return false;

    return true;
}

bool is_symbol(int row, int column, std::vector<std::vector<std::string>>& engine)
{
    return engine[row][column] != "." && !is_number(engine[row][column]);
}

bool is_part(int row, int column, std::vector<std::vector<std::string>>& engine)
{
    int heigth = (int)engine.size();
    int width = (int)engine[0].size();

    // If the number is on the corner.
    if (row == 0 && column == 0) 
        return is_symbol(row, column + 1, engine) || is_symbol(row + 1, column + 1, engine) || is_symbol(row + 1, column, engine);

    if (row == 0 && column == width - 1)
        return is_symbol(row, column - 1, engine) || is_symbol(row + 1, column - 1, engine) || is_symbol(row + 1, column, engine);

    if (row == heigth - 1 && column == 0) 
        return is_symbol(row - 1, column, engine) || is_symbol(row - 1, column + 1, engine) || is_symbol(row, column + 1, engine);

    if (row == heigth - 1 && column == width - 1)
        return is_symbol(row, column - 1, engine) || is_symbol(row - 1, column - 1, engine) || is_symbol(row - 1, column, engine);

    // If the number is on the edge.
    if (row == 0)
        return is_symbol(row, column - 1, engine) || is_symbol(row, column + 1, engine) || is_symbol(row + 1, column - 1, engine) 
                || is_symbol(row + 1, column, engine) || is_symbol(row + 1, column + 1, engine);

    if (row == heigth - 1)
        return is_symbol(row, column - 1, engine) || is_symbol(row, column + 1, engine) || is_symbol(row - 1, column - 1, engine) 
                || is_symbol(row - 1, column, engine) || is_symbol(row - 1, column + 1, engine);

    if (column == 0)
        return is_symbol(row - 1, column, engine) || is_symbol(row + 1, column, engine) || is_symbol(row - 1, column + 1, engine) 
                || is_symbol(row, column + 1, engine) || is_symbol(row + 1, column + 1, engine);

    if (column == width - 1)
        return is_symbol(row - 1, column, engine) || is_symbol(row + 1, column, engine) || is_symbol(row - 1, column - 1, engine) 
                || is_symbol(row, column - 1, engine) || is_symbol(row + 1, column - 1, engine);

    // If the number is in the center.
    return is_symbol(row - 1, column - 1, engine) || is_symbol(row - 1, column, engine) || is_symbol(row - 1, column + 1, engine) 
                || is_symbol(row, column - 1, engine) || is_symbol(row, column + 1, engine) || is_symbol(row + 1, column - 1, engine)
                || is_symbol(row + 1, column, engine) || is_symbol(row + 1, column + 1, engine);
}

bool check_if_number_is_part(int row, int startColumn, int endColumn, std::vector<std::vector<std::string>>& engine)
{
    for (int index = startColumn; index <= endColumn; index++)
        if (is_part(row, index, engine))
            return true;

    return false;
}

std::string get_number(int row, int start, int end, std::vector<std::vector<std::string>>& engine)
{
    std::string number = "";

    for (int index = start; index <= end; index++)
        number += engine[row][index];

    return number;
}

int main()
{
    std::ifstream input("input.txt");

    std::vector<std::vector<std::string>> engine = std::vector<std::vector<std::string>>{};

    char lineChar[200];
    int lineCount = 0;
    while (input.getline(lineChar, 200))
    {
        std::string line{lineChar};

        std::string number = "";

        engine.push_back(std::vector<std::string>{});

        for (char symbol : line)
        {
            std::string symbolString{symbol};
            engine[lineCount].push_back(symbolString);
        }

        lineCount++;
    }

    int row = 0;
    long sum = 0;

    for (std::vector<std::string>& line : engine)
    {
        for (int index = 0; index < (int)line.size(); index++)
        {
            if (!isdigit(line[index].c_str()[0]))
                continue;

            int startIndex = index;
            int endIndex = index;

            while (endIndex < (int)line.size() - 1 && isdigit(line[endIndex + 1].c_str()[0]))
                endIndex++;

            if (check_if_number_is_part(row, startIndex, endIndex, engine))
            {
                int number = atoi(get_number(row, startIndex, endIndex, engine).c_str());
                sum += number;
            }

            index += (endIndex - startIndex) + 1;
        }

        row++;
    }

    std::cout << sum << '\n';

    return 0;
}