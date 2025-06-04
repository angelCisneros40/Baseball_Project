#include "stadiumgraph.h"

stadiumGraph::stadiumGraph(stadium value)
{
    vertices = 1;
    adjacencyList = new graphNode *[vertices];

    adjacencyList[0] = new graphNode(value);
}

// copy constructor
stadiumGraph::stadiumGraph(const stadiumGraph &otherGraph)
{
    vertices = otherGraph.vertices;
    adjacencyList = new graphNode *[vertices];

    for (int i = 0; i < vertices; i++)
    {
        adjacencyList[i] = new graphNode(otherGraph.adjacencyList[i]->value);

        graphNode *current = adjacencyList[i], *other =
                                                   otherGraph.adjacencyList[i];
        for (; other != nullptr; current = current->adjacent,
                                 other = other->adjacent)
        {
            *current = *other;
        }
    }
}

// destructor
stadiumGraph::~stadiumGraph()
{
    clear();
}

/**********************************************************
 *
 * Method insert: Class stadiumGraph
 *_________________________________________________________
 * This method increases the size of the adjacencyList and
 * assigns the last index of the adjacencyList to being
 * a graphNode with the given value. Adding a new stadium
 * to graph.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   value - the value of the node being inserted
 *
 * POST-CONDITIONS
 * This function will size up the adjacency list and insert
 * a node with the given value at the last index.
 ***********************************************************/
void stadiumGraph::insert(stadium value)
{
    sizeUp();

    adjacencyList[vertices - 1] = new graphNode(value);
}

/**********************************************************
 *
 * Method insert: Class stadiumGraph
 *_________________________________________________________
 * This method inserts a graphNode with the given value
 * and distance at the end of the linked list whose first
 * graphNode has the given target value in adjacencyList.
 * Adding an edge/adjacent vertex to the graph.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   target - the value of the node whose linked list is being
 *      inserted into
 *   value - the value of the node being inserted
 *   distance - the distance of the node being inserted
 *
 * POST-CONDITIONS
 * This function will add an adjacent stadium to the target
 * stadium.
 ***********************************************************/
void stadiumGraph::insert(stadium target, stadium value, int distance)
{
    // Find index of target node in adjacencyList
    int spot = find(target);

    // Reach the end of the target linked list
    graphNode *end = adjacencyList[spot];
    for (; end->adjacent != nullptr; end = end->adjacent)
        ;

    // Add adjacent stadium at end
    end->adjacent = new graphNode(value, distance);
    end = nullptr;
}

/**********************************************************
 *
 * Method dijkstra: Class stadiumGraph
 *_________________________________________________________
 * This method applies dijkstra's algorithm to this graph
 * starting at the stadium at the start index of adjacencyList,
 * The corresponding dijkstra algorithm arrays (S holding the vetices
 * as they are added according to shortest distance from the start node,
 * C holding the shortest distances from the start node to all other
 * nodes, and P holding the path from which the shortest path to the
 * node with the corresponding index came from. indexes of C and P
 * correspond with indexes of adjacencyList) are altered by reference
 * to reflect the shortest paths from the start node and all other
 * nodes.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   start - the index of stadium that dijkstra's algorithm
 *      will expand/originate from in adjacencyList.
 *   S - the array holding the vertices as they are added in the algorithm
 *   C - the array holding the costs to move from the start stadium to the
 *      other stadiums.
 *   P - the array holding the indexes of the graphNodes whose path leads
 *      to the corresponding graphNode
 *
 * POST-CONDITIONS
 * This function will fill the dijkstra arrays.
 ***********************************************************/
