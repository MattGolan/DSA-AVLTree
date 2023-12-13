# DSA-AVLTree
AVL tree for data structures and algorithms class project. I designed a custom AVL tree to organize University of Florida student accounts based on student IDs. Specifically, I implemented methods for insertion, deletion, search, and traversals for an AVL tree data structure. (Please see below for a detailed overview of each method). Additionally, I implemented a main method to call specific methods based on validated user inputs. Subsequently, I tested my implementation using the catch2 framework. 

Detailed Overview of Methods:

insert NAME ID

•	Adds a student object into the tree with the specified name, NAME and ID number, ID.
•	Balances the tree automatically if necessary.
•	Prints “successful” if insertion is successful. Otherwise, prints “unsuccessful.”

remove ID

•	Finds and removes the account with the specified ID from the tree.
•	Prioritizes replacing a removed node with its inorder successor if the deleted node had two children.
•	If deletion was successful, print “successful”.
•	If the ID does not exist within the tree, print “unsuccessful”.

search ID

•	Searches for the student with the specified ID from the tree.
•	If the ID was found, print out their NAME.
•	If the ID does not exist within the tree, print “unsuccessful”.

search NAME

•	Searches for the student with the specified name, NAME in the tree.
•	If the student name was found, print the associated ID.
•	If the tree has more than one object with the same NAME, print each ID on a new line in pre-order traversal order.
•	If the name does not exist within the tree, print “unsuccessful”.

printInorder

•	Prints comma-separated inorder traversal of the names in the tree.

printPreorder

•	Prints comma-separated preorder traversal of the names in the tree.

printPostorder

•	Prints comma-separated postorder traversal of the names in the tree.

printLevelCount	

•	Prints the current level count. (e.g. 0 for empty, 1 for tree with only a root).

removeInorder N

•	Removes the Nth ID from the inorder traversal of the tree (N = 0 for the first item, etc).
•	If removal was successful, print “successful”.
•	If the Nth ID does not exist within the tree, print “unsuccessful”.
