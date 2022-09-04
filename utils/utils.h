#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <cmath>
#include <string>

using namespace std;

#define COORDS_PATH "../datasets/random_coords.csv"
#define MATRIX_PATH "../datasets/ady_matrix.csv"
#define LIMIT_X 100
#define LIMIT_Y 100
#define N_NODES 26

char limiter = ',';

struct Node{
    int x, y, id;
    Node(){}
    Node(int _x, int _y, int _id)
        : x(_x), y(_y), id(_id)
    {}
};

struct Edge{
    Node from, to;
    Edge() {}
    Edge(Node _from, Node _to)
        : from(_from), to(_to)
    {}
};


typedef vector<Node>            IA_NODES;
typedef vector<vector<Node>>    IA_ADJ_LIST;
typedef vector<vector<int>>     IA_ADJ_MATRIX;

char get_node_name(int i){
    return char(i + 65);
}

float euclideanDistance(Node one, Node two){
    float result = 0.0f;
    result += (((one.x - two.x) * (one.x - two.x)) + (one.y - two.y) * (one.y - two.y));
    return sqrt(result);
}

vector<bool> splitString(string s, int n_data){
    vector<bool> tokens;
    for(int i = 0, j = 0; i < n_data; i++, j+=2){
        tokens.push_back(atoi(&s[j]));
    }
    return tokens;
}

#endif //__UTILS_H__
