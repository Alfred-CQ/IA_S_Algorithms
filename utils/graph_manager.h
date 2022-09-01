#ifndef __GRAPH_MANAGER_H__
#define __GRAPH_MANAGER_H__

#include <fstream>
#include "./csv_files_reader.h"
#include "./utils.h"

void create_random_coords(IA_NODES &nodes){
    srand (time(NULL));

    for(int i = 0; i < N_NODES; i++)
    {
        int _x = -1 * (rand() % 2 ? -1 : 1) * rand() % LIMIT_X;
        int _y = -1 * (rand() % 2 ? -1 : 1) * rand() % LIMIT_Y;
        Node temp(_x, _y, i);
        nodes.push_back(temp);
    }
    
}

void warrant_no_orphan_nodes(IA_ADJ_MATRIX &adj_matrix){
    for(int i = 0; i < N_NODES; i++){
        int sum = 0;
        for(int j = 0; j < N_NODES; j++){
            sum += adj_matrix[i][j];
        }
        if(sum == 0){
            srand (time(NULL));
            int target_node;
            do{
                target_node = rand() % N_NODES;
            } while(target_node == i);
            adj_matrix[i][target_node] = adj_matrix[target_node][i] = 1;
        }
    }
}

IA_ADJ_MATRIX get_edges(const IA_NODES &nodes, const float epsilon){
    
    IA_ADJ_MATRIX adj_matrix(N_NODES, vector<int>(N_NODES, 0));

    for(int i = 0; i < N_NODES; i++){
        for(int j = i + 1; j < N_NODES; j++){
            if(euclideanDistance(nodes[i], nodes[j]) <= epsilon){
                adj_matrix[i][j] = adj_matrix[j][i] = 1;
            }
        }
    }

    warrant_no_orphan_nodes(adj_matrix);

    return adj_matrix;
}

void write_nodes_to_csv(const IA_NODES &nodes){
    ofstream out(COORDS_PATH);
    out<<"x,y\n";

    for(int i = 0; i < N_NODES; i++)
    {
        out << nodes[i].x << "," << nodes[i].y << "\n";
    }
    
    out.close();
}

void write_adj_matrix_to_csv(const IA_ADJ_MATRIX &adj_matrix){
    ofstream out(MATRIX_PATH);

    for(int i = 0; i < N_NODES - 1; i++){
        out << get_node_name(i) << ",";
    }

    out << "Z\n";

    for(int i = 0; i < N_NODES; i++){
        for(int j = 0; j < N_NODES - 1; j++){
            out << adj_matrix[i][j] << ",";
        }
        out << adj_matrix[i][N_NODES - 1] << "\n";
    }
    out.close();
}

#endif //__GRAPH_MANAGER_H__