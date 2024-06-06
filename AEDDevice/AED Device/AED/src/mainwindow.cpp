#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Remove all items in the stackwidget,
    // By default, QtDesigner adds two QWidgets to the StackWidget
    for(int i = ui->stackedWidget->count(); i >= 0; i--)
    {
        QWidget* widget = ui->stackedWidget->widget(i); // Get QWidget at index i
        ui->stackedWidget->removeWidget(widget);
        widget->deleteLater();
    }

    // Create Stack Widgets
    // These are the Widgets that will be showing the different pages of the app
    splashWidget = new SplashForm;              // Initial Page, just like a splashscreen
    dashboardWidget = new DashboardForm;        // Dashboard home that displays the charts
    padsAttachWidget = new PadsAttachForm;      // AED attach pads instruction page
    systemCheckWidget = new SystemCheckForm;    // System self check page

    ecgInterface = new ECGInterfaceRunner(this);
    // Connect signals from the runner to this class or the other pages and vice versa

    // Add the widgets into the stackwidget
    ui->stackedWidget->addWidget(splashWidget);
    ui->stackedWidget->addWidget(systemCheckWidget);
    ui->stackedWidget->addWidget(padsAttachWidget);
    ui->stackedWidget->addWidget(dashboardWidget);


    // Connect signals from/to the different pages to this MainWindo class
    connect(splashWidget, &SplashForm::nextPageRequest, this, &MainWindow::onNextWindowRequest);
    connect(dashboardWidget, &DashboardForm::nextPageRequest, this, &MainWindow::onNextWindowRequest);
    connect(padsAttachWidget, &PadsAttachForm::nextPageRequest, this, &MainWindow::onNextWindowRequest);
    connect(systemCheckWidget, &SystemCheckForm::nextPageRequest, this, &MainWindow::onNextWindowRequest);
    connect(dashboardWidget, &DashboardForm::showMessage, this, &MainWindow::displayMessage);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_stackedWidget_currentChanged(int currentIndex)
{
    // Actions when the main widget is changed
    if(currentIndex == 1)
    {
        // Initiate the system checks when we switch to this window
        systemCheckWidget->startSystemCheck();
    }

    else if(currentIndex == 2)
    {
        // Reset the page state when we switch to this page
        padsAttachWidget->resetPadsState();
    }

    else if(currentIndex == 3)
    {
        // Reset dashboard when we switch to this page
        dashboardWidget->resetDashboard();
    }
}

void MainWindow::onNextWindowRequest()
{
    // auto widget = sender();
    // qDebug() << widget;

    // Advance to the next stack page
    if(ui->stackedWidget->currentIndex() < ui->stackedWidget->count()-1)
    {
        // Get current stack index, add one to it
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    }
}

void MainWindow::displayMessage(const QString &msg, int timeout)
{
    // Display message on the MainWindow statusbar
    ui->statusbar->showMessage(msg, timeout);
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    // Emit the custom shown signal when the widget is shown
    emit windowShown();
}

