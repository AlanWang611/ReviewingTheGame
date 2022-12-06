#include <iostream>
#include <vector>

using namespace std;

//class representing the red black tree and its functions
class RedBlackTree{
public:
    //class representing each individual tree node
    struct Node{
        int id;
        string review;
        string game;
        int color;    //1 will represent red and 0 will represent black
        Node* parent;
        Node* left;
        Node* right;
        Node();
        ~Node();
    };
    //declares class variables and functions
    Node* root;
    //constructor
    RedBlackTree();
    //function to insert a node into the red black tree
    void insert(int id, string game, string review);
    //function to maintain the red-black trees
    void maintain(Node* node);
    //function to perform a left rotation
    void LeftRotation(Node* node);
    //function to perform a right rotation
    void RightRotation(Node* node);
    //function to perform a preorder traversal
    void preorder(Node* node);
    //function to look for a specified game ID and print out its review
    Node* searchID(Node* node , int id);
};