#include <iostream>
#include <fstream>
#include <queue>

#include "../utils/csv_files_reader.h"
#include "../utils/graph.h"

void hill_climbing (Graph* G, int beg, int end)
{
    string file_name = "../datasets/HC_path.csv",
           file_exp  = "../datasets/HC_expn.csv",
           PATH;

    ofstream out(file_name);
    ofstream out_exp(file_exp);

    int id, min_d, dist_here;
    bool found = false;



    vector<bool> visited;

    visited.resize(G->nodes.size(),false);
    visited[beg] = true;
    bool explored = true;

    Node beg_n = G->nodes[beg];
    Node end_n = G->nodes[end];

    cout << " -- HC algorithm --" << '\n';

    cout << char(G->nodes[beg].id + 65) << "->";
        
    PATH.push_back(char(G->nodes[beg].id + 65));

    while (beg_n.id != end_n.id && explored) 
    {
        min_d = 99999;
        explored = false;
        
        for (auto x: G->adj_list[beg_n.id]) 
        {
            if (!visited[x.id]) 
            {
                dist_here = euclideanDistance(x, end_n);
                
                if (dist_here < min_d) 
                {
                    min_d = dist_here;
                    id = x.id;
                }

                out_exp << char(beg_n.id + 65) << "," << char(x.id + 65) << '\n';

            }
            explored = true;
        }
        
        visited[id] = true;

        cout << char(G->nodes[id].id + 65) << "->";
        
        PATH.push_back(char(id + 65));
        PATH.push_back(',');

        beg_n = G->nodes[id];
    }

    PATH.pop_back();
    out << PATH;
    
    found = beg_n.id == end_n.id;

    if (found)
        cout << "END\nFound!" << endl;
    else
        cout << "\nNot Found!" << endl;

    out_exp.close();
    out.close();
}
