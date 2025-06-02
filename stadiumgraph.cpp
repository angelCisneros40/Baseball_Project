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

        graphNode *current = adjacencyList[i], *other = otherGraph.adjacencyList[i];
        for (; other != nullptr; current = current->adjacent, other = other->adjacent)
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

// Insert new stadium into graph
void stadiumGraph::insert(stadium value)
{
    sizeUp();

    adjacencyList[vertices - 1] = new graphNode(value);
}

// add adjacent stadium to existing stadium (add edge)
void stadiumGraph::insert(stadium target, stadium value, int distance)
{
    int spot = find(target);

    graphNode *end = adjacencyList[spot];
    for (; end->adjacent != nullptr; end = end->adjacent)
        ;

    end->adjacent = new graphNode(value, distance);
    end = nullptr;
}

// dijkstra's algorithm, alters the dynamic arrays that hold the parsed nodes and the costs and paths
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

            // If first non-repeat vertex or is smaller cost than current smallest cost index
            if (smallestC == -1 || C[smallestC] > C[i])
                smallestC = i;
        }

        // Adds node with smallest cost to S
        S[s_size] = *adjacencyList[smallestC];
        s_size++;

        // Checks to alter all adjacent nodes to the vertex just added to S
        for (graphNode *current = adjacencyList[smallestC]->adjacent; current != nullptr; current = current->adjacent)
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

            // If this path to given vertex was cheaper, change its cost and the path taken to get there
            if (C[smallestC] + current->distance < C[spot])
            {
                C[spot] = C[smallestC] + current->distance;
                P[spot] = smallestC;
            }
        }
    }
}

// Creates and returns complete graph of current graph object (each node connected to each other node)
stadiumGraph stadiumGraph::completeGraph()
{
    stadiumGraph compGraph;

    for (int i = 0; i < vertices; i++)
    {
        graphNode *S = new graphNode[vertices];
        int *C = new int[vertices];
        int *P = new int[vertices];

        dijkstra(i, S, C, P);

        // Insert the starting node into the complete graph
        compGraph.insert(adjacencyList[i]->value);

        for (int n = 0; n < vertices; n++)
        {
            if (i == n)
                continue;

            // Make sure destination node exists in the graph
            compGraph.insert(adjacencyList[n]->value);

            int fromIdx = compGraph.find(adjacencyList[i]->value.getName());
            int toIdx = compGraph.find(adjacencyList[n]->value.getName());

            if (fromIdx != -1 && toIdx != -1)
            {
                compGraph.insert(
                    compGraph.adjacencyList[fromIdx]->value,
                    compGraph.adjacencyList[toIdx]->value,
                    C[n]);
            }
        }

        delete[] S;
        delete[] C;
        delete[] P;
    }

    return compGraph;
}


