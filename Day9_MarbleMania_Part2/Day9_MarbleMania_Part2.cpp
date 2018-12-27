// Day9_MarbleMania_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "circular_list.h"

void solve(_In_ unsigned int numberOfPlayers, _In_ unsigned int lastMarble)
{
    circular_list marbleCirle;
    circular_list::iterator iter = marbleCirle.insert(marbleCirle.begin(), 0);

    std::vector<unsigned int> scores(numberOfPlayers, 0);

    unsigned int currentPlayer = 0;
    unsigned int currentMarble = 1;

    while (currentMarble <= lastMarble)
    {
        if (currentMarble % 23 == 0)
        {
            scores[currentPlayer] += currentMarble;
            for (size_t i = 0; i < 7; i++)
            {
                --iter;
            }
            scores[currentPlayer] += *iter;
            iter = marbleCirle.erase(iter);
        }
        else
        {
            ++iter;
            iter = marbleCirle.insert(iter, currentMarble);
        }

        currentPlayer++;
        if (currentPlayer >= numberOfPlayers)
        {
            currentPlayer = 0;
        }
        currentMarble++;
    }

    std::vector<unsigned int>::const_iterator max =
        std::max_element(scores.cbegin(), scores.cend());

    std::wcout << *max << std::endl;
}

int main()
{
    //solve(9, 25);
    //solve(10, 1618);
    //solve(13, 7999);
    //solve(17, 1104);
    //solve(21, 6111);
    //solve(30, 5807);
    solve(411, 71170);
    return 0;
}
