// Graph.cpp
// Graphs class that handles the organization of Movie verticies into a graph datastucture
// Allows edges to be formed between verticies and keeps track of all verticies in a given graph

#include "Movie_Vertex.h"
#include "Graph.h"

using namespace std;

//Generate a graph whose edges depend on ratings, close ratings preferred
Graph::Graph(string type, vector<Movie_Vertex>& movies)
{
    this->type = type;

    for (int i = 0; i < movies.size() - 1; i++)
    {
        for (int j = 0; j < movies.size(); j++)
        {
            if (j == i)
            {
                continue;
            }
            if (movies[j].getRating() >= movies[i].getRating() - 0.5 && movies[j].getRating() <= movies[i].getRating() + 0.5)
            {
                addEdge(movies[i], movies[j]);
            }
            else
            {
                addEdge(movies[i], movies[i + 1]);
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

//Return a random movie
Movie_Vertex* Graph::randomMovie(Graph* graph)
{
    int index = rand() % (graph->verts.size() + 1);
    return Graph::findTitleBDS(graph, graph->verts[index]->getTitle());
}

//Find a title using BDS algorithm
Movie_Vertex* Graph::findTitleBDS(Graph* graph, string title)
{
    vector<Movie_Vertex*> checkedVerts;
    vector<Movie_Vertex*> queuedVerts;

    checkedVerts.push_back(graph->verts[0]);
    queuedVerts.push_back(graph->verts[0]);

    cout << "\nTraversing Graph... \n";
    while (queuedVerts.size() > 0)
    {
        // Pull movie vertex to be checked
        Movie_Vertex* vert = queuedVerts[0];
        // Remove it from vector of vertices to check
        queuedVerts.erase(queuedVerts.begin());
        cout << vert->getTitle() << "->";

        // Get all edges of the currently checked movie vertex
        for (int i = 0; i < vert->getEdges()->size(); i++)
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
            cout << endl;
            return vert;
        }
    }
    cout << "\nNo Matches!\n" << endl;
    return nullptr;
}

//Find all movies within a rating of min-max using BDS
vector<Movie_Vertex*> Graph::findRatingBDS(Graph* graph, double min, double max)
{
    vector<Movie_Vertex*> checkedVerts;
    vector<Movie_Vertex*> queuedVerts;
    vector<Movie_Vertex*> matches;

    checkedVerts.push_back(graph->verts[0]);
    queuedVerts.push_back(graph->verts[0]);

    cout << "\nTraversing Graph...\n";
    while (queuedVerts.size() > 0)
    {
        // Pull movie vertex to be checked
        Movie_Vertex* vert = queuedVerts[0];
        // Remove it from vector of vertices to check
        queuedVerts.erase(queuedVerts.begin());
        cout << vert->getTitle() << "->";

        // Get all edges of the currently checked movie vertex
        for (int i = 0; i < vert->getEdges()->size(); i++)
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

        if (vert->getRating() >= min && vert->getRating() <= max)
        {
            matches.push_back(vert);
        }
    }

    if (matches.size() == 0) 
    {
    
        cout << "\nNo Matches!\n" << endl;

    }

    cout << endl;
    return matches;
}

//Find all movies of a certain genre
vector<Movie_Vertex*> Graph::findGenreBDS(Graph* graph, string genre)
{
    vector<Movie_Vertex*> checkedVerts;
    vector<Movie_Vertex*> queuedVerts;
    vector<Movie_Vertex*> matches;

    checkedVerts.push_back(graph->verts[0]);
    queuedVerts.push_back(graph->verts[0]);

    cout << "\nTraversing Graph... \n";
    while (queuedVerts.size() > 0)
    {
        // Pull movie vertex to be checked
        Movie_Vertex* vert = queuedVerts[0];
        // Remove it from vector of vertices to check
        queuedVerts.erase(queuedVerts.begin());
        cout << vert->getTitle() << "->";

        // Get all edges of the currently checked movie vertex
        for (int i = 0; i < vert->getEdges()->size(); i++)
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

        if (vert->getGenre().compare(genre) == 0)
        {
            matches.push_back(vert);
        }
    }

    if (matches.size() == 0)
    {

        cout << "\nNo Matches!\n" << endl;

    }

    cout << endl;
    return matches;
}


// Connects mainVert to adjVert and stores both into the list of verticies in the graph if they don't already exist
void Graph::addEdge(Movie_Vertex& mainVert, Movie_Vertex& adjVert)
{
    //Bi-directional
    mainVert.addEdge(adjVert);
    adjVert.addEdge(mainVert);

    bool firstExists = false;
    bool secondExists = false;

    //Prevent duplicates from being logged
    for (Movie_Vertex* v : verts)
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
        Movie_Vertex* ptr1 = &mainVert;
        Movie_Vertex* ptr2 = &adjVert;
        verts.push_back(ptr1);
        verts.push_back(ptr2);
    }
    else if (secondExists && !firstExists)
    {
        Movie_Vertex* ptr1 = &mainVert;
        verts.push_back(ptr1);
    }
    else if (firstExists && !secondExists)
    {
        Movie_Vertex* ptr2 = &adjVert;
        verts.push_back(ptr2);
    }
}

// Returns list of every vertex in the graph
vector<Movie_Vertex*> Graph::getVerts()
{
    return verts;
}
