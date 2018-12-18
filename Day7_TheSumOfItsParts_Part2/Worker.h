#pragma once
#include "StepManager.h"

class Worker
{
public:
    Worker(_In_ StepManager& stepManager);

    bool Tick();

private:
    StepManager& m_stepManager;
    wchar_t m_currentStep;
    unsigned int m_remainingWork;
};