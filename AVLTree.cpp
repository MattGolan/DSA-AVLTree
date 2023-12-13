#include "AVLTree.h"

// Node constructor.
AVLTree::Node::Node(string _NAME, int _ID)
{
    NAME = _NAME;
    ID = _ID;
    balance = 0;
    left = nullptr;
    right = nullptr;
}

// AVLTree constructor.
AVLTree::AVLTree()
{
    root = nullptr;
    markedID = -1;
    success = false;
    printIDSearch = true;
}

/*====  Private helper functions  ====*/

// Rotate left.
AVLTree::Node* AVLTree::RotateLeft(Node* _root)
{
    // Credit to Aman lecture for overall approach.
    Node* grandchild = _root->right->left;
    Node* newParent = _root->right;
    newParent->left = _root;
    _root->right = grandchild;
    return newParent;
}

// Rotate right.
AVLTree::Node* AVLTree::RotateRight(Node* _root)
{
    // Credit to Aman lecture for overall approach.
    Node* grandchild = _root->left->right;
    Node* newParent = _root->left;
    newParent->right = _root;
    _root->left = grandchild;
    return newParent;
}

// Rotates left right by calling rotate left and then rotate right.
AVLTree::Node* AVLTree::RotateLeftRight(Node* _root)
{
    // Credit to Aman lecture for overall approach.
    _root->left = RotateLeft(_root->left);
    _root = RotateRight(_root);
    return _root;
}

// Rotates right left by calling rotate right and then rotate left.
AVLTree::Node* AVLTree::RotateRightLeft(Node* _root)
{
    // Credit to Aman lecture for overall approach.
    _root->right = RotateRight(_root->right);
    _root = RotateLeft(_root);
    return _root;
}

// Calculates height for passed in node.
int AVLTree::Height(Node* _root)
{
    if (_root==nullptr)
    {
        return 0;
    }
    else
    {
        int leftHeight = Height(_root->left);
        int rightHeight = Height(_root->right);
        // Assigns max with the larger height.
        int max;
        if (leftHeight >= rightHeight)
            max = leftHeight;
        else
            max = rightHeight;
        return max + 1;
    }
}

// Removes passed in node.
AVLTree::Node* AVLTree::Remove(Node* _root)
{
    Node* temp = _root;
    success = true;
    // The removed node has no children.
    if (_root->left == nullptr && _root->right == nullptr)
    {
        _root = nullptr;
        delete temp;
        return _root;
    }
    // The removed node has only a left child.
    else if (_root->left != nullptr && _root->right == nullptr)
    {
        _root = _root->left;
        delete temp;
        return _root;
    }
    // The removed node has only a right child.
    else if (_root->left == nullptr && _root->right != nullptr)
    {
        _root = _root->right;
        delete temp;
        return _root;
    }
    // The removed node has both a left and a right child.
    else
    {
        Node* predecessor = _root->left;
        // The predecessor of removed does not have a right child.
        if (predecessor->right == nullptr) {
            predecessor->right =_root->right;
            delete _root;
            return predecessor;
        }
        // The predecessor of removed has a right child.
        else
        {
            Node* parent = predecessor;
            Node* leftChild = predecessor;
            while (predecessor->right != nullptr)
            {
                predecessor = predecessor->right;
            }
            while (parent->right != nullptr && parent->right->right != nullptr)
            {
                parent = parent->right;
            }
            parent->right = predecessor->left;
            predecessor->left = leftChild;
            predecessor->right= _root->right;
            delete _root;
            return predecessor;
        }
    }
}

/*====  Private variable accessors/modifiers  ====*/

// Returns root.
AVLTree::Node* AVLTree::GetRoot()
{
    return root;
}

// Modifies AVL Tree by updating root node.
void AVLTree::ModifyNode(Node* _root)
{
    root = _root;
}

// Returns markedID variable for use in removal.
int AVLTree::GetMarkedID()
{
    return markedID;
}

// Checks whether operation was successful, resets to false regardless.
bool AVLTree::AccessResetSuccess()
{
    bool currentsuccess = success;
    success = false;
    return currentsuccess;

}

// Stops/starts ID printing during ID search.
void AVLTree::ChangePrint()
{
    printIDSearch = !printIDSearch;
}

/*====  Accomplish tasks based on input commands  ====*/

