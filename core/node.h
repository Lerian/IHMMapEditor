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

    QString getName() {return name;}
    QString getReference() {return reference;}
    QString getType() {return type;}
    float getAltitude() {return altitude;}
    float getLatitude() {return latitude;}
    float getLongitude() {return longitude;}
};

#endif // NODE_H
