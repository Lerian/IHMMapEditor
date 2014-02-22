#ifndef FLOOR_H
#define FLOOR_H

#include "node.h"
#include <vector>

class Floor
{
    std::vector<Node> nodes;
    QString name;

public:
    Floor();

    void addNode(Node n);
    void setName(QString n);
    QString getName() {return name;}
    int getNodeNumber() {return nodes.size();}
    Node getNodeAt(int i) {return nodes.at(i);}
};

#endif // FLOOR_H
