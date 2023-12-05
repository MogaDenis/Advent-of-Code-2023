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

std::pair<bool, std::pair<int, int>> is_part(int row, int column, std::vector<std::vector<std::string>>& engine)
{
    int heigth = (int)engine.size();
    int width = (int)engine[0].size();

    // If the number is on the corner.
    if (row == 0 && column == 0) 
    {
        if (is_symbol(row, column + 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row, column + 1}};

        if (is_symbol(row + 1, column + 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column + 1}};

        if (is_symbol(row + 1, column, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column}};

        return std::pair<bool, std::pair<int, int>>{false, std::pair<int, int>{-1, -1}};
    }

    if (row == 0 && column == width - 1) 
    {
        if (is_symbol(row, column - 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row, column - 1}};

        if (is_symbol(row + 1, column - 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column - 1}};

        if (is_symbol(row + 1, column, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column}};

        return std::pair<bool, std::pair<int, int>>{false, std::pair<int, int>{-1, -1}};
    }

    if (row == heigth - 1 && column == 0) 
    {
        if (is_symbol(row - 1, column, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column}};

        if (is_symbol(row - 1, column + 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column + 1}};

        if (is_symbol(row, column + 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row, column + 1}};

        return std::pair<bool, std::pair<int, int>>{false, std::pair<int, int>{-1, -1}};
    }

    if (row == heigth - 1 && column == width - 1) 
    {
        if (is_symbol(row, column - 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row, column - 1}};

        if (is_symbol(row - 1, column - 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column - 1}};

        if (is_symbol(row - 1, column, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column}};

        return std::pair<bool, std::pair<int, int>>{false, std::pair<int, int>{-1, -1}};
    }

    // If the number is on the edge.
    if (row == 0)
    {
        if (is_symbol(row, column - 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row, column - 1}};
        
        if (is_symbol(row, column + 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row, column + 1}};

        if (is_symbol(row + 1, column - 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column - 1}};

        if (is_symbol(row + 1, column, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column}};

        if (is_symbol(row + 1, column + 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column + 1}};

        return std::pair<bool, std::pair<int, int>>{false, std::pair<int, int>{-1, -1}};
    }

    if (row == heigth - 1)
    {
        if (is_symbol(row, column - 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row, column - 1}};
        
        if (is_symbol(row, column + 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row, column + 1}};

        if (is_symbol(row - 1, column - 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column - 1}};

        if (is_symbol(row - 1, column, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column}};

        if (is_symbol(row - 1, column + 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column + 1}};

        return std::pair<bool, std::pair<int, int>>{false, std::pair<int, int>{-1, -1}};
    }

    if (column == 0)
    {
        if (is_symbol(row - 1, column, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column}};
        
        if (is_symbol(row + 1, column, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column}};

        if (is_symbol(row - 1, column + 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column + 1}};

        if (is_symbol(row, column + 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row, column + 1}};

        if (is_symbol(row + 1, column + 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column + 1}};

        return std::pair<bool, std::pair<int, int>>{false, std::pair<int, int>{-1, -1}};
    }

    if (column == width - 1)
    {
        if (is_symbol(row - 1, column, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column}};
        
        if (is_symbol(row + 1, column, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column}};

        if (is_symbol(row - 1, column - 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column - 1}};

        if (is_symbol(row, column - 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row, column - 1}};

        if (is_symbol(row + 1, column - 1, engine))
            return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column - 1}};

        return std::pair<bool, std::pair<int, int>>{false, std::pair<int, int>{-1, -1}};
    }

    // If the number is in the center.
    if (is_symbol(row - 1, column - 1, engine))
        return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column - 1}};

    if (is_symbol(row - 1, column, engine))
        return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column}};

    if (is_symbol(row - 1, column + 1, engine))
        return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row - 1, column + 1}};

    if (is_symbol(row, column - 1, engine))
        return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row, column - 1}};

    if (is_symbol(row, column + 1, engine))
        return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row, column + 1}};

    if (is_symbol(row + 1, column - 1, engine))
        return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column - 1}};

    if (is_symbol(row + 1, column, engine))
        return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column}};

    if (is_symbol(row + 1, column + 1, engine))
        return std::pair<bool, std::pair<int, int>>{true, std::pair<int, int>{row + 1, column + 1}};

    return std::pair<bool, std::pair<int, int>>{false, std::pair<int, int>{-1, -1}};
}

std::pair<int, int> get_indices_of_symbols(int row, int startColumn, int endColumn, std::vector<std::vector<std::string>>& engine)
{
    for (int index = startColumn; index <= endColumn; index++)
    {
        auto truthValueAndIndices = is_part(row, index, engine);

        if (truthValueAndIndices.first)
            return truthValueAndIndices.second;
    }

    return std::pair<int, int>{-1, -1};
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

    std::map<std::pair<int, int>, std::vector<int>> positionsAndNumbers{};

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

            std::pair<int, int> symbolIndices = get_indices_of_symbols(row, startIndex, endIndex, engine);

            if (symbolIndices != std::pair<int, int>{-1, -1})
            {
                int number = atoi(get_number(row, startIndex, endIndex, engine).c_str());
                if (!positionsAndNumbers.contains(symbolIndices))
                    positionsAndNumbers[symbolIndices] =  std::vector<int>{};
 
                positionsAndNumbers[symbolIndices].push_back(number);
            }

            index += (endIndex - startIndex) + 1;
        }

        row++;
    }

    for (auto pair : positionsAndNumbers)
    {
        if (pair.second.size() != 2)
            continue;

        sum += pair.second[0] * pair.second[1];
    }

    std::cout << sum << '\n';

    return 0;
}