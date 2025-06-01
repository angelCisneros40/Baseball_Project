#include "stadiumtree.h"
#include "stadium.h"

// Default and argumented constructor
StadiumTree::StadiumTree(stadiumNode *root, char sortCriteria) : root(root), sortCriteria(sortCriteria)
{
    if (sortCriteria == 's')
        compare = compName;
    else if (sortCriteria == 'n')
        compare = compTeam;
    else
        compare = compDate;
}

StadiumTree::StadiumTree(char sortCriteria) : sortCriteria(sortCriteria)
{
    if (sortCriteria == 's')
        compare = compName;
    else if (sortCriteria == 'n')
        compare = compTeam;
    else
        compare = compDate;
    root = nullptr;
}

// Copy Constructor
StadiumTree::StadiumTree(const StadiumTree &otherTree)
{
    root = NULL;
    compare = otherTree.compare;
    copyNode(root, otherTree.root);
}

/**********************************************************
 *
 * Method insertNode: Class StadiumTree
 *_________________________________________________________
 * This method creates and inserts a new node into the tree
 * using the given stadium. style dictates whether is for
 * all stadiums, only national, only american, or field-
 * separated.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   val - the value of the node being inserted
 *   style - extra sorting parameter specification
 *
 * POST-CONDITIONS
 * This function will insert a node with a value of val
 ***********************************************************/
void StadiumTree::insertNode(stadium val, char style)
{
    // If only national and is american or only american and is national, don't add
    if ((style == 'n' && val.getLeague() == "American") || (style == 'm' && val.getLeague() == "National"))
        return;

    stadiumNode *newNode = new stadiumNode;

    newNode->value = val;
    newNode->left = newNode->right = NULL;

    // Insert the Node
    insert(root, newNode, style);
}

/**********************************************************
 *
 * Method insertNode: Class StadiumTree
 *_________________________________________________________
 * This method recursively calls itself until an empty
 * branch is reached and inserts newNode into that spot.
 * style dictates whether is for field-separated.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   nodePtr - The spot being checked for emptiness/adding spot
 *   newNode - The node that will be added to the new spot
 *   style - extra sorting parameter specification
 *
 * POST-CONDITIONS
 * This function will insert the given node to the correct
 * spot at the correct empty spot.
 ***********************************************************/
void StadiumTree::insert(stadiumNode *&nodePtr, stadiumNode *&newNode, char style)
{
    // Empty spot reached
    if (nodePtr == NULL)
        nodePtr = newNode;
    // If field-separated, and don't both have same field type
    else if (style == 'f' && nodePtr->value.getField() != newNode->value.getField())
    {
        // Grass come first, meaning lower value/left side of tree
        if (newNode->value.getField() == "grass")
            insert(nodePtr->left, newNode, style);
        // Turf -> move right
        else
            insert(nodePtr->right, newNode, style);
    }
    // Move to left branch
    else if (compare(nodePtr->value, newNode->value) == -1)
        insert(nodePtr->left, newNode, style);
    // Move to right branch
    else
        insert(nodePtr->right, newNode, style);
}

/**********************************************************
 *
 * Method accessInOrder: Class StadiumTree
 *_________________________________________________________
 * This method recursively calls itself, changing the values
 * of the given dynamic array to the values in the leaves
 * of the tree as it traverses the tree in-order.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   nodePtr - spot currently being outputted/checked for
 *       branches
 *   stadiumList - the dynamic array being added to
 *   index - the index of the spot in the array being changed
 *
 * POST-CONDITIONS
 * This function will change all values in the stadiumList
 * array.
 ***********************************************************/
void StadiumTree::accessInOrder(stadiumNode *nodePtr, stadium *&stadiumList, int &index) const
{
    if (nodePtr)
    {
        accessInOrder(nodePtr->left, stadiumList, index); // check left branch
        stadiumList[index] = nodePtr->value;
        index++;
        accessInOrder(nodePtr->right, stadiumList, index); // check right branch
    }
}

/**********************************************************
 *
 * Method size: Class StadiumTree
 *_________________________________________________________
 * This method recursively calls itself, counting each node
 * within the tree.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   nodePtr - the spot being checked for branches to search
 *       past.
 *
 * POST-CONDITIONS
 * This function will return the number of nodes in the tree.
 ***********************************************************/
