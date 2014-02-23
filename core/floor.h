#ifndef FLOOR_H
#define FLOOR_H

#include "node.h"
#include <vector>

#include "link.h"

class Floor
{
    std::vector<Node> nodes;
    std::vector<Link> links;
    QString name;

public:
    Floor();

    void addNode(Node n);
    void addLink(Link l);
    void setName(QString n);
    QString getName() {return name;}
    int getNodeNumber() {return nodes.size();}
    int getLinkNumber() {return links.size();}
    Node getNodeAt(int i) {return nodes.at(i);}
    void resetNodes() {nodes.clear();}
    Link getLinkAt(int i) {return links.at(i);}
    void resetLinks() {links.clear();}
};

#endif // FLOOR_H