// Inserts new node. Credit to Aman in Module 3 lecture videos for insertion strategy.
AVLTree::Node* AVLTree::InsertNode(Node* _root, string _NAME, int _ID)
{
    // Insert new node.
    if (_root == nullptr)
    {
        return new Node(_NAME, _ID);
    }
    // Compares new ID with root ID.
    if (_ID < _root->ID)
    {
        _root->left = InsertNode(_root->left, _NAME, _ID);
    }
    else
    {
        _root->right = InsertNode(_root->right, _NAME, _ID);
    }
    // Check whether the tree is balanced.
    int balance = Height(_root->left) - Height(_root->right);
    // If unbalanced, calls one of four rotate functions.
    if (balance >= 2 || balance <= -2)
    {
        if (balance == 2)
        {
            if (_root->left->balance == 1)
            {
                _root = RotateRight(_root);
            }
            else if (_root->left->balance == -1)
                _root = RotateLeftRight(_root);
        }
        else if (balance == -2)
        {
            if (_root->right->balance == 1)
                _root = RotateRightLeft(_root);
            else if (_root->right->balance == -1)
                _root = RotateLeft(_root);
        }
        // assigns current root with a balance factor.
        _root->balance = Height(_root->left) - Height(_root->right);
    }
    // Updates balance factor if already balanced.
    else
    {
        _root->balance = balance;
    }
    return _root;
}

// Removes node. Credit to psuedocode in Module 3 lecture videos for strategy.
AVLTree::Node* AVLTree::RemoveNode(Node* _root, int _ID)
{
    // Checks for nullptr.
    if (_root == nullptr)
    {
        return _root;
    }
    //Compares target ID with passed in root's ID.
    if (_ID < _root->ID)
    {
        _root->left = RemoveNode(_root->left, _ID);
    }
    else if (_ID > _root->ID)
    {
        _root->right = RemoveNode(_root->right, _ID);
    }
    // Removes node if not less or greater than target.
    else
    {
        _root = Remove(_root);
    }
    return _root;
}

// Searches IDs returns success status. Credit to Aman lecture for overall approach.
bool AVLTree::SearchID(Node* _root, int _ID, bool _success)
{
    if(_root==nullptr)
        return _success;
    else
    {
        // Searches IDs
        if (_ID < _root->ID)
        {
            _success = SearchID(_root->left, _ID, _success);
        }
        else if (_root->ID==_ID)
        {
            if (printIDSearch == true) {
                cout << _root->NAME << endl;
            }
            _success = true;
            return _success;
        }
        else if (_ID > _root->ID) {
            _success = SearchID(_root->right, _ID, _success);
        }
    }
    // Returns result.
    return _success;
}

// Searches all names for match.
void AVLTree::SearchNAME(Node* _root, string _NAME)
{
    if(_root==nullptr)
    {
        return;
    }
    else
    {
        // Searches names in preorder.
        if (_root->NAME==_NAME)
        {
            // If equal, assigns success and converts ID into proper format for display.
            success = true;
            string idString = to_string(_root->ID);
            int counter = 8 - idString.size();
            string printString;
            for (unsigned int i = 0; i < counter; i++)
            {
                printString += '0';
            }
              printString += idString;
            cout << printString << endl;
        }
        SearchNAME(_root->left, _NAME);
        SearchNAME(_root->right, _NAME);
        return;
    }
}

// Prints inorder. Credit to Aman lecture for overall approach.
string AVLTree::PrintInOrder(Node* _root, string printList)
{
    if(_root==nullptr)
        return printList;
    else
    {
        // Inorder.
        printList = PrintInOrder(_root->left, printList);
        printList += _root->NAME;
        printList += ", ";
        printList = PrintInOrder(_root->right, printList);
        return printList;
    }
}

// Prints preorder. Credit to Aman lecture for overall approach.
string AVLTree::PrintPreOrder(Node* _root, string printList)
{
    if(_root==nullptr)
        return printList;
    else
    {
        // Preorder.
        printList += _root->NAME;
        printList += ", ";
        printList = PrintPreOrder(_root->left, printList);
        printList = PrintPreOrder(_root->right, printList);
        return printList;
    }
}

// Prints postorder. Credit to Aman lecture for overall approach.
string AVLTree::PrintPostOrder(Node* _root, string printList)
{
    if(_root==nullptr)
        return printList;
    else
    {
        // Postorder.
        printList = PrintPostOrder(_root->left, printList);
        printList = PrintPostOrder(_root->right, printList);
        printList += _root->NAME;
        printList += ", ";
        return printList;
    }
}

// Prints level count.
void AVLTree::PrintLevelCount(Node* _root)
{
    cout << Height(_root) << endl;
}

// Marks appropriate node without disrupting recursion.
int AVLTree::MarkInorder(Node* _root, int n, int counter)
{
    if (_root==nullptr)
        return counter;
    else if (counter < n + 1)
    {
        counter = MarkInorder(_root->left, n, counter);
        counter++;
        if (counter == n + 1)
        {
            this->markedID = _root->ID;
        }
        counter = MarkInorder(_root->right, n, counter);
    }
    return counter;
}


