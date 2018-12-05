// Day3_NoMatterHowYouSliceIt_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Data.h"

template<size_t Count>
void solve(_In_ const std::array<Claim, Count> input)
{
    std::unique_ptr<std::array<std::array<size_t, 1000>, 1000>> fabric_storage =
        std::make_unique<std::array<std::array<size_t, 1000>, 1000>>();

    std::array<std::array<size_t, 1000>, 1000>& fabric = *fabric_storage.get();

    // Mark every square used in each claim
    for (const Claim& claim : input)
    {
        for (size_t i = claim.x; i < claim.x + claim.width; i++)
        {
            for (size_t j = claim.y; j < claim.y + claim.height; j++)
            {
                fabric[j][i]++;
            }
        }
    }

    // Count every square used more than once
    size_t duplicated = 0;
    for (const std::array<size_t, 1000>& row : fabric)
    {
        for (const size_t& cell : row)
        {
            if (cell >= 2)
            {
                duplicated++;
            }
        }
    }

    std::wcout << duplicated << std::endl;
}

int main()
{
    solve(input_claims);
}
