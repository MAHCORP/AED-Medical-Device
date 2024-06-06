#include "splashform.h"
#include "ui_splashform.h"

SplashForm::SplashForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SplashForm)
{
    ui->setupUi(this);

    // Exit from the splashscreen after the delay has completed
    QTimer::singleShot(4000, [&](){ emit nextPageRequest(); });
}

SplashForm::~SplashForm()
{
    delete ui;
}
