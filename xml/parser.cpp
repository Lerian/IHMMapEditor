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


void Parser::add_node(QString id_node)
{
    // création de la balise "node"
    QDomElement node = doc.createElement("node");
    graph.appendChild(node);
    node.setAttribute("id",id_node);
}

void Parser::add_data(QString key_data, QString text_data)
{
	// création de la balise "data"
    QDomElement data = doc.createElement("data");
    node.appendChild(data);
	if(key_data == "name" || key_data == "ref" || key_data == "type" || key_data == "altitude" || key_data == "latitude" || key_data == "longitude"){
		data.setAttribute("key",key_data);
		QDomText dataText = doc.createTextNode(text_data); // création de la donnée dataText
		data.appendChild(dataText);
	}
}

Parser::~Parser(){
    // insertion en début de document de <?xml version="1.0" ?>
    QDomNode noeud = doc.createProcessingInstruction("xml","version=\"1.0\"");
    doc.insertBefore(noeud,doc.firstChild());
    // sauvegarde dans le flux (deux espaces de décalage dans l'arborescence)
    doc.save(out,2);
    file.close();
}
