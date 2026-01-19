/*
Author: Rachel Luo

Desc: Inspired by lecture on de Brujin approach to piecing together DNA sequences from k-mers

Input: file path to text file of k-mers of equal length, delimited by "\n"
Output: de Brujin graph representation of possible DNA strings

Example (paste this into command line):
    Input: ./sequence_constructor demo_case_3mers.txt
    Output: 
*/


#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include <map> // for DFS traversal
#include "graph.h"

using namespace std;

string dfs(Graph*, Vertex*);

int main(int argc, char** argv){
    if(argc < 2){
        cerr << "USAGE: ./sequence_constructor <PATH_TO_KMERS>" << endl;
        return 1;
    }

    /*
    The inital graph of the kmers is represented as follows:
        - a k-mer is a directed edge between two vertices, where its source is a suffix and its sink is a prefix
        - a vertex is a shared prefix/suffix of 2 or more k-mers of length k - 1 
    */ 

    // First, parse all k-mers from the file
    ifstream infile(argv[1]);

    if(!infile){
        cerr << "Unable to open file" << endl;
        return 1;
    }
    
    string k_mer;
    vector<string> k_mers;

    while(infile >> k_mer){
        if(k_mer.length() < 2){
            cerr << "k-mer is of invalid length" << endl;
            return 1;
        }
        k_mers.push_back(k_mer);
    }

    //vector<string> n_fixes;
    Graph* possible_sequences = new Graph();

    for (string k_mer: k_mers){
        string prefix = k_mer.substr(0, k_mer.length() - 1); // left half of the string
        string suffix = k_mer.substr(1); // right half of the string

        Vertex* suffix_node = possible_sequences->insert_vertex(suffix);
        Vertex* prefix_node = possible_sequences->insert_vertex(prefix);

        Edge* k_edge = new Edge(k_mer);
        k_edge->add_neighbor(suffix_node); // direct the edge to the suffix

        prefix_node->add_edge(k_edge); // Link the k_mer to point out the prefix
    }

    // Graph has been constructed, find root node and traverse
    Vertex* root = possible_sequences->get_root();

    string sequence = dfs(possible_sequences, root);
    cout << sequence << endl;

    return 0;
    
}

string dfs(Graph* g, Vertex* root){
    map<Vertex*, bool> visited;
    for(Vertex* v : g->vertices){
        visited[v] = false;
    }

    string sequence = "";
    vector<Vertex*> exploring;

    exploring.push_back(root);
    
    while (!exploring.empty()){
        Vertex* current = exploring.back();

        sequence += current->n_fix;
        exploring.pop_back();

        for (Edge* e : current->edges){
            for (Vertex* v : e->neighbors){
                if (!visited[v]){
                    exploring.push_back(v);
                }
            }
        }
    }

    return sequence;
}