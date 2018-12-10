#pragma once

struct Coordinate
{
    size_t X;
    size_t Y;
    bool Infinite;
    size_t ClosestArea;
};

// Convert with the following regex:
// '<,'>s/\(.*\)/    { \1, false, 0 },
std::array<Coordinate, 6> sample_coordinates = { {
    { 1, 1, false, 0 },
    { 1, 6, false, 0 },
    { 8, 3, false, 0 },
    { 3, 4, false, 0 },
    { 5, 5, false, 0 },
    { 8, 9, false, 0 },
} };

