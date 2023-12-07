#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

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

enum
{
    FIVE,
    FOUR,
    FULL,
    THREE,
    TWO,
    ONE,
    HIGH,
};

const int MAX_NUMBER_OF_CARDS = 5;

typedef struct 
{
    std::string cards;
    int bid;
    int type;

} hand;

inline hand create_hand(std::string& cards, int& bid)
{
    hand newHand;
    newHand.cards = cards;
    newHand.bid = bid;
    newHand.type = -1;

    return newHand;
}

inline void set_hand_type(hand& hand_to_change, int type)
{
    hand_to_change.type = type;
}

int get_hand_type(const hand& hand_to_check)
{
    std::map<char, int> usedCards{};

    for (const char& card : hand_to_check.cards)
    {
        if (!usedCards.contains(card))
            usedCards[card] = 1;
        else
            usedCards[card]++;
    }

    int uniqueCards = (int)usedCards.size();

    if (uniqueCards == 1)
        return FIVE;
    if (uniqueCards == MAX_NUMBER_OF_CARDS)
        return HIGH;
    if (uniqueCards == 4)
        return ONE;

    int maxOccurrences = 0;
    for (const auto& pair : usedCards)
        if (pair.second > maxOccurrences)
            maxOccurrences = pair.second;

    if (uniqueCards == 2)
    {
        if (maxOccurrences == 4)
            return FOUR;

        return FULL;
    }

    // now uniqueCards = 3
    if (maxOccurrences == 3)
        return THREE;

    return TWO;
}

std::map<char, int> cardsToValue{{'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10}, {'9', 9},
                                {'8', 8}, {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2}};

bool compare_hands(const hand& firstHand, const hand& secondHand)
{
    if (firstHand.type < secondHand.type)
        return true;
    else if (firstHand.type > secondHand.type)
        return false;

    int index = 0;
    while (firstHand.cards[index] == secondHand.cards[index])
        index++;

    return cardsToValue[firstHand.cards[index]] > cardsToValue[secondHand.cards[index]];
}

int main()
{
    std::ifstream input("input.txt");

    std::vector<hand> hands{};

    char lineChar[100];
    while (input.getline(lineChar, 100))
    {
        std::string line{lineChar};

        std::vector<std::string> handString = split(line, ' ');

        std::string cards = handString[0];
        int bid = atoi(handString[1].c_str());

        hand newHand = create_hand(cards, bid);
        set_hand_type(newHand, get_hand_type(newHand));
        hands.push_back(newHand);
    }

    std::sort(hands.begin(), hands.end(), compare_hands);

    uint64_t sum = 0;
    int rank = (int)hands.size();

    for (const hand& h : hands)
    {
        sum += h.bid * rank;
        rank--;
    }

    std::cout << sum << '\n';

    return 0;
}