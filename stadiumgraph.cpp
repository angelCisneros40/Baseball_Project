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

//dijkstra's algorithm, alters the dynamic arrays that hold the parsed nodes and the costs and paths
void stadiumGraph::dijkstra(int start, graphNode*& S, int*& C, int*& P) {
    int s_size = 0;
    std::fill(S, S + vertices, graphNode());
    std::fill(P, P + vertices, -1);
    std::fill(C, C + vertices, std::numeric_limits<int>::max());
    C[start] = 0;

    //While all vertices haven't been parsed
    while (s_size != vertices)
    {
        //Searching for smallest edge cost to move to next node and add it to S
        int smallestC = -1;
        for (int i = 0; i < vertices; i++)
        {
            //Check if vertex exists in S already
            bool repeat = false;
            for (int n = 0; n < s_size; n++)
            {
                if (S[n].value == adjacencyList[i]->value)
                {
                    repeat = true;
                    break;
                }
            }

            //If exists in S
            if (repeat)
                continue;

            //If first non-repeat vertex or is smaller cost than current smallest cost index
            if (smallestC == -1 || C[smallestC] > C[i])
                smallestC = i;
        }

        //Adds node with smallest cost to S
        S[s_size] = *adjacencyList[smallestC];
        s_size++;

        //Checks to alter all adjacent nodes to the vertex just added to S
        for (graphNode* current = adjacencyList[smallestC]->adjacent; current != nullptr; current = current->adjacent)
        {
            //Check if adjacent node already in S
            bool repeat = false;
            int spot = find(current->value);
            for (int n = 0; n < s_size; n++)
            {
                if (S[n].value == adjacencyList[spot]->value)
                {
                    repeat = true;
                    break;
                }
            }

            if (repeat)
                continue;

            //If this path to given vertex was cheaper, change its cost and the path taken to get there
            if (C[smallestC] + current->distance < C[spot])
            {
                C[spot] = C[smallestC] + current->distance;
                P[spot] = smallestC;
            }
        }
    }
}

//Creates and returns complete graph of current graph object (each node connected to each other node)
stadiumGraph stadiumGraph::completeGraph() {
    stadiumGraph compGraph;

    graphNode* S;
    int* C;;
    int* P;

    //Run for each vertex
    for (int i = 0; i < vertices; i++)
    {
        S = new graphNode[vertices];
        C = new int[vertices];
        P = new int[vertices];

        //Obtain dijkstra arrays
        dijkstra(i, S, C, P);

        compGraph.insert(adjacencyList[i]->value);

        //Add adjacent nodes by using shortest distances between given node and all other nodes
        for (int n = 0; n < vertices; n++)
        {
            if (i == n)
                continue;

            compGraph.insert(adjacencyList[i]->value, adjacencyList[n]->value, C[n]);
        }

        //Reset dijkstra arrays
        delete[] S;
        delete[] C;
        delete[] P;
    }

    return compGraph;
}

//Best algorithm for best path I could think of right now, kinda just Kruskal's algorithm, but goes along a
//single path, which is possible with complete graph
graphNode* stadiumGraph::shortestPathAll() {
    stadiumGraph compGraph = completeGraph();

    int numVisited = 0;
    graphNode* visited, *end;
    visited = end = nullptr;

    //Start at dodger stadium
    visited = new graphNode(adjacencyList[find("Dodger Stadium")]->value);
    end = visited;
    numVisited++;
    graphNode* current = compGraph.adjacencyList[compGraph.find("Dodger Stadium")];

    //Until all stadiums are visited
    while (numVisited < vertices)
    {
        //Finds shortest path to another stadium that isn't already visited
        graphNode* smallestNode = nullptr;
        int smallest = std::numeric_limits<int>::max();
        //Loops for all adjacent nodes
        for (; current; current = current->adjacent)
        {
            //If smaller cost found
            if (current->distance < smallest)
            {
                //Check if already visited
                bool alreadyVisited = false;
                for (graphNode* ptr = visited; ptr; ptr = ptr->adjacent)
                {
                    if (ptr->value == current->value)
                    {
                        alreadyVisited = true;
                        break;
                    }
                }

                if (alreadyVisited)
                    continue;

                smallestNode = current;
                smallest = current->distance;
            }
        }

        //Add next closest stadium to current stadium, change current stadium to added stadium
        end->adjacent = new graphNode(smallestNode->value);
        end = end->adjacent;
        numVisited++;
        current = compGraph.adjacencyList[compGraph.find(smallestNode->value)];
    }

    //Expand the paired paths to include the in-between stadiums needed to travel between stadiums.
    expandPath(visited);

    return visited;
}

