/*
Nolawee Mengist
Assignment 6
Professor Hoenigman
Worked with: Sami Meharzi and Sarah Godine
*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "MovieTree.h"
using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
    ifstream infile;
    infile.open("Assignment5Movies.txt");
    string line, word, title;
    int quantity, rating, year;
    stringstream ss;
    string command;
    MovieTree* stuff = new MovieTree;

    while (!infile.eof())
    {
        getline(infile,line);
        ss << line;
        int counter = 0;
        //for(int i =0; getline(ss,word,','); i++)
        while (getline(ss,word,','))
        {
            if(counter==0)
            {
                rating = stoi(word);
            }
            else if(counter==1)
            {
                title = word;
            }
            else if(counter == 2)
            {
                year = stoi(word);
            }
            else if(counter == 3)
            {
                quantity = stoi(word);
            }
            counter++;
        }
        stuff->addMovieNode(rating, title, year, quantity);
        ss.clear();
    }

    while(command != "5")
    {
        displayMenu();
        getline(cin, command);
        if(command == "1")
        {
            cout << "Enter title:" << endl;
            string input;
            getline(cin, input);
            //call rent movie
            stuff->rentMovie(input);
        }
        else if(command == "2")
        {
            stuff->printMovieInventory();
            //for all movies in the tree
            //cout<< "Movie: " << node->title << endl;
        }
        else if(command == "3")
        {
            //delete a movie
            cout << "Enter title:" << endl;
            string input;
            getline(cin, input);
            stuff->deleteMovieNode(input);
        }
        else if(command == "4")
        {
            //count the movies
            cout << stuff->countMovieNodes() << endl;
        }

    }
    cout << "Goodbye!" << endl;
    return 0;
}

void displayMenu()
{
    cout << "======Main Menu=====" << endl;
    cout << "1. Rent a movie" << endl;
    cout << "2. Print the inventory" << endl;
    cout << "3. Delete a movie" << endl;
    cout << "4. Count the movies" << endl;
    cout << "5. Quit" << endl;
}
