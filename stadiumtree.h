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
    stadiumNode *root;
    char sortCriteria;
    int (*compare)(const stadium &, const stadium &);

    void insert(stadiumNode *&, stadiumNode *&, char);
    void destroySubTree(stadiumNode *);
    void deleteNode(stadium, stadiumNode *&);
    void makeDeletion(stadiumNode *&);
    void accessInOrder(stadiumNode *, stadium *&, int &) const;
    int size(stadiumNode *);
    bool equal(stadiumNode *target, stadiumNode *otherTree);
    void copyNode(stadiumNode *target, stadiumNode *otherTree);

public:
    // Constructor
    StadiumTree(stadiumNode *root = nullptr, char sortCriteria = 's');
    StadiumTree(const StadiumTree &otherTree);

    ~StadiumTree()
    {
        destroySubTree(root);
    }

    void showNode(stadiumNode *);

    // Binary Tree Operations
    void insertNode(stadium, char style = 'a');
    stadiumNode *searchNode(stadium);
    void editNode(stadium &target, stadium &newStadium);
    void remove(stadium);
    stadium *compileInOrder();
    int size();
    void showFront();

    bool operator==(const StadiumTree &otherTree);
    StadiumTree &operator=(const StadiumTree &otherTree);
};


#endif // STADIUMTREE_H