void stadiumGraph::dijkstra(int start, graphNode *&S, int *&C, int *&P)
{
    int s_size = 0;
    fill(S, S + vertices, graphNode());
    fill(P, P + vertices, -1);
    fill(C, C + vertices, numeric_limits<int>::max());
    C[start] = 0;

    // While all vertices haven't been parsed
    while (s_size != vertices)
    {
        // Searching for smallest edge cost to move to next node and add it to S
        int smallestC = -1;
        for (int i = 0; i < vertices; i++)
        {
            // Check if vertex exists in S already
            bool repeat = false;
            for (int n = 0; n < s_size; n++)
            {
                if (S[n].value == adjacencyList[i]->value)
                {
                    repeat = true;
                    break;
                }
            }

            // If exists in S
            if (repeat)
                continue;

            // If first non-repeat vertex or is smaller
            // cost than current smallest cost index
            if (smallestC == -1 || C[smallestC] > C[i])
                smallestC = i;
        }

        // Adds node with smallest cost to S
        S[s_size] = *adjacencyList[smallestC];
        s_size++;

        // Checks to alter all adjacent nodes to the vertex just added to S
        for (graphNode *current = adjacencyList[smallestC]->adjacent;
             current != nullptr; current = current->adjacent)
        {
            // Check if adjacent node already in S
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

            // If this path to given vertex was cheaper,
            // change its cost and the path taken to get there
            if (C[smallestC] + current->distance < C[spot])
            {
                C[spot] = C[smallestC] + current->distance;
                P[spot] = smallestC;
            }
        }
    }
}

/**********************************************************
 *
 * Method completeGraph: Class stadiumGraph
 *_________________________________________________________
 * This method applies dijkstra's algorithm at each vertex,
 * using those arrays to create a complete graph based off
 * of this graph.
 *_________________________________________________________
 * PRE-CONDITIONS
 * none
 *
 * POST-CONDITIONS
 * This function will return a complete graph based off of
 * this graph.
 ***********************************************************/
stadiumGraph stadiumGraph::completeGraph()
{
    stadiumGraph compGraph;

    graphNode *S;
    int *C;
    int *P;

    // Run for each vertex
    for (int i = 0; i < vertices; i++)
    {
        S = new graphNode[vertices];
        C = new int[vertices];
        P = new int[vertices];

        // Obtain dijkstra arrays
        dijkstra(i, S, C, P);

        compGraph.insert(adjacencyList[i]->value);

        // Add adjacent nodes by using shortest distances between
        // given node and all other nodes
        for (int n = 0; n < vertices; n++)
        {
            if (i == n)
                continue;

            compGraph.insert(
                adjacencyList[i]->value,
                adjacencyList[n]->value,
                C[n]);
        }

        // Reset dijkstra arrays
        delete[] S;
        delete[] C;
        delete[] P;
    }

    return compGraph;
}

/**********************************************************
 *
 * Method shortestPathAll: Class stadiumGraph
 *_________________________________________________________
 * This method creates a complete graph based on this graph,
 * and then uses a greedy algorithm starting at Dodger stadium
 * to travel along and add the next closest stadium that
 * has not already been visitied to a linked list. This
 * process stops once all major league stadiums have been
 * visited. Then, the visited linked list is expanded to
 * include each intermediate stadium traveled to bridge two
 * stadiums. Then, the list of visited stadiums is returned.
 *_________________________________________________________
 * PRE-CONDITIONS
 * none
 *
 * POST-CONDITIONS
 * This function will return a linked list containing the
 * shortest path to pass through all major league stadiums.
 ***********************************************************/
