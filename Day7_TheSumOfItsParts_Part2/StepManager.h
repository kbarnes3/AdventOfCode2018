#pragma once
class StepManager
{
public:
    StepManager(_In_ const std::map<wchar_t, std::set<wchar_t>>& steps, unsigned int startingCost);

    std::pair<wchar_t, unsigned int> GetNextStep();
    void CompleteStep(_In_ wchar_t step);
    void FlushCompleteQueue();

private:
    wchar_t PopWaitingStep();
    unsigned int GetCostOfStep(_In_ wchar_t step);

    std::map<wchar_t, std::set<wchar_t>> m_pendingSteps;
    std::set<wchar_t> m_completedSteps;
    std::vector<wchar_t> m_pendingCompletedSteps;
    unsigned int m_startingCost;
};
