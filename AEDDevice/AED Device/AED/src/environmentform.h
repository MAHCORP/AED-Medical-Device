#ifndef ENVIRONMENTPANEL_H
#define ENVIRONMENTPANEL_H

#include <QWidget>

namespace Ui {
	class EnvironmentPanel;
}

#include <QWidget>

class EnvironmentPanel : public QWidget {
    Q_OBJECT

public:
    explicit EnvironmentPanel(QWidget* parent = nullptr);
    ~EnvironmentPanel();

public slots:
    void on_padBtn_clicked();

    void on_batteryBtn_clicked();

private:
    Ui::EnvironmentPanel* ui;
};

#endif // !ENVIRONMENTPANEL_H