graphNode *stadiumGraph::shortestPathAll()
{
    int startIdx = find("Dodger Stadium");
    if (startIdx == -1)
    {
        cerr << "Error: Dodger Stadium not found.\n";
        return nullptr;
    }

    unordered_set<string> visited;
    graphNode *head = nullptr;
    graphNode *tail = nullptr;

    int currentIdx = startIdx;
    visited.insert(adjacencyList[currentIdx]->value.getName());

    while (visited.size() < vertices)
    {
        // Run Dijkstra from current stadium
        graphNode *S = new graphNode[vertices];
        int *C = new int[vertices];
        int *P = new int[vertices];
        dijkstra(currentIdx, S, C, P);

        // Find closest unvisited stadium
        int closestIdx = -1;
        int minDist = numeric_limits<int>::max();
        for (int i = 0; i < vertices; ++i)
        {
            string name = adjacencyList[i]->value.getName();
            if (visited.count(name) == 0 && C[i] < minDist)
            {
                minDist = C[i];
                closestIdx = i;
            }
        }

        if (closestIdx == -1)
        {
            cerr << "No reachable unvisited stadium from "
                 << adjacencyList[currentIdx]->value.getName() << "\n";
            delete[] S;
            delete[] C;
            delete[] P;
            break;
        }

        // Reconstruct path from currentIdx to closestIdx
        vector<int> path;
        for (int at = closestIdx; at != -1; at = P[at])
            path.push_back(at);
        reverse(path.begin(), path.end());

        for (size_t i = 1; i < path.size(); ++i)
        {
            graphNode *node = new graphNode(adjacencyList[path[i]]->value);
            node->distance = C[path[i]] - C[path[i - 1]];

            if (!head)
                head = tail = node;
            else
            {
                tail->adjacent = node;
                tail = tail->adjacent;
            }

            visited.insert(node->value.getName());
        }

        currentIdx = closestIdx;
        delete[] S;
        delete[] C;
        delete[] P;
    }

    // Prepend start stadium if head is null
    if (!head)
        head = new graphNode(adjacencyList[startIdx]->value);
    else
    {
        graphNode *startNode = new graphNode(adjacencyList[startIdx]->value);
        startNode->adjacent = head;
        head = startNode;
    }

    return head;
}

/**********************************************************
 *
 * Method shortestPathNational: Class stadiumGraph
 *_________________________________________________________
 * This method creates a complete graph based on this graph,
 * and then uses a greedy algorithm starting at Dodger stadium
 * to travel along and add the next closest stadium that
 * has not already been visitied to a linked list. This
 * process stops once all national league stadiums have been
 * visited. Then, the visited linked list is expanded to
 * include each intermediate stadium traveled to bridge two
 * stadiums. Then, the list of visited stadiums is returned.
 *_________________________________________________________
 * PRE-CONDITIONS
 * none
 *
 * POST-CONDITIONS
 * This function will return a linked list containing the
 * shortest path to pass through all national league stadiums.
 ***********************************************************/
graphNode *stadiumGraph::shortestPathNational()
{
    int startIdx = find("Dodger Stadium");
    if (startIdx == -1)
    {
        cerr << "Dodger Stadium not found.\n";
        return nullptr;
    }

    unordered_set<string> visited;
    graphNode *head = new graphNode(adjacencyList[startIdx]->value);
    graphNode *tail = head;
    visited.insert(head->value.getName());

    stadium currentStadium = adjacencyList[startIdx]->value;

    while (true)
    {
        // Run Dijkstra from current stadium
        graphNode *S = new graphNode[vertices];
        int *C = new int[vertices];
        int *P = new int[vertices];
        dijkstra(find(currentStadium), S, C, P);

        int nextIdx = -1;
        int minDist = numeric_limits<int>::max();

        // Find closest unvisited National League stadium
        for (int i = 0; i < vertices; ++i)
        {
            if (adjacencyList[i]->value.getLeague() != "National")
                continue;
            if (visited.count(adjacencyList[i]->value.getName()))
                continue;

            if (C[i] < minDist)
            {
                minDist = C[i];
                nextIdx = i;
            }
        }

        // Done visiting all National League stadiums
        if (nextIdx == -1)
        {
            delete[] S;
            delete[] C;
            delete[] P;
            break;
        }

        // Reconstruct path from P[] and add to linked list
        vector<int> pathIndices;
        for (int v = nextIdx; v != -1; v = P[v])
            pathIndices.push_back(v);
        reverse(pathIndices.begin(), pathIndices.end());

        for (size_t j = 1; j < pathIndices.size(); ++j)
        {
            graphNode *step = new graphNode(
                adjacencyList[pathIndices[j]]->value);
            step->distance = C[pathIndices[j]];
            tail->adjacent = step;
            tail = step;
            visited.insert(step->value.getName());
        }

        currentStadium = adjacencyList[nextIdx]->value;

        delete[] S;
        delete[] C;
        delete[] P;
    }

    return head;
}

