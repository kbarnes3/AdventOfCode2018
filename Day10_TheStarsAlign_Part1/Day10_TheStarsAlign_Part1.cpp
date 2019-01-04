// Day10_TheStarsAlign_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Data.h>
#include "SparseGrid.h"

std::string createTempFilename()
{
    char dirname[MAX_PATH + 1] = {};
    char filename[MAX_PATH] = {};
    GetTempPathA(ARRAYSIZE(dirname), dirname);
    GetTempFileNameA(dirname, "AOC", 0, filename);

    std::string tempFileName(filename);

    return tempFileName;
}

void printGrid(_In_ const SparseGrid& grid)
{
    std::string filename = createTempFilename();
    std::ofstream file;
    file.open(filename);

    SparseGrid::Bounds bounds = grid.GetBounds();
    for (int x = bounds.MinX; x <= bounds.MaxX; x++)
    {
        for (int y = bounds.MinY; y <= bounds.MaxY; y++)
        {
            GridValue value = GridValue::Empty;
            value = grid.GetValue(x, y);
        }
    }

    file.close();
}

template <size_t Size>
void solve(_In_ const std::array<Point, Size>& inputPoints)
{
    SparseGrid grid;
    std::for_each(inputPoints.cbegin(), inputPoints.cend(),
        [&grid](_In_ const Point point)
        {
            Position pos = point.Position;
            grid.Insert(pos.X, pos.Y, GridValue::Unseen);
        });

    printGrid(grid);
}

int main()
{
    solve(samplePoints);
    return 0;
}
