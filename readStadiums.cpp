#include "readStadiums.h"
#include <cstring>
#include <stdlib.h>
#include <string>
#include <vector>

void readStadiumFiles(StadiumTree &nameSorted,
                      StadiumTree &teamSorted,
                      StadiumTree &dateSorted,
                      StadiumTree &americanTeamSorted,
                      StadiumTree &nationalTeamSorted,
                      StadiumTree &fieldTeamSorted,
                      stadiumGraph &graph)
{

    fs::path projectRoot = findProjectRoot();
    fs::path filePath = projectRoot / "src" / "stadiums.txt";
    ifstream infile(filePath);
    if (!infile.is_open())
    {
        cerr << "Error: Could not open stadiums.txt for reading\n";
        return;
    }

    std::string line, name, team, address, addressLine2, phoneNum, date, capStr, league, field;
    int day, month, year, capacity;
    bool og30;

    while (std::getline(infile, name))
    {
        std::getline(infile, team);
        std::getline(infile, address);
        std::getline(infile, addressLine2);
        std::getline(infile, phoneNum);
        std::getline(infile, date);
        std::getline(infile, capStr);
        std::getline(infile, league);
        std::getline(infile, field);

        capacity = std::stoi(capStr);

        char *modifiableCDate = new char[capStr.size() + 1];
        std::strcpy(modifiableCDate, capStr.c_str());

        char *part = strtok(modifiableCDate, "/");
        month = atoi(part);
        part = strtok(NULL, "/");
        day = atoi(part);
        part = strtok(NULL, "/");
        year = atoi(part);
        delete[] part;

        std::getline(infile, line);
        if (line == "{")
        {
            og30 = true;
        }
        else
        {
            og30 = false;
        }

        stadium newStadium(name, team, address, addressLine2, phoneNum, month, day, year, capacity, league, field, og30);
        nameSorted.insertNode(newStadium);
        teamSorted.insertNode(newStadium);
        dateSorted.insertNode(newStadium);
        americanTeamSorted.insertNode(newStadium, 'm');
        nationalTeamSorted.insertNode(newStadium, 'n');
        fieldTeamSorted.insertNode(newStadium, 'f');

        if (!og30)
            continue;

        graph.insert(newStadium);

        std::getline(infile, line);
        while (line != "}")
        {
            std::string newName;
            int distance;

            char *modifiableLine = new char[line.size() + 1];
            std::strcpy(modifiableLine, line.c_str());

            char *halves = strtok(modifiableLine, ",");
            newName = halves;
            halves = strtok(NULL, ",");
            distance = atoi(halves);

            graph.insert(newStadium, stadium(newName), distance);

            std::getline(infile, line);
        }

        infile.close();
    }
}

void writeStadiumFiles(StadiumTree &nameSorted, stadiumGraph &graph)
{
    fs::path projectRoot = findProjectRoot();
    fs::path filePath = projectRoot / "src" / "stadiums.txt";
    ofstream outfile(filePath, ios::out | ios::trunc);
    if (!outfile.is_open())
    {
        cerr << "Error: Could not open stadiums.txt for writing\n";
        return;
    }

    stadium *allStadiums = nameSorted.compileInOrder();
    int size = nameSorted.size();

    for (int i = 0; i < size; i++)
    {
        int index = graph.find(allStadiums[i]);

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

        if (index != -1)
        {
            graphNode *current = graph.getStadium(index)->adjacent;

            for (; current; current = current->adjacent)
                outfile << "\n"
                        << current->value.getName() << "," << current->distance;
            outfile << "\n";
        }

        outfile << "}\n";
    }

    outfile.close();
}
