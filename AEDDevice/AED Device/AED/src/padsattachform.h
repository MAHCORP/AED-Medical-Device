#ifndef PADSATTACHFORM_H
#define PADSATTACHFORM_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QMovie>
#include <QSound>

namespace Ui {
class PadsAttachForm;
}

class PadsAttachForm : public QWidget
{
    Q_OBJECT

public:
    // Save Pads State, whether connected | unconnected | checking | etc
    enum PadsState {
        UNCONNECTED = 0,
        CHECKING,
        CONNECTED,
        NONE
    };

    explicit PadsAttachForm(QWidget *parent = nullptr);
    ~PadsAttachForm();

    // Reset the page state, when switching to this page
    void resetPadsState();

    void disconnectPad();
signals:
    void nextPageRequest();

private slots:
    void on_nextBtn_clicked();

    void on_verifyBtn_clicked();

    void onVerifyActionCompleted();

private:
    void setPadsState(PadsState padsState);
    Ui::PadsAttachForm *ui;

    PadsState padsState;
    QMovie * movie;
};

#endif // PADSATTACHFORM_H
