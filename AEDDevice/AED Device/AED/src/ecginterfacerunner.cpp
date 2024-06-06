#include "ecginterfacerunner.h"

ECGInterfaceRunner::ECGInterfaceRunner(QObject *parent)
    : QObject{parent}
{
    // Access the mainwindow through the 'parent' object
}

void ECGInterfaceRunner::startCPRProcess()
{

}

void ECGInterfaceRunner::startShockProcess()
{

}

int ECGInterfaceRunner::cprState() const
{
    return m_cprState;
}

void ECGInterfaceRunner::setCprState(int newCprState)
{
    if (m_cprState == newCprState)
        return;

    m_cprState = newCprState;
    emit cprStateChanged(newCprState);
}

void ECGInterfaceRunner::handleCardiacEmmergencies()
{
    // Handle each cardiac emmergency and how to resolve it
    switch(m_cardiacEmmergency)
    {
        case CardiacEmmergencies::NO_EMMERGENCY:
        {
            // Handle resetting any flags/labels/etc
            break;
        }

        // case CardiacEmmergencies::EMMERGENCY_A: {}
    }
}

int ECGInterfaceRunner::cardiacEmmergency() const
{
    return m_cardiacEmmergency;
}

void ECGInterfaceRunner::setCardiacEmmergency(int newCardiacEmmergency)
{
    if (m_cardiacEmmergency == newCardiacEmmergency)
        return;
    m_cardiacEmmergency = newCardiacEmmergency;
    emit cardiacEmmergencyChanged();
}
