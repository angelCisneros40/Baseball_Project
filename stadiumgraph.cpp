#include "stadiumgraph.h"

stadiumGraph::stadiumGraph(stadium value) {
    vertices = 1;
    adjacencyList = new graphNode*[vertices];

    adjacencyList[0] = new graphNode(value);
}

//copy constructor
stadiumGraph::stadiumGraph(const stadiumGraph &otherGraph) {
    vertices = otherGraph.vertices;
    adjacencyList = new graphNode*[vertices];

    for (int i = 0; i < vertices; i++)
    {
        adjacencyList[i] = new graphNode(otherGraph.adjacencyList[i]->value);

        graphNode* current = adjacencyList[i], * other = otherGraph.adjacencyList[i];
        for (; other != nullptr; current = current->adjacent, other = other->adjacent)
        {
            *current = *other;
        }
    }
}

//destructor
stadiumGraph::~stadiumGraph() {
    clear();
}

//Insert new stadium into graph
void stadiumGraph::insert(stadium value) {
    sizeUp();

    adjacencyList[vertices - 1] = new graphNode(value);
}

//add adjacent stadium to existing stadium (add edge)
void stadiumGraph::insert(stadium target, stadium value, int distance) {
    int spot = find(target);

    graphNode* end = adjacencyList[spot];
    for (; end->adjacent != nullptr; end = end->adjacent);

    end->adjacent = new graphNode(value, distance);
    end = nullptr;
}

stadiumGraph& stadiumGraph::operator= (const stadiumGraph& otherGraph) {
    clear();

    vertices = otherGraph.vertices;
    adjacencyList = new graphNode * [vertices];

    for (int i = 0; i < vertices; i++)
    {
        adjacencyList[i] = new graphNode(otherGraph.adjacencyList[i]->value);

        graphNode* current = adjacencyList[i], * other = otherGraph.adjacencyList[i];
        for (; other != nullptr; current = current->adjacent, other = other->adjacent)
        {
            *current = *other;
        }
    }

    return *this;
}

//Copy and increase size of graph adjacency list
void stadiumGraph::sizeUp() {
    int newSize = vertices + 1;
    graphNode** newList = new graphNode*[newSize];

    for (int i = 0; i < vertices; i++)
    {
        newList[i] = new graphNode(adjacencyList[i]->value);

        graphNode* current = newList[i], * other = adjacencyList[i];
        for (; other != nullptr; current = current->adjacent, other = other->adjacent)
        {
            *current = *other;
        }
    }

    newList[newSize - 1] = nullptr;

    clear();
    vertices = newSize;
    adjacencyList = newList;
    newList = nullptr;
}

void stadiumGraph::clear() {
    for (int i = 0; i < vertices; i++)
    {
        for (graphNode* current = adjacencyList[i]; current != nullptr;)
        {
            graphNode* placehold = current->adjacent;
            delete current;
            current = placehold;
        }

        adjacencyList[i] = nullptr;
    }

    delete[] adjacencyList;

    adjacencyList = nullptr;
    vertices = 0;
}

//find and return index of stadium with same value in list
int stadiumGraph::find(stadium value) {
    for (int i = 0; i < vertices; i++)
        if (value == adjacencyList[i]->value)
            return i;

    return -1;
}
