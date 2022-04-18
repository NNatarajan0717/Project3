// Graph.cpp
// Graphs class that handles the organization of Movie verticies into a graph datastucture
// Allows edges to be formed between verticies and keeps track of all verticies in a given graph

#include "Movie_Vertex.h"
#include "Graph.h"

using namespace std;

Graph::Graph(string type, vector<Movie_Vertex> &movies)
{
    this->type = type;

    for (int i = 0; i < movies.size() - 1; i++)
    {
        for(int j = 0; j < movies.size(); j++)
        {
            if(j == i)
            {
                continue;
            }
            if (movies[j].getRating() >= movies[i].getRating() - 0.5 && movies[j].getRating() <= movies[i].getRating() + 0.5)
            {
                addEdge(movies[i], movies[j]);
            }
            else 
            {
                addEdge(movies[i], movies[i+1]);
            }
        }
    }
    
    

    if (movies[movies.size() - 1].getEdges()->size() == 0)
    {
        int k = -1;
        // Ensure no connection with self
        while (k == -1 || k == movies.size() - 1)
        {
            k = (rand() % movies.size() - 1);
        }

        addEdge(movies[movies.size() - 1], movies[k]);
    }
}

Movie_Vertex* Graph::breadthDepthSearch(Graph* graph, string title)
{
    vector<Movie_Vertex*> checkedVerts;
    vector<Movie_Vertex*> queuedVerts;

    checkedVerts.push_back(graph->verts[0]);
    queuedVerts.push_back(graph->verts[0]);

    cout << "Traversing... ";
    while (queuedVerts.size() > 0)
    {
        // Pull movie vertex to be checked
        Movie_Vertex* vert = queuedVerts[0];
        // Remove it from vector of vertices to check
        queuedVerts.erase(queuedVerts.begin());
        cout << vert->getTitle() << " ";
        
        // Get all edges of the currently checked movie vertex
        for(int i = 0; i < vert->getEdges()->size(); i++)
        {
            // Determine if the adjacent movie has been traversed before
           bool movieChecked = false;
            for (Movie_Vertex* movie : checkedVerts)
            {
                if (movie->getTitle().compare(vert->getEdges()->at(i).second->getTitle()) == 0)
                {
                    movieChecked = true;
                }
            }
            
            // Add this adjacent movie vertex to be checked since it hasn't been traversed
            if (!movieChecked)
            {
                checkedVerts.push_back(vert->getEdges()->at(i).second);
                queuedVerts.push_back(vert->getEdges()->at(i).second);
            }
        }

        if (vert->getTitle().compare(title) == 0)
        {
            cout << " Match Found!" << endl;
            return vert;
        }
    }
    cout << "No Matches!" << endl;
    return nullptr; 
}

// Connects mainVert to adjVert and stores both into the list of verticies in the graph if they don't already exist
void Graph::addEdge(Movie_Vertex &mainVert, Movie_Vertex &adjVert)
{
    mainVert.addEdge(adjVert);
    adjVert.addEdge(mainVert);

    bool firstExists = false;
    bool secondExists = false;

    for (Movie_Vertex *v : verts)
    {

        if (mainVert.getTitle().compare(v->getTitle()) == 0)
        {
            firstExists = true;
        }
        if (adjVert.getTitle().compare(v->getTitle()) == 0)
        {
            secondExists = true;
        }
    }

    if (!firstExists && !secondExists)
    {
        Movie_Vertex *ptr1 = &mainVert;
        Movie_Vertex *ptr2 = &adjVert;
        verts.push_back(ptr1);
        verts.push_back(ptr2);
    }
    else if (secondExists && !firstExists)
    {
        Movie_Vertex *ptr1 = &mainVert;
        verts.push_back(ptr1);
    }
    else if (firstExists && !secondExists)
    {
        Movie_Vertex *ptr2 = &adjVert;
        verts.push_back(ptr2);
    }
}

// Returns list of every vertex in the graph
vector<Movie_Vertex *> Graph::getVerts()
{
    return verts;
}

// Quick example made to show how the graph handler works
// THIS SHOULD BE DELETED FOR THE FINAL IMPLEMENTATION
int main()
{
    vector<Movie_Vertex> ex;
    for (int i = 0; i < 50; i++)
    {
        string movie = "Movie ";
        Movie_Vertex a(movie.append(to_string(i + 1)), "Horror", 1 + ((double)rand() / RAND_MAX) * 9);
        ex.push_back(a);
    }
    Graph example("Horror", ex);

   vector<Movie_Vertex *> vertx = example.getVerts();
    for (int i = 0; i < vertx.size(); i++)
    {
        for (int j = 0; j < vertx[i]->getEdges()->size(); j++)
        {
           cout << vertx[i]->getTitle() << ": " << vertx[i]->getEdges()->at(j).second->getTitle() << " : " << to_string(vertx[i]->getEdges()->at(j).first) << endl;
        }
    }
    
    Graph* ptr = &example;
    Graph::breadthDepthSearch(ptr, ex[20].getTitle());

    return 0;
}