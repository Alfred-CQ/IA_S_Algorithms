#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "./graph_manager.h"

struct Graph{
    IA_NODES nodes;
    IA_ADJ_LIST adj_list;
    IA_ADJ_MATRIX adj_matrix;
    float max_distance_between_nodes;
    
    Graph(float _distance, bool random = false) : max_distance_between_nodes(_distance){
        if(random) create_random_coords(nodes);
        adj_matrix = IA_ADJ_MATRIX(N_NODES, vector<int>(N_NODES, 0));
        nodes = get_nodes_from_file();
        adj_matrix = get_edges(nodes, max_distance_between_nodes);
        warrant_no_orphan_nodes(adj_matrix);
    }

    void export_adj_matrix(){
        write_adj_matrix_to_csv(adj_matrix);
    }

    void export_nodes(){
        write_nodes_to_csv(nodes);
    }
};


#endif //__GRAPH_H__