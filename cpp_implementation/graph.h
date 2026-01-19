#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using namespace std;

class Vertex;
class Edge;
class Graph;

class Vertex {
    public:
        string n_fix;
        vector<Edge*> edges;
        int num_inbound_edges = 0;

        Vertex(string fix){
            n_fix = fix;
        }

        void add_edge(Edge* edge){
            edges.push_back(edge);
        }
};

class Edge {
    public:
        string k_mer;
        vector<Vertex*> neighbors;

        Edge(string k_edge){
            k_mer = k_edge;
        }

        void add_neighbor(Vertex* vert){
            neighbors.push_back(vert);
            vert->num_inbound_edges += 1;
        }
};

class Graph {
    public:
        vector<Vertex*> vertices;

        Vertex* insert_vertex(string); // create new Vertex in graph-- if already existing, return the Vertex
        Vertex* find_vertex(string); // finds a Vertex with the given value
        Vertex* get_root(); // finds a possible starting Vertex -- NULL if nonexistent

};

#endif