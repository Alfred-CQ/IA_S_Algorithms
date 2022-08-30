#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

#define COORDS_PATH "../datasets/random_coords.csv"
#define MATRIX_PATH "../datasets/ady_matrix.csv"
#define N_NODES 26

char limiter = ',';

struct Node{
    int x, y, id;
    Node(int _x, int _y, int _id)
        : x(_x), y(_y), id(_id)
    {}
};

typedef vector<Node>            IA_NODES;
typedef vector<vector<Node>>    IA_ADJ_LIST;

vector<Node> get_nodes_from_file(){
    vector<Node> nodes;
    
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

vector<bool> splitString(string s, int n_data){
    vector<bool> tokens;
    for(int i = 0, j = 0; i < n_data; i++, j+=2){
        tokens.push_back(atoi(&s[j]));
    }
    return tokens;
}

vector<vector<Node>> get_adj_list_from_file(const IA_NODES& nodes){
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
