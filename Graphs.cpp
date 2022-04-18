//Graphs.cpp
//Graphs class that handles the organization of Movie verticies into a graph datastucture
//Allows edges to be formed between verticies and keeps track of all verticies in a given graph

#include <iostream>
#include <list>
#include <vector>
#include <string>

#include "Movie_Vertex.h"

using namespace std;

class Graph
{
private:

    vector<Movie_Vertex*> verts;

public:
    
    Graph()
    {
    }
    
    //Connects mainVert to adjVert and stores both into the list of verticies in the graph if they don't already exist
    void addEdge(Movie_Vertex& mainVert, Movie_Vertex& adjVert)
    {
        mainVert.addEdge(adjVert, adjVert.getRating());
        adjVert.addEdge(mainVert, mainVert.getRating());
    
        bool firstExists = false;
        bool secondExists = false;
        for(Movie_Vertex* v : verts)
        {
            if(mainVert.getTitle() == v->getTitle())
            {
                firstExists = true;
            }
            if(adjVert.getTitle() == v->getTitle())
            {
                secondExists = true;
            }
        }
        
        if(!firstExists && !secondExists)
        {
        Movie_Vertex* ptr1 = &mainVert;
        Movie_Vertex* ptr2 = &adjVert;
        verts.push_back(ptr2);
        verts.push_back(ptr1);
        }
        else if(firstExists)
        {
        Movie_Vertex* ptr2 = &adjVert;
        verts.push_back(ptr2);
        }
        else if(secondExists)
        {
        Movie_Vertex* ptr1 = &mainVert;
        verts.push_back(ptr1);
        }
    }

    //Removes the connection between mainVert and adjVert
    void removeEdge(Movie_Vertex mainVert, Movie_Vertex adjVert)
    {
      mainVert.removeEdge(adjVert);
      adjVert.removeEdge(mainVert);
    }

    //Removes vertex vert from the graph
    void removeVertex(Movie_Vertex vert)
    {
        for(pair<double, Movie_Vertex> edge : vert.getEdges())
        {
            //Access vertex associated with edge
            edge.second.removeEdge(vert);
            //Remove both verticies from the edge, thus deleting edge
            vert.removeEdge(edge.second);
        }
        for (int i = 0; i < verts.size(); i++)
        {
            if (verts[i]->getTitle() == vert.getTitle())
            {
                verts.erase(verts.begin() + i);
            }
        }
    }

    //Returns list of every vertex in the graph
    vector<Movie_Vertex*> getVerts()
    {
        return verts;
    }
};

//Quick example made to show how the graph handler works
//THIS SHOULD BE DELETED FOR THE FINAL IMPLEMENTATION
int main()
{
    Graph example;
    Movie_Vertex a("Movie 1", "Horror", 12, 11.3);
    Movie_Vertex b("Movie 2", "Comedy", 1.2, 1.3);
    Movie_Vertex c("Movie 3", "Adventure", 1.9, 1.3);
    example.addEdge(a, b);
    example.addEdge(b, c);
    example.addEdge(c, a);

    for(int i = 0; i < example.getVerts().size(); i++)
    {
        for(int j = 0; j < example.getVerts()[i]->getEdges().size(); j++)
        {
        cout << "i: " << to_string(i) << " j: " << to_string(j) << endl;
        cout << example.getVerts()[i]->getTitle() << ": " << to_string(example.getVerts()[i]->getEdges()[j].first) << endl;
        }
    }
    
    return 0;
}