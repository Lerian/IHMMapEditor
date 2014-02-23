#include "floor.h"

Floor::Floor()
{
}

void Floor::addNode(Node n)
{
    nodes.push_back(n);
}

void Floor::setName(QString n)
{
    name = n;
}

void Floor::addLink(Link l)
{
    links.push_back(l);
}
