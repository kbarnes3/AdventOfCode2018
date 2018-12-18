#include "pch.h"
#include "StepManager.h"

StepManager::StepManager(_In_ const std::map<wchar_t, std::set<wchar_t>>& steps, unsigned int startingCost) :
    m_pendingSteps(steps),
    m_startingCost(startingCost)
{

}

std::pair<wchar_t, unsigned int> StepManager::GetNextStep()
{
    wchar_t step = PopWaitingStep();
    if (step != L'\0')
    {
        unsigned int cost = GetCostOfStep(step);
        return { step, cost };
    }
    else
    {
        return { L'\0', 0 };
    }
}

void StepManager::CompleteStep(_In_ wchar_t step)
{
    m_pendingCompletedSteps.push_back(step);
}

void StepManager::FlushCompleteQueue()
{
    std::for_each(m_pendingCompletedSteps.cbegin(), m_pendingCompletedSteps.cend(), 
        [this](_In_ wchar_t step)
        {
            m_completedSteps.insert(step);
        });
    m_pendingCompletedSteps.clear();
}

wchar_t StepManager::PopWaitingStep()
{
    std::map<wchar_t, std::set<wchar_t>>::iterator iter = m_pendingSteps.begin();
    while (iter != m_pendingSteps.end())
    {
        bool allRequirementsDone = true;
        for (wchar_t requirement : iter->second)
        {
            if (m_completedSteps.count(requirement) == 0)
            {
                allRequirementsDone = false;
                break;
            }
        }

        if (allRequirementsDone)
        {
            wchar_t step = iter->first;
            m_pendingSteps.erase(iter);
            return step;
        }

        iter++;
    }

    return L'\0';
}

unsigned int StepManager::GetCostOfStep(_In_ wchar_t step)
{
    unsigned int incrementalCost = step - L'A' + 1;
    return m_startingCost + incrementalCost;
}
