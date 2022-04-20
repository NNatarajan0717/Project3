#include "Movie_Vertex.h"
#include "Graph.h"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;

void displayMovie(Movie_Vertex movie) {
    cout << "\nMovie Selected:" << endl;
    cout << "Title: " << movie.getTitle() << endl;
    cout << "Genre: " << movie.getGenre() << endl;
    cout << "Rating: " << movie.getRating() << endl;

}

void heapify(Movie_Vertex* arr, int x, int j) {
    int max = j;
    int left = 2 * j + 1;
    int right = 2 * j + 2;
    if (arr[left].getRating() > arr[max].getRating() && left < x) {
        max = left;
    }
    if (arr[right].getRating() > arr[max].getRating() && right < x) {
        max = right;
    }
    if (max != j) {
        swap(arr[j], arr[max]);
        heapify(arr, x, max);
    }
}

void createHeap(Movie_Vertex* arr, int x) {
    int firstIndex = (x / 2) - 1;
    for (int j = firstIndex; j >= 0; j--) {
        heapify(arr, x, j);
    }
}


vector<Movie_Vertex*> findRatingBDS(Movie_Vertex* arr, double min, double max, int size) {
    vector<Movie_Vertex*> checkedVerts;
    vector<Movie_Vertex*> queuedVerts;
    vector<Movie_Vertex*> matches;

    checkedVerts.push_back(&arr[0]);
    queuedVerts.push_back(&arr[0]);

    cout << "\nTraversing Heap...\n";
    while (queuedVerts.size() > 0)
    {
        // Pull movie vertex to be checked
        Movie_Vertex* vert = queuedVerts[0];
        // Remove it from vector of vertices to check
        queuedVerts.erase(queuedVerts.begin());
        cout << vert->getTitle() << "->";

        int idx;
        // Get all edges of the currently checked movie vertex
        for (int i = 0; i < size; i++)
        {
            if (arr[i].getTitle().compare(vert->getTitle()) == 0)
            {
                idx = i;
                break;
            }
        }

        // Determine if the adjacent movie has been traversed before
        bool leftChecked = false;
        bool rightChecked = false;
        for (Movie_Vertex* movie : checkedVerts)
        {
            if (idx * 2 + 2 < size)
            {
                if (movie->getTitle().compare(arr[idx * 2 + 2].getTitle()) == 0 || idx * 2 > size)
                {
                    rightChecked = true;
                }
                if (movie->getTitle().compare(arr[idx * 2 + 1].getTitle()) == 0 || idx * 2 > size)
                {
                    leftChecked = true;
                }
            }
            else
            {
                rightChecked = true;
                leftChecked = true;
            }

        }

        // Add this adjacent movie vertex to be checked since it hasn't been traversed
        if (!rightChecked)
        {
            checkedVerts.push_back(&arr[idx * 2 + 2]);
            queuedVerts.push_back(&arr[idx * 2 + 2]);
        }
        if (!leftChecked)
        {
            checkedVerts.push_back(&arr[idx * 2 + 1]);
            queuedVerts.push_back(&arr[idx * 2 + 1]);
        }

        if (vert->getRating() <= max && vert->getRating() >= min)
        {
            matches.push_back(vert);
        }
    }

    cout << endl;
    return matches;
}

vector<Movie_Vertex*> findGenreBDS(Movie_Vertex* arr, string genre, int size) {
    vector<Movie_Vertex*> checkedVerts;
    vector<Movie_Vertex*> queuedVerts;
    vector<Movie_Vertex*> matches;

    checkedVerts.push_back(&arr[0]);
    queuedVerts.push_back(&arr[0]);

    cout << "\nTraversing Heap...\n";
    while (queuedVerts.size() > 0)
    {
        // Pull movie vertex to be checked
        Movie_Vertex* vert = queuedVerts[0];
        // Remove it from vector of vertices to check
        queuedVerts.erase(queuedVerts.begin());
        cout << vert->getTitle() << "->";

        int idx;
        // Get all edges of the currently checked movie vertex
        for (int i = 0; i < size; i++)
        {
            if (arr[i].getTitle().compare(vert->getTitle()) == 0)
            {
                idx = i;
                break;
            }
        }

        // Determine if the adjacent movie has been traversed before
        bool leftChecked = false;
        bool rightChecked = false;
        for (Movie_Vertex* movie : checkedVerts)
        {
            if (idx * 2 + 2 < size)
            {
                if (movie->getTitle().compare(arr[idx * 2 + 2].getTitle()) == 0 || idx * 2 > size)
                {
                    rightChecked = true;
                }
                if (movie->getTitle().compare(arr[idx * 2 + 1].getTitle()) == 0 || idx * 2 > size)
                {
                    leftChecked = true;
                }
            }
            else
            {
                rightChecked = true;
                leftChecked = true;
            }

        }

        // Add this adjacent movie vertex to be checked since it hasn't been traversed
        if (!rightChecked)
        {
            checkedVerts.push_back(&arr[idx * 2 + 2]);
            queuedVerts.push_back(&arr[idx * 2 + 2]);
        }
        if (!leftChecked)
        {
            checkedVerts.push_back(&arr[idx * 2 + 1]);
            queuedVerts.push_back(&arr[idx * 2 + 1]);
        }

        if (vert->getGenre().compare(genre) == 0)
        {
            matches.push_back(vert);
        }
    }

    cout << endl;
    return matches;
}

