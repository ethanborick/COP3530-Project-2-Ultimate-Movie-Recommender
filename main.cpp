#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "movie.h"
using namespace std;

int main() {
    ifstream file("../ml-latest-small/moviedata.csv");
    string line;
    unordered_map<MovieNode*, int> vertex_to_index;
    unordered_map<int, MovieNode*> index_to_vertex;
    unordered_map<string, MovieNode*> rating_counts;
    int index_counter = 0;
    while (getline(file, line)) {
        stringstream stream(line);
        string id, name, genres, rating;
        getline(stream, id, ',');
        getline(stream, name, ',');
        getline(stream, genres, ',');
        getline(stream, rating, ',');
        if (rating_counts.find(name) == rating_counts.end()) {
            MovieNode* movie = new MovieNode(name, index_counter, genres);
            rating_counts[name] = movie;
            vertex_to_index[movie] = index_counter;
            index_to_vertex[index_counter] = movie;
            index_counter++;
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
