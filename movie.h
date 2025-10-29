#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

struct MovieNode {
    string name;
    int movie_index;
    double total_rating = 0;
    int rating_count = 0;
    double avg_rating;
    vector<int> genres;

    MovieNode(string n, int index, string genre_string) {
        name = n;
        movie_index = index;
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

class MovieGraph { // https://edugator.app/courses/2eff7d57-3f4b-4297-ac6c-0bb5ce67348b/lesson/20e56cf4-13ca-4482-a492-26b779ebc746
    int movie_count;
    unordered_map<MovieNode*, int> vertex_to_index;
    unordered_map<int, MovieNode*> index_to_vertex;
    vector<vector<int>> adjacency_matrix;
    public:
        MovieGraph(int movie_count) {
            adjacency_matrix = vector<vector<int>>(movie_count, vector<int>(movie_count, 0));
        }
};