//Same algorithm as above, but only intentionally travels to national league stadiums
graphNode* stadiumGraph::shortestPathNational() {
    stadiumGraph compGraph = completeGraph();

    graphNode* visited, *end;
    visited = end = nullptr;

    visited = new graphNode(adjacencyList[find("Dodger Stadium")]->value);
    end = visited;
    graphNode* current = compGraph.adjacencyList[compGraph.find("Dodger Stadium")];

    //Loops until no more national league stadiums to visit, everything else the same
    while (true)
    {
        graphNode* smallestNode = nullptr;
        int smallest = std::numeric_limits<int>::max();
        for (; current; current = current->adjacent)
        {
            if (current->distance < smallest && current->value.getLeague() == "National")
            {
                bool alreadyVisited = false;
                for (graphNode* ptr = visited; ptr; ptr = ptr->adjacent)
                {
                    if (ptr->value == current->value)
                    {
                        alreadyVisited = true;
                        break;
                    }
                }

                if (alreadyVisited)
                    continue;

                smallestNode = current;
                smallest = current->distance;
            }
        }

        //If no more national league stadiums to visit
        if (smallest == std::numeric_limits<int>::max())
            break;

        end->adjacent = new graphNode(smallestNode->value);
        end = end->adjacent;
        current = compGraph.adjacencyList[compGraph.find(smallestNode->value)];
    }

    expandPath(visited);

    return visited;
}

//Same as above but for american league stadiums
graphNode* stadiumGraph::shortestPathAmerican() {
    stadiumGraph compGraph = completeGraph();

    graphNode* visited, *end;
    visited = end = nullptr;

    //Starts at Angel stadium cuz american league
    visited = new graphNode(adjacencyList[find("Angel Stadium")]->value);
    end = visited;
    graphNode* current = compGraph.adjacencyList[compGraph.find("Angel Stadium")];

    //Loops until no more american league stadiums to visit, everything else same
    while (true)
    {
        graphNode* smallestNode = nullptr;
        int smallest = std::numeric_limits<int>::max();
        for (; current; current = current->adjacent)
        {
            if (current->distance < smallest && current->value.getLeague() == "American")
            {
                bool alreadyVisited = false;
                for (graphNode* ptr = visited; ptr; ptr = ptr->adjacent)
                {
                    if (ptr->value == current->value)
                    {
                        alreadyVisited = true;
                        break;
                    }
                }

                if (alreadyVisited)
                    continue;

                smallestNode = current;
                smallest = current->distance;
            }
        }

        //If no more American league stadiums to visit
        if (smallest == std::numeric_limits<int>::max())
            break;

        end->adjacent = new graphNode(smallestNode->value);
        end = end->adjacent;
        current = compGraph.adjacencyList[compGraph.find(smallestNode->value)];
    }

    expandPath(visited);

    return visited;
}

//Uses the dijkstra algorithm arrays to determine the intermediate stadiums visited between the edge pairing
//in the complete graph, and editing the linked list accordingly
void stadiumGraph::expandPath(graphNode *&visited) {
    graphNode* S;
    int* C;
    int* P;
    graphNode* current = visited;

    //While not at the end of the linked list
    while (current->adjacent)
    {
        //obtain dijkstra arrays
        dijkstra(find(current->value), S, C, P);

        //If the two stadiums actually directly connected, move to next
        if (P[find(current->adjacent->value)] == find(current->value))
        {
            continue;
            current = current->adjacent;
        }

        //path chain that gets update from end to start, save end node in end
        graphNode* newChain = new graphNode(current->adjacent->value);
        graphNode* end = newChain;

        //Loops until the stadium at current is added to newChain
        while (newChain->value != current->value)
        {
            //Obtain cost between this stadium and its source stadium
            int spot = find(newChain->value);
            newChain->distance = C[spot];

            //Add source stadium to front of newChain
            graphNode* newNode = nullptr;
            newNode = new graphNode(adjacencyList[P[spot]]->value);
            newNode->adjacent = newChain;
            newChain = newNode;
        }

        //Remove first node in newChain, since This value will either just be 0, or will have been
        //assigned in previous cycle
        graphNode* placehold = newChain->adjacent;
        delete newChain;
        newChain = placehold;

        //Connect newChain to original linked list
        end->adjacent = current->adjacent->adjacent;

        //Remove back end of 2-stadium edge, connects the current node to beginning of newChain
        delete current->adjacent;
        current->adjacent = newChain;
        current = end; //Change current to start at the next 2-stadium edge

        //reset dijkstra arrays
        delete[] S;
        delete[] C;
        delete[] P;
    }
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

//find and return index of stadium with same name in list
int stadiumGraph::find(std::string name) {
    for (int i = 0; i < vertices; i++)
        if (name == adjacencyList[i]->value.getName())
            return i;

    return -1;
}
