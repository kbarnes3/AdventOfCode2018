// Day2_InventoryManagementSystem_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Data.h"

template<size_t Rows, size_t Columns>
void solve(_In_ const std::array<std::array<wchar_t, Columns>, Rows>& input)
{
    for (size_t i = 0; i < input.size(); i++)
    {
        const std::array<wchar_t, Columns>& currentBoxId = input[i];
        for (size_t j = 0; j < i; j++)
        {
            const std::array<wchar_t, Columns>& comparingBoxId = input[j];
            size_t differences = 0;

            for (size_t k = 0; k < currentBoxId.size(); k++)
            {
                if (currentBoxId[k] != comparingBoxId[k])
                {
                    differences++;
                    if (differences > 1)
                    {
                        break;
                    }
                }
            }

            if (differences == 1)
            {
                for (size_t k = 0; k < currentBoxId.size(); k++)
                {
                    if (currentBoxId[k] == comparingBoxId[k])
                    {
                        std::wcout << currentBoxId[k];
                    }
                }
                std::wcout << std::endl;
                return;
            }
        }
    }

    std::wcout << L"No matches found" << std::endl;
}

int main()
{
    solve(real_boxids);
}
