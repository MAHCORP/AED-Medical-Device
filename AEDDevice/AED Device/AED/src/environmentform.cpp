#include "environmentform.h"
#include "ui_environmentform.h"

EnvironmentPanel::EnvironmentPanel(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::EnvironmentPanel)
{
    ui->setupUi(this);

    setWindowTitle("Environment Panel");
}

EnvironmentPanel::~EnvironmentPanel()
{
    delete ui;
}

void EnvironmentPanel::on_padBtn_clicked()
{
}

void EnvironmentPanel::on_batteryBtn_clicked()
{
}