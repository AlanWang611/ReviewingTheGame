#ifndef PROJECT3_REVIEWING_THE_GAME_SPLAYTREE_H
#define PROJECT3_REVIEWING_THE_GAME_SPLAYTREE_H
//
// Created by Alan Wang on 10/7/2022.
//
#include <iostream>
#include <queue>

using namespace std;
class SplayTree
{
public:
    //creating a struct for the splay tree
    struct Node
    {
        int value;
        Node* parent;
        Node *left;
        Node *right;
        string gameName;
        string gameReview;

        //default constructor
        Node(int ID, string GameName, string GameReview) : value(ID), gameName(GameName), gameReview(GameReview), left(nullptr), right(nullptr), parent(nullptr) {}

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
        //if the right value is null then no rotation needed
        if (oldTopNode -> right != nullptr)
        {
            //set the current top node
            Node *topNode = oldTopNode->right;
            //set the moved function to the old top
            oldTopNode->right = topNode->left;
            //set the child to the parent
            if (topNode->left == nullptr)
            {
                topNode -> left = nullptr;
            }
            else
            {
                topNode->left->parent = oldTopNode;
            }
            topNode->parent = oldTopNode->parent;
            if (oldTopNode->parent == nullptr) {
                head = topNode;
            } else if (oldTopNode == oldTopNode->parent->left) {
                oldTopNode->parent->left = topNode;
            } else {
                oldTopNode->parent->right = topNode;
            }
            topNode->left = oldTopNode;
            oldTopNode->parent = topNode;
        }
    }

    void rightRotate(Node* oldTopNode)
    {
        Node* topNode = oldTopNode -> left;
        oldTopNode -> left = topNode -> right;
        if (topNode -> right != nullptr) {
            topNode -> right -> parent = oldTopNode;
        }
        topNode -> parent = oldTopNode -> parent;
        if (oldTopNode -> parent == nullptr) {
            head = topNode;
        }
        else if (oldTopNode == oldTopNode -> parent -> right) {
            oldTopNode ->parent -> right = topNode;
        }
        else
        {
            oldTopNode -> parent -> left = topNode;
        }
        topNode -> right = oldTopNode;
        oldTopNode -> parent = topNode;
    }
    void splay(Node* x)
    {
        while (x->parent) {
            if (!x->parent->parent) {
                if (x == x->parent->left) {
                    // zig rotation
                    rightRotate(x->parent);
                } else {
                    // zag rotation
                    leftRotate(x->parent);
                }
            } else if (x == x->parent->left && x->parent == x->parent->parent->left) {
                // zig-zig rotation
                rightRotate(x->parent->parent);
                rightRotate(x->parent);
            } else if (x == x->parent->right && x->parent == x->parent->parent->right) {
                // zag-zag rotation
                leftRotate(x->parent->parent);
                leftRotate(x->parent);
            } else if (x == x->parent->right && x->parent == x->parent->parent->left) {
                // zig-zag rotation
                leftRotate(x->parent);
                rightRotate(x->parent);
            } else {
                // zag-zig rotation
                rightRotate(x->parent);
                leftRotate(x->parent);
            }
        }
    }

    //searches for the key
    //outputs the game and review
    void search(int key)
    {
        //store the head in temp
        Node* temp = head;
        //goes through the tree to find data
        while (temp != nullptr || temp -> value == key)
        {
            //checks if it is on the right side
            if (temp -> value < key)
            {
                //checks if value is not found then output
                if (temp -> right == nullptr)
                {
                    //if not found output NOT FOUND
                    cout << "REVIEW ID: " << key << " CAN NOT BE FOUND" << endl;
                    break;
                }
                //keeps traversing right
                temp = temp -> right;
            }
            //checks if it is on the left side
            else if (temp -> value > key)
            {
                //checks if value is not found then output
                if (temp -> left == nullptr)
                {
                    //if not found output NOT FOUND
                    cout << "REVIEW ID: " << key << " CAN NOT BE FOUND" << endl;
                    break;
                }
                //keeps traversing left
                temp = temp -> left;
            }
            //checks if it equals the current value
            else if (temp -> value == key)
            {
                //output statement
                cout << "This review is for " << "\"" + temp -> gameName + "\"";
                cout <<" and the review says \"" + temp -> gameReview + "\"" << endl;
                break;
            }
            //if not found output NOT FOUND
            else
            {
                cout << "REVIEW ID: " << key << " CAN NOT BE FOUND" << endl;
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
            if (node->value < temp->value)
            {
                temp = temp->left;
            }
            //checks if it is on the right
            else
            {
                temp = temp->right;
            }
        }
    }

    //helps the parents point the child node
    void childFunction(Node*& node, Node*& temp, Node*& parent)
    {
        //checks if it is on the left
        if (node->value < parent->value)
        {
            parent->left = node;
        }
        //checks if it is on the right
        else
        {
            parent->right = node;
        }
    }

    //insert function with the parameters for the node
    void insert(int key, string name, string review)
    {
        // creating node with set parameters
        Node* node = new Node(key, name, review);

        //set parent to null
        Node* parent = nullptr;

        //set temp to head
        Node* temp = head;

        //finds the value of the parent function at
        parentFunction(node,temp,parent);

        // parent is parent of temp
        node->parent = parent;

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

    void printLevelorder()
    {
        printLevelorder(head);
    }
    void printLevelorder(Node *node)
    {
        if (node != nullptr){
            //create queue
            int level = 0;
            queue<Node *> q;
            q.push(node);
            //find current level
            int current = 0;
            int sum = 0;
            while (!q.empty()) {
                int size = q.size();
                for (int i = 0; i < size; i++) {

                    node = q.front();
                    q.pop();
                    cout << node->value << ", ";
                    if (node->left != nullptr) {
                        q.push(node->left);
                    }
                    if (node->right != nullptr) {
                        q.push(node->right);
                    }
                }
            }
        }
    }
};

#endif //PROJECT3_REVIEWING_THE_GAME_SPLAYTREE_H
