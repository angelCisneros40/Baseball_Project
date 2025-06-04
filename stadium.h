#ifndef STADIUM_H
#define STADIUM_H

#include <iostream>
#include <string>
using namespace std;

class stadium
{
public:
    /******************************
    ** CONSTRUCTORS & DESTRUCTOR **
    ******************************/
    stadium( // default constructor
        string name = "",
        string team = "",
        string address = "",
        string addressLine2 = "",
        string phoneNum = "",
        int month = 0,
        int day = 0,
        int year = 0,
        int capacity = 0,
        string league = "National",
        string field = "grass",
        bool og30 = true);
    stadium(const stadium &otherStadium); // copy constructor

    /***************
    ** ACCESSORS **
    ***************/
    string getName() const { return name; }
    string getTeam() const { return team; }
    string getAddress() const { return address; }
    string getAddressLine2() const { return addressLine2; }
    string getPhone() const { return phoneNum; }
    int getMonth() const { return dateOpened[0]; }
    int getDay() const { return dateOpened[1]; }
    int getYear() const { return dateOpened[2]; }
    int getCapacity() const { return capacity; }
    string getLeague() const { return league; }
    bool isOg() const { return og30; }
    string getField() const { return field; }

    /***************
    **  MUTATORS  **
    ***************/
    void setName(string name) { this->name = name; }
    void setTeam(string team) { this->team = team; }
    void setAddress(string address) { this->address = address; }
    void setAddressLine2(string addressLine2)
    {
        this->addressLine2 = addressLine2;
    }
    void setPhone(string phone) { this->phoneNum = phone; }
    void setDate(int month, int day, int year)
    {
        dateOpened[0] = month;
        dateOpened[1] = day;
        dateOpened[2] = year;
    }
    void setCapacity(int capacity) { this->capacity = capacity; }
    void setLeague(string league) { this->league = league; }
    void setOG(bool og30) { this->og30 = og30; }
    void setField(string field) { this->field = field; }

    stadium &operator=(const stadium &otherStadium);
    friend bool operator==(const stadium &stadium1, const stadium &stadium2)
    {
        return stadium1.name == stadium2.name;
    }
    friend bool operator!=(const stadium &stadium1, const stadium &stadium2)
    {
        return stadium1.name != stadium2.name;
    }

private:
    string name;         // CALC/OUT - Name of the stadium
    string team;         // CALC/OUT - Name of the team in the stadium
    string address;      // OUT - Address of the stadium
    string addressLine2; // OUT - City, state, country if applicable
                         // , and zip code
    string phoneNum;     // OUT - Phone number of the stadium
    int dateOpened[3];   // CALC/OUT - Date the stadium opened
                         // (0,month/1,day/2,year)
    int capacity;        // OUT - The seating capacity of the stadium
    string league;       // CALC/OUT - Which league the stadium's
                         //  team is a part of
    bool og30;           // CALC/OUT - Whether the stadium was in
                         // original 30, and thus part of graph
    string field;        // CALC/OUT - Whether the field is
                         // made of turf or grass
};

int compName(const stadium &stadium1, const stadium &stadium2);
int compTeam(const stadium &stadium1, const stadium &stadium2);
int compDate(const stadium &stadium1, const stadium &stadium2);

#endif // STADIUM_H

/****************************************************************
 * class stadium
 * This class represents a stadium object. It manages 10 attributes,
 * name, team, address, addressLine2, phoneNum, dateOpened, capaciity,
 * league, og30, and field.
 ***************************************************************/

/******************************
** CONSTRUCTORS & DESTRUCTOR **
******************************/

/****************************************************************
* stadium( // default constructor
    string name = "",
    string team = "",
    string address = "",
    string addressLine2 = "",
    string phoneNum = "",
    int month = 0,
    int day = 0,
    int year = 0,
    int capacity = 0,
    string league = "National",
    string field = "grass",
    bool og30 = true);
* Constructor; Default constructor, sets attributes to empty values
* by default, and the corresponding arguments if given
* Parameters: name (string), team (string), address (string),
*   addressLine2 (string), phoneNum (string), month (int), day (int),
*   year (int), capacity (int), league (string), field (grass),
*   og30 (bool)
* Return: none
***************************************************************/

/****************************************************************
 * stadium(const stadium& otherStadium);
 * Constructor; Copy constructor, copies attributes of otherStadium.
 * Parameters: otherStadium (const stadium&)
 * Return: none
 ***************************************************************/

/***************
** ACCESSORS **
***************/

/*******************************************************************
 * string getName()
 *
 * Accessor; This method returns the name attribute
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: name attribute
 *******************************************************************/

/*******************************************************************
 * string getTeam()
 *
 * Accessor; This method returns the team attribute
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: team attribute
 *******************************************************************/

