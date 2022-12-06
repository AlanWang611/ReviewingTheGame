#ifndef PROJECT3_REVIEWING_THE_GAME_SPLAYTREE_H
#define PROJECT3_REVIEWING_THE_GAME_SPLAYTREE_H
//
// Created by Alan Wang on 12/6/2022 at 11:59pm.
//
#include <iostream>
#include <chrono>
#include <queue>
#include <vector>

using namespace std;
using namespace std::chrono;
class SplayTree
{
public:
    //creating a struct for the splay tree
    struct Node
    {
        int ID;
        Node* parent;
        Node *left;
        Node *right;
        string gameName;
        string gameReview;

        //default constructor
        Node(int ID, string GameName, string GameReview) : ID(ID), gameName(GameName), gameReview(GameReview), left(nullptr), right(nullptr), parent(nullptr) {}

    };
    //store root node here
    Node* head;

public:
    //constructor setting head == null
    SplayTree()
    {
        head = nullptr;
    }

    //left rotation on the selected node
    void leftRotate(Node* oldTopNode)
    {
        //if the right ID is null then no rotation needed
        if (oldTopNode -> right != nullptr)
        {
            //set the current top node
            Node *topNode = oldTopNode -> right;

            //set the moved function to the old top
            oldTopNode -> right = topNode -> left;

            //find parent of the old root
            Node* parent = oldTopNode -> parent;
            //set the child to the parent
            if (topNode -> left == nullptr)
            {
                topNode -> left = nullptr;
            }
            else
            {
                //set parent
                topNode -> left -> parent = oldTopNode;
            }
            //if the node is not near the top of the tree
            if (topNode -> parent != nullptr)
            {
                topNode -> parent = oldTopNode -> parent;
            }
            //only one element in tree
            if (noFamily(oldTopNode))
            {
                head = topNode;
            }
            //checks if it is on the left
            else if (oldTopNode == parent -> left)
            {
                parent -> left = topNode;
            }
            //checks if it is on the right
            else
            {
                parent -> right = topNode;
            }

            //set back to the original
            topNode -> left = oldTopNode;
            oldTopNode -> parent = topNode;
        }
    }

    //right rotation on the selected node
    void rightRotate(Node* oldTopNode)
    {
        //if the left ID is null then no rotation needed
        if (oldTopNode -> left != nullptr)
        {
            //set the current top node
            Node *topNode = oldTopNode->left;

            //set the moved function to the old top
            oldTopNode->left = topNode->right;

            //find parent of the old root
            Node *parent = oldTopNode->parent;

            //set the child to the parent
            if (topNode->right == nullptr)
            {
                topNode->right = nullptr;
            } else
            {
                //set parent
                topNode->right->parent = oldTopNode;
            }
            //if the node is not near the top of the tree
            if (topNode->parent != nullptr)
            {
                topNode->parent = oldTopNode->parent;
            }
            //only one element in tree
            if (noFamily(oldTopNode))
            {
                head = topNode;
            }
            //checks if it is on the left
            else if (oldTopNode == parent->right)
            {
                parent->right = topNode;
            }
            //checks if it is on the right
            else
            {
                parent->left = topNode;
            }

            //set back to the original
            topNode->right = oldTopNode;
            oldTopNode->parent = topNode;
        }
    }

    //splays the current node to the top
    void splay(Node* current)
    {
        //checks if node is null
        if (current != nullptr)
        {

            //recursively call splay until the node is the root
            while (current -> parent != nullptr)
            {

                //checks the two previous nodes
                if (current -> parent -> parent == nullptr)
                {
                    //checks the zig or zag rotation
                    if (current == current -> parent -> left)
                    {
                        // right rotation
                        rightRotate(current -> parent);
                    } else
                    {
                        // left rotation
                        leftRotate(current -> parent);
                    }
                }
                //checks left-left
                else if (leftOne(current) && leftTwo(current))
                {
                    // left-left rotation
                    rightRotate(current -> parent -> parent);
                    rightRotate(current -> parent);
                }
                //checks right-right
                else if (rightOne(current) && rightTwo(current))
                {
                    // right-right rotation
                    leftRotate(current -> parent -> parent);
                    leftRotate(current -> parent);
                }
                //checks left-right
                else if (rightOne(current) && leftTwo(current))
                {
                    // left-right rotation
                    leftRotate(current -> parent);
                    rightRotate(current -> parent);
                }
                //if default then right-left
                else
                {
                    // right-left rotation
                    rightRotate(current -> parent);
                    leftRotate(current -> parent);
                }
            }
        }
    }

    //checks one level up if a left rotation is possible
    static bool leftOne (Node* current)
    {
        if (current != current -> parent -> left)
            return false;

        return true;
    }