// Best algorithm for best path I could think of right now, kinda just Kruskal's algorithm, but goes along a
// single path, which is possible with complete graph
graphNode* stadiumGraph::shortestPathAll()
{
    int startIdx = find("Dodger Stadium");
    if (startIdx == -1)
    {
        std::cerr << "Error: Dodger Stadium not found.\n";
        return nullptr;
    }

    std::unordered_set<std::string> visited;
    graphNode* head = nullptr;
    graphNode* tail = nullptr;

    int currentIdx = startIdx;
    visited.insert(adjacencyList[currentIdx]->value.getName());

    while (visited.size() < vertices)
    {
        // Run Dijkstra from current stadium
        graphNode* S = new graphNode[vertices];
        int* C = new int[vertices];
        int* P = new int[vertices];
        dijkstra(currentIdx, S, C, P);

        // Find closest unvisited stadium
        int closestIdx = -1;
        int minDist = std::numeric_limits<int>::max();
        for (int i = 0; i < vertices; ++i)
        {
            std::string name = adjacencyList[i]->value.getName();
            if (visited.count(name) == 0 && C[i] < minDist)
            {
                minDist = C[i];
                closestIdx = i;
            }
        }

        if (closestIdx == -1)
        {
            std::cerr << "No reachable unvisited stadium from " << adjacencyList[currentIdx]->value.getName() << "\n";
            delete[] S;
            delete[] C;
            delete[] P;
            break;
        }

        // Reconstruct path from currentIdx to closestIdx
        std::vector<int> path;
        for (int at = closestIdx; at != -1; at = P[at])
            path.push_back(at);
        std::reverse(path.begin(), path.end());

        for (size_t i = 1; i < path.size(); ++i)
        {
            graphNode* node = new graphNode(adjacencyList[path[i]]->value);
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
        graphNode* startNode = new graphNode(adjacencyList[startIdx]->value);
        startNode->adjacent = head;
        head = startNode;
    }

    return head;
}




// Same algorithm as above, but only intentionally travels to national league stadiums
graphNode *stadiumGraph::shortestPathNational()
{
    stadiumGraph compGraph = completeGraph();

    graphNode *visited, *end;
    visited = end = nullptr;

    visited = new graphNode(adjacencyList[find("Dodger Stadium")]->value);
    end = visited;
    graphNode *current = compGraph.adjacencyList[compGraph.find("Dodger Stadium")];

    // Loops until no more national league stadiums to visit, everything else the same
    while (true)
    {
        graphNode *smallestNode = nullptr;
        int smallest = numeric_limits<int>::max();
        for (; current; current = current->adjacent)
        {
            if (current->distance < smallest && current->value.getLeague() == "National")
            {
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

        // If no more national league stadiums to visit
        if (smallest == numeric_limits<int>::max())
            break;

        end->adjacent = new graphNode(smallestNode->value);
        end = end->adjacent;
        current = compGraph.adjacencyList[compGraph.find(smallestNode->value)];
    }

    expandPath(visited);

    return visited;
}

// Same as above but for american league stadiums
graphNode *stadiumGraph::shortestPathAmerican()
{
    stadiumGraph compGraph = completeGraph();

    graphNode *visited, *end;
    visited = end = nullptr;

    // Starts at Angel stadium cuz american league
    visited = new graphNode(adjacencyList[find("Angel Stadium")]->value);
    end = visited;
    graphNode *current = compGraph.adjacencyList[compGraph.find("Angel Stadium")];

    // Loops until no more american league stadiums to visit, everything else same
    while (true)
    {
        graphNode *smallestNode = nullptr;
        int smallest = numeric_limits<int>::max();
        for (; current; current = current->adjacent)
        {
            if (current->distance < smallest && current->value.getLeague() == "American")
            {
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

        // If no more American league stadiums to visit
        if (smallest == numeric_limits<int>::max())
            break;

        end->adjacent = new graphNode(smallestNode->value);
        end = end->adjacent;
        current = compGraph.adjacencyList[compGraph.find(smallestNode->value)];
    }

    expandPath(visited);

    return visited;
}

//Same as others before, but now only explicitly travel to stadiums in given linked list.
graphNode *stadiumGraph::shortestPathSpecified(graphNode* specifiedList)
{
    stadiumGraph compGraph = completeGraph();

    graphNode *visited, *end;
    visited = end = nullptr;

    //Path/trip starts at the first stadium in the specifiedList
    visited = new graphNode(adjacencyList[find(specifiedList->value)]->value);
    end = visited;
    graphNode *current = compGraph.adjacencyList[compGraph.find(specifiedList->value)];

    // Loops until no more stadiums to visit from specifiedList, everything else the same
    while (true)
    {
        graphNode *smallestNode = nullptr;
        int smallest = numeric_limits<int>::max();
        for (; current; current = current->adjacent)
        {
            if (current->distance < smallest)
            {
                bool inList = false;
                for (graphNode* ptr = specifiedList; ptr; ptr = ptr->adjacent)
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

void stadiumGraph::expandPath(graphNode *&visited)
{
    graphNode *current = visited;

    // While not at the end of the linked list
    while (current->adjacent)
    {
        // Allocate memory BEFORE calling dijkstra
        graphNode *S = new graphNode[vertices];
        int *C = new int[vertices];
        int *P = new int[vertices];

        dijkstra(find(current->value), S, C, P);

        // If directly connected, skip to next
        if (P[find(current->adjacent->value)] == find(current->value))
        {
            delete[] S;
            delete[] C;
            delete[] P;
            current = current->adjacent;
            continue;
        }

        // Build new path
        graphNode *newChain = new graphNode(current->adjacent->value);
        graphNode *end = newChain;

        while (newChain->value != current->value)
        {
            int spot = find(newChain->value);
            newChain->distance = C[spot];

            int predIndex = P[spot];
            if (predIndex == -1)
            {
                std::cerr << "Invalid path: No predecessor found for node.\n";
                break;
            }

            graphNode *newNode = new graphNode(adjacencyList[predIndex]->value);
            newNode->adjacent = newChain;
            newChain = newNode;
        }

        // Delete first node in newChain (duplicate of current)
        graphNode *placehold = newChain->adjacent;
        delete newChain;
        newChain = placehold;

        // Connect path
        end->adjacent = current->adjacent->adjacent;
        delete current->adjacent;
        current->adjacent = newChain;
        current = end;

        // Clean up
        delete[] S;
        delete[] C;
        delete[] P;
    }
}


stadiumGraph &stadiumGraph::operator=(const stadiumGraph &otherGraph)
{
    clear();

    vertices = otherGraph.vertices;
    adjacencyList = new graphNode *[vertices];

    for (int i = 0; i < vertices; i++)
    {
        adjacencyList[i] = new graphNode(otherGraph.adjacencyList[i]->value);

        graphNode *current = adjacencyList[i], *other = otherGraph.adjacencyList[i];
        for (; other != nullptr; current = current->adjacent, other = other->adjacent)
        {
            *current = *other;
        }
    }

    return *this;
}

// Copy and increase size of graph adjacency list
void stadiumGraph::sizeUp()
{
    int newSize = vertices + 1;
    graphNode **newList = new graphNode *[newSize];

    for (int i = 0; i < vertices; i++)
    {
        newList[i] = new graphNode(adjacencyList[i]->value);

        graphNode *current = newList[i], *other = adjacencyList[i];
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

void stadiumGraph::clear()
{
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

// find and return index of stadium with same value in list
int stadiumGraph::find(stadium value)
{
    for (int i = 0; i < vertices; i++)
        if (value == adjacencyList[i]->value)
            return i;

    return -1;
}

// find and return index of stadium with same name in list
int stadiumGraph::find(string name)
{
    for (int i = 0; i < vertices; i++)
        if (name == adjacencyList[i]->value.getName())
            return i;

    return -1;
}

// find and return list of links with the shortest path fron start to end
graphNode *stadiumGraph::shortestPathBetween(const string &startName, const string &endName)
{
    int startIdx = find(startName);
    int endIdx = find(endName);
    if (startIdx == -1 || endIdx == -1)
        return nullptr;

    graphNode *S = new graphNode[vertices];
    int *C = new int[vertices];
    int *P = new int[vertices];

    dijkstra(startIdx, S, C, P);

    if (C[endIdx] == numeric_limits<int>::max())
    {
        delete[] S;
        delete[] C;
        delete[] P;
        return nullptr;
    }

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

void stadiumGraph::printGraph() const
{
    if (!adjacencyList || vertices == 0)
    {
        cout << "Graph is empty.\n";
        return;
    }

    cout << "===== Stadium Graph =====" << endl;
    for (int i = 0; i < vertices; ++i)
    {
        graphNode *current = adjacencyList[i];
        if (!current)
            continue;

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

int stadiumGraph::getVertexCount() const
{
    return vertices;
}

bool stadiumGraph::isEmpty() const {
    return vertices == 0 || adjacencyList == nullptr;
}

graphNode* stadiumGraph::shortestPathAllFrom(const std::string& startName)
{
    int startIdx = find(startName);
    if (startIdx == -1)
    {
        std::cerr << "Error: Starting stadium not found.\n";
        return nullptr;
    }

    std::unordered_set<std::string> visited;
    graphNode* head = new graphNode(adjacencyList[startIdx]->value);
    graphNode* tail = head;
    visited.insert(head->value.getName());

    graphNode* current = adjacencyList[startIdx];

    while (visited.size() < getVertexCount())
    {
        graphNode* next = nullptr;
        int minDist = std::numeric_limits<int>::max();

        for (graphNode* adj = current->adjacent; adj; adj = adj->adjacent)
        {
            std::string neighbor = adj->value.getName();
            if (visited.count(neighbor) == 0 && adj->distance < minDist)
            {
                minDist = adj->distance;
                next = adj;
            }
        }

        if (!next)
        {
            std::cerr << "Error: No unvisited neighbor found from " << current->value.getName() << "\n";
            break;
        }

        tail->adjacent = new graphNode(next->value);
        tail->adjacent->distance = minDist;
        tail = tail->adjacent;
        visited.insert(tail->value.getName());

        current = adjacencyList[find(next->value)];
    }

    return head;
}

