#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

#define LIMIT_X 100
#define LIMIT_Y 100
#define N_NODES 26

struct Node{
    int x, y, id;
    Node(int _x, int _y, int _id)
        : x(_x), y(_y), id(_id)
    {}
};


int main(){
    srand (time(NULL));
    vector<Node> nodes;
    
    string file_name = "random_coords.csv";

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