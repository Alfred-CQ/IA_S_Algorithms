#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>

#include "../utils/csv_files_reader.h"
#include "../utils/graph.h"

using namespace std;

void get_Table(IA_NODES nodes, Node end, vector<float>& dist_to_end)
{
    for (int i = 0; i < nodes.size(); ++i)
        dist_to_end.push_back( euclideanDistance(nodes[i], end));    
}

void AStar_t(Graph* G, int beg, int end)
{
    
    cout << " -- A* algorithm --" << '\n'; 

    string file_name = "../datasets/AStar_path.csv",
           file_exp  = "../datasets/AStar_expn.csv",
           PATH;

    ofstream out(file_name);
    ofstream out_exp(file_exp);

    out_exp<<"from,to\n";

    cout << char(G->nodes[beg].id + 65) << "->";
        
    PATH.push_back(char(G->nodes[beg].id + 65));
    
    int id;
    float min_d, aStar_op;
    bool found = false, explore = true; 
    
    vector<bool> visited;
    visited.resize(G->nodes.size(),false);
    visited[beg] = true;
    
    Node beg_n = G->nodes[beg];
    Node end_n = G->nodes[end];
    
    while ( (beg_n.id != end_n.id) && explore)
    {
        min_d = 99999;
        explore = false;

        for (auto x: G->adj_list[beg_n.id])
        {
            if (!visited[x.id])
            {
                
                aStar_op = euclideanDistance(beg_n, x) + euclideanDistance(x, end_n);
                
                if ( aStar_op < min_d)
                {
                    min_d = aStar_op;
                    id = x.id;
                }

                out_exp << char(beg_n.id + 65) << "," << char(x.id + 65) << '\n';
            
            }
            explore = true;
        }
        
        visited[id] = true;
        
        cout << char(G->nodes[id].id + 65) << "->";
        
        PATH.push_back(char(id + 65));

        beg_n = G->nodes[id];
    }
    
    out<<"label\n";
    for(auto c : PATH)
        out<<c<<"\n";
    
    found = (beg_n.id == end_n.id);

    if (found)
        cout << "END\nFound!" << endl;
    else
        cout << "\nNot Found!" << endl;

    out_exp.close();
    out.close();
}
