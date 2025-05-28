#ifndef STADIUM_H
#define STADIUM_H

#include <iostream>
#include <string>

class stadium
{
public:
    stadium( // default constructor
        std::string name = "",
        std::string team = "",
        std::string address = "",
        std::string addressLine2 = "",
        std::string phoneNum = "",
        int month = 0,
        int day = 0,
        int year = 0,
        int capacity = 0,
        std::string league = "National",
        std::string field = "grass",
        bool og30 = true);
    stadium(const stadium& otherStadium);                               //copy constructor


    //Accessors
    std::string getName() const {return name;}
    std::string getTeam() const {return team;}
    std::string getAddress() const {return address;}
    std::string getAddressLine2() const {return addressLine2;}
    std::string getPhone() const {return phoneNum;}
    int getMonth() const {return dateOpened[0];}
    int getDay() const {return dateOpened[1];}
    int getYear() const {return dateOpened[2];}
    int getCapacity() const {return capacity;}
    std::string getLeague() const {return league;}
    bool isOg() const {return og30;}
    std::string getField() const {return field;}

    //Mutators
    void setName(std::string name) {this->name = name;}
    void setTeam(std::string team) {this->team = team;}
    void setAddress(std::string address) {this->address = address;}
    void setAddressLine2(std::string addressLine2) {this->addressLine2 = addressLine2;}
    void setPhone(std::string phone) {this->phoneNum = phone;}
    void setDate(int month, int day, int year) {dateOpened[0] = month; dateOpened[1] = day; dateOpened[2] = year;}
    void setCapacity(int capacity) {this->capacity = capacity;}
    void setLeague(std::string league) {this->league = league;}
    void setOG(bool og30) {this->og30 = og30;}
    void setField(std::string field) {this->field = field;}


    stadium &operator=(const stadium &otherStadium);
    friend bool operator==(const stadium &stadium1, const stadium &stadium2) { return stadium1.name == stadium2.name; }
    friend bool operator!=(const stadium &stadium1, const stadium &stadium2) { return stadium1.name != stadium2.name; }

private:
    std::string name;                           //CALC/OUT - Name of the stadium
    std::string team;                           //CALC/OUT - Name of the team in the stadium
    std::string address;                        //OUT - Address of the stadium
    std::string addressLine2;                   //OUT - City, state, country if applicable, and zip code
    std::string phoneNum;                       //OUT - Phone number of the stadium
    int dateOpened[3];                          //CALC/OUT - Date the stadium opened (0,month/1,day/2,year)
    int capacity;                               //OUT - The seating capacity of the stadium
    std::string league;                         //CALC/OUT - Which league the stadium's team is a part of
    bool og30;                                  //CALC/OUT - Whether the stadium was in original 30, and thus part of graph
    std::string field;                          //CALC/OUT - Whether the field is made of turf or grass

};

int compName(const stadium &stadium1, const stadium &stadium2);
int compTeam(const stadium &stadium1, const stadium &stadium2);
int compDate(const stadium &stadium1, const stadium &stadium2);

#endif // STADIUM_H
