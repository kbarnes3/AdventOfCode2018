// Day8_MemoryManeuver_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Data.h>
#include "NodeProcessor.h"


template<size_t Size>
void solve(_In_ const std::array<unsigned short, Size>& license)
{
    typename NodeProcessor<Size>::ProcessedNode node = 
        NodeProcessor<Size>::ProcessNode(license.cbegin());

    std::wcout << node.second << std::endl;
}

int main()
{
    solve(inputLicense);
}
