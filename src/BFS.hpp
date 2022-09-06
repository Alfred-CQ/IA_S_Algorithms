#include <iostream>
#include <fstream>
#include <queue>

#include "../utils/csv_files_reader.h"
#include "../utils/graph.h"

using namespace std;

string dfs_path;

void BFS_t(Graph* G, int beg, int end)
{
    string file_name = "../datasets/BFS_path.csv",
           file_exp  = "../datasets/BFS_expn.csv";

    ofstream out(file_name);
    ofstream out_exp(file_exp);
    
    int id;
    bool found = false; 
    
    vector<bool> visited;
    queue<Node> myQueue;

    visited.resize(G->nodes.size(),false);
    visited[beg] = true;
    
    myQueue.push(G->nodes[beg]);
    
    cout << " -- BFS algorithm --" << '\n';
    
    out << "label\n";
    out_exp << "from,to\n";

    float cost = 0;

    while(!myQueue.empty())
    {
        id = myQueue.front().id;
        
        cout << char(id + 65) << "->";
        dfs_path.push_back(char(id + 65));
        out << char(id + 65) << '\n';
        
        if (id == end)
        {
            found = true;
            break;
        }

        myQueue.pop();
        
        for (auto x : G->adj_list[id])
        {
            if (!visited[x.id])
            {
                visited[x.id] = true;
                myQueue.push(x);
                out_exp << char(id + 65) << "," << char(x.id + 65) << '\n';
            }
        }
    }

    for(int i = 0; i < dfs_path.size(); i++){
        if ( i+1 < dfs_path.size())
        {
            cost += euclideanDistance(G->nodes[int(dfs_path[i] - 65)], 
                                      G->nodes[int(dfs_path[i + 1] - 65)]);
        }

    }
    
    if (found)
        cout << "END\nFound!" << endl;
    else
        cout << "\nNot Found!" << endl;

    cout << "Cost: " << cost;

    out.close();
    out_exp.close();
}
