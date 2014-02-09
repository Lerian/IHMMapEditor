#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Masquage de la fenetre d'édition
    ui->editorWindow->hide();
    adjustSize();

    // Centrage de la fenetre
    QDesktopWidget bureau;
    QRect surface_bureau = bureau.screenGeometry();
    int x = surface_bureau.width()/2 - width()/2;
    int y = surface_bureau.height()/2 - height()/2;
    move(x,y);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayEditor() {
    ui->homeWindow->hide();
    ui->editorWindow->show();
    showMaximized();
}
