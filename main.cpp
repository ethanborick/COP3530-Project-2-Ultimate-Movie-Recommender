#include <iostream>
#include <string>
//#include <fstream>
//#include <sstream>
//#include <map>
//#include "movie.h"

using namespace std;

int main() {
    /*
    ifstream file("../ml-latest-small/moviedata.csv");
    string line;
    map<string, MovieNode*> rating_counts;
    while (getline(file, line)) {
        stringstream stream(line);
        string id, name, genres, rating;
        getline(stream, id, ',');
        getline(stream, name, ',');
        getline(stream, genres, ',');
        getline(stream, rating, ',');
        if (rating_counts.find(name) == rating_counts.end()) {
            rating_counts[name] = new MovieNode(name, stoi(id), genres);
        }
        else {
            rating_counts[name]->rating_count++;
            rating_counts[name]->total_rating += stod(rating);
        }
    }
    */
    // loop through the map and calculate each movies average rating
    // loop through the map and insert each movie node into the graph

    string input;
    getline(cin, input); // Read input from standard input
    cout << "Hello, " << input << "! This is output from the C++ program." << endl;
    return 0;
}
