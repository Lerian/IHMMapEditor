#include "node.h"

Node::Node()
{
}

void Node::setName(QString n)
{
    name = n;
}

void Node::setReference(QString r)
{
    reference = r;
}

void Node::setType(QString t)
{
    type = t;
}

void Node::setAltitude(float a)
{
    altitude = a;
}

void Node::setLatitude(float l)
{
    latitude = l;
}

void Node::setLongitude(float l)
{
    longitude = l;
}
