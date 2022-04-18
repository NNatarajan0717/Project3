#include "Movie_Vertex.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    
    ifstream moviesInfile("MovieDataBaseInput.txt");
    ifstream ratingsInfile("MovieRatings.txt");
    string tconst, title, releaseYear, genres, buffer, rating;

    //skip first line of input that contains format info of file
    getline(moviesInfile, buffer);
    getline(ratingsInfile, buffer);

    /*going through input files line by line, still have to create graph object in order to store movie vertices*/
    for (int i = 0; i < 50; i++) 
    {

        //get index of movie
        getline(moviesInfile, tconst, '\t');

        //skip title type info
        getline(moviesInfile, buffer, '\t');

        //get title type info
        getline(moviesInfile, title, '\t');

        //skip original title info
        getline(moviesInfile, buffer, '\t');

        //skip isAdult info
        getline(moviesInfile, buffer, '\t');

        //get release Year info
        getline(moviesInfile, releaseYear, '\t');

        //skip end year info
        getline(moviesInfile, buffer, '\t');

        //skip runtime info
        getline(moviesInfile, buffer, '\t');

        //get genres info
        getline(moviesInfile, genres);

        //skip index info
        getline(ratingsInfile, buffer, '\t');

        //get the movie rating
        getline(ratingsInfile, rating, '\t');

        //skip number of votes info
        getline(ratingsInfile, buffer);

        cout << tconst << endl << title << endl << releaseYear << endl << genres << endl << rating << "\n\n";

    }

}
