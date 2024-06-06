#ifndef DASHBOARDFORM_H
#define DASHBOARDFORM_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>
#include <QSound>

namespace Ui {
    class DashboardForm;
}

/*
 * This class handles the dashboard UI, key note:
 * - Has several QTimers that fire after some milliseconds to display the different messages needed
 */

class DashboardForm : public QWidget
{
    Q_OBJECT

public:
    enum ECGState {
        NORMAL,
        TACHYCARDIA,
        FIBRILLATION,
        ASYSTOLE
    };

    enum SimulationMode {
        NORMAL_BEAT_SIMULATION = 0,
        CPR_SIMULATION,
        TACHYCARDIA_ONCE_SUCCESS,
        TACHYCARDIA_TWICE_FAIL
    };

    explicit DashboardForm(QWidget* parent = nullptr);
    ~DashboardForm();

    void resetDashboard();

    void beginCPRCycle();

    void beginShockCycle();

    void setECGState(ECGState ecgState);

    void runSimulations();

signals:
    void nextPageRequest();

    void simulationCompleted();

    void showMessage(const QString&, int duration = 0);

private slots:
    void on_shockBtn_clicked();

    void on_chargeBtn_clicked();

    void animateBPM();

    void onSimulationCompleted();

private:
    void setChargeTimerProgress(int sec);

    Ui::DashboardForm* ui;

    ECGState ecgState;

    SimulationMode simulationMode;

    QTimer* bpmAnimTimer;

    int shockCounts = 0;
};

#endif // DASHBOARDFORM_H
