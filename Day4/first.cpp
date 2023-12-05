#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

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

int getNumberOfWinningCards(std::vector<std::string>& yourCards, std::vector<std::string>& winningCards)
{
    int count = 0;
    for (std::string yourCard : yourCards)
    {
        if (yourCard[0] == ' ')
            yourCard = yourCard.substr(1, yourCard.size() - 1);

        for (std::string winningCard : winningCards)
        {
            if (winningCard[0] == ' ')
                winningCard = winningCard.substr(1, winningCard.size() - 1);

            if (yourCard == winningCard)
            {
                count++;
                break;
            }
        }
    }

    return count;
}

std::vector<std::string> removeSpacesAndEmpty(std::vector<std::string> strings)
{
    std::vector<std::string> result{};
    for (std::string& text : strings)
    {
        remove_if(text.begin(), text.end(), isspace);

        if (!text.empty())
            result.push_back(text);
    }

    return result;
}

long power(int base, int exp)
{
    int result = 1;

    while (exp != 0)
    {
        result *= base;
        exp--;
    }

    return result;
}

int main()
{
    std::ifstream input("input.txt");

    char lineChar[200];

    long sum = 0;

    while (input.getline(lineChar, 200))
    {
        std::string line{lineChar};

        std::vector<std::string> indexAndCards = split(line, ':');

        std::string cards = indexAndCards[1];

        std::vector<std::string> winningAndYourCards = split(cards, '|');

        std::string winningCardsString = winningAndYourCards[0].substr(1, winningAndYourCards[0].length() - 1);
        std::string yourCardsString = winningAndYourCards[1].substr(1, winningAndYourCards[1].length() - 1);

        std::vector<std::string> winningCards = split(winningCardsString, ' ');
        std::vector<std::string> yourCards = split(yourCardsString, ' ');

        winningCards = removeSpacesAndEmpty(winningCards);
        yourCards = removeSpacesAndEmpty(yourCards);

        int count = getNumberOfWinningCards(yourCards, winningCards);

        std::cout << count << '\n';
        
        if (count > 0)
            sum += power(2, count - 1);
    }

    std::cout << sum << '\n';

    return 0;
}