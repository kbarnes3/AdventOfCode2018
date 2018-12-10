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

std::array<Coordinate, 50> input_coordinates = { {
    { 154, 159, false, 0 },
    { 172, 84, false, 0 },
    { 235, 204, false, 0 },
    { 181, 122, false, 0 },
    { 161, 337, false, 0 },
    { 305, 104, false, 0 },
    { 128, 298, false, 0 },
    { 176, 328, false, 0 },
    { 146, 71, false, 0 },
    { 210, 87, false, 0 },
    { 341, 195, false, 0 },
    { 50, 96, false, 0 },
    { 225, 151, false, 0 },
    { 86, 171, false, 0 },
    { 239, 68, false, 0 },
    { 79, 50, false, 0 },
    { 191, 284, false, 0 },
    { 200, 122, false, 0 },
    { 282, 240, false, 0 },
    { 224, 282, false, 0 },
    { 327, 74, false, 0 },
    { 158, 289, false, 0 },
    { 331, 244, false, 0 },
    { 154, 327, false, 0 },
    { 317, 110, false, 0 },
    { 272, 179, false, 0 },
    { 173, 175, false, 0 },
    { 187, 104, false, 0 },
    { 44, 194, false, 0 },
    { 202, 332, false, 0 },
    { 249, 197, false, 0 },
    { 244, 225, false, 0 },
    { 52, 127, false, 0 },
    { 299, 198, false, 0 },
    { 123, 198, false, 0 },
    { 349, 75, false, 0 },
    { 233, 72, false, 0 },
    { 284, 130, false, 0 },
    { 119, 150, false, 0 },
    { 172, 355, false, 0 },
    { 147, 314, false, 0 },
    { 58, 335, false, 0 },
    { 341, 348, false, 0 },
    { 236, 115, false, 0 },
    { 185, 270, false, 0 },
    { 173, 145, false, 0 },
    { 46, 288, false, 0 },
    { 214, 127, false, 0 },
    { 158, 293, false, 0 },
    { 237, 311, false, 0 },
} };
