// Day8_MemoryManeuver_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Data.h>
#include "NodeProcessor.h"


template<size_t Size>
void solve(_In_ const std::array<unsigned short, Size>& license)
{
    NodeProcessor<Size> node(license.cbegin());
    unsigned short value = node.GetValue();

    std::wcout << value << std::endl;
}

int main()
{
    solve(inputLicense);
}
