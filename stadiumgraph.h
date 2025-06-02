#ifndef STADIUMGRAPH_H
#define STADIUMGRAPH_H

#include <iostream>
#include <limits>
#include "stadium.h"
using namespace std;


struct graphNode
{
    stadium value;                                      //CALC/OUT - stadium value of the node
    int distance;                                       //CALC/OUT - Distance between this node and a previous one (ambiguous for potential use for adjacency list and linked list).
    graphNode *adjacent;                                //CALC - Pointer to other adjacent stadiums

    /******************************
    ** CONSTRUCTORS & DESTRUCTOR **
    ******************************/
    graphNode() : value(stadium()), distance(0), adjacent(nullptr) {}
    graphNode(stadium value, int distance = 0, graphNode *adjacent = nullptr) : value(value), distance(distance), adjacent(adjacent) {}
    graphNode(const graphNode &otherNode) : value(otherNode.value), distance(otherNode.distance), adjacent(otherNode.adjacent) {}

    /***************
    ** ACCESSORS **
    ***************/
    bool operator==(const graphNode &otherNode) { return value == otherNode.value; }
    bool operator!=(const graphNode &otherNode) { return value != otherNode.value; }
    bool operator<(const graphNode &otherNode) { return distance < otherNode.distance; }
    bool operator>(const graphNode &otherNode) { return distance > otherNode.distance; }
    bool operator<=(const graphNode &otherNode) { return distance <= otherNode.distance; }
    bool operator>=(const graphNode &otherNode) { return distance >= otherNode.distance; }

    /***************
    **  MUTATORS  **
    ***************/
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
    /******************************
    ** CONSTRUCTORS & DESTRUCTOR **
    ******************************/
    stadiumGraph() : adjacencyList(nullptr), vertices(0) {}             //Default constructor
    stadiumGraph(stadium value);
    stadiumGraph(const stadiumGraph &otherGraph);                       //Copy constructor
    ~stadiumGraph();                                                    //Destructor

    /***************
    **  MUTATORS  **
    ***************/
    void insert(stadium value);
    void insert(stadium target, stadium value, int distance);
    stadiumGraph &operator=(const stadiumGraph &otherGraph);

    /***************
    ** ACCESSORS **
    ***************/
    void dijkstra(int start, graphNode *&S, int *&C, int *&P);
    stadiumGraph completeGraph();
    graphNode *shortestPathAll();
    graphNode *shortestPathNational();
    graphNode *shortestPathAmerican();
    graphNode *shortestPathSpecified(graphNode* specifiedList);
    void expandPath(graphNode *&visited);
    graphNode *shortestPathBetween(const string &startName, const string &endName);

    graphNode *getStadium(int index) { return adjacencyList[index]; }
    int find(stadium value);
    int find(string name);

    void printGraph() const;
    int getVertexCount() const;

private:
    graphNode **adjacencyList;                                  //CALC/OUT - adjacency list containing all nodes and the nodes they're adjacent to
    int vertices;                                               //CALC/OUT - the number of nodes/vertices in the graph, also size of adjacencyList

    /***************
    **  MUTATORS  **
    ***************/
    void sizeUp();
    void clear();
};

#endif // STADIUMGRAPH_H

/****************************************************************
* struct graphNode
* This struct represents a vertex node of a stadium graph
* with 3 attributes, value, distance, and adjacent.
***************************************************************/

/******************************
** CONSTRUCTORS & DESTRUCTOR **
******************************/

/****************************************************************
* graphNode();
* Constructor; Default constructor, sets value to default stadium,
* distance to 0, and adjacent to nullptr.
* Parameters: none
* Return: none
***************************************************************/

/****************************************************************
* graphNode(stadium value, int distance, graphNode *adjacent);
* Constructor; Constructor to create with given value, and
* either default 0 distance and nullptr adjacent, or the given
* values for them if they are given
* Parameters: value (stadium), distance (int), adjacent (graphNode*)
* Return: none
***************************************************************/

/****************************************************************
* graphNode(const graphNode* otherNode);
* Constructor; Copy constructor, copies over all 3 attributes
* Parameters: otherNode (const graphNode&)
* Return: none
***************************************************************/

/***************
** ACCESSORS **
***************/

/*******************************************************************
* bool operator==(const graphNode& otherNode)
*
* Accessor; This method overloads the equality operator, using the
* value of the node as the criteria for equality.
*------------------------------------------------------------------
* Parameter: otherNode (const graphNode&)
*------------------------------------------------------------------
* Return: true if equal, otherwise false
*******************************************************************/

/*******************************************************************
* bool operator!=(const graphNode& otherNode)
*
* Accessor; This method overloads the inequality operator, using the
* value of the node as the criteria for inequality.
*------------------------------------------------------------------
* Parameter: otherNode (const graphNode&)
*------------------------------------------------------------------
* Return: true if inequal, otherwise false
*******************************************************************/

