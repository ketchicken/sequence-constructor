#include "graph.h"
#include <string> 

using namespace std;

Vertex* Graph::insert_vertex(string new_fix){

    // Check if vertice first exists
    Vertex* vertice = find_vertex(new_fix);

    if (!vertice) {
        // Create a new vertice to insert 
        vertice = new Vertex(new_fix);
        vertices.push_back(vertice);
    }

    return vertice; // return the vertice
}

Vertex* Graph::find_vertex(string new_fix){
    for(Vertex* v : vertices){
        if (v->n_fix.compare(new_fix) == 0){
            return v;
        }
    }
    return NULL;
}

Vertex* Graph::get_root(){
    for(Vertex* v : vertices){
        if (v->num_inbound_edges == 0){
            return v;
        }
    }   

    return NULL;
}