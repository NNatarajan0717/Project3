//Graphs.h

#ifndef Graph_H
#define Graph_H

#include <iostream>
#include <list>
#include <vector>
#include <string>

class Graph
{
    private:

        std::vector<Movie_Vertex*> verts;
        std::string type;

    public:

        Graph(std::string type, std::vector<Movie_Vertex>& movies);
        static Movie_Vertex* breadthDepthSearch(Graph* graph, std::string title);
        void addEdge(Movie_Vertex& mainVert, Movie_Vertex& adjVert);
        void removeEdge(Movie_Vertex mainVert, Movie_Vertex adjVert);
        void removeVertex(Movie_Vertex vert);
        std::vector<Movie_Vertex*> getVerts();
};

#endif