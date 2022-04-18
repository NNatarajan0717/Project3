#include <iostream>

#include "Graph.h"
#include "Movie_Vertex.h"

using namespace std;

vector<Movie_Vertex> breadthDepthSearch(Graph graph, Movie_Vertex root, string title) {
    vector<Movie_Vertex> checkedVerts;
    vector<Movie_Vertex> queuedVerts;

    checkedVerts.push_back(root);
    queuedVerts.push_back(root);

    bool matchFound = false;
    while(queuedVerts.size() > 0 && !matchFound)
    {
        //Pull movie vertex to be checked
        Movie_Vertex vert = queuedVerts[0];
        //Remove it from vector of vertices to check
        queuedVerts.erase(queuedVerts.begin());

        cout << vert.getTitle() << " ";

        //Get all edges of the currently checked movie vertex
        for(pair<double, Movie_Vertex> edge : vert.getEdges())
        {
            //Determine if the adjacent movie has been traversed before
            bool movieChecked = false;
            for(Movie_Vertex movie : checkedVerts)
            {
                if(movie.getTitle().compare(edge.second.getTitle()) == 0)
                {
                    movieChecked = true;
                    break;
                }
            }

            //Add this adjacent movie vertex to be checked since it hasn't been traversed
            if(!movieChecked)
            {
                checkedVerts.push_back(edge.second);
                queuedVerts.push_back(edge.second);
            }
        }

        if(vert.getTitle().compare(title) == 0)
        {
            cout << " Match Found!" << endl;
            return checkedVerts;
        }
    }
}


double partition(double arr[], int low, int high){
    double pivot = arr[low];
    int up = low;
    int down = high;
    while(up < down){
        for(int i = up; i < high; i++){
            if(arr[up] > pivot){
                break;
            }
            up += 1;
            for(int j = high; j > low; j--){
                if(arr[down] < pivot){
                    break;
                }
                down -= 1;
            }
            if(up < down) {
                swap(arr[up], arr[down]);
            }
        }
    }
    swap(arr[low],arr[down]);
    return down;
}