int StadiumTree::size(stadiumNode *nodePtr)
{
    int nodes = 1; // Each node has value of 1

    // Move left to get sum of nodes in left branch paths
    if (nodePtr->left)
        nodes += size(nodePtr->left);
    // Move righ to to get sum of node in right branch paths
    if (nodePtr->right)
        nodes += size(nodePtr->right);

    // Return growing total of nodes.
    return nodes;
}

/**********************************************************
 *
 * Method equal: Class StadiumTree
 *_________________________________________________________
 * This method recursively calls itself, going through the
 * branch paths connected to the otherNode, and returning
 * false if values do not match, or if 1 has a branch that
 * the other does not. If it safely traverses both lists,
 * returns true;
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   target - the current node being checked against the other
 *       tree's current node.
 *   otherNode - the other tree's current node being checked
 *       against this tree's current node.
 *
 * POST-CONDITIONS
 * This function will return true if the branch/leaf structure
 * and values are the same, otherwise false.
 ***********************************************************/
bool StadiumTree::equal(stadiumNode *target, stadiumNode *otherNode)
{
    // If both are NULL, return true
    if (target == NULL && otherNode == NULL)
        return true;
    // If only 1 is NULL, return false
    else if (!(target && otherNode))
        return false;

    // If values don't match, return false
    if (compare(target->value, otherNode->value))
        return false;

    // If both have a left branch
    if (otherNode->left && target->left)
    {
        // If the left branches are not equal in structure and value, return false
        if (!equal(target->left, otherNode->left))
            return false;
    }
    // If only 1 has a left branch return false
    else if (!(!otherNode->left && !target->left))
        return false;

    // If both have a right branch
    if (otherNode->right && target->right)
    {
        // If the right branches are not equal in structure and value, return false
        if (!equal(target->right, otherNode->right))
            return false;
    }
    // If only 1 has a right branch return false
    else if (!(!otherNode->right && !target->right))
        return false;

    // the nodes and the branches are of equal value
    return true;
}

/**********************************************************
 *
 * Method copyNode: Class StadiumTree
 *_________________________________________________________
 * This method recursively calls itself, copying each node
 * in the otherNode into a newNode that is created and
 * inserted into a corresponding spot in this tree.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   target - the current node being created/copied into
 *   otherNode - the other tree's current node being copied
 *
 * POST-CONDITIONS
 * This function will make an identical tree structure to
 * the tree structure starting from the otherNode attached
 * to target.
 ***********************************************************/
void StadiumTree::copyNode(stadiumNode *&target, stadiumNode *otherNode)
{
    // Create a new node with value equal to otherNodes.
    target = new stadiumNode;
    target->value = otherNode->value;
    target->left = NULL;
    target->right = NULL;

    // If otherNode has a left branch, make a copy in the left branch
    if (otherNode->left)
        copyNode(target->left, otherNode->left);
    // If otherNode has a right branch, make a copy in the right branch
    if (otherNode->right)
        copyNode(target->right, otherNode->right);
}

/**********************************************************
 *
 * Method showNode: Class StadiumTree
 *_________________________________________________________
 * This method outputs the contents of the value of a given
 * node's value attribute.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   target - the current node being outputted
 *
 * POST-CONDITIONS
 * This function output the value attribute of target in a
 * user-friendly way.
 ***********************************************************/
void StadiumTree::showNode(stadiumNode *target)
{
    // If target isn't NULL
    if (target)
        cout << "Results: " << target->value.getName(); // Output target's value
    else
    {
        // If the whole tree is empty
        if (target == root)
            cout << "The tree is currently empty.";
        // If searching for a node failed
        else
            cout << "No such value could be found in the tree.";
    }
}

/**********************************************************
 *
 * Method destroySubTree: Class StadiumTree
 *_________________________________________________________
 * This method recursively calls itself, moving through
 * each branch to destroy all nodes in the tree starting
 * from nodePtr;
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   target - the current node being created/copied into
 *   otherNode - the other tree's current node being copied
 *
 * POST-CONDITIONS
 * This function will make an identical tree structure to
 * the tree structure starting from the otherNode attached
 * to target.
 ***********************************************************/

