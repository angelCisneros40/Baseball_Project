#include "stadium.h"

// Default constructor
stadium::stadium(
    std::string name,
    std::string team,
    std::string address,
    std::string addressLine2,
    std::string phoneNum,
    int month,
    int day,
    int year,
    int capacity,
    std::string league,
    std::string field,
    bool og30) : name(name),
                 team(team),
                 address(address),
                 addressLine2(addressLine2),
                 phoneNum(phoneNum),
                 capacity(capacity),
                 league(league),
                 og30(og30),
                 field(field)
{
    dateOpened[0] = month;
    dateOpened[1] = day;
    dateOpened[2] = year;
}

// copy constructor
stadium::stadium(const stadium &otherStadium)
{
    name = otherStadium.name;
    team = otherStadium.team;
    address = otherStadium.address;
    addressLine2 = otherStadium.addressLine2;
    phoneNum = otherStadium.phoneNum;
    dateOpened[0] = otherStadium.dateOpened[0];
    dateOpened[1] = otherStadium.dateOpened[1];
    dateOpened[2] = otherStadium.dateOpened[2];
    capacity = otherStadium.capacity;
    league = otherStadium.league;
    og30 = otherStadium.og30;
    field = otherStadium.field;
}

// Assignment operator
stadium &stadium::operator=(const stadium &otherStadium)
{
    name = otherStadium.name;
    team = otherStadium.team;
    address = otherStadium.address;
    addressLine2 = otherStadium.addressLine2;
    phoneNum = otherStadium.phoneNum;
    dateOpened[0] = otherStadium.dateOpened[0];
    dateOpened[1] = otherStadium.dateOpened[1];
    dateOpened[2] = otherStadium.dateOpened[2];
    capacity = otherStadium.capacity;
    league = otherStadium.league;
    og30 = otherStadium.og30;
    field = otherStadium.field;

    return *this;
}

/**********************************************************
 *
 * Function compName: Class Stadium
 *_________________________________________________________
 * This function compares two stadium objects based on the
 * name of the stadium, -1 meaning stadium1.name is before
 * stadium2.name in alphabet, 0 meaning they're equal, and 1
 * meaning stadium1.name is after stadium2.name in alphabet.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   stadium1 - the 1st stadium being compared
 *   stadium2 - the 2nd stadium being compared
 *
 * POST-CONDITIONS
 * This function returns -1 if stadium1.name < stadium2.name
 * 0 if stadium1.name == stadium2.name, and 1 if
 * stadium1.name > stadium2.name.
 ***********************************************************/
int compName(const stadium &stadium1, const stadium &stadium2)
{
    if (stadium1.getName() == stadium2.getName())
        return 0;
    else if (stadium1.getName() > stadium2.getName())
        return 1;
    else
        return -1;
}

/**********************************************************
 *
 * Function compTeam: Class Stadium
 *_________________________________________________________
 * This function compares two stadium objects based on the
 * team of the stadium, -1 meaning stadium1.team is before
 * stadium2.team in alphabet, 0 meaning they're equal, and 1
 * meaning stadium1.team is after stadium2.team in alphabet.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   stadium1 - the 1st stadium being compared
 *   stadium2 - the 2nd stadium being compared
 *
 * POST-CONDITIONS
 * This function returns -1 if stadium1.team < stadium2.team
 * 0 if stadium1.team == stadium2.team, and 1 if
 * stadium1.team > stadium2.team.
 ***********************************************************/
int compTeam(const stadium &stadium1, const stadium &stadium2)
{
    if (stadium1.getTeam() == stadium2.getTeam())
        return 0;
    else if (stadium1.getTeam() > stadium2.getTeam())
        return 1;
    else
        return -1;
}

/**********************************************************
 *
 * Function compDate: Class Stadium
 *_________________________________________________________
 * This function compares two stadium objects based on the
 * opening date of the stadium, -1 meaning stadium1.date is
 * before stadium2.date, 0 meaning they're equal, and 1
 * meaning stadium1.date is after stadium2.date.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   stadium1 - the 1st stadium being compared
 *   stadium2 - the 2nd stadium being compared
 *
 * POST-CONDITIONS
 * This function returns -1 if stadium1.date < stadium2.date
 * 0 if stadium1.date == stadium2.date, and 1 if
 * stadium1.date > stadium2.date.
 ***********************************************************/
int compDate(const stadium &stadium1, const stadium &stadium2)
{
    // stadium1 opened years(s) after stadium2
    if (stadium1.getYear() > stadium2.getYear())
        return 1;
    // stadium2 opened years(s) after stadium1
    else if (stadium1.getYear() < stadium2.getYear())
        return -1;

    // stadium1 opened month(s) after stadium2
    if (stadium1.getMonth() > stadium2.getMonth())
        return 1;
    // stadium2 opened month(s) after stadium1
    else if (stadium1.getMonth() < stadium2.getMonth())
        return -1;

    // stadium1 opened day(s) after stadium2
    if (stadium1.getDay() > stadium2.getDay())
        return 1;
    // stadium2 opened day(s) after stadium1
    else if (stadium1.getDay() < stadium2.getDay())
        return -1;

    // They are the same
    return 0;
}
