// Day7_TheSumOfItsParts_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Data.h"
#include <iostream>

void print_steps(_In_ const std::map<wchar_t, std::set<wchar_t>>& steps)
{
    for (const std::pair<wchar_t, std::set<wchar_t>>& value : steps)
    {
        std::wcout << L"Step " << value.first << L" depends on ";
        std::set<wchar_t>::const_iterator iter = value.second.cbegin();
        if (iter == value.second.cend())
        {
            std::wcout << L"nothing." << std::endl;
        }
        else
        {
            std::wcout << L'{' << *iter;
            iter++;
            while (iter != value.second.cend())
            {
                std::wcout << L", " << *iter;
                iter++;
            }
            std::wcout << L'}' << std::endl;
        }
    }
}

template<size_t Size>
void solve(_In_ const std::array<Dependency, Size>& input_steps)
{
    std::map<wchar_t, std::set<wchar_t>> steps;
    std::set<wchar_t> completedSteps;
    
    // Process the list of input and construct a map of steps to
    // the set of dependent steps each one has
    for (const Dependency& dependency : input_steps)
    {
        // Insert this dependency into steps. This may involve creating a new set or just inserting into an existing one
        std::map<wchar_t, std::set<wchar_t>>::iterator iter = steps.find(dependency.Step);
        if (iter == steps.end())
        {
            std::pair<wchar_t, std::set<wchar_t>> value = { dependency.Step, { dependency.Requirement } };
            steps.insert(value);
        }
        else
        {
            iter->second.insert(dependency.Requirement);
        }

        // Also make sure the requirement exists in our full set. If it doesn't, insert it with an empty set of dependencies
        iter = steps.find(dependency.Requirement);
        if (iter == steps.end())
        {
            std::pair<wchar_t, std::set<wchar_t>> value = { dependency.Requirement, {} };
            steps.insert(value);
        }
    }

    //print_steps(steps);
    
    // Now try and drain the map of steps by completing and removing steps we can
    // std::map is sorted, so starting at the front and matching the first one we can
    // will order things appropriately
    while (!steps.empty())
    {
        std::map<wchar_t, std::set<wchar_t>>::iterator iter = steps.begin();
        while (iter != steps.end())
        {
            bool allRequirementsDone = true;
            for (wchar_t requirement : iter->second)
            {
                if (completedSteps.count(requirement) == 0)
                {
                    allRequirementsDone = false;
                    break;
                }
            }

            if (allRequirementsDone)
            {
                std::wcout << iter->first;
                completedSteps.insert(iter->first);
                steps.erase(iter);
                break;
            }

            iter++;
        }

        if (iter == steps.end())
        {
            std::wcout << std::endl << L"No matches found" << std::endl;
        }
    }
    std::wcout << std::endl;
}

int main()
{
    solve(input_steps);
}
