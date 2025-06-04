#ifndef READSTADIUMS_H
#define READSTADIUMS_H
#include "fileWriteTest.h"
#include "stadiumtree.h"
#include "stadiumgraph.h"
using namespace std;

void readStadiumFiles(StadiumTree &nameSorted,
                      StadiumTree &teamSorted,
                      StadiumTree &dateSorted,
                      StadiumTree &americanTeamSorted,
                      StadiumTree &nationalTeamSorted,
                      StadiumTree &turfTeamSorted,
                      stadiumGraph &graph);

void writeStadiumFiles(StadiumTree &nameSorted, stadiumGraph &graph);

#endif // READSTADIUMS_H

/*******************************************************************
* void readStadiumFiles(StadiumTree &nameSorted,
                      StadiumTree &teamSorted,
                      StadiumTree &dateSorted,
                      StadiumTree &americanTeamSorted,
                      StadiumTree &nationalTeamSorted,
                      StadiumTree &turfTeamSorted,
                      stadiumGraph &graph)
*
* This function reads the information from stadiums.txt, and accordingly
* fills the given trees and the graph.
*------------------------------------------------------------------
* Parameter: nameSorted (StadiumTree&), teamSorted (StadiumTree&),
*   dateSorted (StadiumTree&), americanTeamSorted (StadiumTree&),
*   nationalTeamSorted (StadiumTree&), turfTeamSorted (StadiumTree&)
*   graph (stadiumGraph&)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
 * void writeStadiumFiles(StadiumTree &nameSorted, stadiumGraph &graph)
 *
 * This function writes stadium information to stadiums.txt using
 * the informatin in nameSorted and graph.
 *------------------------------------------------------------------
 * Parameter: nameSorted (StadiumTree&), graph (stadiumGraph&)
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/
