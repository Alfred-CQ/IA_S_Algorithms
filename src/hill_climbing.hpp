#include <iostream>
#include <fstream>
#include <queue>

#include "../utils/csv_files_reader.h"

using namespace std;

void hill_climbing (){
    string file_name = "../datasets/BFS.csv", PATH;
    ofstream out(file_name);

    IA_NODES nodes = get_nodes_from_file();
    IA_ADJ_LIST adj = get_adj_list_from_file(nodes);
    //Input
    char beg_c, end_c;
    cout << "Start: ";
    cin >> beg_c;

    cout << "End: ";
    cin >> end_c;

    int beg{int(beg_c) - 65}, end{int(end_c) - 65}, id; 
    int min_d, dist_here;
    bool found = false;

    vector<bool> visited;
    //queue<Node> myQueue;

    visited.resize(nodes.size(),false);
    visited[beg] = true;
    bool explored = true;

    //myQueue.push(nodes[beg]);

    Node beg_n = nodes[beg];
    Node end_n = nodes[end];

    while (beg_n.id != end_n.id && explored) {
        min_d = 99999;
        explored = false;
        for (auto x: adj[beg_n.id]) {
            if (!visited[x.id]) {
                dist_here = euclideanDistance(x, end_n);
                if (dist_here < min_d) {
                    min_d = dist_here;
                    id = x.id;
                }
            }
            explored = true;
        }
        visited[id] = true;

        cout << char(nodes[id].id + 65) << "->";
        
        PATH.push_back(char(id + 65));
        PATH.push_back(',');

        beg_n = nodes[id];
    }

    PATH.pop_back();
    out << PATH;
    
    found = beg_n.id == end_n.id;

    if (found)
        cout << "\nFound!" << endl;
    else
        cout << "\nNot Found!" << endl;

    out.close();
}