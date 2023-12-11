#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <math.h>

class Point
{
public:
    int x, y;

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Point()
    {
        this->x = -1;
        this->y = -1;
    }

    int manhattan_norm(Point otherPoint)
    {
        return abs(this->x - otherPoint.x) + abs(this->y - otherPoint.y);
    }

    std::string toString()
    {
        return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
    }
};

int get_min(int first, int second)
{
    return (first < second) ? first : second;
}

int get_max(int first, int second)
{
    return (first > second) ? first : second;
}

std::map<int, bool> emptyRows{};
std::map<int, bool> emptyColumns{};

uint64_t get_distance_increase(int row, int column, int type)
{
    uint64_t distanceVariance = 0;

    int lower = get_min(row, column);
    int upper = get_max(row, column);

    for (int value = lower + 1; value < upper; value++)
    {
        if (type == 0)
        {
            if (emptyRows.contains(value))
                distanceVariance++;
        }

        if (type == 1)
        {
            if (emptyColumns.contains(value))
                distanceVariance++;;
        }
    }

    return distanceVariance;
}

int main()
{
    std::ifstream input("input.txt");

    std::vector<std::vector<char>> diagram{};
    std::vector<Point> galaxies{};

    std::map<int, int> galaxiesPerColumn{};

    int rowCount = 0;

    char lineChar[200];
    while (input.getline(lineChar, 200))
    {
        diagram.push_back(std::vector<char>{});
        std::string line{lineChar};

        int columnCount = 0;
        bool emptyRow = true;

        for (const char& character : line)
        {
            diagram[rowCount].push_back(character);

            if (!galaxiesPerColumn.contains(columnCount))
                galaxiesPerColumn[columnCount] = 0;

            if (character == '#')
            {
                galaxies.push_back(Point{columnCount, rowCount});
                emptyRow = false;

                galaxiesPerColumn[columnCount]++;
            }

            columnCount++;
        }

        if (emptyRow)
            emptyRows[rowCount] = true;

        rowCount++;
    }

    for (std::pair<int, int> pair : galaxiesPerColumn)
    {
        if (pair.second == 0)
            emptyColumns[pair.first] = true;
    }

    // Compute the Manhattan norms between all pairs of points.

    uint64_t sum = 0;
    int pairs = 0;

    for (int i = 0; i < (int)galaxies.size() - 1; i++)
    {
        for (int j = i + 1; j < (int)galaxies.size(); j++)
        {
            uint64_t distance = galaxies[i].manhattan_norm(galaxies[j]) + get_distance_increase(galaxies[i].x, galaxies[j].x, 1) + get_distance_increase(galaxies[i].y, galaxies[j].y, 0);
            sum += distance;
            pairs++;
        }
    }

    std::cout << sum << '\n';

    return 0;
}

