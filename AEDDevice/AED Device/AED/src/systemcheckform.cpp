#include "systemcheckform.h"
#include "ui_systemcheckform.h"

SystemCheckForm::SystemCheckForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SystemCheckForm)
{
    ui->setupUi(this);

    // Create timer to toggle the system check options to true
    // Animate the system checks process
    timer = new QTimer(this);
    timer->setInterval(1);
    connect(timer, &QTimer::timeout, this, &SystemCheckForm::animateSystemCheck);
}

SystemCheckForm::~SystemCheckForm()
{
    delete ui;
}

void SystemCheckForm::startSystemCheck()
{
    // Start timer
    timer->start();

    // Reset all checkboxes
    ui->cb1->setChecked(false);
    ui->cb2->setChecked(false);
    ui->cb3->setChecked(false);
    ui->cb4->setChecked(false);
    ui->cb5->setChecked(false);

    // Disable next button until cheks pass
    ui->nextBtn->setEnabled(false);

    // Hide the checks passed label
    ui->checksPassedLbl->setVisible(false);
}

void SystemCheckForm::animateSystemCheck()
{
    switch(currentIndex)
    {
    case 0:
    {
        ui->cb1->setChecked(true);
        currentIndex++;
        break;
    }
    case 1:
    {
        ui->cb2->setChecked(true);
        currentIndex++;
        break;
    }
    case 2:
    {
        ui->cb3->setChecked(true);
        currentIndex++;
        break;
    }
    case 3:
    {
        ui->cb4->setChecked(true);
        currentIndex++;
        break;
    }
    case 4:
    {
        ui->cb5->setChecked(true);
        currentIndex++;
        timer->stop();

        // Show checks passed label  and activate next button
        ui->checksPassedLbl->setVisible(true);
        ui->nextBtn->setEnabled(true);

        QSound::play(":/src/assets/sounds/Unit OK.wav");
        break;
    }

    default:
        timer->stop();
    }
}

void SystemCheckForm::on_nextBtn_clicked()
{
    // Switch to the next page if user clicks next button
    emit nextPageRequest();
}

