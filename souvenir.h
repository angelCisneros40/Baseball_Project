#ifndef SOUVENIR_H
#define SOUVENIR_H
#include <iostream>
#include <string>
using namespace std;

class souvenir
{
public:
    // Default constructor
    souvenir(string stadium = "",
             string item = "",
             double price = 0) : stadium(stadium),
                                 item(item),
                                 price(price) {}

    // Accessors
    string getStadiumName() { return stadium; }
    string getItemName() { return item; }
    double getPrice() { return price; }

    // Mutators
    void setStadiumName(string name) { this->stadium = name; }
    void setItemName(string name) { this->item = name; }
    void setPrice(double price) { this->price = price; }

private:
    string stadium; // OUT - name of souvenir's stadium
    string item;    // OUT - name of souvenir
    double price;   // OUT - price of souvenir
};

#endif // SOUVENIR_H
