#ifndef STADIUMTREE_H
#define STADIUMTREE_H

#include <iostream>
#include <iomanip>
#include "stadium.h"

using namespace std;

struct stadiumNode
{
    stadium value;
    stadiumNode *left;
    stadiumNode *right;
};

class StadiumTree
{
private:
    stadiumNode *root;                                              //CALC/OUT - root of stadium binary search tree
    char sortCriteria;                                              //CALC - char representing how tree is to be sorted
    int (*compare)(const stadium &, const stadium &);               //CALC - function type holding the style of comparing stadiums

    /***************
    ** ACCESSORS **
    ***************/
    void accessInOrder(stadiumNode *, stadium *&, int &) const;
    int size(stadiumNode *);
    bool equal(stadiumNode *target, stadiumNode *otherTree);

    /***************
    **  MUTATORS  **
    ***************/
    void insert(stadiumNode *&, stadiumNode *&, char);
    void destroySubTree(stadiumNode *);
    void deleteNode(stadium, stadiumNode *&);
    void makeDeletion(stadiumNode *&);
    void copyNode(stadiumNode *&target, stadiumNode *otherNode);

public:
    /******************************
    ** CONSTRUCTORS & DESTRUCTOR **
    ******************************/
    StadiumTree(stadiumNode *root = nullptr, char sortCriteria = 's');
    StadiumTree(const StadiumTree &otherTree);
    StadiumTree(char sortCriteria);

    ~StadiumTree()
    {
        destroySubTree(root);
    }

    /***************
    ** ACCESSORS **
    ***************/
    void showNode(stadiumNode *);
    stadiumNode *searchNode(stadium);
    int size();
    void showFront();
    stadium *findStadiumByName(const std::string &name);
    stadium *findNodeByNameHelper(stadiumNode *node, const std::string &name);
    bool operator==(const StadiumTree &otherTree);


    /***************
    **  MUTATORS  **
    ***************/
    void insertNode(stadium, char style = 'a');
    void editNode(stadium &target, stadium &newStadium);
    void remove(stadium);
    stadium *compileInOrder();
    StadiumTree &operator=(const StadiumTree &otherTree);
    void clear();


};

#endif // STADIUMTREE_H

/****************************************************************
* struct stadiumNode
* This struct represents node of stadium binary search tree
* with 3 attributes, value, left, and right.
***************************************************************/

/****************************************************************
* class StadiumTree
* This class represents a StadiumTree object. It manages 3 attributes,
* root, sortCriteria, and compare.
***************************************************************/

/******************************
** CONSTRUCTORS & DESTRUCTOR **
******************************/

/****************************************************************
* stadiumTree(stadiumNode* root, char sortCriteria);
* Constructor; Default constructor, setting the root and sortCriteria
* attributes to their default values or their given values if present,
* and then using the sortCriteria, assign the compare attribute.
* Parameters: root (stadiumNode*), sortCriteria (char)
* Return: none
***************************************************************/

/****************************************************************
* stadiumTree(const stadiumTree& otherTree);
* Constructor; Copy constructor, copies attributes and each
* element of the tree.
* Parameters: otherTree (const stadiumTree&)
* Return: none
***************************************************************/

/****************************************************************
* stadiumTree(char sortCriteria);
* Constructor; Initializes root to nullptr and, initializing
* sortCriteria using given char, and using it to set compare.
* Parameters: sortCriteria (char)
* Return: none
***************************************************************/

/****************************************************************
* ~stadiumTree();
* Destructor; Deletes the dynamic memory set aside for the tree
* starting at root.
* Parameters: none
* Return: none
***************************************************************/

/***************
** ACCESSORS **
***************/

/*******************************************************************
* void accessInOrder(stadiumNode *nodePtr, stadium *&stadiumList, int &index)
*
* Accessor; This traverses the tree recursively in-order, adding
* stadiums to stadiumList as it traverses.
*------------------------------------------------------------------
* Parameter: nodePtr (stadiumNode*), stadiumList (stadium*&) index (int&)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* int size(stadiumNode* nodePtr)
*
* Accessor; recursively traverses all nodes and counts them, returning
* number of nodes.
*------------------------------------------------------------------
* Parameter: nodePtr (stadiumNode*)
*------------------------------------------------------------------
* Return: number of nodes in the tree.
*******************************************************************/

/*******************************************************************
* bool equal(stadiumNode *target, stadiumNode *otherTree)
*
* Accessor; This recursively checks every branch of each tree, making
* sure that they have the same tree structure and node values. If
* all the same, return true, otherwise false.
*------------------------------------------------------------------
* Parameter: target (stadiumNode*), otherTree (stadiumNode*)
*------------------------------------------------------------------
* Return: true if equal, otherwise false
*******************************************************************/

