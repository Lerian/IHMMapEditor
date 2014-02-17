#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);
    ~Parser();

private:
    QFile file;
    QDomDocument doc;
    QTextStream out;
    QDomElement graphml;
    QDomElement graph;

signals:
    
public slots:
    void add_key(QString id_key,QString for_key,QString name_key,QString type_key);
    void add_graph(QString id_graph);
    void add_node(QString id_node, QString name_node,QString ref_node,QString type_node,float alt_node,float lat_node,float long_node);
    
};

#endif // PARSER_H
