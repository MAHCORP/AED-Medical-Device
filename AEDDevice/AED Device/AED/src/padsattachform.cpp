#include "padsattachform.h"
#include "ui_padsattachform.h"

PadsAttachForm::PadsAttachForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PadsAttachForm)
    , padsState(PadsState::NONE)
{
    ui->setupUi(this);

    // Set the pad placement image
    ui->userelectrodeplacementlbl->setStyleSheet("image: url(:/src/assets/imgs/electrode-placement.png);");

    // Set the default state
    setPadsState(PadsState::UNCONNECTED);

    // Create a QMovie to play the giff for loading state
    movie = new QMovie(":/src/assets/imgs/spinner.gif");
    movie->setScaledSize(QSize(24,24));
    ui->loaderLbl->setMovie(movie);     // Put the QMovie in the label
}

PadsAttachForm::~PadsAttachForm()
{
    delete ui;
}

void PadsAttachForm::resetPadsState()
{
    QSound::play(":/src/assets/sounds/Attach defib pads to patient's bare chest.wav");

    ui->verifyBtn->setVisible(true);
    ui->nextBtn->setVisible(false);
    ui->loaderLbl->setVisible(false);   // Loader label, has the spinning gif
    ui->msgLbl->setVisible(false);      // Label to show messages
}

void PadsAttachForm::setPadsState(PadsState padsState)
{
    // Show different image depending on if the pads are connected or not

    switch(padsState)
    {
    case PadsState::CONNECTED: {
        ui->userelectrodeplacementlbl->setStyleSheet("image: url(:/src/assets/imgs/electrode-placement-ok.png);");
        break;
    }
    case PadsState::UNCONNECTED: {
        ui->userelectrodeplacementlbl->setStyleSheet("image: url(:/src/assets/imgs/electrode-placement.png);");
        break;
    }
    default:
    {
        ui->userelectrodeplacementlbl->setStyleSheet("image: url(:/src/assets/imgs/electrode-placement.png);");
    }
    }

    this->padsState = padsState;
}

void PadsAttachForm::on_nextBtn_clicked()
{
    // Set QMovie to stop
    movie->stop();

    // Emit next page signal
    emit nextPageRequest();
}


void PadsAttachForm::on_verifyBtn_clicked()
{
    ui->loaderLbl->setVisible(true);
    ui->msgLbl->setVisible(true);
    ui->verifyBtn->setDisabled(true);
    movie->start();

    // Let the verification take 3.5s then exit
    QTimer::singleShot(3500, this, [&](){ onVerifyActionCompleted(); });
}

void PadsAttachForm::onVerifyActionCompleted()
{
    ui->verifyBtn->setEnabled(true);
    ui->verifyBtn->setVisible(false);
    ui->loaderLbl->setVisible(false);
    ui->msgLbl->setVisible(false);

    setPadsState(PadsState::CONNECTED);
    ui->nextBtn->setVisible(true);
    movie->stop();  // Stop animation
}

