#ifndef STADIUM_H
#define STADIUM_H

#include <iostream>
#include <string>

class stadium
{
public:

    stadium(                                                            //default constructor
        std::string name = "",
        std::string team = "",
        std::string address = "",
        std::string city = "",
        std::string state = "",
        int zip = 0,
        std::string phoneNum = "",
        int month = 0,
        int day = 0,
        int year = 0,
        int capacity = 0,
        std::string league = "National",
        bool og30 = true);
    stadium(const stadium& otherStadium);                               //copy constructor


    //Accessors
    std::string getName() {return name;}
    std::string getTeam() {return team;}
    std::string getAddress() {return address;}
    std::string getCity() {return city;}
    std::string getState() {return state;}
    int getZip() {return zip;}
    std::string getPhone() {return phoneNum;}
    int getMonth() {return dateOpened[0];}
    int getDay() {return dateOpened[1];}
    int getYear() {return dateOpened[2];}
    int getCapacity() {return capacity;}
    std::string getLeague() {return league;}
    bool isOg() {return og30;}

    //Mutators
    void setName(std::string name) {this->name = name;}
    void setTeam(std::string team) {this->team = team;}
    void setAddress(std::string address) {this->address = address;}
    void setCity(std::string city) {this->city = city;}
    void setState(std::string state) {this->state = state;}
    void setZip(int zip) {this->zip = zip;}
    void setPhone(std::string phone) {this->phoneNum = phone;}
    void setDate(int month, int day, int year) {dateOpened[0] = month; dateOpened[1] = day; dateOpened[2] = year;}
    void setCapacity(int capacity) {this->capacity = capacity;}
    void setLeague(std::string league) {this->league = league;}
    void setOG(bool og30) {this->og30 = og30;}


    //Relational functions
    friend int compName(const stadium& stadium1, const stadium& stadium2);
    friend int compTeam(const stadium& stadium1, const stadium& stadium2);
    friend int compDate(const stadium& stadium1, const stadium& stadium2);

    stadium& operator= (const stadium& otherStadium);
    friend bool operator== (const stadium& stadium1, const stadium& stadium2) {return stadium1.name == stadium2.name;}
    friend bool operator!= (const stadium& stadium1, const stadium& stadium2) {return stadium1.name != stadium2.name;}

private:
    std::string name;                           //CALC/OUT - Name of the stadium
    std::string team;                           //CALC/OUT - Name of the team in the stadium
    std::string address;                        //OUT - Address of the stadium
    std::string city;                           //OUT - City the stadium is in
    std::string state;                          //OUT - The state the stadium is in
    int zip;                                    //OUT - Zip code of the stadium
    std::string phoneNum;                       //OUT - Phone number of the stadium
    int dateOpened[3];                          //CALC/OUT - Date the stadium opened (0,month/1,day/2,year)
    int capacity;                               //OUT - The seating capacity of the stadium
    std::string league;                         //CALC/OUT - Which league the stadium's team is a part of
    bool og30;                                  //CALC/OUT - Whether the stadium was in original 30, and thus part of graph

};

//Default constructor
stadium::stadium(
    std::string name,
    std::string team,
    std::string address,
    std::string city,
    std::string state,
    int zip,
    std::string phoneNum,
    int month,
    int day,
    int year,
    int capacity,
    std::string league,
    bool og30):
    name(name), team(team), address(address), city(city), state(state), zip(zip), phoneNum(phoneNum), capacity(capacity), league(league), og30(og30)
{
    dateOpened[0] = month;
    dateOpened[1] = day;
    dateOpened[2] = year;
}

//copy constructor
stadium::stadium(const stadium& otherStadium) {
    name = otherStadium.name;
    team = otherStadium.team;
    address = otherStadium.address;
    city = otherStadium.city;
    state = otherStadium.state;
    zip = otherStadium.zip;
    phoneNum = otherStadium.phoneNum;
    dateOpened[0] = otherStadium.dateOpened[0];
    dateOpened[1] = otherStadium.dateOpened[1];
    dateOpened[2] = otherStadium.dateOpened[2];
    capacity = otherStadium.capacity;
    league = otherStadium.league;
    og30 = otherStadium.og30;
}

/**********************************************************
*
* Friend function compName: Class Stadium
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
int compName(const stadium& stadium1, const stadium& stadium2) {
    if (stadium1.name == stadium2.name)
        return 0;
    else if (stadium1.name > stadium2.name)
        return 1;
    else
        return -1;
}

/**********************************************************
*
* Friend function compTeam: Class Stadium
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
int compTeam(const stadium& stadium1, const stadium& stadium2) {
    if (stadium1.team == stadium2.team)
        return 0;
    else if (stadium1.team > stadium2.team)
        return 1;
    else
        return -1;
}

/**********************************************************
*
* Friend function compDate: Class Stadium
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
int compDate(const stadium& stadium1, const stadium& stadium2) {
    //stadium1 opened years(s) after stadium2
    if (stadium1.dateOpened[2] > stadium2.dateOpened[2])
        return 1;
    //stadium2 opened years(s) after stadium1
    else if (stadium1.dateOpened[2] < stadium2.dateOpened[2])
        return -1;

    //stadium1 opened month(s) after stadium2
    if (stadium1.dateOpened[0] > stadium2.dateOpened[0])
        return 1;
    //stadium2 opened month(s) after stadium1
    else if (stadium1.dateOpened[0] < stadium2.dateOpened[0])
        return -1;

    //stadium1 opened day(s) after stadium2
    if (stadium1.dateOpened[1] > stadium2.dateOpened[1])
        return 1;
    //stadium2 opened day(s) after stadium1
    else if (stadium1.dateOpened[1] < stadium2.dateOpened[1])
        return -1;

    //They are the same
    return 0;
}

stadium& stadium::operator= (const stadium& otherStadium) {
    name = otherStadium.name;
    team = otherStadium.team;
    address = otherStadium.address;
    city = otherStadium.city;
    state = otherStadium.state;
    zip = otherStadium.zip;
    phoneNum = otherStadium.phoneNum;
    dateOpened[0] = otherStadium.dateOpened[0];
    dateOpened[1] = otherStadium.dateOpened[1];
    dateOpened[2] = otherStadium.dateOpened[2];
    capacity = otherStadium.capacity;
    league = otherStadium.league;
    og30 = otherStadium.og30;

    return *this;
}

#endif // STADIUM_H
