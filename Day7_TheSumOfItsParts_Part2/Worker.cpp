#include "pch.h"
#include "Worker.h"

Worker::Worker(_In_ StepManager& stepManager) :
    m_stepManager(stepManager),
    m_currentStep(L'\0'),
    m_remainingWork(0U)
{

}

bool Worker::Tick()
{
    // Attempt to get some work if we don't have any
    if (m_currentStep == L'\0')
    {
        std::pair<wchar_t, unsigned int> nextStep = m_stepManager.GetNextStep();
        if (nextStep.first == L'\0')
        {
            return false;
        }
        else
        {
            m_currentStep = nextStep.first;
            m_remainingWork = nextStep.second;
        }
    }
    else
    {
        m_remainingWork--;
    }

    // Check to see if we completed the work
    if (m_remainingWork == 0)
    {
        m_stepManager.CompleteStep(m_currentStep);
        m_currentStep = L'\0';
    }

    return true;
}
