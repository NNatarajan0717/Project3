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
    //map<string, vector<Movie_Vertex>> movieGenres;

    vector<Movie_Vertex> movieList;

    /*going through input files line by line, still have to create graph object in order to store movie vertices*/
    for (int i = 0; i < 10; i++) 
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
        movieList.push_back(movie);

    }

    Graph graph("", movieList);

    Graph* ptr = &graph;

    //cout << graph.breadthDepthSearch(ptr, "The Ball Game")->getTitle();

    //format for user input
    cout << "Welcome to the Movie Carosel!\n\n";

    bool movieFound = false;

    while (!movieFound) 
    {
    
        cout << "Choose an option to start:\n\nSearch by rating (enter: 1)\nSearch by genre (enter: 2)\nSearch by name (enter: 3)\nSearch for a random movie (enter: 4)\noption:";
        
        string searchChoice;
       
        getline(cin, searchChoice);

        if (stoi(searchChoice) == 1) 
        {
        
            string upperBound, lowerBound;
            cout << "\nEnter Upperbound (0.0 - 10.0): ";
            getline(cin, upperBound);
            cout << "Enter Lowerbound (0.0 - 10.0): ";
            getline(cin, lowerBound);
            graph.findRatingBDS(ptr, stod(lowerBound), stod(upperBound));

        }
        else if (stoi(searchChoice) == 2) 
        {

            string genre;
            cout << "\nEnter Genre: ";
            getline(cin, genre);
            graph.findGenreBDS(ptr, genre);

        }
        else if (stoi(searchChoice) == 3) 
        {

            cout << "\nEnter Movie Name:";
            string movieTitle;
            getline(cin, movieTitle);
            graph.findTitleBDS(ptr, movieTitle);
            
        }
        else if (stoi(searchChoice) == 4) 
        {

            graph.randomMovie(ptr);

        }
        else 
        {
        
            cout << "\nInvalid Input!\n\n";

        }

        cout << "Is this the movie you wanted? (y / n)" << endl;
        string answer;
        getline(cin, answer);
        if (answer == "y") 
        {
        
            movieFound = true;

        }

    }

    return 0;

}
