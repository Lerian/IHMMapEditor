#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Masquage de la fenetre d'édition
    ui->editorWindow->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayEditor() {
    ui->homeWindow->hide();
    ui->editorWindow->show();
}
