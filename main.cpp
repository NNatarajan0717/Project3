#include "Movie_Vertex.h"
#include "Graph.h"
#include <iostream>
#include <map>
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

    //map of vectors of movies, each vector contains movies of the same genre
    map<string, vector<Movie_Vertex>> movieGenres;

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

        genres = genres.substr(0, genres.find(","));

        //skip index info
        getline(ratingsInfile, buffer, '\t');

        //get the movie rating
        getline(ratingsInfile, rating, '\t');

        //skip number of votes info
        getline(ratingsInfile, buffer);

        //create movie object
        Movie_Vertex movie(title, genres, stod(rating));

        //push movie object into vector of movies
        movieGenres[movie.getGenre()].push_back(movie);

    }

    map<string, Graph> movieGraphs;

    for (auto itr = movieGenres.begin(); itr != movieGenres.end(); itr++) 
    {
    
        movieGraphs.insert(pair<string, Graph>(itr->first, Graph(itr->first, itr->second)));
        cout << itr->first << " : " << to_string(itr->second.size()) << endl;

    }

}
