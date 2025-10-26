#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "movie.h"
using namespace std;

int main() {
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
        rating_counts[name]->rating_count++;
        rating_counts[name]->total_rating += stod(rating);
    }
    for (auto it = rating_counts.begin(); it != rating_counts.end(); it++) {
        MovieNode* movie = it->second;
        movie->avg_rating = movie->total_rating / double(movie->rating_count);
    }
    // loop through the map and insert each movie node into the graph
    return 0;
}