    //checks two levels up if a left rotation is possible
    static bool leftTwo (Node* current)
    {
        if (current -> parent == current -> parent -> parent -> left)
            return false;
        return true;
    }

    //checks one level up if a right rotation is possible
    static bool rightOne (Node* current)
    {
        if (current != current -> parent -> right)
            return false;

        return true;
    }

    //checks two levels up if a right rotation is possible
    static bool rightTwo (Node* current)
    {
        if (current -> parent == current -> parent -> parent -> right)
            return false;
        return true;
    }

    //searches for the key
    //outputs the game and review
    void search(int ID)
    {
        //start timer occurs at the start of search
        auto start = high_resolution_clock::now();

        //store the head in temp
        Node* temp = head;
        //goes through the tree to find data
        while (temp != nullptr || temp -> ID == ID)
        {
            //checks if it is on the right side
            if (temp -> ID < ID)
            {
                //checks if ID is not found then output
                if (temp -> right == nullptr)
                {
                    //if not found output NOT FOUND
                    cout << "REVIEW: " << ID << " COULD NOT BE FOUND :(" << endl;

                    //timer ends since splay tree search is over
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);

                    //prints out splay tree time
                    cout << "The Splay Tree Search took " << duration.count() << " nanoseconds!" << endl;
                    break;
                }
                //keeps traversing right
                temp = temp -> right;
            }
            //checks if it is on the left side
            else if (temp -> ID > ID)
            {
                //checks if ID is not found then output
                if (temp -> left == nullptr)
                {
                    //if not found output NOT FOUND
                    cout << "REVIEW: " << ID << " COULD NOT BE FOUND :(" << endl;

                    //timer ends since splay tree search is over
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);

                    //prints out splay tree time
                    cout << "The Splay Tree Search took " << duration.count() << " nanoseconds!" << endl;
                    break;
                }
                //keeps traversing left
                temp = temp -> left;
            }
            //checks if it equals the current ID
            else if (temp -> ID == ID)
            {
                //output statement
                if(temp -> gameReview[0] == '"')
                {
                    cout << "This review is for " << "\"" + temp -> gameName + "\"";
                    cout <<" and the review says " + temp -> gameReview << endl;

                    //timer ends since splay tree search is over
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);

                    //prints out splay tree time
                    cout << "The Splay Tree Search took " << duration.count() << " nanoseconds!" << endl;
                    break;
                }
                else
                {
                    cout << "This review is for " << "\"" + temp -> gameName + "\"";
                    cout << " and the review says \"" + temp -> gameReview + "\"" << endl;

                    //timer ends since splay tree search is over
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);

                    //prints out splay tree time
                    cout << "The Splay Tree Search took " << duration.count() << " nanoseconds!" << endl;
                    break;
                }

                break;
            }
            //if not found output NOT FOUND
            else
            {
                cout << "REVIEW: " << ID << " COULD NOT BE FOUND :(" << endl;

                //timer ends since splay tree search is over
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);

                //prints out splay tree time
                cout << "The Splay Tree Search took " << duration.count() << " nanoseconds!" << endl;
                break;
            }
        }
        //splays the node
        splay(temp);
    }

    //find the parent of the node
    //parent auto set to nullptr
    void parentFunction(Node*& node, Node*& temp, Node*& parent)
    {
    //goes through all the nodes until it reaches it
        while (temp != nullptr)
        {
            parent = temp;
            //checks if it is on the left
            if (node -> ID < temp -> ID)
            {
                temp = temp -> left;
            }
            //checks if it is on the right
            else
            {
                temp = temp -> right;
            }
        }
    }

    //returns true if the node has no alive family
    bool noFamily(Node* node)
    {
        if (node -> parent == nullptr)
            return true;
        return false;
    }

    //helps the parents point the child node
    void childFunction(Node*& node, Node*& temp, Node*& parent)
    {
        //checks if it is on the left
        if (node -> ID < parent -> ID)
        {
            parent -> left = node;
        }
        //checks if it is on the right
        else
        {
            parent -> right = node;
        }
    }

    //insert function with the parameters for the node
    void insert(int ID, string name, string review)
    {
        // creating node with set parameters
        Node* node = new Node(ID, name, review);

        //set parent to null
        Node* parent = nullptr;

        //set temp to head
        Node* temp = head;

        //finds the ID of the parent function at
        parentFunction(node,temp,parent);

        // parent is parent of temp
        node -> parent = parent;

        //if no parent then only one node
        if (node -> parent == nullptr)
        {
            head = node;
        }
        else
            childFunction(node,temp,parent);

        // splay the node
        if (node != nullptr)
            splay(node);
    }
};

#endif //PROJECT3_REVIEWING_THE_GAME_SPLAYTREE_H
