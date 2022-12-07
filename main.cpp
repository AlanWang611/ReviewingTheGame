#include <iostream>
#include "RedBlackTree.h"
#include "SplayTree.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    //creates a red black and splay tree object
    RedBlackTree redBlackTree;
    SplayTree splayTree;

    //reads the file and inserts data into the tree
    string data;
    string header;
    ifstream SteamReviews("SteamReviews.txt");
    if(SteamReviews.is_open())
    {
        getline(SteamReviews, header);
        //retrieves every line from the file
        while(getline(SteamReviews, data))
        {
            //creates a stream from the line from the file
            istringstream in(data);

            //declares the variables that holds the data
            string id_;
            string game;
            string review;
            string language;

            //retrieves and assigns the data from the line
            getline(in, game, ',');
            getline(in, game, ',');
            getline(in, game, ',');
            getline(in, id_, ',');
            getline(in, language, ',');
            getline(in, review);
            review = review.substr(0, review.find(",16"));

            //converts the review id to an int
            int id = stoi(id_);

            //cout << game << " " << id << " " << review << endl;
            redBlackTree.insert(id, game, review);
            splayTree.insert(id, game, review);
        }
    }
    //asks the user how many reviews they want to look up
    int userInput;
    int userTimes;
    cout << "How many searches would you like to perform? ";
    cin >> userTimes;
    //asks the user what review they want to find
    for(int n = 0; n < userTimes; n++)
    {
        cout << "Which review would you like to find: ";
        cin >> userInput;
        cout << endl;
        cout << "Searching in the Red Black Tree:" << endl;
        redBlackTree.searchID(redBlackTree.root, userInput);
        cout << endl;
        cout << "Searching in the Splay Tree:" << endl;
        splayTree.search(userInput);
        cout << endl;
    }
    return 0;
}
