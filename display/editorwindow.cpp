#include "display/editorwindow.h"
#include "ui_editorwindow.h"
#include "graphitem.h"
#include <QFileDialog>
#include "mapgraphicsview.h"
#include "parser.h"
#include "map.h"

EditorWindow::EditorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWindow)
{
    ui->setupUi(this);

    QGraphicsScene* presentationScene = new QGraphicsScene(this);

    GraphItem* doorItem = new GraphItem(":/resource/porte.png");
    doorItem->setPos(0,20);
    doorItem->setType("porte");
    presentationScene->addItem(doorItem);
    QGraphicsTextItem* txtPorte = presentationScene->addText("Porte");
    txtPorte->setPos(60,0);
    txtPorte->scale(2,2);

    GraphItem* elevatorItem = new GraphItem(":/resource/ascenseur.png");
    elevatorItem->setPos(0,80);
    elevatorItem->setType("ascenseur");
    presentationScene->addItem(elevatorItem);
    QGraphicsTextItem* txtElevator = presentationScene->addText("Ascenseur");
    txtElevator->setPos(60,60);
    txtElevator->scale(2,2);

    GraphItem* stairsItem = new GraphItem(":/resource/escalier.png");
    stairsItem->setPos(0,140);
    stairsItem->setType("escalier");
    presentationScene->addItem(stairsItem);
    QGraphicsTextItem* txtStairs = presentationScene->addText("Escalier");
    txtStairs->setPos(60,120);
    txtStairs->scale(2,2);

    GraphItem* exitItem = new GraphItem(":/resource/issueSecours.png");
    exitItem->setPos(0,200);
    exitItem->setType("sortieDeSecours");
    presentationScene->addItem(exitItem);
    QGraphicsTextItem* txtExit = presentationScene->addText("Issue de secours");
    txtExit->setPos(60,180);
    txtExit->scale(2,2);

    GraphItem* qrcodeItem = new GraphItem(":/resource/qrcode.png");
    qrcodeItem->setPos(0,260);
    qrcodeItem->setType("qrcode");
    presentationScene->addItem(qrcodeItem);
    QGraphicsTextItem* txtQRCode = presentationScene->addText("QR Code");
    txtQRCode->setPos(60,240);
    txtQRCode->scale(2,2);

    GraphItem* wcItem = new GraphItem(":/resource/wc.png");
    wcItem->setPos(0,320);
    wcItem->setType("wc");
    presentationScene->addItem(wcItem);
    QGraphicsTextItem* txtWC = presentationScene->addText("WC");
    txtWC->setPos(60,300);
    txtWC->scale(2,2);

    GraphItem* wcHItem = new GraphItem(":/resource/wcH.png");
    wcHItem->setPos(0,380);
    wcHItem->setType("wcHandicapes");
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

        MapGraphicsView* elementView = new MapGraphicsView(mapFileName);
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

        ui->zoomIdeal->setEnabled(true);
        ui->zoomInButton->setEnabled(true);
        ui->zoomOutButton->setEnabled(true);
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
    //MapGraphicsView* currentView = static_cast<MapGraphicsView*>(ui->mapAreaStack->currentWidget());

    /*qreal sceneWidth = currentView->scene()->width();
    qreal sceneHeight = currentView->scene()->height();

    currentView->resize(sceneWidth,sceneHeight);*/

    //currentView->adjustSize();

    //currentView->fitInView(currentView->scene());
}

void EditorWindow::saveRequested()
{
    Parser p;

    Map map;

    for(int i=0;i < ui->mapAreaStack->count();i++) {
        MapGraphicsView* currentGraphicView = static_cast<MapGraphicsView*>(ui->mapAreaStack->widget(i));

        Floor* currentFloor = currentGraphicView->getFloor();

        QGraphicsScene* currentScene = currentGraphicView->scene();
        QList<QGraphicsItem*> elements = currentScene->items();

        for(int j=0; j < elements.count()-1; j++) {
            GraphItem* currentItem = static_cast<GraphItem*>(elements.at(j));
            currentFloor->addNode(*(currentItem->getNode()));
        }
        map.addFloor(*currentFloor);
        currentFloor->resetNodes();
    }

    p.saveMap(map);
}
