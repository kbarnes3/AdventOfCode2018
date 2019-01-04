// Day10_TheStarsAlign_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Data.h>
#include "SparseGrid.h"

void markLetterAsSeen(_In_ SparseGrid& grid, _In_ int startX, _In_ int startY)
{
    std::queue<Position> pointsInLetter;
    pointsInLetter.push({ startX, startY });
    while (!pointsInLetter.empty())
    {
        Position& point = pointsInLetter.front();
        grid.Insert(point.X, point.Y, GridValue::Seen);

        // Left
        Position neighbor = { point.X - 1, point.Y };
        GridValue neighborValue = grid.GetValue(neighbor.X, neighbor.Y);
        if (neighborValue == GridValue::Unseen)
        {
            pointsInLetter.push(neighbor);
        }

        // Right
        neighbor = { point.X + 1, point.Y };
        neighborValue = grid.GetValue(neighbor.X, neighbor.Y);
        if (neighborValue == GridValue::Unseen)
        {
            pointsInLetter.push(neighbor);
        }

        // Up
        neighbor = { point.X, point.Y - 1 };
        neighborValue = grid.GetValue(neighbor.X, neighbor.Y);
        if (neighborValue == GridValue::Unseen)
        {
            pointsInLetter.push(neighbor);
        }

        // Down
        neighbor = { point.X, point.Y + 1 };
        neighborValue = grid.GetValue(neighbor.X, neighbor.Y);
        if (neighborValue == GridValue::Unseen)
        {
            pointsInLetter.push(neighbor);
        }

        pointsInLetter.pop();
    }
}

size_t countLetters(_In_ SparseGrid& grid)
{
    size_t letters = 0;
    SparseGrid::Bounds bounds = grid.GetBounds();

    for (int y = bounds.MinY; y <= bounds.MaxY; y++)
    {
        for (int x = bounds.MinX; x <= bounds.MaxX; x++)
        {
            GridValue value = GridValue::Empty;
            value = grid.GetValue(x, y);
            if (value == GridValue::Unseen)
            {
                letters++;
                markLetterAsSeen(grid, x, y);
            }
        }
    }

    return letters;
}

std::string createTempFilename()
{
    char dirname[MAX_PATH + 1] = {};
    char filename[MAX_PATH] = {};
    GetTempPathA(ARRAYSIZE(dirname), dirname);
    GetTempFileNameA(dirname, "AOC", 0, filename);

    std::string tempFileName(filename);

    return tempFileName;
}

void printGrid(_In_ const SparseGrid& grid, _In_ std::ofstream& file)
{
    SparseGrid::Bounds bounds = grid.GetBounds();
    const std::map<GridValue, char> printedValues = {
        {GridValue::Empty, ' '},
        {GridValue::Unseen, '?'},
        {GridValue::Seen, '#'} };

    for (int y = bounds.MinY; y <= bounds.MaxY; y++)
    {
        for (int x = bounds.MinX; x <= bounds.MaxX; x++)
        {
            GridValue value = GridValue::Empty;
            value = grid.GetValue(x, y);
            file << printedValues.at(value);
        }
        file << std::endl;
    }
}

void displayGrid(_In_ const SparseGrid& grid)
{
    std::string filename = createTempFilename();
    std::ofstream file;
    file.open(filename);

    printGrid(grid, file);

    file.close();

    ShellExecuteA(NULL, nullptr, filename.data(), nullptr, nullptr, SW_SHOW);
}

template <size_t Size>
bool solveAtTime(_In_ const std::array<Point, Size>& inputPoints, _In_ int seconds)
{
    SparseGrid grid;
    std::for_each(inputPoints.cbegin(), inputPoints.cend(),
        [&grid, seconds](_In_ const Point point)
    {
        int x = point.Position.X + (point.Velocity.XPerSecond * seconds);
        int y = point.Position.Y + (point.Velocity.YPerSecond * seconds);

        grid.Insert(x, y, GridValue::Unseen);
    });

    // The sample input had 2 letters with 31 points, or 15.5 points per letter.
    // Set our threshold to be about half that.
    size_t letterThreshold = Size / 8;
    size_t letterCount = countLetters(grid);

    std::wcout << L"After " << seconds << L" seconds, there are " << letterCount << L" letters." << std::endl;

    if (letterCount <= letterThreshold)
    {
        displayGrid(grid);
        return true;
    }
    else
    {
        return false;
    }
}

template <size_t Size>
void solve(_In_ const std::array<Point, Size>& inputPoints)
{
    int seconds = 0;
    bool solved = false;
    while (!solved)
    {
        solved = solveAtTime(inputPoints, seconds);
        seconds++;
    }
}

int main()
{
    solve(samplePoints);
    return 0;
}
