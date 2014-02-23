#include "mainwindow.h"
#include "xml/parser.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    //Utilisation de l'utf8 pour afficher correctement les accents
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
