#pragma once
#include <array>

// Convert the input data with this regex:
// '<,'>s/\([ \n]\)/,\1/g

const std::array<unsigned short, 16> sampleLicense = { {
    2, 3, 0, 3, 10, 11, 12, 1, 1, 0, 1, 99, 2, 1, 1, 2,
} };
