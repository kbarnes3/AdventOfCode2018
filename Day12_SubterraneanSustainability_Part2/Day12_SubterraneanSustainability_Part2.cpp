// Day12_SubterraneanSustainability_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

std::map<int64_t, bool> processGeneration(const std::map<int64_t, bool>& prevGeneration, const std::map<std::tuple<bool, bool, bool, bool, bool>, bool>& rules, bool allowMissingRules)
{
    std::map<int64_t, bool> pots;
    // Degenerate case, an empty map produces an empty map
    if (prevGeneration.cbegin() == prevGeneration.cend())
    {
        return pots;
    }

    // Get the range of pots we need to consider. We need to go two left and right of the previous generation
    int64_t leftmost = prevGeneration.cbegin()->first - 2;
    int64_t rightmost = prevGeneration.crbegin()->first + 2;

    for (int64_t pot = leftmost; pot <= rightmost; ++pot)
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

int64_t sumPots(const std::map<int64_t, bool>& pots)
{
    // Take the sum of all the indices of pots that contain a plant
    int64_t sum = std::accumulate(pots.cbegin(), pots.cend(), 0,
        [](int64_t a, const std::pair<int64_t, bool>& b) -> int64_t
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

    return sum;
}

template<size_t Count>
void solve(const std::array<bool, Count>& initialState, const std::map<std::tuple<bool, bool, bool, bool, bool>, bool>& rules, bool allowMissingRules)
{
    std::map<int64_t, bool> pots;
    for (int i = 0; i < Count; ++i)
    {
        if (initialState[i])
        {
            pots[i] = initialState[i];
        }
    }
    
    uint64_t generation = 1;
    const uint64_t totalGenerations = 50000000000;
    int64_t pastSum = sumPots(pots);
    int64_t difference = 0;
    int64_t differenceHits = 0;

    for (; generation <= totalGenerations; ++generation)
    {
        pots = processGeneration(pots, rules, allowMissingRules);
        int64_t sum = sumPots(pots);
        int64_t newDifference = sum - pastSum;
        pastSum = sum;
        if (newDifference == difference)
        {
            ++differenceHits;
        }
        else
        {
            difference = newDifference;
            differenceHits = 1;
        }

        if (differenceHits > 10)
        {
            break;
        }
    }

    // After we find the pattern, just do the math instead of counting each generation
    uint64_t remainingGenerations = totalGenerations - generation;
    int64_t sum = pastSum + remainingGenerations * difference;


    std::wcout << sum << std::endl;
}

int main()
{
    solve(inputInitialState, inputRules, false);
    return 0;
}
