#ifndef SYSTEMCHECKFORM_H
#define SYSTEMCHECKFORM_H

#include <QWidget>
#include <QTimer>
#include <QSound>

namespace Ui {
class SystemCheckForm;
}

class SystemCheckForm : public QWidget
{
    Q_OBJECT

public:
    explicit SystemCheckForm(QWidget *parent = nullptr);
    ~SystemCheckForm();

    void startSystemCheck();

signals:
    void nextPageRequest();

private slots:
    void animateSystemCheck();

    void on_nextBtn_clicked();

private:
    Ui::SystemCheckForm *ui;

    QTimer * timer;

    int currentIndex = 0;
};

#endif // SYSTEMCHECKFORM_H
