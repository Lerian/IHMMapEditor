#include "xml/parser.h"
#include <iostream>

Parser::Parser(QObject *parent) :
    QObject(parent)
{
    // insertion en début de document de <?xml version="1.0" ?>
    QDomNode noeud = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.insertBefore(noeud,doc.firstChild());

    graphml = doc.createElement("graphml");
    doc.appendChild(graphml);
    graphml.setAttribute("xmlns","http://graphml.graphdrawing.org/xmlns");

    file.setFileName("test.xml");

    if (!file.open(QIODevice::ReadWrite))
        return;
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

Parser::~Parser(){

    // sauvegarde dans le flux (deux espaces de décalage dans l'arborescence)
    doc.save(out,2);

    std::cout<<"sauvegarde"<<std::endl;

    file.close();
}
