// Day10_TheStarsAlign_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Data.h>
#include "SparseGrid.h"

template <size_t Size>
void solve(_In_ const std::array<Point, Size>& inputPoints)
{
    SparseGrid grid;
    std::for_each(inputPoints.cbegin(), inputPoints.cend(),
        [&grid](_In_ const Point point)
        {
            Position pos = point.Position;
            grid.Insert(pos, GridValue::Unseen);
        });
}

int main()
{
    solve(samplePoints);
    return 0;
}
