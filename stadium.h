#ifndef STADIUM_H
#define STADIUM_H

#include <iostream>
#include <string>
using namespace std;

class stadium
{
public:
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

    // Accessors
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

    // Mutators
    void setName(string name) { this->name = name; }
    void setTeam(string team) { this->team = team; }
    void setAddress(string address) { this->address = address; }
    void setAddressLine2(string addressLine2) { this->addressLine2 = addressLine2; }
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
    friend bool operator==(const stadium &stadium1, const stadium &stadium2) { return stadium1.name == stadium2.name; }
    friend bool operator!=(const stadium &stadium1, const stadium &stadium2) { return stadium1.name != stadium2.name; }

private:
    string name;         // CALC/OUT - Name of the stadium
    string team;         // CALC/OUT - Name of the team in the stadium
    string address;      // OUT - Address of the stadium
    string addressLine2; // OUT - City, state, country if applicable, and zip code
    string phoneNum;     // OUT - Phone number of the stadium
    int dateOpened[3];   // CALC/OUT - Date the stadium opened (0,month/1,day/2,year)
    int capacity;        // OUT - The seating capacity of the stadium
    string league;       // CALC/OUT - Which league the stadium's team is a part of
    bool og30;           // CALC/OUT - Whether the stadium was in original 30, and thus part of graph
    string field;        // CALC/OUT - Whether the field is made of turf or grass
};

int compName(const stadium &stadium1, const stadium &stadium2);
int compTeam(const stadium &stadium1, const stadium &stadium2);
int compDate(const stadium &stadium1, const stadium &stadium2);

#endif // STADIUM_H
