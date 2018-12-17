// Day6_ChronalCoordinates_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Data.h"

bool isOnXEdge(_In_ size_t min_x, _In_ size_t max_x, _In_ size_t x)
{
    return (x == min_x || x == max_x);
}

bool isOnYEdge(_In_ size_t min_y, _In_ size_t max_y, _In_ size_t y)
{
    return (y == min_y || y == max_y);
}

bool isOnEdge(_In_ size_t min_x, _In_ size_t max_x, _In_ size_t min_y, _In_ size_t max_y, _In_ size_t x, _In_ size_t y)
{
    return isOnXEdge(min_x, max_x, x) || isOnYEdge(min_y, max_y, y);
}

bool isOnCorner(_In_ size_t min_x, _In_ size_t max_x, _In_ size_t min_y, _In_ size_t max_y, _In_ size_t x, _In_ size_t y)
{
    return isOnXEdge(min_x, max_x, x) && isOnYEdge(min_y, max_y, y);
}

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

size_t projectFromEdge(_In_ size_t edgeDistance, _In_ size_t maxDistance, _In_ size_t countOfCoordinates)
{
    size_t closeNodes = 0;
    size_t currentDistance = edgeDistance;
    while (currentDistance < maxDistance)
    {
        closeNodes++;
        currentDistance += countOfCoordinates;
    }

    std::wcout << L"projectFromEdge(" << edgeDistance << L", " << maxDistance << L", " << countOfCoordinates << ") returned " << closeNodes << L"." << std::endl;

    return closeNodes;
}

size_t projectFromCorner(_In_ size_t cornerDistance, _In_ size_t maxDistance, _In_ size_t countOfCoordinates)
{
    // Figure out how far in a straight line we could go from this corner
    size_t straightLine = projectFromEdge(cornerDistance, maxDistance, countOfCoordinates);

    // For every distance step we can go from the corner, there are more possible nodes an equal distance away
    // at different diagonal lines. If straightLine is 1, the only spot is the corner itself. If straightLine
    // is 2, there are two extra spaces, one horizontal and one vertical. If straightLine is 3, there are 3
    // extra spaces, 2 horizontal spaces away (2,0), 2 vertical spaces away (0,2), and (1,1) spaces away.
    size_t closeNodes = 0;
    for (size_t i = 1; i <= straightLine; i++)
    {
        closeNodes += i;
    }

    std::wcout << L"projectFromCorner(" << cornerDistance << L", " << maxDistance << L", " << countOfCoordinates << ") returned " << closeNodes << L"." << std::endl;

    return closeNodes;
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
        max_x = std::max(max_x, coordinate.X);
        min_y = std::min(min_y, coordinate.Y);
        max_y = std::max(max_y, coordinate.Y);
    }

    // Then look at points within these bounds and compute its total distance
    for (size_t x = min_x; x <= max_x; x++)
    {
        for (size_t y = min_y; y <= max_y; y++)
        {
            size_t totalDistance = std::accumulate(
                coordinates.cbegin(),
                coordinates.cend(),
                static_cast<size_t>(0),
                [x, y](_In_ size_t runningDistance, _In_ const Coordinate& coordinate) -> size_t
                {
                    size_t newDistance = distance(x, y, coordinate);
                    return runningDistance + newDistance;
                });

            if (totalDistance < maxDistance)
            {
                // If this point is close enough, check if it is along the border so we can count the points outside of it
                if (isOnCorner(min_x, max_x, min_y, max_y, x, y))
                {
                    closeRegion += projectFromCorner(totalDistance, maxDistance, Size);
                }
                else if (isOnEdge(min_x, max_x, min_y, max_y, x, y))
                {
                    closeRegion += projectFromEdge(totalDistance, maxDistance, Size);
                }
                else
                {
                    closeRegion++;
                }
            }

        }
    }

    std::wcout << closeRegion << std::endl;
}

int main()
{
    //solve(sample_coordinates, 32);
    solve(input_coordinates, 10000);
}
