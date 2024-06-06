#include "dashboardform.h"
#include "ui_dashboardform.h"

DashboardForm::DashboardForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DashboardForm)
{
    ui->setupUi(this);

    setECGState(ECGState::FIBRILLATION);

    // Create a timer to animate the BPMs
    bpmAnimTimer = new QTimer();
    bpmAnimTimer->setInterval(1000);
    connect(bpmAnimTimer, &QTimer::timeout, this, &DashboardForm::animateBPM);

    // Initial BPM value
    animateBPM();

    connect(this, &DashboardForm::simulationCompleted, this, &DashboardForm::onSimulationCompleted);
}

DashboardForm::~DashboardForm()
{
    delete ui;
}

void DashboardForm::resetDashboard()
{
    // Reset any actions, disable buttons, etc.
    ui->shockBtn->setDisabled(true);
    ui->chargeBtn->setDisabled(true);
    ui->chargeProgressBar->setVisible(false);

    bpmAnimTimer->start();

    emit showMessage("All set, analyzing patient ECG", 3000);

    simulationMode = NORMAL_BEAT_SIMULATION;

    runSimulations();

    // if(ecgState == ECGState::NORMAL)
    // {
    //     // Nothing, just display the chart

    //     ui->msgLbl->setText("");
    // }

    // else if(ecgState == ECGState::TACHYCARDIA)
    // {
    //     beginShockCycle();
    // }

    // else
    // {
    //     beginCPRCycle();
    // }
}

void DashboardForm::beginCPRCycle()
{
    setECGState(ECGState::FIBRILLATION);

    emit showMessage("Beginning CPR guidelines, follow the onboard instructions ...", 12000);

    ui->msgLbl->setText("Analyzing patient **ECG**, stay calm");

    QSound::play(":/src/assets/sounds/Analyzing heart rhythm.wav");

    QTimer::singleShot(2000, this, [&]() {
        QSound::play(":/src/assets/sounds/Don't touch patient.wav");
        });

    QTimer::singleShot(7000, this, [&]() {
        ui->msgLbl->setText("ECG analyzed, CPR recommended, follow the following prompts.");
        });

    QTimer::singleShot(9000, this, [&]() {
        ui->msgLbl->setText("Give the patient **Chest Compressions** with an interval of 2seconds after every compression. Ensure you do a total of 21 cycles..");
        });

    QTimer::singleShot(12000, this, [&]() {
        ui->msgLbl->setText("Beat detected, shock cycles initiated ...");
        });

    QTimer::singleShot(14000, this, [&]() {
        // beginShockCycle();

        // End this simulation
        emit simulationCompleted();
        });
}

void DashboardForm::beginShockCycle()
{
    setECGState(ECGState::TACHYCARDIA);
    ui->shockBtn->setDisabled(true);
    ui->chargeBtn->setDisabled(true);

    emit showMessage("Beginning patient shock, follow the onboard instructions ...", 10000);

    ui->msgLbl->setText("Analyzing patient **ECG**, stay calm");

    QSound::play(":/src/assets/sounds/Analyzing heart rhythm.wav");

    QTimer::singleShot(2000, this, [&]() {
        QSound::play(":/src/assets/sounds/Don't touch patient.wav");
        });

    QTimer::singleShot(5000, this, [&]() {
        ui->msgLbl->setText("ECG analyzed, preparing to administer shock. Press the **CHARGE** button to begin the charging.");
        ui->chargeBtn->setEnabled(true);
        });
}

void DashboardForm::setECGState(ECGState ecgState)
{
    this->ecgState = ecgState;

    switch (ecgState)
    {
    case ECGState::NORMAL:
    {
        ui->chartLabel->setStyleSheet("image: url(:/src/assets/imgs/norm.png);");
        break;
    }
    case ECGState::TACHYCARDIA:
    {
        ui->chartLabel->setStyleSheet("image: url(:/src/assets/imgs/vt.png);");
        break;
    }
    default:
    {
        ui->chartLabel->setStyleSheet("image: url(:/src/assets/imgs/vf.png);");
    }
    }
}

void DashboardForm::runSimulations()
{
    switch (simulationMode)
    {
    case NORMAL_BEAT_SIMULATION:
    {
        setECGState(NORMAL);
        ui->msgLbl->setText("Analyzing patient ECG, please hold on ...");

        QSound::play(":/src/assets/sounds/Analyzing heart rhythm.wav");

        QTimer::singleShot(2000, this, [&]() {
            QSound::play(":/src/assets/sounds/Don't touch patient.wav");
            });

        QTimer::singleShot(3000, this, [&]() {
            ui->msgLbl->setText("Patient ECG heart back to normal, all is clear. Monitoring further ...");
            setECGState(ECGState::NORMAL);
            });

        QTimer::singleShot(5000, this, [&]() {
            emit simulationCompleted();
            });
        break;
    }

    case CPR_SIMULATION:
    {
        beginCPRCycle();
        break;
    }

    case TACHYCARDIA_ONCE_SUCCESS:
    {
        shockCounts = 0;
        beginShockCycle();
        break;
    }

    case TACHYCARDIA_TWICE_FAIL:
    {
        shockCounts = 0;
        beginShockCycle();
        break;
    }
    }
}

