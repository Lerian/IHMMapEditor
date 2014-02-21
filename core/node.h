#ifndef NODE_H
#define NODE_H

#include <QString>

class Node
{
    QString name;
    QString reference;
    QString type;
    float altitude;
    float latitude;
    float longitude;

public:
    Node();

    void setName(QString n);
    void setReference(QString r);
    void setType(QString t);
    void setAltitude(float a);
    void setLatitude(float l);
    void setLongitude(float l);
};

#endif // NODE_H
