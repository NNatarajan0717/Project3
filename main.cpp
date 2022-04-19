#include "Movie_Vertex.h"
#include "Graph.h"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

void displayMovie(Movie_Vertex movie) {
    cout << "Movie Selected:" << endl;
    cout << "Title: " << movie.getTitle() << endl;
    cout << "Genre: " << movie.getGenre() << endl;
    cout << "Rating: " << movie.getRating() << endl;

}

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
        movieList.push_back(movie);

    }

    //format for user input
    cout << "Welcome to the Movie Carosel!\n\n";

    bool movieFound = false;

    vector<Movie_Vertex> reset = movieList;

    while (!movieFound) 
    {

        cout << "Search Space Size: " << movieList.size() << endl;

        Graph graph("", movieList);

        Graph* ptr = &graph;
    
        cout << "Choose an option to start:\n\nSearch by rating (enter: 1)\nSearch by genre (enter: 2)\nSearch by name (enter: 3)\nSearch for a random movie (enter: 4)\nReset Search Space\noption:";
        
        string searchChoice;
       
        getline(cin, searchChoice);

        if (stoi(searchChoice) == 1) 
        {
        
            string upperBound, lowerBound;
            cout << "\nEnter Upperbound (0.0 - 10.0): ";
            getline(cin, upperBound);
            cout << "Enter Lowerbound (0.0 - 10.0): ";
            getline(cin, lowerBound);

            vector<Movie_Vertex*> updatedMovieList = graph.findRatingBDS(ptr, stod(lowerBound), stod(upperBound));
            cout << "\n\nMovie titles found with a rating between " << lowerBound << " - " << upperBound << ":" << endl;

            for (int i = 0; i < updatedMovieList.size(); i++) 
            {
            
                cout << updatedMovieList.at(i)->getTitle() << endl;

            }

            cout << "\nWould you like to continue searching among these titles? (y / n)" << endl;
            string answer;
            getline(cin, answer);
            if (answer == "y") 
            {
            
                for (int i = 0; i < updatedMovieList.size(); i++) 
                {
                
                    movieList.at(i) = *updatedMovieList.at(i);

                }

                unsigned int size = movieList.size();

                for (int i = updatedMovieList.size(); i < size; i++)
                {

                    movieList.pop_back();

                }

            }
            else 
            {
            
                continue;

            }

        }
        else if (stoi(searchChoice) == 2) 
        {

            string genre;
            cout << "\nEnter Genre: ";
            getline(cin, genre);
            vector<Movie_Vertex*> updatedMovieList = graph.findGenreBDS(ptr, genre);
            cout << "\n\nMovie titles under " << genre << ":" << endl;

            for (int i = 0; i < updatedMovieList.size(); i++)
            {

                cout << updatedMovieList.at(i)->getTitle() << endl;

            }

            cout << "\nWould you like to continue searching among these titles? (y / n)" << endl;
            string answer;
            getline(cin, answer);
            if (answer == "y")
            {

                for (int i = 0; i < updatedMovieList.size(); i++)
                {

                    movieList.at(i) = *updatedMovieList.at(i);

                }

                unsigned int size = movieList.size();

                for (int i = updatedMovieList.size(); i < size; i++)
                {

                    movieList.pop_back();

                }

            }
            else
            {

                continue;

            }

        }
        else if (stoi(searchChoice) == 3) 
        {

            cout << "\nEnter Movie Name:";
            string movieTitle;
            getline(cin, movieTitle);
            Movie_Vertex *movie = graph.findTitleBDS(ptr, movieTitle);
            if (movie != nullptr) 
            {
            
                displayMovie(*movie);

                cout << "Is this the movie you wanted? (y / n)" << endl;
                string answer;
                getline(cin, answer);
                if (answer == "y")
                {

                    movieFound = true;

                }

            }
            else 
            {
            
                continue;

            }
            
        }
        else if (stoi(searchChoice) == 4) 
        {

            Movie_Vertex* movie = graph.randomMovie(ptr);
            if (movie != nullptr)
            {

                displayMovie(*movie);
                
                cout << "\nIs this the movie you wanted? (y / n)" << endl;
                string answer;
                getline(cin, answer);
                if (answer == "y")
                {

                    movieFound = true;

                }

            }
            else
            {

                continue;

            }


        }
        else if (stoi(searchChoice) == 5)
        {
        movieList = reset;
        }
        else 
        {
        
            cout << "\nInvalid Input!\n\n";

        }

    }

    cout << "\nThanks for riding the movie carosel!" << endl;

    return 0;

}
