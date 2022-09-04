#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>

#include "../utils/csv_files_reader.h"

using namespace std;

void get_Table(IA_NODES nodes, Node end, vector<float>& dist_to_end)
{
    for (int i = 0; i < nodes.size(); ++i)
        dist_to_end.push_back( euclideanDistance(nodes[i], end));    
}

void AStar_t()
{
    string file_name = "../datasets/AStar.csv", PATH;
    ofstream out(file_name);

    IA_NODES nodes = get_nodes_from_file();
    IA_ADJ_LIST adj = get_adj_list_from_file(nodes);

    // Input
    char beg_c, end_c;
    cout << "Start: ";
    cin >> beg_c;

    cout << "End: ";
    cin >> end_c;

    int beg{int(beg_c) - 65}, end{int(end_c) - 65}, id; 
    float min_d, aStar_op;
    bool found = false, explore = true; 
    
    vector<bool> visited;
    visited.resize(nodes.size(),false);
    visited[beg] = true;
    
    Node beg_n = nodes[beg];
    Node end_n = nodes[end];
    
    while ( (beg_n.id != end_n.id) && explore)
    {
        min_d = 99999;
        explore = false;

        for (auto x: adj[beg_n.id])
        {
            if (!visited[x.id])
            {
                
                aStar_op = euclideanDistance(beg_n, x) + euclideanDistance(x, end_n);
                
                if ( aStar_op < min_d)
                {
                    min_d = aStar_op;
                    id = x.id;
                }

            }
            explore = true;
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