Movie_Vertex* findTitleBDS(Movie_Vertex* arr, string title, int size) {
    vector<Movie_Vertex*> checkedVerts;
    vector<Movie_Vertex*> queuedVerts;

    checkedVerts.push_back(&arr[0]);
    queuedVerts.push_back(&arr[0]);

    int count = 1;

    cout << "Traversing Heap...\n";
    while (queuedVerts.size() > 0)
    {
        // Pull movie vertex to be checked
        Movie_Vertex* vert = queuedVerts[0];
        // Remove it from vector of vertices to check
        queuedVerts.erase(queuedVerts.begin());
        cout << vert->getTitle() << "->";

        int idx;
        // Get all edges of the currently checked movie vertex
        for (int i = 0; i < size; i++)
        {
            if (arr[i].getTitle().compare(vert->getTitle()) == 0)
            {
                idx = i;
                break;
            }
        }

        // Determine if the adjacent movie has been traversed before
        bool leftChecked = false;
        bool rightChecked = false;
        for (Movie_Vertex* movie : checkedVerts)
        {
            if (idx * 2 + 2 < size)
            {
                if (movie->getTitle().compare(arr[idx * 2 + 2].getTitle()) == 0 || idx * 2 > size)
                {
                    rightChecked = true;
                }
                if (movie->getTitle().compare(arr[idx * 2 + 1].getTitle()) == 0 || idx * 2 > size)
                {
                    leftChecked = true;
                }
            }
            else
            {
                rightChecked = true;
                leftChecked = true;
            }

        }

        // Add this adjacent movie vertex to be checked since it hasn't been traversed
        if (!rightChecked)
        {
            checkedVerts.push_back(&arr[idx * 2 + 2]);
            queuedVerts.push_back(&arr[idx * 2 + 2]);
        }
        if (!leftChecked)
        {
            checkedVerts.push_back(&arr[idx * 2 + 1]);
            queuedVerts.push_back(&arr[idx * 2 + 1]);
        }

        if (vert->getTitle().compare(title) == 0)
        {
            cout << endl;
            return vert;
        }
    }

    return nullptr;
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
    for (int i = 0; i < 100000; i++)
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
    cout << "Welcome to the Movie Carousel!\n\n";

    bool movieFound = false;

    vector<Movie_Vertex> reset = movieList;

    while (!movieFound)
    {

        cout << "Search Space Size: " << movieList.size() << endl;
        
        Movie_Vertex* heap[100000];

        for (int i = 0; i < 100000; i++) 
        {

            if (i < movieList.size()) 
            {
            
                heap[i] = &movieList.at(i);

            }

        }

        createHeap(*heap, 100000);

        Graph graph("", movieList);

        Graph* ptr = &graph;

        cout << "\nChoose an option to start:\n\nSearch by rating (enter: 1)\nSearch by genre (enter: 2)\nSearch by name (enter: 3)\nSearch for a random movie (enter: 4)\nReset Search Space\noption:";

        //stores user input choice option
        string searchChoice;

        getline(cin, searchChoice);

        //search by Rating
        if (stoi(searchChoice) == 1)
        {

            //upper and lower bound ranges are given by user input
            string upperBound, lowerBound;
            cout << "\nEnter Upperbound (0.0 - 10.0): ";
            getline(cin, upperBound);
            cout << "Enter Lowerbound (0.0 - 10.0): ";
            getline(cin, lowerBound);

            //run heap search and display time taken
            auto heapStart = chrono::steady_clock::now();
            findRatingBDS(*heap, stod(lowerBound), stod(upperBound), 100000);
            auto heapEnd = chrono::steady_clock::now();

            cout << "\nTime taken for Heap Search: " << chrono::duration_cast<chrono::nanoseconds>(heapEnd - heapStart).count() << " ns\n";

            //run graph depth-first-search and display time taken
            auto graphStart = chrono::steady_clock::now();
            vector<Movie_Vertex*> updatedMovieList = graph.findRatingBDS(ptr, stod(lowerBound), stod(upperBound));
            auto graphEnd = chrono::steady_clock::now();

            cout << "\nTime taken for Graph Search: " << chrono::duration_cast<chrono::nanoseconds>(graphEnd - graphStart).count() << " ns\n";

            cout << "\nMovie titles found with a rating between " << lowerBound << " - " << upperBound << ":" << endl;

            //Display Updated Search Space based on Search by Genre y Rating
            for (int i = 0; i < updatedMovieList.size(); i++)
            {

                cout << updatedMovieList.at(i)->getTitle() << endl;

            }

            cout << "\nWould you like to continue searching among these titles? (y / n)" << endl;
            string answer;
            getline(cin, answer);
            //Shortens search base to movies found by the Search By Rating function
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
        //Search By Genre
        else if (stoi(searchChoice) == 2)
        {

            string genre;
            cout << "\nEnter Genre: ";
            getline(cin, genre);

            //Run Heap Search and Display time taken
            auto heapStart = chrono::steady_clock::now();
            findGenreBDS(*heap, genre, 100000);
            auto heapEnd = chrono::steady_clock::now();

            cout << "\nTime taken for Heap Search: " << chrono::duration_cast<chrono::nanoseconds>(heapEnd - heapStart).count() << " ns\n";

            //Run Depth First Search on Graph and display time taken
            auto graphStart = chrono::steady_clock::now();
            vector<Movie_Vertex*> updatedMovieList = graph.findGenreBDS(ptr, genre);
            auto graphEnd = chrono::steady_clock::now();

            cout << "\nTime taken for Graph Search: " << chrono::duration_cast<chrono::nanoseconds>(graphEnd - graphStart).count() << " ns\n";

            cout << "\n\nMovie titles under " << genre << ":" << endl;

            //Display movies found under the Genre Specified
            for (int i = 0; i < updatedMovieList.size(); i++)
            {

                cout << updatedMovieList.at(i)->getTitle() << endl;

            }

            cout << "\nWould you like to continue searching among these titles? (y / n)" << endl;
            string answer;
            getline(cin, answer);
            //Shorten search space to the movies founder under this genre
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
        //Search By Name
        else if (stoi(searchChoice) == 3)
        {

            cout << "\nEnter Movie Name:";
            string movieTitle;
            getline(cin, movieTitle);

            //Run Heap Search and Display Time taken
            auto heapStart = chrono::steady_clock::now();
            findTitleBDS(*heap, movieTitle, 100000);
            auto heapEnd = chrono::steady_clock::now();

            cout << "\nTime taken for Heap Search: " << chrono::duration_cast<chrono::nanoseconds>(heapEnd - heapStart).count() << " ns\n";

            //Run Depth First Search on Graph and Display time taken
            auto graphStart = chrono::steady_clock::now();
            Movie_Vertex* movie = graph.findTitleBDS(ptr, movieTitle);
            auto graphEnd = chrono::steady_clock::now();

            cout << "\nTime taken for Graph Search: " << chrono::duration_cast<chrono::nanoseconds>(graphEnd - graphStart).count() << " ns\n";

            //If movie title is found, display its information
            if (movie != nullptr)
            {

                displayMovie(*movie);

                //If movie found is the movie that the movie wants, terminate the program
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
        //Search For Random Movie
        else if (stoi(searchChoice) == 4)
        {

            //Run Depth First Search and display time taken
            auto graphStart = chrono::steady_clock::now();
            Movie_Vertex* movie = graph.randomMovie(ptr);
            auto graphEnd = chrono::steady_clock::now();
            
            //Run Heap Search and display time taken
            auto heapStart = chrono::steady_clock::now();
            findTitleBDS(*heap, movie->getTitle(), 100000);
            auto heapEnd = chrono::steady_clock::now();

            cout << "\nTime taken for Heap Search: " << chrono::duration_cast<chrono::nanoseconds>(heapEnd - heapStart).count() << " ns\n";
            cout << "\nTime taken for Graph Search: " << chrono::duration_cast<chrono::nanoseconds>(graphEnd - graphStart).count() << " ns\n";


            //Display contents of Random Movie
            if (movie != nullptr)
            {

                displayMovie(*movie);

                cout << "\nIs this the movie you wanted? (y / n)" << endl;
                string answer;
                getline(cin, answer);
                //if the movie selected is the movie wanted by the user, terminate the program
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
        //Reset Search Space
        else if (stoi(searchChoice) == 5)
        {
            movieList = reset;
        }
        //Alert user that selection choice is invalid
        else
        {

            cout << "\nInvalid Input!\n\n";

        }

    }

    cout << "\nThanks for riding the Movie Carousel!" << endl;

    return 0;

}
