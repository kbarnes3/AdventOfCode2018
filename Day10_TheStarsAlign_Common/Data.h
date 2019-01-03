#pragma once
#include <array>

struct Position
{
    int x;
    int y;
};

struct Velocity
{
    int xPerSecond;
    int yPerSecond;
};

struct Point
{
    Position Position;
    Velocity Velocity;
};

// Convert the input data with this regex:
// %s/position = < *\(-\?\d\+\), \(-\?\d\+\)> velocity = < *\(-\?\d\+\), \(-\?\d\+\)>/    { { \1, \2 }, { \3, \4 } },
std::array<Point, 31> samplePoints = { {
    { { 9, 1 }, { 0, 2 } },
    { { 7, 0 }, { -1, 0 } },
    { { 3, -2 }, { -1, 1 } },
    { { 6, 10 }, { -2, -1 } },
    { { 2, -4 }, { 2, 2 } },
    { { -6, 10 }, { 2, -2 } },
    { { 1, 8 }, { 1, -1 } },
    { { 1, 7 }, { 1, 0 } },
    { { -3, 11 }, { 1, -2 } },
    { { 7, 6 }, { -1, -1 } },
    { { -2, 3 }, { 1, 0 } },
    { { -4, 3 }, { 2, 0 } },
    { { 10, -3 }, { -1, 1 } },
    { { 5, 11 }, { 1, -2 } },
    { { 4, 7 }, { 0, -1 } },
    { { 8, -2 }, { 0, 1 } },
    { { 15, 0 }, { -2, 0 } },
    { { 1, 6 }, { 1, 0 } },
    { { 8, 9 }, { 0, -1 } },
    { { 3, 3 }, { -1, 1 } },
    { { 0, 5 }, { 0, -1 } },
    { { -2, 2 }, { 2, 0 } },
    { { 5, -2 }, { 1, 2 } },
    { { 1, 4 }, { 2, 1 } },
    { { -2, 7 }, { 2, -2 } },
    { { 3, 6 }, { -1, -1 } },
    { { 5, 0 }, { 1, 0 } },
    { { -6, 0 }, { 2, 0 } },
    { { 5, 9 }, { 1, -2 } },
    { { 14, 7 }, { -2, 0 } },
    { { -3, 6 }, { 2, -1 } },
} };
