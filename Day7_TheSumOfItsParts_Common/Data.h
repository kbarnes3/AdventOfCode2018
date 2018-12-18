#pragma once
#include <array>

struct Dependency
{
    wchar_t Step;
    wchar_t Requirement;
};

// Convert input data with this regex:
// %s/Step \(\w\) must be finished before step \(\w\) can begin\./    { L'\2', L'\1' },
const std::array<Dependency, 7> sample_steps = { {
    { L'A', L'C' },
    { L'F', L'C' },
    { L'B', L'A' },
    { L'D', L'A' },
    { L'E', L'B' },
    { L'E', L'D' },
    { L'E', L'F' },
} };
