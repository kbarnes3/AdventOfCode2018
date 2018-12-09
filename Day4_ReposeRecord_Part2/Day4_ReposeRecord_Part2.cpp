// Day4_ReposeRecord_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Data.h"

template<size_t Number>
void solve(_In_ const std::array<Record, Number>& input_records)
{
    std::array<Record, Number> sorted_records = input_records;
    std::sort(
        sorted_records.begin(),
        sorted_records.end(),
        [](const Record& a,
            const Record& b) -> bool
    {
        if (a.TimeStamp.Year != b.TimeStamp.Year)
        {
            return a.TimeStamp.Year < b.TimeStamp.Year;
        }
        if (a.TimeStamp.Month != b.TimeStamp.Month)
        {
            return a.TimeStamp.Month < b.TimeStamp.Month;
        }
        if (a.TimeStamp.Day != b.TimeStamp.Day)
        {
            return a.TimeStamp.Day < b.TimeStamp.Day;
        }
        if (a.TimeStamp.Hour != b.TimeStamp.Hour)
        {
            return a.TimeStamp.Hour < b.TimeStamp.Hour;
        }
        if (a.TimeStamp.Minute < b.TimeStamp.Minute)
        {
            return a.TimeStamp.Minute < b.TimeStamp.Minute;
        }
        return false;
    });

    // Find which guards were asleep on which minutes
    std::map<GuardId, std::vector<unsigned int>> minutesSlept;

    bool guardAssigned = false;
    GuardId currentGuard = 0;
    bool guardAsleep = false;
    unsigned int asleepTime = 0;

    for (const Record& record : sorted_records)
    {
        switch (record.Event)
        {
        case EventType::GuardChange:
            currentGuard = record.Guard;
            guardAssigned = true;
            break;
        case EventType::FallAsleep:
            if (!guardAssigned)
            {
                std::wcerr << L"Error: Guard not assigned" << std::endl;
                return;
            }
            if (guardAsleep)
            {
                std::wcerr << L"Error: Guard already asleep" << std::endl;
                return;
            }
            asleepTime = record.TimeStamp.Minute;
            guardAsleep = true;
            break;
        case EventType::WakeUp:
        {
            if (!guardAssigned)
            {
                std::wcerr << L"Error: Guard not assigned" << std::endl;
                return;
            }
            if (!guardAsleep)
            {
                std::wcerr << L"Error: Guard already awake" << std::endl;
                return;
            }

            // Mark every minute in [asleepTime, currentTime) as a minute this guard was asleep
            unsigned int currentTime = record.TimeStamp.Minute;
            for (unsigned int minuteSlept = asleepTime; minuteSlept < currentTime; minuteSlept++)
            {
                minutesSlept[currentGuard].push_back(minuteSlept);
            }
            guardAsleep = false;
            break;
        }
        }
    }

    // Find the minute each guard slept the most
    std::map<GuardId, ptrdiff_t> sleepiestMinutes;
    for (const std::pair<GuardId, std::vector<unsigned int>>& guardStats : minutesSlept)
    {
        std::array<unsigned int, 60> minutesHistogram = {};
        for (unsigned int minute : guardStats.second)
        {
            minutesHistogram[minute]++;
        }
        ptrdiff_t sleepiestMinute = std::max_element(minutesHistogram.begin(), minutesHistogram.end()) - minutesHistogram.begin();

        sleepiestMinutes[guardStats.first] = sleepiestMinute;
    }

    std::map<GuardId, ptrdiff_t>::const_iterator sleepiestGuard = std::max_element(
        sleepiestMinutes.cbegin(),
        sleepiestMinutes.cend(),
        [](const std::pair<GuardId, ptrdiff_t>& a,
            const std::pair<GuardId, ptrdiff_t>& b)
        {
            return a.second < b.second;
        });

    std::wcout << sleepiestGuard->first * sleepiestGuard->second << std::endl;

}

int main()
{
    solve(sample_records);
}
