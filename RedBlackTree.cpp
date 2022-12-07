#include "RedBlackTree.h"
#include <chrono>
using namespace std::chrono;

//destructor for red black tree
RedBlackTree::Node::~Node() {

}

//constructor for node object
RedBlackTree::Node::Node() {

}

//constructor for red black tree
RedBlackTree::RedBlackTree() {
    root = nullptr;
}

//inserts into red black tree
void RedBlackTree::insert(int id, string game, string review) {
    //creates a new node with the correct data
    Node* node = new Node;
    node -> right = nullptr;
    node -> left = nullptr;
    node -> parent = nullptr;
    node -> id = id;
    node -> review = review;
    node -> game = game;
    node -> color = 1;

    //Inserts into the tree at the correct location
    Node* cur = root;
    Node* temp = nullptr;
    while(cur != nullptr)
    {
        temp = cur;
        //node id is greater so go right
        if(node -> id > cur -> id)
        {
            cur = cur -> right;
        }
        //node id is less so go left
        else
        {
            cur = cur -> left;
        }
    }
    node -> parent = temp;
    //the tree is empty so makes the new node the root of tree
    if(temp == nullptr)
    {
        root = node;
        root -> color = 0;
        return;
    }
    //if new node's value is less than the leafs value then make it the left child of the leaf
    else if(node -> id < temp -> id)
    {
        temp -> left = node;
    }
    //if new node's value is greater than the leafs value then make it the right child of the leaf
    else
    {
        temp -> right = node;
    }

    //only 2 nodes in the tree so keep the new node red and the root black
    if(node -> parent -> parent == nullptr)
    {
        return;
    }

    //makes sure that the red black tree properties are maintained
    maintain(node);
}

//function to maintain the properties of red black tree
void RedBlackTree::maintain(RedBlackTree::Node *node) {
    while(node -> parent -> color == 1)
    {
        //the parent of the node is the left child of the grandparent node
        if(node -> parent == node -> parent -> parent -> left)
        {
            Node* temp = node -> parent -> parent -> right;
            if(temp == nullptr || temp -> color == 0)
            {
                //node is the right child of the parent
                if(node == node -> parent -> right)
                {
                    node = node -> parent;
                    LeftRotation(node);
                }
                node -> parent -> parent -> color = 1;
                node -> parent -> color = 0;
                RightRotation(node -> parent -> parent);
            }
            //if temp node is red, make the parent and temp black and grandparent red
            else if(temp -> color == 1)
            {
                node -> parent -> color = 0;
                temp -> color = 0;
                node -> parent -> parent -> color = 1;
                //move up the tree
                node = node -> parent -> parent;
            }
        }
        //the parent of the node is the right child of the grandparent node
        else
        {
            Node* temp = node -> parent -> parent -> left;
            if(temp == nullptr || temp -> color == 0)
            {
                //node is the left child of the parent
                if(node == node -> parent -> left)
                {
                    node = node -> parent;
                    RightRotation(node);
                }
                node -> parent -> parent -> color = 1;
                node -> parent -> color = 0;
                LeftRotation(node -> parent -> parent);
            }
            //temp node is red so make the parent and temp black and grandparent red
            else if(temp -> color == 1)
            {
                node -> parent -> color = 0;
                temp -> color = 0;
                node -> parent -> parent -> color = 1;
                //move up the tree
                node = node -> parent -> parent;
            }
        }
        //leave the loop once the root is reached
        if(node == root)
        {
            break;
        }
    }
    //sets the root of the tree as black
    root -> color = 0;
}

//function to perform a left rotation on the node
void RedBlackTree::LeftRotation(RedBlackTree::Node *node) {
    Node* child = node -> right;
    node -> right = child -> left;
    //reassigns the parent of the left child of child to the new node
    if(child -> left != nullptr)
    {
        child -> left -> parent = node;
    }
    child -> parent = node -> parent;
    //child now becomes the root
    if(node -> parent == nullptr)
    {
        root = child;
    }
    //node is the left child so make the new left child the child
    else if(node == node -> parent -> left)
    {
        node -> parent -> left = child;
    }
    //node is the right child so make the new right child the child
    else
    {
        node -> parent -> right = child;
    }
    child -> left = node;
    node -> parent = child;
}

//function to perform a right rotation on the node
void RedBlackTree::RightRotation(RedBlackTree::Node *node) {
    Node* child = node -> left;
    node -> left = child -> right;
    //reassigns the parent of the right child of child to the new node
    if(child -> right != nullptr)
    {
        child -> right -> parent = node;
    }
    child ->parent = node -> parent;
    //child now becomes the root
    if(node -> parent == nullptr)
    {
        root = child;
    }
    //node is the right child so make the new right child the child
    else if(node == node -> parent -> right)
    {
        node -> parent -> right = child;
    }
    //node is the left child so make the new left child the child
    else
    {
        node -> parent -> left = child;
    }
    child -> right = node;
    node -> parent = child;
}

//preorder traversal of the red black tree
void RedBlackTree::preorder(RedBlackTree::Node *node) {
    if(node == nullptr)
    {
        cout << "";
    }
    else
    {
        cout << node -> id <<", ";
        preorder(node -> left);
        preorder(node -> right);
    }
}

//function to find a specified id in the red black tree
RedBlackTree::Node *RedBlackTree::searchID(RedBlackTree::Node *node, int id) {
    //starts the clock
    auto start = high_resolution_clock::now();
    if(node == nullptr)
    {
        cout << "REVIEW ID: " << id << " COULD NOT BE FOUND :(" << endl;
        //item is found or not found so the timer stops and the time is printed
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        //prints out the final time
        cout << "The Red Black Tree Search took " << duration.count() << " microseconds!" << endl;
        return node;
    }
    else if(id == node -> id)
    {
        if(node -> review[0] == '"')
        {
            cout << "This review is for " << "\"" + node -> game + "\"";
            cout <<" and the review says " + node -> review << endl;
            //item is found or not found so the timer stops and the time is printed
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            //prints out the final time
            cout << "The Red Black Tree Search took " << duration.count() << " microseconds!" << endl;
            return node;
        }
        else
        {
            cout << "This review is for " << "\"" + node -> game + "\"";
            cout <<" and the review says \"" + node -> review + "\"" << endl;
            //item is found or not found so the timer stops and the time is printed
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            //prints out the final time
            cout << "The Red Black Tree Search took " << duration.count() << " microseconds!" << endl;
            return node;
        }
    }
    else if(node -> left == nullptr && node -> right == nullptr)
    {
        cout << "REVIEW ID: " << id << " COULD NOT BE FOUND :(" << endl;
        //item is found or not found so the timer stops and the time is printed
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        //prints out the final time
        cout << "The Red Black Tree Search took " << duration.count() << " microseconds!" << endl;
        return node;
    }
    else if(id < node -> id)
    {
        searchID(node -> left, id);
    }
    else
    {
        searchID(node -> right, id);
    }
    return node;
}
