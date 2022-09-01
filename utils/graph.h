#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <cctype>
#include "./graph_manager.h"


struct Graph{
    IA_NODES nodes;
    IA_ADJ_LIST adj_list;
    IA_ADJ_MATRIX adj_matrix;
    float max_distance_between_nodes;
    
    Graph(float _distance) : max_distance_between_nodes(_distance){
        adj_list = IA_ADJ_LIST(N_NODES, IA_NODES());
        adj_matrix = IA_ADJ_MATRIX(N_NODES, vector<int>(N_NODES, 0));
        nodes = get_nodes_from_file();
        adj_matrix = get_edges(nodes, max_distance_between_nodes);
    }

    void export_adj_matrix(){
        write_adj_matrix_to_csv(adj_matrix);
    }

    void export_nodes(){
        write_nodes_to_csv(nodes);
    }

    void reset(){

        nodes.clear();
        adj_list.clear();
        adj_matrix.clear();

        adj_list = IA_ADJ_LIST(N_NODES, IA_NODES());
        adj_matrix = IA_ADJ_MATRIX(N_NODES, vector<int>(N_NODES, 0));
        
        bool ok = false;

        while(!ok){
            nodes.clear();
            create_random_coords(nodes);
            write_nodes_to_csv(nodes);

            //wait for plotting
            char key;
            cout << "Generate random coordinates again? (y/n): ";
            cin >> key;
            if(tolower(key) == 'n') ok = true;
        }

        ok = false;

        while(!ok){
            cout << "Type max distance between nodes: ";
            cin >> max_distance_between_nodes;
            adj_matrix = get_edges(nodes, max_distance_between_nodes);
            write_adj_matrix_to_csv(adj_matrix);

            //wait for plotting

            char key;
            cout << "Generate nodes connection again? (y/n): ";
            cin >> key;
            if(tolower(key) == 'n') ok = true;
        }
    }
};


#endif //__GRAPH_H__