// Day6_ChronalCoordinates_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Data.h"

size_t distance(_In_ size_t x, _In_ size_t y, _In_ const Coordinate& coordinate)
{
    size_t distance = 0;
    if (coordinate.X > x)
    {
        distance = coordinate.X - x;
    }
    else
    {
        distance = x - coordinate.X;
    }

    if (coordinate.Y > y)
    {
        distance += coordinate.Y - y;
    }
    else
    {
        distance += y - coordinate.Y;
    }

    return distance;
}

template<size_t Size>
void solve(_In_ std::array<Coordinate, Size>& coordinates, _In_ size_t maxDistance)
{
    // First find the intersting bounds by finding the min and max X and Y values
    size_t min_x = (coordinates[0]).X;
    size_t max_x = (coordinates[0]).X;
    size_t min_y = (coordinates[0]).Y;
    size_t max_y = (coordinates[0]).Y;
    
    size_t closeRegion = 0;

    for (Coordinate& coordinate : coordinates)
    {
        min_x = std::min(min_x, coordinate.X);
        max_x = std::max(min_x, coordinate.X);
        min_y = std::min(min_y, coordinate.Y);
        max_y = std::max(min_y, coordinate.Y);
    }

    // Then look at points within these bounds and compute its total distance
    for (size_t x = min_x; x <= max_x; x++)
    {
        for (size_t y = min_y; y <= max_y; y++)
        {
            size_t totalDistance = std::accumulate(
                coordinates.cbegin(),
                coordinates.cend(),
                0,
                [x, y](_In_ size_t runningDistance, _In_ const Coordinate& coordinate) -> size_t
                {
                    size_t newDistance = distance(x, y, coordinate);
                    return runningDistance + newDistance;
                });

            if (totalDistance < maxDistance)
            {
                closeRegion++;
            }

        }
    }

    std::wcout << closeRegion << std::endl;
}

int main()
{
    solve(sample_coordinates, 32);
    //solve(input_coordinates, 10000);
}
