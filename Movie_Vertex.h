//Movie_Vertex.h
//Declaration file for Movie_Vertex class, a dependency for the Graphs data structure
//Make sure to have #include "Movie_Vertex.h" in any file that uses this

#ifndef Movie_Vertex_H
#define Movie_Vertex_H

#include <string>
#include <vector>

class Movie_Vertex
{
private:
    std::vector<std::pair<double, Movie_Vertex>> adjVerts;
    std::string title, genre;
    double rating, price;

public:
    Movie_Vertex(std::string title, std::string genre, double rating, double price);
    void addEdge(Movie_Vertex& adjVert, double rating);
    void removeEdge(Movie_Vertex& adjVert);
    std::vector<std::pair<double, Movie_Vertex>> getEdges();
    std::string getTitle();
    std::string getGenre();
    double getRating();
    double getPrice();
};
#endif