/*******************************************************************
* bool operator<(const graphNode& otherNode)
*
* Accessor; This method overloads the less than operator, using the
* distance of the node as the criteria for less than.
*------------------------------------------------------------------
* Parameter: otherNode (const graphNode&)
*------------------------------------------------------------------
* Return: true if this distance is less than otherNode distance,
* otherwise false.
*******************************************************************/

/*******************************************************************
* bool operator>(const graphNode& otherNode)
*
* Accessor; This method overloads the greater than operator, using the
* distance of the node as the criteria for greater than.
*------------------------------------------------------------------
* Parameter: otherNode (const graphNode&)
*------------------------------------------------------------------
* Return: true if this distance is greater than otherNode distance,
* otherwise false.
*******************************************************************/

/*******************************************************************
* bool operator<=(const graphNode& otherNode)
*
* Accessor; This method overloads the less than or equal to operator,
* using the distance of the node as the criteria.
*------------------------------------------------------------------
* Parameter: otherNode (const graphNode&)
*------------------------------------------------------------------
* Return: true if this distance is less than or equal to otherNode's
* distance.
*******************************************************************/

/*******************************************************************
* bool operator>=(const graphNode& otherNode)
*
* Accessor; This method overloads the greater than or equal to operator,
* using the distance of the node as the criteria.
*------------------------------------------------------------------
* Parameter: otherNode (const graphNode&)
*------------------------------------------------------------------
* Return: true if this distance is greater than or equal to otherNode's
* distance.
*******************************************************************/

/***************
**  MUTATORS  **
***************/

/*******************************************************************
* graphNode& operator=(const graphNode& otherNode)
*
* Accessor; This method overloads the assignment operator, copying
* all attributes from otherNode to this one.
*------------------------------------------------------------------
* Parameter: otherNode (const graphNode&)
*------------------------------------------------------------------
* Return: this object.
*******************************************************************/

/****************************************************************
* class stadiumGraph
* This class represents a stadiumGraph object. It manages 2 attributes,
* adjacencyList and vertices.
***************************************************************/

/******************************
** CONSTRUCTORS & DESTRUCTOR **
******************************/

/****************************************************************
* stadiumGraph();
* Constructor; Default constructor, setting adjacencyList to
* nullptr and vertices to 0.
* Parameters: none
* Return: none
***************************************************************/

/****************************************************************
* stadiumGraph(stadium value);
* Constructor; fills the adjacencyList[0] with a node with given
* value, setting vertices to 1.
* Parameters: value (stadium)
* Return: none
***************************************************************/

/****************************************************************
* stadiumGraph(const stadiumGraph& otherGraph);
* Constructor; Copy constructor, fills adjacencyList with same
* nodes as otherGraph, setting vertices to be same as well.
* Parameters: otherGraph (const stadiumGraph&)
* Return: none
***************************************************************/

/****************************************************************
* ~stadiumGraph();
* Destructor; Deletes the dynamic memory set aside for adjacencyList.
* Parameters: none
* Return: none
***************************************************************/

/***************
**  MUTATORS  **
***************/

/*******************************************************************
* void insert(stadium value)
*
* Mutator; This method inserts a graphNode with the given value and
* distance of 0 into a new index of the adjacencyList and expanding it.
* Represents an entirely new vertex being added to the graph, thus
* increasing vertices.
*------------------------------------------------------------------
* Parameter: value (stadium)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void insert(stadium target, stadium value, int distance)
*
* Mutator; This method inserts a graphNode with the given value and
* distance at the end of the linked list whose head ptr has a value
* of target, meaning adding an adjacent vertex/edge to targeted node.
*
*------------------------------------------------------------------
* Parameter: target, (stadium), value (stadium), distance (int)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* stadiumGraph& operator=(const stadiumGraph& otherGraph)
*
* Mutator; This method overloads the assignment operator, clearing the
* current adjacency list and then copying over all elements of the
* otherGraph adjacency list and the vertices value.
*------------------------------------------------------------------
* Parameter: otherGraph (const stadiumGraph&)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void sizeUp()
*
* Mutator; This method increments vertices, increases size of
* adjacencyList and copies all old values back in.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void clear()
*
* Mutator; This method deletes all dynamic memory allocated for
* adjacencyList and sets it to nullptr and vertices to 0.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/***************
** ACCESSORS **
***************/

/*******************************************************************
* void dijkstra(int start, graphNode*& S, int*& C, int*& P)
*
* Accessor; This method applies dijkstra's algorithm to the graph
* starting at the node whose at index start in the adjacencyList.
* The corresponding dijkstra algorithm arrays (S holding the vetices
* as they are added according to shortest distance from the start node,
* C holding the shortest distances from the start node to all other
* nodes, and P holding the path from which the shortest path to the
* node with the corresponding index came from. indexes of C and P
* correspond with indexes of adjacencyList) are altered by reference
* to reflect the shortest paths from the start node and all other
* nodes.
*------------------------------------------------------------------
* Parameter: start (int), S (graphNode*&), C (int*&), P (int*&)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* stadiumGraph completeGraph()
*
* Accessor; This method applies dijkstra's algorithm from all nodes
* in the graph to effectively obtain the shortest edges from each
* node to all other nodes, and using that information to create and
* return a complete graph equivalent of this graph.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: a complete graph based on this graph object
*******************************************************************/

