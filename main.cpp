#include "mainwindow.h"
#include <QApplication>

stadium parseStadium(std::ifstream &inFile)
{
    string name, team, address, addressLine2, phoneNum, dateStr, league, field;
    int capacity;
    int month = 0, day = 0, year = 0;

    getline(inFile, name);
    getline(inFile, team);
    getline(inFile, address);
    getline(inFile, addressLine2);
    getline(inFile, phoneNum);
    getline(inFile, dateStr);

    // Parse date MM/DD/YYYY
    sscanf(dateStr.c_str(), "%d/%d/%d", &month, &day, &year);

    inFile >> capacity;
    inFile.ignore(); // discard newline
    getline(inFile, league);
    getline(inFile, field);

    return stadium(name, team, address, addressLine2, phoneNum, month, day, year, capacity, league, field, true);
}
void loadStadiums(stadiumGraph &graph, const fs::path &filePath)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open file.\n";
        return;
    }

    vector<stadium> stadiums;
    unordered_map<string, vector<pair<string, int>>> adjacencyMap;

    while (inFile)
    {
        stadium s = parseStadium(inFile);
        if (s.getName().empty())
            break; // End of file or bad read

        stadiums.push_back(s);

        string line;
        getline(inFile, line); // should be '{'
        while (getline(inFile, line) && line != "}")
        {
            stringstream ss(line);
            string neighbor;
            int dist;
            if (getline(ss, neighbor, ',') && ss >> dist)
            {
                adjacencyMap[s.getName()].emplace_back(neighbor, dist);
            }
        }
    }

    for (const auto &s : stadiums)
        graph.insert(s);

    for (const auto &s : stadiums)
    {
        for (const auto &[neighborName, dist] : adjacencyMap[s.getName()])
        {
            int neighborIdx = graph.find(neighborName);
            if (neighborIdx != -1)
                graph.insert(s, graph.getStadium(neighborIdx)->value, dist);
        }
    }
}

int main(int argc, char *argv[])
{
    stadiumGraph graph;

    fs::path projectRoot = findProjectRoot(); // your helper
    fs::path stadiumsPath = projectRoot / "src" / "stadiums.txt";

    loadStadiums(graph, stadiumsPath);

    graphNode *path = graph.shortestPathBetween("Dodger Stadium", "Chase Field");

    if (!path)
    {
        std::cout << "No path found.\n";
        return 1;
    }

    std::cout << "Shortest path from Dodger Stadium to Chase Field:\n";
    for (graphNode *curr = path; curr; curr = curr->adjacent)
    {
        std::cout << "-> " << curr->value.getName() << '\n';
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
