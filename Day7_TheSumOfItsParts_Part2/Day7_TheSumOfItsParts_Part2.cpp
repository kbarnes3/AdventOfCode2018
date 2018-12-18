// Day7_TheSumOfItsParts_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Data.h"
#include "StepManager.h"
#include "Worker.h"
#include <iostream>

template<size_t WorkerCount, size_t Size>
void solve(_In_ const std::array<Dependency, Size>& input_steps, _In_ unsigned int starting_cost)
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

    StepManager stepManager(steps, starting_cost);
    std::vector<Worker> workers(WorkerCount, Worker(stepManager));

    // Now tick until none of the workers accomplish anything
    unsigned int tick = 0;
    do
    {
        bool workHappened = std::accumulate(
            workers.begin(),
            workers.end(),
            false,
            [](_In_ bool a, _In_ Worker& b) -> bool
            {
                bool didWork = b.Tick();
                return a || didWork;
            }
        );

        if (!workHappened)
        {
            std::wcout << tick << std::endl;
            return;
        }

        stepManager.FlushCompleteQueue();
        tick++;

    } while (true);
}

int main()
{
    //solve<2>(sample_steps, 0);
    solve<5>(input_steps, 60);
}
