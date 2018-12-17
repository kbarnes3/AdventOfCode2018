// Day6_ChronalCoordinates_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Data.h"

size_t distance(_In_ size_t x, _In_ size_t y, _In_ Coordinate& coordinate)
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
        max_x = std::max(max_x, coordinate.X);
        min_y = std::min(min_y, coordinate.Y);
        max_y = std::max(max_y, coordinate.Y);
    }

    // Next mark any coordinates along these bounds as having an infinite area
    for (Coordinate& coordinate : coordinates)
    {
        if (coordinate.X == min_x || coordinate.X == max_x ||
            coordinate.Y == min_y || coordinate.Y == max_y)
        {
            coordinate.Infinite = true;
        }
    }

    // Then look at points within these bounds and see which coordinate it is closest to
    for (size_t x = min_x + 1; x < max_x; x++)
    {
        for (size_t y = min_y + 1; y < max_y; y++)
        {
            typename std::array<Coordinate, Size>::iterator iter = coordinates.begin();
            typename std::array<Coordinate, Size>::iterator closest = iter;
            size_t closestDistance = distance(x, y, *iter);
            iter++;

            while (iter != coordinates.end())
            {
                size_t iterDistance = distance(x, y, *iter);
                // If the new distance is strictly less than the old one, we have a new candidate
                if (iterDistance < closestDistance)
                {
                    closest = iter;
                    closestDistance = iterDistance;
                }
                else if (iterDistance == closestDistance)
                {
                    // If the new distance is the same, mark this node as tied for now
                    closest = coordinates.end();
                }

                iter++;
            }

            // If there was one node that was strictly closer than all the others, increment its count of closest spaces
            if (closest != coordinates.end())
            {
                closest->ClosestArea++;
            }
        }
    }

    // Finally find the coordinate with the largest finite closest area
    typename std::array<Coordinate, Size>::const_iterator iter = std::max_element(
        coordinates.cbegin(),
        coordinates.cend(),
        [](
            _In_ const Coordinate& a,
            _In_ const Coordinate& b
            ) -> bool
        {
            // All Infinite spaces are considered equally low elements
            if (a.Infinite && b.Infinite)
            {
                return false;
            }
            if (a.Infinite)
            {
                return true;
            }
            if (b.Infinite)
            {
                return false;
            }
            return a.ClosestArea < b.ClosestArea;
        }
    );

        std::wcout << iter->ClosestArea << std::endl;
}

int main()
{
    solve(input_coordinates);
}
