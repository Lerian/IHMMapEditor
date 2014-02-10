#include "display/editorwindow.h"
#include "ui_editorwindow.h"
#include "graphitem.h"
#include <QFileDialog>

EditorWindow::EditorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWindow)
{
    ui->setupUi(this);

    QGraphicsScene* presentationScene = new QGraphicsScene(this);
    GraphItem* doorItem = new GraphItem(":/resource/porte.png");
    doorItem->setPos(0,0);
    presentationScene->addItem(doorItem);
    GraphItem* elevatorItem = new GraphItem(":/resource/ascenseur.png");
    elevatorItem->setPos(0,60);
    presentationScene->addItem(elevatorItem);
    GraphItem* stairsItem = new GraphItem(":/resource/escalier.png");
    stairsItem->setPos(0,120);
    presentationScene->addItem(stairsItem);
    GraphItem* exitItem = new GraphItem(":/resource/issueSecours.png");
    exitItem->setPos(0,180);
    presentationScene->addItem(exitItem);
    GraphItem* qrcodeItem = new GraphItem(":/resource/qrcode.png");
    qrcodeItem->setPos(0,240);
    presentationScene->addItem(qrcodeItem);
    GraphItem* wcItem = new GraphItem(":/resource/wc.png");
    wcItem->setPos(0,300);
    presentationScene->addItem(wcItem);
    GraphItem* wcHItem = new GraphItem(":/resource/wcH.png");
    wcHItem->setPos(0,360);
    presentationScene->addItem(wcHItem);

    ui->itemsPresentationArea->setScene(presentationScene);
}

EditorWindow::~EditorWindow()
{
    delete ui;
}

void EditorWindow::on_newElementButton_clicked()
{
    QString mapFileName = QFileDialog::getOpenFileName(this, "Choisir une image d'arrière plan", "./", "Images (*.png *.jpg *.bmp)");
    QStringList fileNameParts = mapFileName.split("/");

    ui->elementsComboBox->addItem(fileNameParts.back());
    ui->elementsComboBox->setCurrentIndex(ui->elementsComboBox->count()-1);

    QGraphicsView* elementView = new QGraphicsView();
    QPixmap pixmap(mapFileName);
    QBrush brush(pixmap);
    QPalette palette;
    palette.setBrush(elementView->backgroundRole(),brush);
    elementView->setPalette(palette);

    QGraphicsScene* elementScene = new QGraphicsScene(0,0,pixmap.width(),pixmap.height());
    elementView->setScene(elementScene);

    ui->mapAreaStack->addWidget(elementView);
}
