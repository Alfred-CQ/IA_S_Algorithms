#ifndef __CSV_READER_H__
#define __CSV_READER_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "./utils.h"

IA_NODES get_nodes_from_file(){
    IA_NODES nodes;
    
    ifstream file(COORDS_PATH);
    string line;
    
    getline(file, line);
    int idx = 0;
    while(getline(file, line))
    {
        stringstream stream(line);
        string x, y;
        getline(stream, x, limiter);
        getline(stream, y, limiter);
        int _x, _y;
        _x = stoi(x);
        _y = stoi(y);
        Node temp(_x, _y, idx);
        nodes.push_back(temp);
        idx++;
    }

    return nodes;
}

IA_ADJ_LIST get_adj_list_from_file(const IA_NODES& nodes){
    vector<vector<Node>> adj_list(N_NODES, vector<Node>());
    ifstream file(MATRIX_PATH);
    string line;
    vector<bool> tokens;
    getline(file, line);
    int cur_node = 0;
    while(getline(file,line)){
        tokens = splitString(line, N_NODES);
        for(int i = 0; i < tokens.size(); i++){
            if(tokens[i]){
                adj_list[cur_node].push_back(nodes[i]);
            }
        }
        cur_node++;
    }
    return adj_list;
}

void test(){
    IA_NODES nodes = get_nodes_from_file();
    IA_ADJ_LIST adj_list = get_adj_list_from_file(nodes);

    cout << "[TESTING NODES COORDINATES] . . .\n";

    for(size_t i = 0; i < nodes.size(); i++){
        cout << "[" << nodes[i].id <<"] -> ("<<nodes[i].x<<", "<<nodes[i].y<<")"<<"\n";
    }

    cout<< "\n[DONE]\n";

    cout << "\n\n[TESTING ADJACENCY LIST EDGES] . . . \n";

    for(int i = 0; i < adj_list.size(); i++){
        cout<< "[" << get_node_name(i) <<"] -> ";
        for(auto e : adj_list[i]){
            cout<<get_node_name(e.id)<<"->";
        }
        cout<<"\n";
    }

    cout<< "\n[DONE]\n";
}

#endif //__CSV_READER_H__