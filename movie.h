#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <iterator>
#include <ctime>
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

    public:
    map<string, vector<string>> graph;

    //undirected graph
    void insertEdge(const string& from, const string& to, int weight) {
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    void buildGraph(const map<string, MovieNode*>& movies) {
        vector<string> titles;
        for (auto& pair : movies) {
            titles.push_back(pair.first);
        }

        //random edges
        srand(time(nullptr));
        for (auto& from : titles) {
            int connections = rand() % 3 + 1; //1–3 random connections, keep sparse since using adjacency list
            for (int i = 0; i < connections; i++) {
                string to = titles[rand() % titles.size()];
                if (to != from)
                    insertEdge(from, to, 1); //weight = 1 for all edges: unweighted graph
            }
        } 
    }

    void printGraph() {
        int i = 0;
        for (auto it = graph.begin(); it != graph.end(); ++it, ++i) {
            cout << it->first << " -> ";
            for (int j = 0; j < it->second.size(); j++) {
                cout << "(" << it->second[j] << ") ";
            }
            cout << endl;
        }
    }
    // //search functions

};
