#include "mainwindow.h"
#include "environmentform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    EnvironmentPanel environmentPanel;
    environmentPanel.show();

    return a.exec();
}
