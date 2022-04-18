//Graph.cpp
//Graphs class that handles the organization of Movie verticies into a graph datastucture
//Allows edges to be formed between verticies and keeps track of all verticies in a given graph

#include "Movie_Vertex.h"
#include "Graph.h"

using namespace std;

    
    Graph::Graph(string type, vector<Movie_Vertex>& movies)
    {
        this->type = type;

        for(int i = 0; i < movies.size() - 1; i++) 
        {
            if(movies[i + 1].getRating() >= movies[i].getRating() - 0.5 
                && movies[i + 1].getRating() <= movies[i].getRating() + 0.5) 
            {
                addEdge(movies[i], movies[i + 1]);
            }
    

            //Randomly assign an edge if rating falls out of tolerance
            if(movies[i].getEdges().size() == 0) 
            {
                int k = -1;
                //Ensure no connection with self
                while(k == -1 || k == i)
                {
                    k = (rand() % movies.size() - 1);
                }

                addEdge(movies[i], movies[k]);
            }
        }
        
        if(movies[movies.size() - 1].getEdges().size() == 0) 
            {
                int k = -1;
                //Ensure no connection with self
                while(k == -1 || k == movies.size() - 1)
                {
                    k = (rand() % movies.size() - 1);
                }

                addEdge(movies[movies.size() - 1], movies[k]);
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
            
            if(mainVert.getTitle().compare(v->getTitle()) == 0)
            {
                firstExists = true;
            }
            if(adjVert.getTitle().compare(v->getTitle()) == 0)
            {
                secondExists = true;
            }
        }
        
        if(!firstExists && !secondExists)
        {
        Movie_Vertex* ptr1 = &mainVert;
        Movie_Vertex* ptr2 = &adjVert;
        verts.push_back(ptr1);
        verts.push_back(ptr2);
        }
        else if(secondExists && !firstExists)
        {
        Movie_Vertex* ptr1 = &mainVert;
        verts.push_back(ptr1);
        }
        else if(firstExists && !secondExists)
        {
        Movie_Vertex* ptr2 = &adjVert;
        verts.push_back(ptr2);
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
    vector<Movie_Vertex> ex;
    for(int i = 0; i < 100000; i++) {
        string movie = "Movie ";
        Movie_Vertex a(movie.append(to_string(i + 1)), "Horror", 1 + ((double)rand() / RAND_MAX) * 9);
        ex.push_back(a);
    }

    Graph example("Horror", ex);
    
    vector<Movie_Vertex*> vertx = example.getVerts();

    for(int i = 0; i < vertx.size(); i++)
    {
        for(int j = 0; j < vertx[i]->getEdges().size(); j++)
       {
           cout << vertx[i]->getTitle() << ": " << vertx[i]->getEdges()[j].second.getTitle() << " : " << to_string(vertx[i]->getEdges()[j].first) << endl;
       }
    }
    
    return 0;
}