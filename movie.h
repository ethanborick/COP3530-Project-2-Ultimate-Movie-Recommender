#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

struct MovieNode {
    string name;
    int movieID;
    double total_rating = 0;
    int rating_count = 0;
    double avg_rating;
    vector<int> genres;

    MovieNode(string n, int id, string genre_string) {
        name = n;
        movieID = id;
        map<string, int> map = {
                {"Action", 0}, {"Adventure", 1}, {"Animation", 2},
                {"Children", 3}, {"Comedy", 4}, {"Crime", 5},
                {"Documentary", 6}, {"Drama", 7}, {"Fantasy", 8},
                {"Film-Noir", 9}, {"Horror", 10}, {"IMAX", 11},
                {"Musical", 12}, {"Mystery", 13}, {"Romance", 14},
                {"Sci-Fi", 15}, {"Thriller", 16}, {"War", 17},
                {"Western", 18}
        };
        istringstream stream(genre_string);
        string genre;
        while (getline(stream, genre, '|')) {
            genres.push_back(map[genre]);
        }
    }
};

class MovieGraph {

};
