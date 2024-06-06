#ifndef ECGINTERFACERUNNER_H
#define ECGINTERFACERUNNER_H

#include <QObject>

// This class should handle all ECG related stuff
// Some functionality in the dashboardform.h can/should be moved here

class ECGInterfaceRunner : public QObject
{
    Q_OBJECT
public:
    enum CPRState {
        NONE = 0
        // Any other state you need to have for the CPR
    };

    enum CardiacEmmergencies {
        NO_EMMERGENCY = 0
        // All states of cardiac emmergencies
    };

    enum SimulatedScenarios {
        // Add scenarios here that you need to handle and simulate
        // Add functions to handle cases
    };

    explicit ECGInterfaceRunner(QObject *parent = nullptr);

    // Property to hold CPR State
    Q_PROPERTY(int cprState READ cprState WRITE setCprState NOTIFY cprStateChanged FINAL);

    // Property to hold current cardiac emmergencies
    Q_PROPERTY(int cardiacEmmergency READ cardiacEmmergency WRITE setCardiacEmmergency NOTIFY cardiacEmmergencyChanged FINAL);

    // Function to run the CPR process
    void startCPRProcess();

    // Function to call to run a Shockable
    void startShockProcess();

    // Setter/Getter for CPR State
    int cprState() const;
    void setCprState(int newCprState);

    int cardiacEmmergency() const;
    void setCardiacEmmergency(int newCardiacEmmergency);

private slots:
    // Slot to handle Cardiac emmergencies
    void handleCardiacEmmergencies();

signals:
    // Emit this signal if a chest compression is detected
    // Connect to this one to any slot ...
    void chestCompressionChanged();

    // Signal emitted when CPR state changes
    void cprStateChanged(int newCprState);

    void cardiacEmmergencyChanged();

private:
    int m_cprState;
    int m_cardiacEmmergency;
};

#endif // ECGINTERFACERUNNER_H
