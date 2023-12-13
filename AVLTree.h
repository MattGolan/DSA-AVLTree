#ifndef SRC_AVLTREE_H
#define SRC_AVLTREE_H

#include<string>
#include<vector>
#include<iostream>
using namespace std;

class AVLTree {

    /*====  Nested Node structure  ====*/
    struct Node
    {
        // Node variables.
        // All caps used to conform with assignment instructions, otherwise camel case is use.
        string NAME;
        int ID;
        int balance;
        Node* left;
        Node* right;

        // Node constructor.
        Node(string _NAME, int _ID);
    };

    /*====  Private AVLTree variables  ====*/

    Node* root;
    int markedID;
    bool success;
    bool printIDSearch;

    /*====  Private 'helper' functions  ====*/

    // Rotations
    Node* RotateLeft(Node* node);
    Node* RotateRight(Node* node);
    Node* RotateLeftRight(Node* node);
    Node* RotateRightLeft(Node* node);
    // Calculates height.
    int Height(Node* node);
    // Called by RemoveNode(), removes node.
    Node* Remove(Node* node);

    /*====  Public functions  ====*/

public:
    // Tree constructor.
    AVLTree();

    /*====  Access and modify private variables  ====*/

    // Accesses or modifies root pointer.
    Node* GetRoot();
    void ModifyNode(Node* _root);
    // Retrieves marked ID for removal.
    int GetMarkedID();
    // Accesses or modifies bool variables so branches can be entered during certain recursive calls.
    bool AccessResetSuccess();
    void ChangePrint();

    /*====  Accomplish tasks based on input commands  ====*/

    // "insert"
    Node* InsertNode(Node* root, string _NAME, int _ID);
    // "remove"
    Node* RemoveNode(Node* root, int _ID);
    // "search..."
    bool SearchID(Node* root, int _ID, bool _success);
    void SearchNAME(Node* root, string _NAME);
    // "print..."
    string PrintInOrder(Node* root, string printList);
    string PrintPreOrder(Node* root, string printList);
    string PrintPostOrder(Node* root, string printList);
    void PrintLevelCount(Node* root);
    //"removeInorder", marks node for removal.
    int MarkInorder(Node* root, int n, int counter);
};

#endif //SRC_AVLTREE_H
