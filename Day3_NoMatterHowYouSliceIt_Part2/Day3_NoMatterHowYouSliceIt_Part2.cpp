// Day3_NoMatterHowYouSliceIt_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

    // Try and find a claim where every square of fabric was used exactly once
    for (const Claim& claim : input)
    {
        bool overclaimed = false;
        for (size_t i = claim.x; i < claim.x + claim.width; i++)
        {
            if (!overclaimed)
            {
                for (size_t j = claim.y; j < claim.y + claim.height; j++)
                {
                    if (fabric[j][i] > 1)
                    {
                        overclaimed = true;
                        break;
                    }
                }
            }
        }

        if (!overclaimed)
        {
            std::wcout << claim.claimId << std::endl;
            return;
        }
    }

    std::wcout << L"Nothing suitable found" << std::endl;
}

int main()
{
    solve(input_claims);
}
