#include <iostream>
#include <string>
#include <sstream>
#include "AVLTree.h"
using namespace std;

// Function declarations.
bool ValidID(string idString);
bool ValidName(string NAME);

int main()
{
    // Converts number of commands into an integer.
    AVLTree tree = AVLTree();
    string numCommandsString;
    getline(cin, numCommandsString);
    int numCommands = stoi(numCommandsString);

    // Repeats loop for the number of times indicated.
    for (unsigned int i = 1; i <=numCommands; i++)
    {
        // Credit to Professor Fox for overall strategy.
        // Read command line from input and convert into data stream.
        string commandLine;
        getline(cin, commandLine);
        istringstream stream(commandLine);
        // Get command prompt from data stream.
        string commandPrompt;
        getline(stream, commandPrompt, ' ');

        // Insert branch.
        if (commandPrompt == "insert")
        {
            // Variable declarations. All caps used for NAME and ID to conform with instructions.
            string discarded;
            string NAME;
            string idString;
            getline(stream, discarded, '"');
            getline(stream, NAME, '"');
            getline(stream, discarded, ' ');
            getline(stream, idString, ' ');

            // Checks whether id is valid. If yes, converts to int.
            if (ValidID(idString) && ValidName(NAME))
            {
                //Checks for repeats.
                int ID = stoi(idString);
                tree.ChangePrint();
                bool repeatID = false;
                repeatID = tree.SearchID(tree.GetRoot(), ID, repeatID);
                tree.ChangePrint();

                // If repeated, ends.
                if (repeatID == true)
                {
                    cout << "unsuccessful" << endl;
                }
                // If not a repeat, adds to tree.
                else
                {
                    tree.ModifyNode(tree.InsertNode(tree.GetRoot(), NAME, ID));
                    cout << "successful" << endl;
                }
            }
            // Prints statement if id not valid.
            else
                cout << "unsuccessful" << endl;
        }
        // Remove branch.
        else if (commandPrompt == "remove")
        {
            string idString;
            getline(stream, idString, ' ');

            // Removes node if valid id.
            if (ValidID(idString))
            {
                tree.ModifyNode(tree.RemoveNode(tree.GetRoot(), stoi(idString)));
                if (tree.AccessResetSuccess() == true)
                    cout << "successful" << endl;
                else
                    cout << "unsuccessful" << endl;
            }
            // Else, prints unsuccessful.
            else
                cout << "unsuccessful" << endl;

        }
        // Search branch.
        else if (commandPrompt == "search")
        {
            string inputValue;
            bool success = false;
            getline(stream, inputValue, '"');

            // Loop for search name.
            if (inputValue.size() == 0) {
                getline(stream, inputValue, '"');
                tree.SearchNAME(tree.GetRoot(),inputValue);
                if (tree.AccessResetSuccess() != true)
                    cout << "unsuccessful" << endl;
            }
            // Loop for search ID.
            else
                if (ValidID(inputValue))
                {
                    success = tree.SearchID(tree.GetRoot(), stoi(inputValue), success);
                    if (!success)
                        cout << "unsuccessful" << endl;
                }
                else
                    cout << "unsuccessful" << endl;

        }

        // Inorder print branch.
        else if (commandPrompt == "printInorder")
        {
            string printString;
            printString = tree.PrintInOrder(tree.GetRoot(), printString);
            // Prints out string without ending comma.
            cout << printString.substr(0,printString.size()-2) << endl;
        }

        // Preorder branch.
        else if (commandPrompt == "printPreorder")
        {
            string printString;
            printString = tree.PrintPreOrder(tree.GetRoot(), printString);
            cout << printString.substr(0,printString.size()-2) << endl;
        }

        // Postorder branch.
        else if (commandPrompt == "printPostorder")
        {
            string printString;
            printString = tree.PrintPostOrder(tree.GetRoot(), printString);
            cout << printString.substr(0,printString.size()-2) << endl;
        }

        // Prints order level.
        else if (commandPrompt == "printLevelCount")
        {
            tree.PrintLevelCount(tree.GetRoot());
        }

        // In order removal branch.
        else if (commandPrompt == "removeInorder")
        {
            string n_string;
            int counter = 0;
            int n;
            getline(stream, n_string);
            n = stoi(n_string);

            // Determines which id to remove.
            counter =tree.MarkInorder(tree.GetRoot(), n, counter);
            if (counter < n + 1)
               cout << "unsuccessful" << endl;
            // Removes ID if it exits.
            else {
                tree.ModifyNode(tree.RemoveNode(tree.GetRoot(), tree.GetMarkedID()));
                cout << "successful" << endl;
            }
        }
        else
            cout << "unsuccessful" << endl;
    }
    return 0;
}

// Function to check whether the id is valid.
bool ValidID(string idString)
{
    // Checks size.
    if (idString.size() != 8)
    {
        return false;
    }
    else
    {
        // Checks that it is only composed of digits.
        for (unsigned int i = 0; i < idString.size(); i++)
        {
            if (idString[i] != '0' && idString[i] != '1' && idString[i] != '2' && idString[i] != '3') {
                if (idString[i] != '4' && idString[i] != '5' && idString[i] != '6' && idString[i] != '7') {
                    if (idString[i] != '8' && idString[i] != '9') {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool ValidName(string NAME)
{
    for (unsigned int i = 0; i < NAME.size(); i++)
    {
        if (NAME[i] != ' ' && NAME[i] != 'A' && NAME[i] != 'a' && NAME[i] != 'B' && NAME[i] != 'b' && NAME[i] != 'C' &&
        NAME[i] != 'c' && NAME[i] != 'D' && NAME[i] != 'd' && NAME[i] != 'E' && NAME[i] != 'e' && NAME[i] != 'F' &&
        NAME[i] != 'f' && NAME[i] != 'G' && NAME[i] != 'g' && NAME[i] != 'H' && NAME[i] != 'h' && NAME[i] != 'I' &&
        NAME[i] != 'i' && NAME[i] != 'J' && NAME[i] != 'j' && NAME[i] != 'K' && NAME[i] != 'k' && NAME[i] != 'L' &&
        NAME[i] != 'l' && NAME[i] != 'M' && NAME[i] != 'm' && NAME[i] != 'N' && NAME[i] != 'n' && NAME[i] != 'O' &&
        NAME[i] != 'o' && NAME[i] != 'P' && NAME[i] != 'p' && NAME[i] != 'Q' && NAME[i] != 'q' && NAME[i] != 'R' &&
        NAME[i] != 'r' && NAME[i] != 'S' && NAME[i] != 's' && NAME[i] != 'T' && NAME[i] != 't' && NAME[i] != 'U' &&
        NAME[i] != 'u' && NAME[i] != 'V' && NAME[i] != 'v' && NAME[i] != 'W' && NAME[i] != 'w' && NAME[i] != 'X' &&
        NAME[i] != 'x' && NAME[i] != 'Y' && NAME[i] != 'y' && NAME[i] != 'Z' && NAME[i] != 'z')
            return false;
    }
    return true;
}
