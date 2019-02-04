// Day12_SubterraneanSustainability_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Data.h"

template<typename Key, typename Value>
Value defaultAt(const std::map<Key, Value>& map, const Key& key, const Value& def)
{
    typename std::map<Key, Value>::const_iterator iter = map.find(key);
    if (iter != map.cend())
    {
        return iter->second;
    }
    else
    {
        return def;
    }
}

std::map<int, bool> processGeneration(const std::map<int, bool>& prevGeneration, const std::map<std::tuple<bool, bool, bool, bool, bool>, bool>& rules, bool allowMissingRules)
{
    std::map<int, bool> pots;
    // Degenerate case, an empty map produces an empty map
    if (prevGeneration.cbegin() == prevGeneration.cend())
    {
        return pots;
    }

    // Get the range of pots we need to consider. We need to go two left and right of the previous generation
    int leftmost = prevGeneration.cbegin()->first - 2;
    int rightmost = prevGeneration.crbegin()->first + 2;

    for (int pot = leftmost; pot <= rightmost; ++pot)
    {
        // Build up the tuple
        std::tuple<bool, bool, bool, bool, bool> nearbyPots = {
            defaultAt(prevGeneration, pot - 2, false),
            defaultAt(prevGeneration, pot - 1, false),
            defaultAt(prevGeneration, pot, false),
            defaultAt(prevGeneration, pot + 1, false),
            defaultAt(prevGeneration, pot + 2, false)
        };

        bool plant = false;
        if (allowMissingRules)
        {
            plant = defaultAt(rules, nearbyPots, false);
        }
        else
        {
            plant = rules.at(nearbyPots);
        }

        if (plant)
        {
            pots[pot] = plant;
        }
    }

    return pots;
}

template<size_t Count>
void solve(const std::array<bool, Count>& initialState, const std::map<std::tuple<bool, bool, bool, bool, bool>, bool>& rules, bool allowMissingRules)
{
    std::map<int, bool> pots;
    for (int i = 0; i < Count; ++i)
    {
        if (initialState[i])
        {
            pots[i] = initialState[i];
        }
    }

    for (unsigned int generation = 1; generation <= 20; ++generation)
    {
        pots = processGeneration(pots, rules, allowMissingRules);
    }

    // Take the sum of all the indices of pots that contain a plant after 20 generations
    int sum = std::accumulate(pots.cbegin(), pots.cend(), 0,
        [](int a, const std::pair<int, bool>& b)
        {
            if (b.second)
            {
                return a + b.first;
            }
            else
            {
                return a;
            }
        });

    std::wcout << sum << std::endl;
}

int main()
{
    solve(sampleInitialState, sampleRules, true);
    return 0;
}

