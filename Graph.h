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
        static Movie_Vertex* findTitleBDS(Graph* graph, std::string title);
        static Movie_Vertex* randomMovie(Graph* graph);
        static std::vector<Movie_Vertex*> findRatingBDS(Graph* graph, double min, double max);
        static std::vector<Movie_Vertex*> findGenreBDS(Graph* graph, std::string genre);
        void addEdge(Movie_Vertex& mainVert, Movie_Vertex& adjVert);
        std::vector<Movie_Vertex*> getVerts();
};

#endif