void DashboardForm::on_shockBtn_clicked()
{
    ui->msgLbl->setText("Administering patient shock, stay clear!");
    ui->chargeProgressBar->setVisible(false);

    QSound::play(":/src/assets/sounds/Shock will be delivered in.wav");

    QTimer::singleShot(2000, this, [&]() {
        QSound::play(":/src/assets/sounds/3.wav");
        });

    QTimer::singleShot(3000, this, [&]() {
        QSound::play(":/src/assets/sounds/2.wav");
        });

    QTimer::singleShot(4000, this, [&]() {
        QSound::play(":/src/assets/sounds/1.wav");
        });

    QTimer::singleShot(4500, this, [&]() {
        QSound::play(":/src/assets/sounds/Shock delivered.wav");
        });

    if (simulationMode == TACHYCARDIA_TWICE_FAIL)
    {
        QTimer::singleShot(6000, this, [&]() {
            ui->msgLbl->setText("That didn't work, retrying in a few ...");
            });


        QTimer::singleShot(8000, this, [&]() {
            shockCounts++;

            if (shockCounts <= 1)
            {
                beginShockCycle();
            }

            else
            {
                ui->msgLbl->setText("This is a medical emmergency, **CALL 911** immediately!");
            }
            });
    }

    else
    {
        QTimer::singleShot(6000, this, [&]() {
            ui->msgLbl->setText("Patient ECG heart back to normal, all is clear. Monitoring further ...");
            setECGState(ECGState::NORMAL);
            });


        QTimer::singleShot(11000, this, [&]() {
            ui->msgLbl->setText("");

            emit simulationCompleted();
            });
    }
}


void DashboardForm::on_chargeBtn_clicked()
{
    ui->msgLbl->setText("**CHARGING** stay clear ...");

    ui->chargeBtn->setDisabled(true);
    ui->chargeProgressBar->setVisible(true);

    emit showMessage("Charging ...", 5000);

    setChargeTimerProgress(0);
    setChargeTimerProgress(10);
    setChargeTimerProgress(20);
    setChargeTimerProgress(30);
    setChargeTimerProgress(40);
    setChargeTimerProgress(50);
    setChargeTimerProgress(60);
    setChargeTimerProgress(70);
    setChargeTimerProgress(80);
    setChargeTimerProgress(90);
    setChargeTimerProgress(100);

}

void DashboardForm::animateBPM()
{
    // Generate BPM values depending on the ECG state

    switch (ecgState)
    {
    case ECGState::NORMAL:
    {
        int bpm = QRandomGenerator::global()->bounded(67, 82);
        ui->bpmLbl->setText(QString::number(bpm));
        break;
    }
    case ECGState::TACHYCARDIA:
    {
        int bpm = QRandomGenerator::global()->bounded(150, 200);
        ui->bpmLbl->setText(QString::number(bpm));
        break;
    }
    case ECGState::FIBRILLATION:
    {
        int bpm = QRandomGenerator::global()->bounded(150, 200);
        ui->bpmLbl->setText(QString::number(bpm));
        break;
    }
    default:
    {
        ui->bpmLbl->setText("---");
    }
    }
}

void DashboardForm::onSimulationCompleted()
{
    switch (simulationMode)
    {
    case NORMAL_BEAT_SIMULATION:
    {
        simulationMode = CPR_SIMULATION;
        runSimulations();
        break;
    }

    case CPR_SIMULATION:
    {
        simulationMode = TACHYCARDIA_ONCE_SUCCESS;
        runSimulations();
        break;
    }

    case TACHYCARDIA_ONCE_SUCCESS:
    {
        simulationMode = TACHYCARDIA_TWICE_FAIL;
        runSimulations();
        break;
    }

    case TACHYCARDIA_TWICE_FAIL:
    {
        break;
    }
    }
}

void DashboardForm::setChargeTimerProgress(int sec)
{
    // Create timers to update progressbar
    QTimer::singleShot(sec * 50, this, [this, sec]() {
        this->ui->chargeProgressBar->setValue(sec);

        if (sec == 100)
        {
            // If progress is at 100%, enable shock button and update
            this->ui->shockBtn->setEnabled(true);
            this->ui->msgLbl->setText("Press **SHOCK** button to administer shock!");
        }
        });
}

