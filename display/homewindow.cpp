#include "display/homewindow.h"
#include <QFileDialog>
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

void HomeWindow::on_loadMapButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir une carte", "./", "Tous les fichiers (*.*);; Images (*.png *.jpg *.bmp)");
    emit loadMap(filename);
}