/**********************************************************
 *
 * Method shortestPathAmerican: Class stadiumGraph
 *_________________________________________________________
 * This method creates a complete graph based on this graph,
 * and then uses a greedy algorithm starting at Angels stadium
 * to travel along and add the next closest stadium that
 * has not already been visitied to a linked list. This
 * process stops once all american league stadiums have been
 * visited. Then, the visited linked list is expanded to
 * include each intermediate stadium traveled to bridge two
 * stadiums. Then, the list of visited stadiums is returned.
 *_________________________________________________________
 * PRE-CONDITIONS
 * none
 *
 * POST-CONDITIONS
 * This function will return a linked list containing the
 * shortest path to pass through all american league stadiums.
 ***********************************************************/
graphNode *stadiumGraph::shortestPathAmerican()
{
    int startIdx = find("Angel Stadium");
    if (startIdx == -1)
    {
        cerr << "Angel Stadium not found.\n";
        return nullptr;
    }

    unordered_set<string> visited;
    graphNode *head = new graphNode(adjacencyList[startIdx]->value);
    graphNode *tail = head;
    visited.insert(head->value.getName());

    stadium currentStadium = adjacencyList[startIdx]->value;

    while (true)
    {
        // Dijkstra to all nodes from current stadium
        graphNode *S = new graphNode[vertices];
        int *C = new int[vertices];
        int *P = new int[vertices];
        dijkstra(find(currentStadium), S, C, P);

        int nextIdx = -1;
        int minDist = numeric_limits<int>::max();

        // Search for the closest unvisited American League stadium
        for (int i = 0; i < vertices; ++i)
        {
            if (adjacencyList[i]->value.getLeague() != "American")
                continue;
            if (visited.count(adjacencyList[i]->value.getName()))
                continue;

            if (C[i] < minDist)
            {
                minDist = C[i];
                nextIdx = i;
            }
        }

        if (nextIdx == -1) // All visited
        {
            delete[] S;
            delete[] C;
            delete[] P;
            break;
        }

        // Reconstruct the shortest path using
        // P[] from currentStadium to nextIdx
        vector<int> pathIndices;
        for (int v = nextIdx; v != -1; v = P[v])
            pathIndices.push_back(v);
        reverse(pathIndices.begin(), pathIndices.end());

        for (size_t j = 1; j < pathIndices.size(); ++j)
        {
            graphNode *step = new graphNode(
                adjacencyList[pathIndices[j]]->value);
            step->distance = C[pathIndices[j]];
            tail->adjacent = step;
            tail = step;
            visited.insert(step->value.getName());
        }

        currentStadium = adjacencyList[nextIdx]->value;

        delete[] S;
        delete[] C;
        delete[] P;
    }

    return head;
}

/**********************************************************
 *
 * Method shortestPathSpecified: Class stadiumGraph
 *_________________________________________________________
 * This method creates a complete graph based on this graph,
 * and then uses a greedy algorithm starting at the first
 * stadium in specifiedList to travel along and add the next
 * closest stadium that has not already been visitied to a
 * linked list. This process stops once all stadiums in
 * specifiedList have been visited. Then, the visited linked list
 * is expanded to include each intermediate stadium traveled
 * to bridge two stadiums. Then, the list of visited stadiums
 * is returned.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   specifiedList - the linked list of graphNodes that contains
 *      the stadiums to be visited.
 *
 * POST-CONDITIONS
 * This function will return a linked list containing the
 * shortest path to pass through all stadiums in specifiedList.
 ***********************************************************/
