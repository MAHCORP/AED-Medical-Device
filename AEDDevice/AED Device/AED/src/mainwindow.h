#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "dashboardform.h"
#include "padsattachform.h"
#include "splashform.h"
#include "systemcheckform.h"
#include "ecginterfacerunner.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void windowShown();

private slots:
    void on_stackedWidget_currentChanged(int arg1);

    // Handle advancing to next page on the StackView
    void onNextWindowRequest();

    // Display message on the status bar.
    // CHeck docs for Qt on statusbar
    void displayMessage(const QString &msg, int timeout=0);

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::MainWindow *ui;

    DashboardForm * dashboardWidget;
    SplashForm * splashWidget;
    SystemCheckForm * systemCheckWidget;
    PadsAttachForm * padsAttachWidget;
    ECGInterfaceRunner * ecgInterface;
};
#endif // MAINWINDOW_H
