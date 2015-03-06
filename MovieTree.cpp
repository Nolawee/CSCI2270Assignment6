#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "MovieTree.h"
using namespace std;

MovieTree::MovieTree()
{
    root = NULL;
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity)
{
    MovieNode* cursor = root;
    MovieNode* cursorTwo = NULL;

    while(cursor != NULL)
    {
        cursorTwo = cursor;
        if(cursor->title.compare(title) > 0)
        {
            cursor = cursor->rightChild;
        }
        else
        {
            cursor = cursor->leftChild;
        }
    }
    cursor = new MovieNode;
    cursor->ranking = ranking;
    cursor->title = title;
    cursor->year = releaseYear;
    cursor->quantity = quantity;
    cursor->rightChild = NULL;
    cursor->leftChild = NULL;
    cursor->parent = cursorTwo;

    if(cursorTwo == NULL)
    {
        root = cursor;
    }
    else if(cursor->title.compare(cursorTwo->title) < 0)
    {
        cursorTwo->rightChild = cursor;
    }
    else
    {
        cursorTwo->leftChild = cursor;
    }
}

void MovieTree::findMovie(string title)
{
    MovieNode* foundMovie = searchMovieTree(root, title, Assignment6Output);
    if (foundMovie == NULL)
    {
        cout << "Movie not found." << endl;
    }
    else
    {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << foundMovie->ranking << endl;
        cout << "Title:" << foundMovie->title << endl;
        cout << "Year:" << foundMovie->year << endl;
        cout << "Quantity:" << foundMovie->quantity << endl;
    }
}

MovieNode* MovieTree::searchMovieTree(MovieNode* node, string title, json_object* traverseLog)
{
    //cout << "looking for " << title << endl;
    if(node != NULL && node->title == title)//value found
    {
        return node;
    }
    else if(node != NULL)
    {
        //cout << "seeing: " << node->title << endl;
        if(node->title.compare(title) < 0)
        {
             node = searchMovieTree(node->leftChild, title, Assignment6Output);
        }
        else
        {
            node = searchMovieTree(node->rightChild, title, Assignment6Output);
        }
    }
    return node;
}

void MovieTree::rentMovie(string title)
{
    MovieNode* foundMovie = searchMovieTree(root, title, Assignment6Output);
    //if movie is out of stock
    if(foundMovie != NULL && foundMovie->quantity == 0)
    {
        cout << "Movie out of stock." << endl;
    }
    //if movie is in stock
    else if(foundMovie != NULL)
    {
        foundMovie->quantity--;
        cout << "Movie has been rented." << endl;
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << foundMovie->ranking << endl;
        cout << "Title:" << foundMovie->title << endl;
        cout << "Year:" << foundMovie->year << endl;
        cout << "Quantity:" << foundMovie->quantity << endl;
    }
    //If movie not found in tree
    else
    {
        cout << "Movie not found" << endl;
    }
}

void MovieTree::printMovieInventory()
{
    printMovieInventory(root, Assignment6Output);
}

void MovieTree::printMovieInventory(MovieNode* node, json_object* traverseLog)
{
    if (node->rightChild != NULL)
    {
        printMovieInventory(node->rightChild, Assignment6Output);
    }
    cout << "Movie: " << node->title << endl;
    if (node->leftChild != NULL)
    {
        printMovieInventory(node->leftChild, Assignment6Output);
    }
}

void DeleteAll(MovieNode * node)
{

}

MovieTree::~MovieTree()
{

}

int MovieTree::countMovieNodes()
{
    //MovieNode* foundMovie = searchMovieTree(root, title, Assignment6Output);
    if (root != NULL)
    {
        return countMovieNodes(root);
    }
    else
    {
        return 0;
    }
    //return countMovieNodes(root);

}

int MovieTree::countMovieNodes(MovieNode* node)
{
    int opCount = 1;
    if (node->leftChild != NULL)
    {
        //countMovieNodes(node->leftChild);
        opCount = opCount+countMovieNodes(node->leftChild);

    }
    //cout << node->title << endl;
    if (node->rightChild != NULL)
    {
        opCount = opCount+countMovieNodes(node->rightChild);
    }
    return opCount;
}

void MovieTree::deleteMovieNode(string title)
{
    MovieNode* deletedNode = searchMovieTree(root, title, Assignment6Output);
    if (deletedNode == NULL)
    {
        return;
    }
    MovieNode* farLeft = deletedNode;
    if(farLeft->rightChild != NULL)
    {
        farLeft = farLeft->rightChild;
        while(farLeft->leftChild != NULL)
        {
            farLeft = farLeft->leftChild;
        }
    }
    MovieNode* leftNode = deletedNode->leftChild;
    if(farLeft != deletedNode)
    {
        farLeft->leftChild = leftNode;
    }
    MovieNode* parentNode = deletedNode->parent;
    if(parentNode != NULL)
    {
        if(parentNode->leftChild == deletedNode)
        {
            parentNode->leftChild = deletedNode->rightChild;
        }
        else
        {
            parentNode->rightChild = deletedNode->rightChild;
        }
    }
    MovieNode* rightNode = deletedNode->rightChild;
    if(rightNode != NULL)
    {
        rightNode->parent = parentNode;
    }
    if (leftNode != NULL)
    {
        leftNode->parent = farLeft;
    }
    if(deletedNode == root)
    {
        root = rightNode;
    }
    delete deletedNode;
}

void initJson()
{
    // Assignment6Output
}
