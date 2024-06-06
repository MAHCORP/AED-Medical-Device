#ifndef SPLASHFORM_H
#define SPLASHFORM_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class SplashForm;
}

class SplashForm : public QWidget
{
    Q_OBJECT

public:
    explicit SplashForm(QWidget *parent = nullptr);
    ~SplashForm();

signals:
    // Signal to emit when we want to advance to the next page on the stack
    void nextPageRequest();

private:
    Ui::SplashForm *ui;
};

#endif // SPLASHFORM_H