graphNode *stadiumGraph::shortestPathSpecified(graphNode *specifiedList)
{
    stadiumGraph compGraph = completeGraph();

    graphNode *visited, *end;
    visited = end = nullptr;

    // Path/trip starts at the first stadium in the specifiedList
    visited = new graphNode(
        adjacencyList[find(specifiedList->value)]->value);
    end = visited;
    graphNode *current = compGraph.adjacencyList[compGraph.find(
        specifiedList->value)];

    // Loops until no more stadiums to visit from specifiedList,
    // everything else the same
    while (true)
    {
        graphNode *smallestNode = nullptr;
        int smallest = numeric_limits<int>::max();
        for (; current; current = current->adjacent)
        {
            if (current->distance < smallest)
            {
                bool inList = false;
                for (graphNode *ptr = specifiedList; ptr; ptr = ptr->adjacent)
                {
                    if (ptr->value == current->value)
                    {
                        inList = true;
                        break;
                    }
                }

                if (!inList)
                    continue;

                bool alreadyVisited = false;
                for (graphNode *ptr = visited; ptr; ptr = ptr->adjacent)
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

        // If no more stadiums in specifiedList to visit
        if (smallest == numeric_limits<int>::max())
            break;

        end->adjacent = new graphNode(smallestNode->value);
        end = end->adjacent;
        current = compGraph.adjacencyList[compGraph.find(smallestNode->value)];
    }

    expandPath(visited);

    return visited;
}

/**********************************************************
 *
 * Method expandPath: Class stadiumGraph
 *_________________________________________________________
 * This method takes the linked list of vertices visited
 * and expands each 2-stadium edge to include each intermediate
 * stadium needed to bridge the two stadiums into visited
 * based on this graph.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   visited - the linked list containing a path to stadiums
 *      based off of a complete graph.
 *
 * POST-CONDITIONS
 * This function will expand visited to include all intermediate
 * stadiums that were traveled through.
 ***********************************************************/
void stadiumGraph::expandPath(graphNode *&visited)
{
    graphNode *S;
    int *C;
    int *P;
    graphNode *current = visited;

    // While not at the end of the linked list
    while (current->adjacent)
    {
        // obtain dijkstra arrays
        dijkstra(find(current->value), S, C, P);

        // If the two stadiums actually directly connected, move to next
        if (P[find(current->adjacent->value)] == find(current->value))
        {
            current = current->adjacent;
            continue;
        }

        // path chain that gets update from end to start, save end node in end
        graphNode *newChain = new graphNode(current->adjacent->value);
        graphNode *end = newChain;

        // Loops until the stadium at current is added to newChain
        while (newChain->value != current->value)
        {
            // Obtain cost between this stadium and its source stadium
            int spot = find(newChain->value);
            newChain->distance = C[spot];

            // Add source stadium to front of newChain
            graphNode *newNode = nullptr;
            newNode = new graphNode(adjacencyList[P[spot]]->value);
            newNode->adjacent = newChain;
            newChain = newNode;
        }

        // Remove first node in newChain, since
        // This value will either just be 0, or will have been
        // assigned in previous cycle
        graphNode *placehold = newChain->adjacent;
        delete newChain;
        newChain = placehold;

        // Connect newChain to original linked list
        end->adjacent = current->adjacent->adjacent;

        // Remove back end of 2-stadium edge, connects the current
        // node to beginning of newChain,
        // effectively replacing the first node we deleted just previously
        delete current->adjacent;
        current->adjacent = newChain;
        current = end; // Change current to start at the next 2-stadium edge

        // reset dijkstra arrays
        delete[] S;
        delete[] C;
        delete[] P;
    }
}

/**********************************************************
 *
 * Method operator=: Class stadiumGraph
 *_________________________________________________________
 * This method overloads the assignment operator, copying the
 * contents of otherGraph's adjacencyList and the vertices
 * attribute.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   otherGraph - the other stadiumGraph being copied from
 *
 * POST-CONDITIONS
 * This function will copy the contents of otherGraph into
 * this stadiumGraph object.
 ***********************************************************/
stadiumGraph &stadiumGraph::operator=(const stadiumGraph &otherGraph)
{
    clear();

    // Copy over size/vertices
    vertices = otherGraph.vertices;
    adjacencyList = new graphNode *[vertices];

    // Copy the linked list of each index in the adjacencyList of otherGraph
    for (int i = 0; i < vertices; i++)
    {
        adjacencyList[i] = new graphNode(otherGraph.adjacencyList[i]->value);

        graphNode *current = adjacencyList[i],
                  *other = otherGraph.adjacencyList[i];
        for (; other != nullptr;
             current = current->adjacent, other = other->adjacent)
        {
            *current = *other;
        }
    }

    return *this;
}

/**********************************************************
 *
 * Method sizeUp: Class stadiumGraph
 *_________________________________________________________
 * This method increases the size of adjacencyList by 1
 * and increments vertices. All contents in adjacencyList
 * are maintained.
 *_________________________________________________________
 * PRE-CONDITIONS
 * none
 *
 * POST-CONDITIONS
 * This function will add one more empty index to the end
 * of adjacencyList and increment vertices.
 ***********************************************************/
void stadiumGraph::sizeUp()
{
    int newSize = vertices + 1;
    graphNode **newList = new graphNode *[newSize];

    for (int i = 0; i < vertices; i++)
    {
        newList[i] = new graphNode(adjacencyList[i]->value);

        graphNode *current = newList[i], *other = adjacencyList[i];
        for (; other != nullptr; current = current->adjacent,
                                 other = other->adjacent)
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

/**********************************************************
 *
 * Method clear: Class stadiumGraph
 *_________________________________________________________
 * This method deletes all dynamic memory allocated to
 * adjacencyList, setting it to nullptr and vertices to 0.
 *_________________________________________________________
 * PRE-CONDITIONS
 * none
 *
 * POST-CONDITIONS
 * This function will clear all contents of this object.
 ***********************************************************/
void stadiumGraph::clear()
{
    // Delete each linked list in each index of adjacencyList
    for (int i = 0; i < vertices; i++)
    {
        for (graphNode *current = adjacencyList[i]; current != nullptr;)
        {
            graphNode *placehold = current->adjacent;
            delete current;
            current = placehold;
        }

        adjacencyList[i] = nullptr;
    }

    delete[] adjacencyList;

    adjacencyList = nullptr;
    vertices = 0;
}

/**********************************************************
 *
 * Method find: Class stadiumGraph
 *_________________________________________________________
 * This method searches for and returns the index of the
 * graphNode in adjacencyList with the given value. If not
 * found, return -1.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   value - the stadium being searched for
 *
 * POST-CONDITIONS
 * This function will return the index of graphNode with the
 * given value in adjacencyList or return -1 if not found.
 ***********************************************************/
int stadiumGraph::find(stadium value)
{
    for (int i = 0; i < vertices; i++)
        if (value == adjacencyList[i]->value)
            return i;

    return -1;
}

/**********************************************************
 *
 * Method find: Class stadiumGraph
 *_________________________________________________________
 * This method searches for and returns the index of the
 * graphNode in adjacencyList with the stadium with the
 * given name. If not found returns -1.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   name - the name of the stadium being searched for
 *
 * POST-CONDITIONS
 * This function will return the index of graphNode with the
 * stadium with the given name in adjacencyList or return
 * -1 if not found.
 ***********************************************************/
int stadiumGraph::find(string name)
{
    for (int i = 0; i < vertices; i++)
        if (name == adjacencyList[i]->value.getName())
            return i;

    return -1;
}

/**********************************************************
 *
 * Method shortestPathBetween: Class stadiumGraph
 *_________________________________________________________
 * This method applies dijkstra's algorithm to the graphNode
 * with the given name, and then uses this information to
 * form a linked list containing the path from start stadium
 * to the stadium with endName that is the shortest.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   startName - the name of the stadium the path is starting from
 *   endName - the name of the stadium the path is ending at.
 *
 * POST-CONDITIONS
 * This function will return a linked list containing the
 * shortest path between the stadiums with the corresponding
 * names.
 ***********************************************************/
graphNode *stadiumGraph::shortestPathBetween(
    const string &startName, const string &endName)
{
    // Find indexes of start and end stadiums
    int startIdx = find(startName);
    int endIdx = find(endName);
    if (startIdx == -1 || endIdx == -1)
        return nullptr;

    graphNode *S = new graphNode[vertices];
    int *C = new int[vertices];
    int *P = new int[vertices];

    // Obtain the dijkstra arrays
    dijkstra(startIdx, S, C, P);

    // If no path exist between the start and end stadiums
    if (C[endIdx] == numeric_limits<int>::max())
    {
        delete[] S;
        delete[] C;
        delete[] P;
        return nullptr;
    }

    // Backtrack using the P array to find the full path starting
    // from the end stadium working back to the start stadium
    graphNode *head = new graphNode(adjacencyList[endIdx]->value);
    graphNode *current = head;
    int currentIdx = endIdx;
    while (P[currentIdx] != -1)
    {
        graphNode *newNode = new graphNode(adjacencyList[P[currentIdx]]->value);
        newNode->adjacent = current;
        current = newNode;
        currentIdx = P[currentIdx];
    }

    delete[] S;
    delete[] C;
    delete[] P;

    return current;
}

/**********************************************************
 *
 * Method printGraph: Class stadiumGraph
 *_________________________________________________________
 * This method outputs the contents of the adjacencyList,
 * and thus the contents of this stadiumGraph.
 *_________________________________________________________
 * PRE-CONDITIONS
 * none
 *
 * POST-CONDITIONS
 * This function will output this object's contents for testing
 * purposes.
 ***********************************************************/
void stadiumGraph::printGraph() const
{
    // If adjacencyList is nullptr or vertices is 0
    if (!adjacencyList || vertices == 0)
    {
        cout << "Graph is empty.\n";
        return;
    }

    cout << "===== Stadium Graph =====" << endl;
    for (int i = 0; i < vertices; ++i)
    {
        // If graph does not have a linked list/a stadium
        // at this index, continue
        graphNode *current = adjacencyList[i];
        if (!current)
            continue;

        // Output full linked list
        cout << "Stadium: " << current->value.getName() << endl;
        graphNode *adj = current->adjacent;
        while (adj)
        {
            cout << "  -> " << adj->value.getName()
                 << " (Distance: " << adj->distance << ")" << endl;
            adj = adj->adjacent;
        }
    }
    cout << "=========================" << endl;
}

/**********************************************************
 *
 * Method getVertexCount: Class stadiumGraph
 *_________________________________________________________
 * This method returns the vertices attribute.
 *_________________________________________________________
 * PRE-CONDITIONS
 * none
 *
 * POST-CONDITIONS
 * This function will return the vertices attribute.
 ***********************************************************/
int stadiumGraph::getVertexCount() const
{
    return vertices;
}

bool stadiumGraph::isEmpty() const
{
    return vertices == 0 || adjacencyList == nullptr;
}

graphNode *stadiumGraph::shortestPathTrip(const vector<string> &stadiums)
{
    if (stadiums.size() < 2)
        return nullptr;

    graphNode *head = nullptr;
    graphNode *tail = nullptr;

    for (size_t i = 0; i < stadiums.size() - 1; ++i)
    {
        string from = stadiums[i];
        string to = stadiums[i + 1];

        graphNode *segment = shortestPathBetween(from, to);
        if (!segment)
        {
            cerr << "No path between " << from << " and " << to << endl;
            // Clean up already-allocated path
            while (head)
            {
                graphNode *next = head->adjacent;
                delete head;
                head = next;
            }
            return nullptr;
        }

        // Chain segment into full path
        if (!head)
        {
            head = segment;
            tail = segment;
        }
        else
        {
            // Skip the first node of the segment (it's a duplicate)
            segment = segment->adjacent;

            while (segment)
            {
                graphNode *next = segment->adjacent;
                segment->adjacent = nullptr;
                tail->adjacent = segment;
                tail = segment;
                segment = next;
            }
        }
    }

    return head;
}
