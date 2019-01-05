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

int computeTotalPower(const std::array<std::array<int, 300>, 300>& fuelCells, int x, int y)
{
    int power = 0;
    for (int yOffset = y; yOffset < y + 3; yOffset++)
    {
        for (int xOffset = x; xOffset < x + 3; xOffset++)
        {
            power += fuelCells[yOffset][xOffset];
        }
    }

    return power;
}

void solve(int serialNumber)
{
    std::array<std::array<int, 300>, 300> fuelCells;
    for (int y = 0; y < 300; y++)
    {
        for (int x = 0; x < 300; x++)
        {
            int powerLevel = computePowerLevel(x+1, y+1, serialNumber);
            fuelCells[y][x] = powerLevel;
        }
    }

    int maxX = 0;
    int maxY = 0;
    int maxPower = -100;

    for (int y = 0; y < 297; y++)
    {
        for (int x = 0; x < 297; x++)
        {
            int totalPower = computeTotalPower(fuelCells, x, y);
            if (totalPower > maxPower)
            {
                maxPower = totalPower;
                maxX = x+1;
                maxY = y+1;
            }
        }
    }
    
    std::wcout << maxX << L',' << maxY << std::endl;
}

int main()
{
    solve(8979);
    return 0;
}