void StadiumTree::destroySubTree(stadiumNode *nodePtr)
{
    if (nodePtr->left)
        destroySubTree(nodePtr->left);
    if (nodePtr->right)
        destroySubTree(nodePtr->right);

    delete nodePtr;
}

/**********************************************************
 *
 * Method searchNode: Class StadiumTree
 *_________________________________________________________
 * This method loops through the tree starting from the
 * root, searching for a node that has the same value as val.
 * If found, returns the node address, otherwise returns NULL.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   val - value being searched for
 *
 * POST-CONDITIONS
 * This function return a pointer to the node with val as its
 * value attribute, or return NULL if not found.
 ***********************************************************/
stadiumNode *StadiumTree::searchNode(stadium val)
{
    stadiumNode *nodePtr = root;

    while (nodePtr)
    {
        if (!compare(nodePtr->value, val))
            return nodePtr;
        else if (compare(nodePtr->value, val) == -1)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;
    }
    return NULL;
}

/**********************************************************
 *
 * Method editNode: Class StadiumTree
 *_________________________________________________________
 * This method effectively edits a node by deleting the target
 * node, and reinserting a new node with different information/
 * attributes.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   target - value being searched for to replace
 *   newStadium - the stadium that is getting reinserted into the tree
 *
 * POST-CONDITIONS
 * This function will have replaced the node with target value
 * and a node with the newStadium value will be somewhere in the
 * tree.
 ***********************************************************/
void StadiumTree::editNode(stadium &target, stadium &newStadium)
{
    // If not found
    if (!compare(target, newStadium))
        return;

    // delete node once found
    stadiumNode *targetNode = searchNode(target);
    makeDeletion(targetNode);

    // Insert new stadium to make sure the tree stays sorted
    insertNode(newStadium);
}

/**********************************************************
 *
 * Method remove: Class StadiumTree
 *_________________________________________________________
 * This method deletes the node with the value of val.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   val - the value being searched for to delete
 *
 * POST-CONDITIONS
 * This function will remove the node with val as its value
 * attribute.
 ***********************************************************/
void StadiumTree::remove(stadium val)
{
    deleteNode(val, root);
}

/**********************************************************
 *
 * Method compileInOrder: Class StadiumTree
 *_________________________________________________________
 * This method traverses the tree in-order, returning a
 * dynamic array sorted accordingly of all leaves.
 *_________________________________________________________
 * PRE-CONDITIONS
 * none
 *
 * POST-CONDITIONS
 * This function returns a dynamic array containing all leaves
 * int the tree in-order.
 ***********************************************************/
stadium *StadiumTree::compileInOrder()
{
    // Create dynamic array to hold all leaf values
    int arraySize = size();
    stadium *sortedStadiums = new stadium[arraySize];

    // fill array
    int start = 0;
    accessInOrder(root, sortedStadiums, start);

    // return array
    return sortedStadiums;
}

/**********************************************************
 *
 * Method deleteNode: Class StadiumTree
 *_________________________________________________________
 * This method recursively calls itself, moving through the
 * tree until node with val as its value attribute before
 * deleting/removing that node.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   val - value being searched for
 *   nodePtr - the pointer to the node currently being checked
 *
 * POST-CONDITIONS
 * This function delete the node with val as its value attribute.
 ***********************************************************/
void StadiumTree::deleteNode(stadium val, stadiumNode *&nodePtr)
{
    // Move to left branch cuz val is less than nodePtr's value
    if (compare(val, nodePtr->value) == -1)
        deleteNode(val, nodePtr->left);
    // Move to right branch cuz val is greater than nodePtr's value
    else if (compare(val, nodePtr->value) == 1)
        deleteNode(val, nodePtr->right);
    // Delete when found
    else
        makeDeletion(nodePtr);
}

/**********************************************************
 *
 * Method makeDeletion: Class StadiumTree
 *_________________________________________________________
 * This method removes the given node according to the corresponding
 * situation, whether it's a leaf, has 1 child, or 2 children.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   nodePtr - the node to be deleted from the tree
 *
 * POST-CONDITIONS
 * This function delete nodePtr from the tree, and shift the
 * structure of the tree accordingly.
 ***********************************************************/
