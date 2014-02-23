#ifndef LINK_H
#define LINK_H

#include <QString>

class Link
{
    QString reference;
    QString origine;
    QString destination;

public:
    Link();

    void setReference(QString r) {reference =r;}
    void setOrigine(QString o) {origine = o;}
    void setDestination(QString d) {destination = d;}

    QString getReference() {return reference;}
    QString getOrigine() {return origine;}
    QString getDestination() {return destination;}
};

#endif // LINK_H
