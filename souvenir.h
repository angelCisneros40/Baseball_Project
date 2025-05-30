#ifndef SOUVENIR_H
#define SOUVENIR_H

#include <iostream>
#include <string>

class souvenir
{
public:
    // Default constructor
    souvenir(std::string name = "", double price = 0) : name(name), price(price) {}

    // Accessors
    std::string getName() { return name; }
    double getPrice() { return price; }

    // Mutators
    void setName(std::string name) { this->name = name; }
    void setPrice(double price) { this->price = price; }

    // Assignment operator
    souvenir &operator=(const souvenir &otherSouvenir);

    // Relational operators
    friend bool operator==(const souvenir &s1, const souvenir &s2) { return (s1.name == s2.name && s1.price == s2.price); }
    friend bool operator!=(const souvenir &s1, const souvenir &s2) { return !(s1.name == s2.name && s1.price == s2.price); }

private:
    std::string name; // OUT - name of souvenir
    double price;     // OUT - price of souvenir
};

struct souvenirNode
{
    souvenir value;     // OUT - value/souvenir of the node
    souvenirNode *link; // CALC/OUT - link to next node of linked list
};

class souvenirList
{
public:
    // Constructors and Destructor
    souvenirList(souvenirNode *head = nullptr) : head(head) {} // Default constructor
    souvenirList(const souvenirList &otherList);               // Copy Constructor
    ~souvenirList();                                           // Destructor

    // Accessors
    souvenirNode *getHead() { return head; }
    souvenirNode *findSouvenir(souvenir &val);

    // Mutators
    void insertHead(souvenir &val);
    void insertEnd(souvenir &val);
    bool deleteNode(souvenir &val);
    bool editNode(souvenir &target, souvenir &newSouvenir);

private:
    souvenirNode *head; // CALC/OUT - The head pointer of the linked list
};

/****************************************************************
 * Class souvenir
 * This class represents a souvenir object. It manages 2 attributes,
 * name and price.
 ***************************************************************/

/**********************************************************
 *
 * Method operator=: Class souvenir
 *_________________________________________________________
 * This method overloads the assignment operator.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   otherSouvenir - the other souvenir being copied.
 *
 * POST-CONDITIONS
 * This function assigns attributes of otherSouvenir to this one.
 ***********************************************************/
souvenir &souvenir::operator=(const souvenir &otherSouvenir)
{
    name = otherSouvenir.name;
    price = otherSouvenir.price;

    return *this;
}

/****************************************************************
 * struct souvenirNode
 * This struct holds nodes for the souvenir linked list, and manages
 * 2 attributes, name and link.
 ***************************************************************/

/****************************************************************
 * Class souvenirList
 * This class represents a souvenir linked list. It manages 1 attribute:
 * head.
 ***************************************************************/

/**********************************************************
 *
 * Method insertHead: Class souvenirList
 *_________________________________________________________
 * This method inserts a node with the given val at the head
 * of the linked list.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   val - the souvenir object being inserted into the linked list.
 *
 * POST-CONDITIONS
 * This function inserts a new node at the front of the list.
 ***********************************************************/
void souvenirList::insertHead(souvenir &val)
{
    if (!findSouvenir(val))
        return;

    souvenirNode *newNode = new souvenirNode;
    newNode->value = val;
    newNode->link = nullptr;

    if (head)
    {
        newNode->link = head->link;
        head = newNode;
        newNode = nullptr;
    }
    else
        head = newNode;
}

/**********************************************************
 *
 * Method insertEnd: Class souvenirList
 *_________________________________________________________
 * This method inserts a node with the given val at the end
 * of the linked list.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   val - the souvenir object being inserted into the linked list.
 *
 * POST-CONDITIONS
 * This function inserts a new node at the end of the list.
 ***********************************************************/
void souvenirList::insertEnd(souvenir &val)
{
    if (!findSouvenir(val))
        return;

    souvenirNode *newNode = new souvenirNode;
    newNode->value = val;
    newNode->value = nullptr;

    if (head)
    {
        souvenirNode *end = nullptr;
        for (end = head; end->link != nullptr; end = end->link)
            ;
        end->link = newNode;
    }
    else
        head = newNode;
}

/**********************************************************
 *
 * Method findSouvenir: Class souvenirList
 *_________________________________________________________
 * This method finds the node with the given value and
 * returns a pointer to that node.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   val - the souvenir object being searched for.
 *
 * POST-CONDITIONS
 * This function returns a pointer to the node with the given value,
 * or nullptr if it isn't found.
 ***********************************************************/
souvenirNode *souvenirList::findSouvenir(souvenir &val)
{
    souvenirNode *spot = nullptr;
    for (spot = head; spot->value != val; spot = spot->link)
        ;

    return spot;
}

/**********************************************************
 *
 * Method deleteNode: Class souvenirList
 *_________________________________________________________
 * This method deletes a node with the given val from the
 * linked list.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   val - the souvenir object being deleted from the linked list.
 *
 * POST-CONDITIONS
 * This function removes a node from the list.
 ***********************************************************/
bool souvenirList::deleteNode(souvenir &val)
{
    if (head->value == val)
    {
        souvenirNode *placehold = head->link;
        delete head;
        head = placehold;
        placehold = nullptr;
        return true;
    }
    else
    {
        souvenirNode *spot = nullptr;
        for (spot = head; spot->link && spot->link->value != val; spot = spot->link)
            ;

        if (!spot->link)
            return false;

        souvenirNode *placehold = spot->link;
        spot->link = spot->link->link;
        delete placehold;
        return true;
    }
}

/**********************************************************
 *
 * Method editNode: Class souvenirList
 *_________________________________________________________
 * This method finds the node with the target value
 * and edits its contents to those of newSouvenir.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   target - the value being searched for to edit in the linked list.
 *   newSouvenir - The souvenir whose contents are being used to
 *       set the target node.
 *
 * POST-CONDITIONS
 * This function will change the attributes of the target node.
 ***********************************************************/
bool souvenirList::editNode(souvenir &target, souvenir &newSouvenir)
{
    souvenirNode *spot = nullptr;
    for (spot = head; spot && spot->value != target; spot = spot->link)
        ;

    if (spot)
    {
        spot->value = newSouvenir.value;
        return true;
    }
    else
        return false;
}

#endif // SOUVENIR_H
