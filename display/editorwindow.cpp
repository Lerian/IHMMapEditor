#include "display/editorwindow.h"
#include "ui_editorwindow.h"
#include "graphitem.h"
#include <QFileDialog>
#include "mapgraphicsview.h"

EditorWindow::EditorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWindow)
{
    ui->setupUi(this);

    QGraphicsScene* presentationScene = new QGraphicsScene(this);

    GraphItem* doorItem = new GraphItem(":/resource/porte.png");
    doorItem->setPos(0,20);
    presentationScene->addItem(doorItem);
    QGraphicsTextItem* txtPorte = presentationScene->addText("Porte");
    txtPorte->setPos(60,0);
    txtPorte->scale(2,2);

    GraphItem* elevatorItem = new GraphItem(":/resource/ascenseur.png");
    elevatorItem->setPos(0,80);
    presentationScene->addItem(elevatorItem);
    QGraphicsTextItem* txtElevator = presentationScene->addText("Ascenseur");
    txtElevator->setPos(60,60);
    txtElevator->scale(2,2);

    GraphItem* stairsItem = new GraphItem(":/resource/escalier.png");
    stairsItem->setPos(0,140);
    presentationScene->addItem(stairsItem);
    QGraphicsTextItem* txtStairs = presentationScene->addText("Escalier");
    txtStairs->setPos(60,120);
    txtStairs->scale(2,2);

    GraphItem* exitItem = new GraphItem(":/resource/issueSecours.png");
    exitItem->setPos(0,200);
    presentationScene->addItem(exitItem);
    QGraphicsTextItem* txtExit = presentationScene->addText("Issue de secours");
    txtExit->setPos(60,180);
    txtExit->scale(2,2);

    GraphItem* qrcodeItem = new GraphItem(":/resource/qrcode.png");
    qrcodeItem->setPos(0,260);
    presentationScene->addItem(qrcodeItem);
    QGraphicsTextItem* txtQRCode = presentationScene->addText("QR Code");
    txtQRCode->setPos(60,240);
    txtQRCode->scale(2,2);

    GraphItem* wcItem = new GraphItem(":/resource/wc.png");
    wcItem->setPos(0,320);
    presentationScene->addItem(wcItem);
    QGraphicsTextItem* txtWC = presentationScene->addText("WC");
    txtWC->setPos(60,300);
    txtWC->scale(2,2);

    GraphItem* wcHItem = new GraphItem(":/resource/wcH.png");
    wcHItem->setPos(0,380);
    presentationScene->addItem(wcHItem);
    QGraphicsTextItem* txtWCH = presentationScene->addText("WC pour handicapés");
    txtWCH->setPos(60,360);
    txtWCH->scale(2,2);

    ui->itemsPresentationArea->setScene(presentationScene);
    ui->itemsPresentationArea->resize(ui->itemsPresentationArea->scene()->width(),ui->itemsPresentationArea->scene()->height());
}

EditorWindow::~EditorWindow()
{
    delete ui;
}

void EditorWindow::on_newElementButton_clicked()
{
    QString mapFileName = QFileDialog::getOpenFileName(this, "Choisir une image d'arrière plan", "./", "Images (*.png *.jpg *.bmp)");
    if(!mapFileName.isEmpty()) {
        QStringList fileNameParts = mapFileName.split("/");

        MapGraphicsView* elementView = new MapGraphicsView();
        QPixmap pixmap(mapFileName);
        QGraphicsPixmapItem* background = new QGraphicsPixmapItem(pixmap);

        QGraphicsScene* elementScene = new QGraphicsScene(0,0,pixmap.width(),pixmap.height());
        elementView->setScene(elementScene);
        elementScene->addItem(background);

        ui->mapAreaStack->addWidget(elementView);

        //elementView->fitInView(background);
        //elementScene->setSceneRect(background->boundingRect());

        ui->elementsComboBox->addItem(fileNameParts.back());
        ui->elementsComboBox->setCurrentIndex(ui->elementsComboBox->count()-1);
    }
}

void EditorWindow::on_zoomInButton_clicked()
{
    MapGraphicsView* currentView = static_cast<MapGraphicsView*>(ui->mapAreaStack->currentWidget());

    currentView->scale(1.25,1.25);
}

void EditorWindow::on_zoomOutButton_clicked()
{
    MapGraphicsView* currentView = static_cast<MapGraphicsView*>(ui->mapAreaStack->currentWidget());

    currentView->scale(1/1.25,1/1.25);
}

void EditorWindow::on_zoomIdeal_clicked()
{
    MapGraphicsView* currentView = static_cast<MapGraphicsView*>(ui->mapAreaStack->currentWidget());

    /*qreal sceneWidth = currentView->scene()->width();
    qreal sceneHeight = currentView->scene()->height();

    currentView->resize(sceneWidth,sceneHeight);*/

    //currentView->adjustSize();

    //currentView->fitInView(currentView->scene());
}