/*******************************************************************
* void showNode(stadiumNode* target)
*
* Accessor; This method outputs the info of the given node.
*------------------------------------------------------------------
* Parameter: target (stadiumNode*)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* stadiumNode* searchNode(stadium val)
*
* Accessor; This searches through tree for node with given val, if
* found returning pointer to it, otherwise returning NULL.
*------------------------------------------------------------------
* Parameter: val (stadium)
*------------------------------------------------------------------
* Return: pointer to node with given val, or NULL
*******************************************************************/

/*******************************************************************
* int size()
*
* Accessor; Returns number of nodes in the tree
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void showFront()
*
* Accessor; This method outputs the info of the root node.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* stadium* findStadiumByName(const std::string& name)
*
* Accessor; This method searches for node with stadium with given name
* and returns a pointer to the stadium of that node.
*------------------------------------------------------------------
* Parameter: name (const std::string&)
*------------------------------------------------------------------
* Return: pointer to the stadium or nullptr if not found.
*******************************************************************/

/*******************************************************************
* stadium* findStadiumByNameHelper(stadiumNode* node, const std::string& name)
*
* Accessor; This method searches recursively through tree for node
* with stadium with given name, and returns pointer to that stadium.
*------------------------------------------------------------------
* Parameter: node (stadiumNode*), name (const std::string&)
*------------------------------------------------------------------
* Return: pointer to the stadium or nullptr if not found.
*******************************************************************/

/*******************************************************************
* bool operator==(const StadiumTree& otherTree)
*
* Accessor; This method overloads equality operator, returning
* true if same structure and same values
*------------------------------------------------------------------
* Parameter: otherTree (const StadiumTree&)
*------------------------------------------------------------------
* Return: true if all equal, otherwise false
*******************************************************************/

/***************
**  MUTATORS  **
***************/

/*******************************************************************
* void insert(stadiumNode*& nodePtr, stadiumNode*& newNode, char style)
*
* Mutator; This recursively searches through the tree for the
* appropriate spot to insert newNode into the tree according to the
* given style.
*------------------------------------------------------------------
* Parameter: nodePtr (stadiumNode*), newNode (stadiumNode*&), style (char)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void destroySubTree(stadiumNode* nodePtr)
*
* Mutator; This method recursively traverses through all nodes starting
* from nodePtr and deleting all nodes that branch from nodePtr,
* including the node pointed at by nodePtr.
*------------------------------------------------------------------
* Parameter: nodePtr (stadiumNode*)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void deleteNode(stadium val, stadiumNode*& nodePtr)
*
* Mutator; This method recursively searches through the tree until
* node with given val is found, and deletes that node.
*------------------------------------------------------------------
* Parameter: val (stadium), nodePtr (stadiumNode*&)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void makeDeletion(stadiumNode*& nodePtr)
*
* Mutator; This method removes the given node according to the
* circumstances, applying the proper method depending on if the
* node is a node, has 1 child, or has 2 children.
*------------------------------------------------------------------
* Parameter: nodePtr (stadiumNode*&)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void copyNode(stadiumNode*& target, stadiumNode* otherNode)
*
* Mutator; This method recursively calls itself, traversing the
* otherNode root's tree, creating a corresponding equivalent node
* in this tree.
*------------------------------------------------------------------
* Parameter: target (stadiumNode*&), otherNode (stadiumNode*)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void insertNode(stadium val, char style)
*
* Mutator; This method inserts a node with the given val into the
* tree according to the given style.
*------------------------------------------------------------------
* Parameter: val (stadium), style (char)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void editNode(stadium& target, stadium& newStadium)
*
* Mutator; This method effectively edits a node by finding the node
* with the given target value, deleting it, and then inserting the
* newStadium in order to replace it, since editing the node could
* potentially affect how it would be sorted in the tree.
*------------------------------------------------------------------
* Parameter: target (stadium&), newStadium (stadium&)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void remove(stadium val)
*
* Mutator; This method deletes the node with the given val from the
* tree.
*------------------------------------------------------------------
* Parameter: val (stadium)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* stadium* compileInOrder()
*
* Mutator; This method returns a linked list containing the nodes
* of the tree listed in-order.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* StadiumTree& operator=(const StadiumTree& otherTree)
*
* Mutator; This method overloads the assignment operator, copying
* all nodes in otherTree.
*------------------------------------------------------------------
* Parameter: otherTree (const StadiumTree&)
*------------------------------------------------------------------
* Return: this object
*******************************************************************/

/*******************************************************************
* void clear()
*
* Mutator; This method clears the entire tree by deleting all nodes
* of the tree, resetting root to nullptr.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: none
*******************************************************************/
