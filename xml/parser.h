#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QMessageBox>
#include "map.h"

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);
    ~Parser();

    void saveMap(Map map);
    void setOutStream(QString filename);

public slots:
    void add_key(QString id_key,QString for_key,QString name_key,QString type_key);
    void add_graph(QString id_graph);
    void add_node(QString id_node);
    void add_data(QString key_data, QString text_data);
    void add_edge(QString id_edge, QString source_edge, QString target_edge);
    void write_xml();
    void read_xml();
    void setProjectName(QString n) {projectName = n;}

private:
    QFile file;
    QDomDocument doc;
    QTextStream out;
    QDomElement graphml;    /*On est obligé de déclarer ici les balises qui peuvent en contenir d'autres*/
    QDomElement graph;
    QDomElement node;

    QString projectName;

};

#endif // PARSER_H
