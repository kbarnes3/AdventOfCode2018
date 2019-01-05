// Day11_ChronalCharge_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

int computePowerLevel(int x, int y, int serialNumber)
{
    int rackId = x + 10;
    int powerLevel = rackId * y;
    powerLevel += serialNumber;
    powerLevel *= rackId;
    powerLevel /= 100;
    powerLevel %= 10;
    powerLevel -= 5;

    return powerLevel;
}

void solve(int serialNumber)
{
    int powerLevel = computePowerLevel(3, 5, serialNumber);
    std::wcout << powerLevel << std::endl;
}

int main()
{
    solve(8);
    return 0;
}
