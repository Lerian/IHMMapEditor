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

    Parser p;
/*    //ajout des key
    p.add_key("name", "node", "name", "string");
    p.add_key("ref", "node", "ref", "string");
    p.add_key("type", "node", "type", "string");
    p.add_key("altitude", "node", "altitude", "string");
    p.add_key("latitude", "node", "latitude", "string");
    p.add_key("longitude", "node", "longitude", "string");
    //création du graph
    p.add_graph("Bat15");
    //Insertion d'un node
    p.add_node("1");
    //Insertion de data
    p.add_data("name", "Master_Alma");
    p.add_data("ref","042");
    p.add_data("type", "porte");
    p.add_data("altitude", "54.6");
    p.add_data("latitude", "43.8");
    p.add_data("longitude", "72.9");
    //Insertion d'un autre node
    p.add_node("2");
    //Insertion de data
    p.add_data("name", "Master_Alma");
    p.add_data("ref","042");
    p.add_data("type", "porte");
    p.add_data("altitude", "54.6");
    p.add_data("latitude", "43.8");
    p.add_data("longitude", "72.9");
    //Insertion de edge
    p.add_edge("5", "1", "2");

    //on écrit
    p.write_xml();
*/

    p.read_xml();
    
    return a.exec();
}
