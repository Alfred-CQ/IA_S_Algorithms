#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include "./csv_files_reader.h"

using namespace std;

#define LIMIT_X 100
#define LIMIT_Y 100
#define N_NODES 26

IA_NODES nodes;
int matrix[N_NODES][N_NODES];

void create_random_coords(){
    srand (time(NULL));
    
    string file_name = "../datasets/random_coords.csv";

    ofstream out(file_name);
    out<<"x,y\n";
    for(int i = 0; i < N_NODES; i++)
    {
        int _x = -1 * (rand() % 2 ? -1 : 1) * rand() % LIMIT_X;
        int _y = -1 * (rand() % 2 ? -1 : 1) * rand() % LIMIT_Y;
        Node temp(_x, _y, i);
        nodes.push_back(temp);
    }
    
    for(int i = 0; i < N_NODES; i++)
    {
        out << nodes[i].x << "," << nodes[i].y << "\n";
    }
    
    out.close();
}

float euclideanDistance(Node one, Node two){
    float result = 0.0f;
    result += (((one.x - two.x) * (one.x - two.x)) + (one.y - two.y) * (one.y - two.y));
    return sqrt(result);
}

void warrant_no_orphan_nodes(){
    for(int i = 0; i < N_NODES; i++){
        int sum = 0;
        for(int j = 0; j < N_NODES; j++){
            sum += matrix[i][j];
        }
        if(sum == 0){
            srand (time(NULL));
            int target_node;
            do{
                target_node = rand() % N_NODES;
            } while(target_node == i);
            matrix[i][target_node] = matrix[target_node][i] = 1;
        }
    }
    
}

void get_edges(float epsilon){
    
    memset(matrix, 0, sizeof(matrix));

    for(int i = 0; i < N_NODES; i++){
        for(int j = i + 1; j < N_NODES; j++){
            if(euclideanDistance(nodes[i], nodes[j]) <= epsilon){
                matrix[i][j] = matrix[j][i] = 1;
            }
        }
    }
}

void write_adj_matrix_to_csv(){
    string file_name = "../datasets/ady_matrix.csv";

    ofstream out(file_name);

    for(int i = 0; i < N_NODES - 1; i++){
        out << get_node_name(i) << ",";
    }

    out << "Z\n";

    for(int i = 0; i < N_NODES; i++){
        for(int j = 0; j < N_NODES - 1; j++){
            out << matrix[i][j] << ",";
        }
        out << matrix[i][N_NODES - 1] << "\n";
    }
    out.close();
}

int main(){
    //create_random_coords(); //uncomment only if necessary
    nodes = get_nodes_from_file();
    get_edges(65.80f);
    warrant_no_orphan_nodes();
    write_adj_matrix_to_csv();
}