void StadiumTree::makeDeletion(stadiumNode *&nodePtr)
{
    stadiumNode *tempNodePtr;

    // If nodePtr empty, nothing to delete
    if (nodePtr == NULL)
        cout << "Cannot delete empty node\n";
    // If only has left child
    else if (nodePtr->right == NULL)
    {
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->left;
        delete tempNodePtr;
        cout << "Deleting employee's info.\n";
    }
    // If only has right child
    else if (nodePtr->left == NULL)
    {
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempNodePtr;
        cout << "Deleting employee's info.\n";
    }
    // If the node has two Children
    else
    {
        // Move one node to the right
        tempNodePtr = nodePtr->right;
        // Go to the end left node
        while (tempNodePtr->left)
            tempNodePtr = tempNodePtr->left;
        // Reattach the left subtree
        tempNodePtr->left = nodePtr->left;
        tempNodePtr = nodePtr;
        // Reattach the right subtree
        nodePtr = nodePtr->right;
        delete tempNodePtr;
        cout << "Deleting employee's info.\n";
    }
}

/**********************************************************
 *
 * Method size: Class StadiumTree
 *_________________________________________________________
 * This method returns the number of nodes in the tree.
 *_________________________________________________________
 * PRE-CONDITIONS
 * none
 *
 * POST-CONDITIONS
 * This function return the number of nodes in the tree.
 ***********************************************************/
int StadiumTree::size()
{
    if (root == nullptr)
    {
        return 0;
    }
    return size(root);
}
/**********************************************************
 *
 * Method operator==: Class StadiumTree
 *_________________________________________________________
 * This method overloads the equality operator, using the
 * structure and values of tree as criteria for equality
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   otherTree - the other tree being compared to this one.
 *
 * POST-CONDITIONS
 * This function return true if they're equal, otherwise false.
 ***********************************************************/
bool StadiumTree::operator==(const StadiumTree &otherTree)
{
    return equal(root, otherTree.root);
}

/**********************************************************
 *
 * Method operator=: Class StadiumTree
 *_________________________________________________________
 * This method overloads the assignment operator.
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following need a previously defined value:
 *   otherTree - the tree being copied into this tree.
 *
 * POST-CONDITIONS
 * This function returns this StadiumTree object
 ***********************************************************/
StadiumTree &StadiumTree::operator=(const StadiumTree &otherTree)
{
    // Self-assignment case
    if (this == &otherTree)
        return *this;

    // Delete the current tree if this object already has nodes in its tree.
    if (root != NULL)
        destroySubTree(root);
    root = NULL;

    // Copy otherTree
    compare = otherTree.compare;
    copyNode(root, otherTree.root);

    return *this;
}

/**********************************************************
 *
 * Method showFront: Class StadiumTree
 *_________________________________________________________
 * This method outputs the root in a user-friendly way
 *_________________________________________________________
 * PRE-CONDITIONS
 * none
 *
 * POST-CONDITIONS
 * This function outputs the root node in a user-friendly way.
 ***********************************************************/
void StadiumTree::showFront()
{
    showNode(root);
}

/**********************************************************
 *
 * Method clear: Class StadiumTree
 *_________________________________________________________
 * This method clears the entire tree by deleting all nodes
 * and resetting the root to nullptr.
 *
 * PRE-CONDITIONS
 * None
 *
 * POST-CONDITIONS
 * The tree will be empty after this function executes.
 ***********************************************************/
void StadiumTree::clear()
{
    if (root != nullptr)
    {
        destroySubTree(root);
        root = nullptr;
    }
}

stadium *StadiumTree::findStadiumByName(const std::string &name)
{
    return findNodeByNameHelper(root, name);
}

stadium *StadiumTree::findNodeByNameHelper(stadiumNode *node, const std::string &name)
{
    if (!node)
        return nullptr;
    if (node->value.getName() == name)
        return &node->value;

    stadium *left = findNodeByNameHelper(node->left, name);
    if (left)
        return left;

    return findNodeByNameHelper(node->right, name);
}