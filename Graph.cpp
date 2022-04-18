//Graph.cpp
//Graphs class that handles the organization of Movie verticies into a graph datastucture
//Allows edges to be formed between verticies and keeps track of all verticies in a given graph

#include "Movie_Vertex.h"
#include "Graph.h"

using namespace std;

    
    Graph::Graph(string type, vector<Movie_Vertex>& movies)
    {
        this->type = type;

        for(int i = 0; i < movies.size() - 2; i++) 
        {
            for(int j = i + 1; j < movies.size(); j++)
            {
                cout << to_string(i) << " " << to_string(j) << endl;
                if(movies[j].getRating() >= movies[i].getRating() - 0.5 
                    && movies[j].getRating() <= movies[i].getRating() + 0.5) 
                    {
                        addEdge(movies[i],movies[j]);
                    }
            }
        }
    }
    
    //Connects mainVert to adjVert and stores both into the list of verticies in the graph if they don't already exist
    void Graph::addEdge(Movie_Vertex& mainVert, Movie_Vertex& adjVert)
    {
        mainVert.addEdge(adjVert);
        adjVert.addEdge(mainVert);
    
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
    void Graph::removeEdge(Movie_Vertex mainVert, Movie_Vertex adjVert)
    {
      mainVert.removeEdge(adjVert);
      adjVert.removeEdge(mainVert);
    }

    //Removes vertex vert from the graph
    void Graph::removeVertex(Movie_Vertex vert)
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
    vector<Movie_Vertex*> Graph::getVerts()
    {
        return verts;
    }

//Quick example made to show how the graph handler works
//THIS SHOULD BE DELETED FOR THE FINAL IMPLEMENTATION
int main()
{
    Movie_Vertex a("Movie 1", "Horror", 1.2);
    Movie_Vertex b("Movie 2", "Horror", 1.6);
    Movie_Vertex c("Movie 3", "Horror", 2);
    Movie_Vertex d("Movie 4", "Adventure", 1.7);
    Movie_Vertex e("Movie 5", "Horror", 2.1);
    Movie_Vertex f("Movie 6", "Horror", 2.5);
    vector<Movie_Vertex> ex;
    ex.push_back(a);
    ex.push_back(b);
    ex.push_back(c);
    ex.push_back(d);
    ex.push_back(e);
    ex.push_back(f);
    Graph example("Horror", ex);

    for(int i = 0; i < example.getVerts().size(); i++)
    {
        for(int j = 0; j < example.getVerts()[i]->getEdges().size(); j++)
        {
        cout << example.getVerts()[i]->getTitle() << ": " << to_string(example.getVerts()[i]->getEdges()[j].first) << endl;
        }
    }
    
    return 0;
}