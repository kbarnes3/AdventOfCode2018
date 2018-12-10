// Day6_ChronalCoordinates_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Data.h"

template<size_t Size>
void solve(_In_ std::array<Coordinate, Size>& coordinates)
{
    // First find the intersting bounds by finding the min and max X and Y values
    size_t min_x = (coordinates[0]).X;
    size_t max_x = (coordinates[0]).X;
    size_t min_y = (coordinates[0]).Y;
    size_t max_y = (coordinates[0]).Y;

    for (Coordinate& coordinate : coordinates)
    {
        min_x = std::min(min_x, coordinate.X);
        max_x = std::max(min_x, coordinate.X);
        min_y = std::min(min_y, coordinate.Y);
        max_y = std::max(min_y, coordinate.Y);
    }

    // Then look at points within these bounds and see which coordinate it is closest too
    for (size_t x = min_x + 1; x < max_x; x++)
    {
        for (size_t y = min_y + 1; y < max_y; y++)
        {

        }
    }
}

int main()
{
    solve(sample_coordinates);
}