/*******************************************************************
 * string getAddress()
 *
 * Accessor; This method returns the address attribute
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: address attribute
 *******************************************************************/

/*******************************************************************
 * string getAddressLine2()
 *
 * Accessor; This method returns the addressLine2 attribute
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: addressLine2 attribute
 *******************************************************************/

/*******************************************************************
 * string getPhone()
 *
 * Accessor; This method returns the phoneNum attribute
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: phoneNum attribute
 *******************************************************************/

/*******************************************************************
 * int getMonth()
 *
 * Accessor; This method returns the month attribute
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: month attribute
 *******************************************************************/

/*******************************************************************
 * int getDay()
 *
 * Accessor; This method returns the day attribute
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: day attribute
 *******************************************************************/

/*******************************************************************
 * int getYear()
 *
 * Accessor; This method returns the year attribute
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: year attribute
 *******************************************************************/

/*******************************************************************
 * int getCapacity()
 *
 * Accessor; This method returns the capacity attribute
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: capacity attribute
 *******************************************************************/

/*******************************************************************
 * string getLeague()
 *
 * Accessor; This method returns the league attribute
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: league attribute
 *******************************************************************/

/*******************************************************************
 * bool isOg()
 *
 * Accessor; This method returns the og30 attribute
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: og30 attribute
 *******************************************************************/

/*******************************************************************
 * string getField()
 *
 * Accessor; This method returns the field attribute
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: field attribute
 *******************************************************************/

/*******************************************************************
 * friend bool operator==(const stadium& stadium1, const stadium& stadium2)
 *
 * Accessor; This method overloads the equality operaotr, comparing
 * using the name attributes of the stadiums.
 *------------------------------------------------------------------
 * Parameter: stadium1 (const stadium&), stadium2 (const stadium&)
 *------------------------------------------------------------------
 * Return: true if equal, otherwise false
 *******************************************************************/

/*******************************************************************
 * friend bool operator!=(const stadium& stadium1, const stadium& stadium2)
 *
 * Accessor; This method overloads the inequality operaotr, comparing
 * using the name attributes of the stadiums.
 *------------------------------------------------------------------
 * Parameter: stadium1 (const stadium&), stadium2 (const stadium&)
 *------------------------------------------------------------------
 * Return: true if inequal, otherwise false
 *******************************************************************/

/***************
**  MUTATORS  **
***************/

/*******************************************************************
 * void setName(string name)
 *
 * Mutator; This method sets the name attribute to the given string
 *------------------------------------------------------------------
 * Parameter: name (string)
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/

/*******************************************************************
 * void setTeam(string team)
 *
 * Mutator; This method sets the team attribute to the given string
 *------------------------------------------------------------------
 * Parameter: team (string)
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/

/*******************************************************************
 * void setAddress(string address)
 *
 * Mutator; This method sets the address attribute to the given string
 *------------------------------------------------------------------
 * Parameter: address (string)
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/

/*******************************************************************
 * void setAddressLine2(string addressLine2)
 *
 * Mutator; This method sets the addressLine2 attribute to the given string
 *------------------------------------------------------------------
 * Parameter: addressLine2 (string)
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/

/*******************************************************************
 * void setPhone(string phone)
 *
 * Mutator; This method sets the phoneNum attribute to the given string
 *------------------------------------------------------------------
 * Parameter: phone (string)
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/

/*******************************************************************
 * void setDate(int month, int day, int year)
 *
 * Mutator; This method sets the dateOpened attribute to the given integers
 *------------------------------------------------------------------
 * Parameter: month (int), day (int), year (int)
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/

/*******************************************************************
 * void setCapacity(string capacity)
 *
 * Mutator; This method sets the capacity attribute to the given integer
 *------------------------------------------------------------------
 * Parameter: capacity (int)
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/

/*******************************************************************
 * void setLeague(string league)
 *
 * Mutator; This method sets the league attribute to the given string
 *------------------------------------------------------------------
 * Parameter: league (string)
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/

/*******************************************************************
 * void setOG(bool og30)
 *
 * Mutator; This method sets the og30 attribute to the given boolean
 *------------------------------------------------------------------
 * Parameter: og30 (bool)
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/

/*******************************************************************
 * void setField(string field)
 *
 * Mutator; This method sets the field attribute to the given string
 *------------------------------------------------------------------
 * Parameter: field (string)
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/

/*******************************************************************
 * stadium& operator= (const stadium& otherStadium)
 *
 * Mutator; overloads assignment operator, copies all attributes over.
 *------------------------------------------------------------------
 * Parameter: otherStadiium (const stadium&)
 *------------------------------------------------------------------
 * Return: this object
 *******************************************************************/
