#ifndef GRAPH_H
#define GRAPH_H
#include <QMetaObject>
#include <QVariantList>

class Graph
{
    Q_GADGET
    Q_PROPERTY(QVariantList graph READ getGraph WRITE setGraph )

public:
    Graph();

    QVariantList graph;

    QVariantList getGraph() {return graph;}
    void setGraph(QVariantList g) {graph = g;}
};

Q_DECLARE_METATYPE(Graph)

#endif // GRAPH_H
