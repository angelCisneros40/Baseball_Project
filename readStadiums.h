#ifndef READSTADIUMS_H
#define READSTADIUMS_H
#include "fileWriteTest.h"
#include "stadiumtree.h"
#include "stadiumgraph.h"

void readStadiumFiles(StadiumTree &nameSorted,
                      StadiumTree &teamSorted,
                      StadiumTree &dateSorted,
                      StadiumTree &americanTeamSorted,
                      StadiumTree &nationalTeamSorted,
                      StadiumTree &turfTeamSorted,
                      stadiumGraph &graph);

void writeStadiumFiles(StadiumTree &nameSorted, stadiumGraph &graph);

#endif // READSTADIUMS_H
