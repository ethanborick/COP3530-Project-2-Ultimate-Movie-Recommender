#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <iterator>
#include <ctime>
#include <unordered_set>
#include <queue>
using namespace std;

struct MovieNode {
    string name;
    int movie_index;
    double total_rating = 0;
    int rating_count = 0;
    double avg_rating;
    unordered_set<int> genres;

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
            genres.insert(map[genre]);
        }
    }
};

class MovieGraph {
    // //insertion function     FROM LECTURE SLIDES, influenced uncommented code below
    // int no_lines;
    // string from, to, wt;
    // map<string, vector<pair<string,int>>> graph;
    // map<string, vector<pair<string,int>>>::iterator it;
    
    // cin >> no_lines;
    
    // for(int i = 0; i < no_lines; i++)
    // {
    //     cin >> from >> to >> wt;
        
    //     //Creating adjacency list
    //     graph[from].push_back(make_pair(to, stoi(wt)));
        
    //     if (graph.find(to)==graph.end())
    //     {
    //         graph[to] = {};
    //     }
    // }
    map<string, vector<MovieNode*>> graph;
    map<int, string> g = { // for printing genres to the front end
            {0, "Action"}, {1, "Adventure"}, {2, "Animation"},
            {3, "Children"}, {4, "Comedy"}, {5, "Crime"},
            {6, "Documentary"}, {7, "Drama"}, {8, "Fantasy"},
            {9, "Film-Noir"}, {10, "Horror"}, {11, "IMAX"},
            {12, "Musical"}, {13, "Mystery"}, {14, "Romance"},
            {15, "Sci-Fi"}, {16, "Thriller"}, {17, "War"},
            {18, "Western"}
    };
    public:


    //undirected graph
    void insertEdge(MovieNode* from, MovieNode* to) {
        graph[from->name].push_back(to);
        graph[to->name].push_back(from);
    }

    void buildGraph(const map<string, MovieNode*>& movies) {
        vector<MovieNode*> titles;
        for (auto& pair : movies) {
            titles.push_back(pair.second);
        }

        //random edges
        srand(time(nullptr));
        for (auto& from : titles) {
            int connections = rand() % 3 + 1; //1–3 random connections, keep sparse since using adjacency list
            for (int i = 0; i < connections; i++) {
                MovieNode* to = titles[rand() % titles.size()];
                if (to != from)
                    insertEdge(from, to);
            }
        } 
    }

    void printGraph() {
        int i = 0;
        for (auto it = graph.begin(); it != graph.end(); ++it, ++i) {
            cout << it->first << " -> ";
            for (int j = 0; j < it->second.size(); j++) {
                cout << "(" << it->second[j]->name << ") ";
            }
            cout << endl;
        }
    }
    void bfs(MovieNode* target, MovieNode* src) {
        int counter = 0;
        int nodes_visited = 0; // testing
        unordered_set<MovieNode*> visited;
        queue<MovieNode*> q;
        visited.insert(src);
        q.push(src);
        while (!q.empty()) {
            nodes_visited++; // testing
            MovieNode* m = q.front();
            q.pop();
            if (m == target) continue;
            int genres_in_common = 0;
            for (auto it = m->genres.begin(); it != m->genres.end(); it++) {
                if (target->genres.count(*it) != 0) {
                    genres_in_common++;
                }
            }
            double movie_score = m->avg_rating + genres_in_common;
            if (movie_score >= 8) {
                // need to add cout statements to print movie info
                counter++;
                if (counter == 10) {
                    break;
                }
            }
            vector<MovieNode*> neighbors = graph[m->name];
            for (MovieNode* p: neighbors) {
                if (visited.count(p) == 0) {
                    visited.insert(p);
                    q.push(p);
                }
            }
        }
        cout << nodes_visited << endl; // testing
    }
};
