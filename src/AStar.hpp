#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>
#include <algorithm>
#include <utility>

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
           file_exp  = "../datasets/AStar_expn.csv";

    ofstream out(file_name);
    ofstream out_exp(file_exp);

    cout << char(G->nodes[beg].id + 65) << "->";
          
    int id;
    float min_d, aStar_op;
    bool found = false, explore = true; 
    
    vector<bool> visited;
    visited.resize(G->nodes.size(),false);
    visited[beg] = true;
    
    Node beg_n = G->nodes[beg];
    Node end_n = G->nodes[end];
    
    out << "label\n" << char(G->nodes[beg].id + 65) << '\n';
    out_exp <<"from,to\n";

    float cost = 0;

    vector<pair<float, int>> m_nodes;

    while ( (beg_n.id != end_n.id) && explore)
    {
        min_d = 99999;
        explore = false;

        for (auto x: G->adj_list[beg_n.id])
        {
            if (!visited[x.id])
            {
                
                aStar_op = euclideanDistance(beg_n, x) + euclideanDistance(x, end_n);

                m_nodes.push_back(make_pair(aStar_op, x.id));

                if ( aStar_op < min_d)
                {
                    min_d = aStar_op;
                    id = x.id;
                }

                out_exp << char(beg_n.id + 65) << "," << char(x.id + 65) << '\n';
            
            }
            explore = true;
        }
        
        sort(m_nodes.begin(), m_nodes.end());

        bool loop = true;

        Node tmp = G->nodes[id];

        for (auto x: G->adj_list[G->nodes[id].id])
        {
            if (!visited[x.id])
            {
                loop = false;
            }
        }
        if (loop)
        {
            int y;

            for (auto x: m_nodes)
            {
                if (!visited[x.second])
                {
                    loop = false;
                    y = x.second;
                }
            }

            id = m_nodes[y].second;
        }

        cost += min_d;

        visited[id] = true;
        
        cout << char(G->nodes[id].id + 65) << "->";
        
        out << char(id + 65) << '\n';

        beg_n = G->nodes[id];
        m_nodes.clear();
    }
    
    found = (beg_n.id == end_n.id);

    if (found)
        cout << "END\nFound!" << endl;
    else
        cout << "\nNot Found!" << endl;

    cout << "Cost: " << cost;

    out_exp.close();
    out.close();
}
