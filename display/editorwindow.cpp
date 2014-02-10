#include "display/editorwindow.h"
#include "ui_editorwindow.h"
#include "graphitem.h"

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
    elevatorItem->setPos(0,50);
    presentationScene->addItem(elevatorItem);
    GraphItem* stairsItem = new GraphItem(":/resource/escalier.png");
    stairsItem->setPos(0,100);
    presentationScene->addItem(stairsItem);
    GraphItem* exitItem = new GraphItem(":/resource/issueSecours.png");
    exitItem->setPos(0,150);
    presentationScene->addItem(exitItem);
    GraphItem* qrcodeItem = new GraphItem(":/resource/qrcode.png");
    qrcodeItem->setPos(0,200);
    presentationScene->addItem(qrcodeItem);
    GraphItem* wcItem = new GraphItem(":/resource/wc.png");
    wcItem->setPos(0,250);
    presentationScene->addItem(wcItem);
    GraphItem* wcHItem = new GraphItem(":/resource/wcH.png");
    wcHItem->setPos(0,300);
    presentationScene->addItem(wcHItem);

    ui->itemsPresentationArea->setScene(presentationScene);
}

EditorWindow::~EditorWindow()
{
    delete ui;
}
