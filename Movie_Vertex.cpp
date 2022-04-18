//Movie_Vertex.cpp
//Implementation of Movie_Vertex class
//Intention is to provide an infrastructure for storing data about movies in a "node" referred to as a vertex
//The vertex can be connected to other verticies using edges, thus creating a graph
//The Graph class is required as a handler for the movie vertex objects
//A single graph object is made and multiple verticies/edges are added to it

#include "Movie_Vertex.h"
#include <vector>
#include <iostream>
using namespace std;

// Constructor for Movie_Vertex, stores all information relating to the movie dataset
Movie_Vertex::Movie_Vertex(string title, string genre, double rating, double price)
{
    this->title = title;
    this->genre = genre;
    this->rating = rating;
    this->price = price;
}

//Adds adjVert to a list of connected verticies, adjVerts
void Movie_Vertex::addEdge(Movie_Vertex& adjVert, double rating)
{
    //Each edge has a rating where higher ratings have lower weights
    adjVerts.push_back(make_pair(1/rating, adjVert));
}

// Remove the connection between this vertex and adjVert
void Movie_Vertex::removeEdge(Movie_Vertex& adjVert)
{
    for (int i = 0; i < adjVerts.size(); i++)
    {
        if (adjVerts[i].second.getTitle() == adjVert.getTitle())
        {
            adjVerts.erase(adjVerts.begin() + i);
        }
    }
}

// Return all connections of this vertex
vector<pair<double, Movie_Vertex>> Movie_Vertex::getEdges()
{
    return adjVerts;
}

string Movie_Vertex::getTitle()
{
    return title;
}

string Movie_Vertex::getGenre()
{
    return genre;
}

double Movie_Vertex::getPrice()
{
    return price;
}

double Movie_Vertex::getRating()
{
    return rating;
}