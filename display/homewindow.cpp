#include "display/homewindow.h"
#include "ui_homewindow.h"

HomeWindow::HomeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::on_quitButton_clicked()
{
    emit quitButtonClicked();
}

void HomeWindow::on_newMapButton_clicked()
{
    emit newMapButtonClicked();
}