/*******************************************************************
* graphNode* shortestPathAll()
*
* Accessor; This method creates a complete graph out of this object
* and then uses a greedy algorithm to find the shortest path to each
* other node starting from Dodger stadium by taking the shortest
* effective edge that goes to a stadium that hasn't already been
* visited, and recording the order of visitation and distances. This
* happens until all vertices have been visited. Then, once the linked
* list path of visitation is expanded to include the intermediate
* stadiums visited, this method returns this linked list.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: linked list containing the shortest path to all major
* league stadiums and the corresponding distances traveled.
*******************************************************************/

/*******************************************************************
* graphNode* shortestPathNational()
*
* Accessor; This method creates a complete graph out of this object
* and then uses a greedy algorithm to find the shortest path to each
* other node starting from Dodger stadium by taking the shortest
* effective edge that goes to a stadium that hasn't already been
* visited, and recording the order of visitation and distances. This
* happens until all national league stadiums have been visited. Then,
* once the linked list path of visitation is expanded to include the
* intermediate stadiums visited, this method returns this linked list.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: linked list containing the shortest path to all national
* league stadiums and the corresponding distances traveled.
*******************************************************************/

/*******************************************************************
* graphNode* shortestPathAmerican()
*
* Accessor; This method creates a complete graph out of this object
* and then uses a greedy algorithm to find the shortest path to each
* other node starting from Angels stadium by taking the shortest
* effective edge that goes to a stadium that hasn't already been
* visited, and recording the order of visitation and distances. This
* happens until all american league stadiums have been visited. Then,
* once the linked list path of visitation is expanded to include the
* intermediate stadiums visited, this method returns this linked list.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: linked list containing the shortest path to all american
* league stadiums and the corresponding distances traveled.
*******************************************************************/

/*******************************************************************
* graphNode* shortestPathSpecified(graphNode* specifiedList)
*
* Accessor; This method creates a complete graph out of this object
* and then uses a greedy algorithm to find the shortest path to each
* other node starting from the first stadium in specifiedList by taking
* the shortest effective edge that goes to a stadium that hasn't already
* been visited, and recording the order of visitation and distances. This
* happens until all stadiums in specifiedList have been visited. Then,
* once the linked list path of visitation is expanded to include the
* intermediate stadiums visited, this method returns this linked list.
*------------------------------------------------------------------
* Parameter: specifiedList (graphNode*)
*------------------------------------------------------------------
* Return: linked list containing the shortest path to all stadiums in
* specifiedList and the corresponding distances traveled.
*******************************************************************/

/*******************************************************************
* void expandPath(graphNode*& visited)
*
* Accessor; This method takes a linked list of edges, applies
* dijkstra's algorithm to the left side of each edge and expands the
* edge in visited to include all intermediate stadiums traveled through
* to connect the two stadiums.
*------------------------------------------------------------------
* Parameter: visited (graphNode*&)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* graphNode* shortestPathBetween(const string& startName, const string& endName)
*
* Accessor; This method applies dijkstra's algorithm starting from
* the stadium with the given startName, and works backwards from the
* stadium with the given endName to obtain the full path/chain of
* stadiums needed to reach bridge the two stadiums, along with the
* corresponding distances. This linked list chain is then returned.
*------------------------------------------------------------------
* Parameter: startName (const string&), endName (const string&)
*------------------------------------------------------------------
* Return: linked list containing the shortest path between two
* stadiums.
*******************************************************************/

/*******************************************************************
* graphNode* getStadium(int index)
*
* Accessor; This method returns the graphNode at the given index of
* the adjacencyList
*------------------------------------------------------------------
* Parameter: index (int)
*------------------------------------------------------------------
* Return: graphNode at the given index of the adjacencyList.
*******************************************************************/

/*******************************************************************
* int find(stadium value)
*
* Accessor; This method returns the index at which a graphNode with
* the given value is found in adjacencyList, or -1 if not found.
*------------------------------------------------------------------
* Parameter: value (stadium)
*------------------------------------------------------------------
* Return: index of adjacencyList holding graphNode with given value
* or -1 if not found.
*******************************************************************/

/*******************************************************************
* int find(string name)
*
* Accessor; This method returns the index at which a graphNode with
* a stadium with the given name is found in adjacencyList, or -1 if
* not found.
*------------------------------------------------------------------
* Parameter: name (string)
*------------------------------------------------------------------
* Return: index of adjacencyList holding stadium with given name
* or -1 if not found.
*******************************************************************/

/*******************************************************************
* void printGraph() const
*
* Accessor; This method outputs the contents of this graph.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* int getVertexCount()
*
* Accessor; This method returns the vertices attribute
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: vertices attribute
*******************************************************************/
