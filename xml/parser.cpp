#include "xml/parser.h"
#include <iostream>

Parser::Parser(QObject *parent) :
    QObject(parent)
{
    setOutStream("test.xml");
}

void Parser::saveMap(Map map)
{
    // efface l'ancien contenu du fichier
    file.remove();
    setOutStream("test.xml");

    // ajout des clés
    add_key("name", "node", "name", "string");
    add_key("ref", "node", "ref", "string");
    add_key("type", "node", "type", "string");
    add_key("altitude", "node", "altitude", "string");
    add_key("latitude", "node", "latitude", "string");
    add_key("longitude", "node", "longitude", "string");

    for(int i=0;i<map.getFloorNumber();i++) {
        Floor currentFloor = map.getFloorAt(i);
        add_graph(currentFloor.getName());
        for(int j=0;j<currentFloor.getNodeNumber();j++) {
            Node currentNode = currentFloor.getNodeAt(j);
            add_node(currentNode.getReference());
            // ajout des attributs du noeud
            add_data("name",currentNode.getName());
            add_data("ref",currentNode.getReference());
            add_data("type",currentNode.getType());
            add_data("altitude",QString::number(currentNode.getAltitude()));
            add_data("latitude",QString::number(currentNode.getLatitude()));
            add_data("longitude",QString::number(currentNode.getLongitude()));
        }
        for(int j=0;j<currentFloor.getLinkNumber();j++) {
            Link currentLink = currentFloor.getLinkAt(j);
            add_edge(currentLink.getReference(),currentLink.getOrigine(),currentLink.getDestination());
        }
    }

    // ajout des instructions de processing xml et sauvegarde
    write_xml();
}

void Parser::setOutStream(QString filename)
{
    graphml = doc.createElement("graphml");
    doc.appendChild(graphml);
    graphml.setAttribute("xmlns","http://graphml.graphdrawing.org/xmlns");
    if(file.isOpen())
        file.close();

    file.setFileName(filename);
    if(file.open(QIODevice::ReadWrite))
       out.setDevice(&file);
}

void Parser::add_key(QString id_key,QString for_key,QString name_key,QString type_key)
{
    // création de la balise "key"
    QDomElement key = doc.createElement("key");
    graphml.appendChild(key);
    key.setAttribute("id",id_key);
    key.setAttribute("for",for_key);
    key.setAttribute("attr.name",name_key);
    key.setAttribute("attr.type",type_key);
}


void Parser::add_graph(QString id_graph)
{
    // création de la balise "graph"
    graph = doc.createElement("graph");
    graphml.appendChild(graph);
    graph.setAttribute("edgedefault","directed");
    graph.setAttribute("id",id_graph);

}


void Parser::add_node(QString id_node)
{
    // création de la balise "node"
    node = doc.createElement("node");
    graph.appendChild(node);
    node.setAttribute("id",id_node);
}


void Parser::add_data(QString key_data, QString text_data)
{
	// création de la balise "data"
    if(key_data == "name" || key_data == "ref" || key_data == "type" || key_data == "altitude" || key_data == "latitude" || key_data == "longitude"){
        QDomElement data = doc.createElement("data");
        node.appendChild(data);
        data.setAttribute("key",key_data);
        QDomText dataText = doc.createTextNode(text_data); // création de la donnée dataText
		data.appendChild(dataText);
	}
}


void Parser::add_edge(QString id_edge, QString source_edge, QString target_edge)
{
    // création de la balise "edge"
    QDomElement edge = doc.createElement("edge");
    graph.appendChild(edge);
    edge.setAttribute("id",id_edge);
    edge.setAttribute("source",source_edge);
    edge.setAttribute("target",target_edge);
}

void Parser::write_xml()
{
    // insertion en début de document de <?xml version="1.0" ?>
    QDomNode noeud = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.insertBefore(noeud,doc.firstChild());

    // sauvegarde dans le flux (deux espaces de décalage dans l'arborescence)
    doc.save(out,2);
}

void Parser::read_xml()
{
    QFile fichier("test.xml");
    if (!fichier.open(QIODevice::ReadOnly))
    {
        return;
    }
    if (!doc.setContent(&fichier))
    {
        fichier.close(); // établit le document XML à partir des données du fichier (hiérarchie, etc.)
        return;
    }

    int i=0, j=0;
    QString affichage;
    QDomNodeList tabSousNoeud;
    QDomNodeList tabSousSousNoeud;
    QDomNode sousNoeud;
    QDomNode sousSousNoeud;
    QDomElement element;
    QDomElement racine = doc.documentElement(); // renvoie la balise racine
    QDomNode noeud = racine.firstChild(); // renvoie la première balise
    while(!noeud.isNull())
    {
        // convertit le nœud en élément pour utiliser les méthodes tagName() et attribute()
        element = noeud.toElement();
        // vérifie la présence de la balise « key »
        if (element.tagName() == "key")
            {
                std::cout<< "Balise key =====>";
                affichage = element.attribute("for"); // récupère l'attribut for
                affichage = affichage + " " + element.attribute("attr.type"); // récupère l'attribut attr.type
                affichage = affichage + " " + element.attribute("attr.name"); // récupère l'attribut attr.type
                affichage = affichage + " " + element.attribute("id"); // récupère l'attribut attr.type
                std::cout<< affichage.toStdString() <<std::endl;
            }
        // vérifie la présence de la balise « graph »
        if (element.tagName() == "graph")
        {
            std::cout<< "Balise graph =====>";
            affichage = element.attribute("id");
            affichage = affichage + " " + element.attribute("edgedefault");
            std::cout<< affichage.toStdString() <<std::endl;
            tabSousNoeud = element.childNodes(); // crée un tableau des enfants de « graph »
            for(i=0;i<tabSousNoeud.length();i++)
            {
                sousNoeud = tabSousNoeud.item(i);
                element=sousNoeud.toElement();
                if(element.tagName() == "node")
                {
                    std::cout<< "=====Balise node =====>";
                    affichage = element.attribute("id");
                    std::cout<< affichage.toStdString() <<std::endl;
                    tabSousSousNoeud = element.childNodes(); // crée un tableau des enfants de « node »
                    for(j=0;j<tabSousSousNoeud.length();j++)
                    {
                        std::cout<< "==========Balise data =====>";
                        sousSousNoeud = tabSousSousNoeud.item(j);
                        affichage = sousSousNoeud.toElement().attribute("key") + " " + sousSousNoeud.firstChild().toText().data();
                        std::cout<< affichage.toStdString() <<std::endl;
                    }
                }
                else if (element.tagName() == "edge")
                {
                    std::cout<< "=====Balise edge =====>";
                    affichage = element.attribute("target");
                    affichage = affichage + " " + element.attribute("id");
                    affichage = affichage + " " + element.attribute("source");
                }

                    // pour chaque enfant, on extrait la donnée et on concatène

                   // n = tab.item(i);
                   // affichage = affichage + " " + n.firstChild().toText().data();
             }
                std::cout<< affichage.toStdString() <<std::endl;
        }
        noeud = noeud.nextSibling(); // passe à la "element" suivante
    }
}


Parser::~Parser(){

    file.close();
}
