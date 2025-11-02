#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include "movie.h"

using namespace std;

int main(int argc, char* argv[]) {

    ifstream file("ml-latest-small/moviedata.csv");
    if (!file.is_open()) {  //this was for debugging, can probably delete now
        cout << "Error: Could not open moviedata.csv" << endl;
        return 1;
    }
    string line;
    map<string, MovieNode*> rating_counts;
    while (getline(file, line)) {
        stringstream stream(line);
        string id, name, genres, rating;
        getline(stream, id, ',');

        //handling quoted and unquoted movie names
            //quoted movie names have commas inside them
        if (stream.peek() == '"') {
            stream.get();
            getline(stream, name, '"');

            size_t pos = 0;
            while ((pos = name.find("\"\"", pos)) != string::npos) {
                name.replace(pos, 2, "\"");
                ++pos;
            }

            if (stream.peek() == ',') stream.get();
        }
        else {
            getline(stream, name, ',');
        }

        getline(stream, genres, ',');
        getline(stream, rating);

        int movieId = stoi(id);
        double ratingVal = stod(rating);
        if (rating_counts.find(name) == rating_counts.end()) {
            rating_counts[name] = new MovieNode(name, movieId, genres);
        }
        rating_counts[name]->rating_count++;
        rating_counts[name]->total_rating += ratingVal;
    }
    
    for (auto it = rating_counts.begin(); it != rating_counts.end(); it++) {
        MovieNode* movie = it->second;
        movie->avg_rating = movie->total_rating / double(movie->rating_count);
    }

    MovieGraph graph;
    graph.buildGraph(rating_counts);
    //graph.printGraph();
    // testing bfs
    graph.bfs(rating_counts["Toy Story (1995)"], rating_counts["Mission: Impossible (1996)"]);
    graph.dfs(rating_counts["Toy Story (1995)"], rating_counts["Mission: Impossible (1996)"]);


    // string input = argv[1];
    // string traversal = argv[2];
    // int time = 1;

    // cout << "Time taken for " << traversal << ": " << time << endl;
    // for (int i = 1; i < 11; i++) {
    //     cout << i << ".) " << input << endl;
    //     cout << "   Genre: genre" << endl;
    //     cout << "   Average Rating: 00%" << endl;
    // }
    return 0;
}