#include "readStadiums.h"
#include <cstring>
#include <stdlib.h>
#include <string>
#include <vector>

/**********************************************************
 *
 * Function readStadiumFiles
 *_________________________________________________________
 * This function reads the contents of stadiums.txt and uses
 * them to fill the given trees and the graph.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   nameSorted - StadiumTree sorted by name
 *   teamSorted - StadiumTree sorted by team name
 *   dateSorted - StadiumTree sorted by dateOpened
 *   americanTeamSorted - StadiumTree sorted by team name containing only american league stadiums
 *   nationalTeamSorted - StadiumTree sorted by team name containing only national league stadiums
 *   fieldTeamSorted - StadiumTree sorted by team name separated by type of field
 *   graph - stadiumGraph object
 *
 * POST-CONDITIONS
 * This function will fill the given trees and graph.
 ***********************************************************/
void readStadiumFiles(StadiumTree &nameSorted,
                      StadiumTree &teamSorted,
                      StadiumTree &dateSorted,
                      StadiumTree &americanTeamSorted,
                      StadiumTree &nationalTeamSorted,
                      StadiumTree &fieldTeamSorted,
                      stadiumGraph &graph)
{

    //Open stadiums.txt
    fs::path projectRoot = findProjectRoot();
    fs::path filePath = projectRoot / "src" / "stadiums.txt";
    ifstream infile(filePath);
    if (!infile.is_open())
    {
        cerr << "Error: Could not open stadiums.txt for reading\n";
        return;
    }

    string line, name, team, address, addressLine2, phoneNum, date, capStr, league, field;
    int day, month, year, capacity;
    bool og30;

    //Loop til eof
    while (getline(infile, name))
    {
        //Same format for all stadiums
        getline(infile, team);
        getline(infile, address);
        getline(infile, addressLine2);
        getline(infile, phoneNum);
        getline(infile, date);
        getline(infile, capStr);
        getline(infile, league);
        getline(infile, field);

        capacity = stoi(capStr);

        char *modifiableCDate = new char[capStr.size() + 1];
        strcpy(modifiableCDate, capStr.c_str());

        //Separate the date into month, day and year
        char *part = strtok(modifiableCDate, "/");
        month = atoi(part);
        part = strtok(NULL, "/");
        day = atoi(part);
        part = strtok(NULL, "/");
        year = atoi(part);
        delete[] part;

        //If open bracket only, has edges/is in graph/is part of og30 major league stadiums
        getline(infile, line);
        if (line == "{")
        {
            og30 = true;
        }
        //If open and closed bracket is a stadium that was added
        else
        {
            og30 = false;
        }

        //Insert stadium object into all trees
        stadium newStadium(name, team, address, addressLine2, phoneNum, month, day, year, capacity, league, field, og30);
        nameSorted.insertNode(newStadium);
        teamSorted.insertNode(newStadium);
        dateSorted.insertNode(newStadium);
        americanTeamSorted.insertNode(newStadium, 'm');
        nationalTeamSorted.insertNode(newStadium, 'n');
        fieldTeamSorted.insertNode(newStadium, 'f');

        if (!og30)
            continue;

        //If part of og30/part of the graph, insert into graph
        graph.insert(newStadium);

        //Until '}' is reached
        getline(infile, line);
        while (line != "}")
        {
            string newName;
            int distance;

            char *modifiableLine = new char[line.size() + 1];
            strcpy(modifiableLine, line.c_str());

            //Separate line into the stadium name and the edge distance
            char *halves = strtok(modifiableLine, ",");
            newName = halves;
            halves = strtok(NULL, ",");
            distance = atoi(halves);

            //Use name and distance information to add edge
            graph.insert(newStadium, stadium(newName), distance);

            getline(infile, line);
        }

        infile.close();
    }
}

/**********************************************************
 *
 * Function writeStadiumFiles
 *_________________________________________________________
 * This function uses the stadium information in nameSorted
 * and graph to fill out and write to stadiums.txt.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   nameSorted - StadiumTree sorted by name
 *   graph - stadiumGraph object
 *
 * POST-CONDITIONS
 * This function will write to stadiums.txt using a tree
 * of all stadiums and a graph of the og30 stadiums.
 ***********************************************************/
void writeStadiumFiles(StadiumTree &nameSorted, stadiumGraph &graph)
{
    //Open stadiums.txt for writing and clear its contents
    fs::path projectRoot = findProjectRoot();
    fs::path filePath = projectRoot / "src" / "stadiums.txt";
    ofstream outfile(filePath, ios::out | ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error: Could not open stadiums.txt for writing\n";
        return;
    }

    //Obtain a dynamic array of all stadiums in-order from the tree
    stadium *allStadiums = nameSorted.compileInOrder();
    int size = nameSorted.size();

    //for each stadium in allStadiums
    for (int i = 0; i < size; i++)
    {
        //Find index of current stadium in graph/check to see if exists in the graph
        int index = graph.find(allStadiums[i]);

        //Write the common info
        outfile << allStadiums->getName() << "\n"
                << allStadiums->getTeam() << "\n"
                << allStadiums->getAddress() << "\n"
                << allStadiums->getAddressLine2() << "\n"
                << allStadiums->getPhone() << "\n"
                << allStadiums->getMonth() << "/" << allStadiums->getDay() << "/" << allStadiums->getYear() << "\n"
                << allStadiums->getCapacity() << "\n"
                << allStadiums->getLeague() << "\n"
                << allStadiums->getField() << "\n"
                << "{";

        //If in graph -> og30 stadium
        if (index != -1)
        {
            //Write each edge
            graphNode *current = graph.getStadium(index)->adjacent;

            for (; current; current = current->adjacent)
                outfile << "\n"
                        << current->value.getName() << "," << current->distance;
            outfile << "\n";
        }

        //If prev if statement doesn't prock, will result in just a line with "{}" on it
        outfile << "}\n";
    }

    outfile.close();
}
