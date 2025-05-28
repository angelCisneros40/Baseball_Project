#ifndef STADIUMGRAPH_H
#define STADIUMGRAPH_H

#include <iostream>
#include <limits>
#include "stadium.h"

// Edges can be stored in pairs of 2 nodes, the first one having 0 distance pointing to the 2nd, containing the distance
struct graphNode
{
    stadium value;
    int distance;
    graphNode *adjacent;

    graphNode() : value(stadium()), distance(0), adjacent(nullptr) {}
    graphNode(stadium value, int distance = 0, graphNode *adjacent = nullptr) : value(value), distance(distance), adjacent(adjacent) {}
    graphNode(const graphNode &otherNode) : value(otherNode.value), distance(otherNode.distance), adjacent(otherNode.adjacent) {}

    bool operator==(const graphNode &otherNode) { return value == otherNode.value; }
    bool operator!=(const graphNode &otherNode) { return value != otherNode.value; }
    bool operator<(const graphNode &otherNode) { return distance < otherNode.distance; }
    bool operator>(const graphNode &otherNode) { return distance > otherNode.distance; }
    bool operator<=(const graphNode &otherNode) { return distance <= otherNode.distance; }
    bool operator>=(const graphNode &otherNode) { return distance >= otherNode.distance; }

    graphNode &operator=(const graphNode &otherNode)
    {
        value = otherNode.value;
        distance = otherNode.distance;
        adjacent = otherNode.adjacent;

        return *this;
    }
};

class stadiumGraph
{
public:
    stadiumGraph() : adjacencyList(nullptr), vertices(0) {}
    stadiumGraph(stadium value);
    stadiumGraph(const stadiumGraph &otherGraph);
    ~stadiumGraph();

    void insert(stadium value);
    void insert(stadium target, stadium value, int distance);

    void dijkstra(int start, graphNode *&S, int *&C, int *&P);
    stadiumGraph completeGraph();
    graphNode *shortestPathAll();
    graphNode *shortestPathNational();
    graphNode *shortestPathAmerican();
    void expandPath(graphNode *&visited);

    stadiumGraph &operator=(const stadiumGraph &otherGraph);

private:
    graphNode **adjacencyList;
    int vertices;

    void sizeUp();
    void clear();
    int find(stadium value);
    int find(std::string name);
};

#endif // STADIUMGRAPH_H
