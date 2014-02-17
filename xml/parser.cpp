#include "xml/parser.h"

Parser::Parser(QObject *parent) :
    QObject(parent)
{
    graphml = doc.createElement("graphml");
        doc.appendChild(graphml);
        graphml.setAttribute("xmlns","http://graphml.graphdrawing.org/xmlns");
        file.setFileName("test1.xml");

        if (!file.open(QIODevice::ReadWrite))
            return;
        out.setDevice(&file);

}


void Parser::add_key(QString id_key,QString for_key,QString name_key,QString type_key)
{
    // création de la balise "key"
    QDomElement key = doc.createElement("key");
    graphml.appendChild(key);
    graph.setAttribute("id",id_key);
    graph.setAttribute("for",for_key);
    graph.setAttribute("attr.name",name_key);
    graph.setAttribute("attr.type",type_key);
}


void Parser::add_graph(QString id_graph)
{
    // création de la balise "graph"
    QDomElement graph = doc.createElement("graph");
    graphml.appendChild(graph);
    graph.setAttribute("id",id_graph);
    graph.setAttribute("edgedefault","directed");
}


void Parser::add_node(QString id_node, QString name_node,QString ref_node,QString type_node,float alt_node,float lat_node,float long_node)
{
    // création de la balise "node"
    QDomElement node = doc.createElement("node");
    graph.appendChild(node);
    graph.setAttribute("id",id_node);
    // création des balises "data"
    QDomElement data = doc.createElement("data");
    node.appendChild(data);
    graph.setAttribute("key","name");
    QDomText n = doc.createTextNode(name_node);
    data.appendChild(n);

}


Parser::~Parser(){
    // insertion en début de document de <?xml version="1.0" ?>
    QDomNode noeud = doc.createProcessingInstruction("xml","version=\"1.0\"");
    doc.insertBefore(noeud,doc.firstChild());
    // sauvegarde dans le flux (deux espaces de décalage dans l'arborescence)
    doc.save(out,2);
    file.close();
}
