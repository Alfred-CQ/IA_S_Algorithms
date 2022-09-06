#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#include "../utils/csv_files_reader.h" 
#include "../utils/graph.h"

bool found = false;

void DFS(IA_NODES nodes,IA_ADJ_LIST adj_list, vector<bool>& visited, int cur, int end, string& EXP, string& PATH, vector<int>& node_path)
{ 
    visited[cur] = 1;
    
    if(cur==end)
    {
        cout << "Found!\n";
        found = true;
        return;
    }

    for (int i = 0; !found && i < adj_list[cur].size(); i++ )
    {
        if (visited[adj_list[cur][i].id]==false)
        {
            EXP.push_back(char(cur+65));
            EXP.push_back(',');
            EXP.push_back(char(adj_list[cur][i].id + 65));
            EXP.push_back('\n');
            node_path[adj_list[cur][i].id] = cur;
            DFS(nodes,adj_list,visited,adj_list[cur][i].id,end, EXP, PATH, node_path);
        }
        
    }
}

void DFS_t(Graph* G, int beg, int end)
{
    string file_name = "../datasets/DFS_path.csv", PATH, EXP,
           file_exp  = "../datasets/DFS_expn.csv";

    ofstream out(file_name);
    ofstream out_expn(file_exp);
    vector<int> node_path(N_NODES, -1);
    vector<bool> visited(G->nodes.size(),0);
    found = false;
    
    cout << " -- DFS algorithm --" << '\n';

    DFS(G->nodes,G->adj_list,visited,beg,end,EXP,PATH, node_path);
    
    stack<int> s;

    int pos = end;

    do
    {
        s.push(pos);
        pos = node_path[pos];
    }while(pos != -1);

    string dfs_path;

    while(!s.empty())
    {
        dfs_path.push_back(get_node_name(s.top()));
        dfs_path.push_back('\n');
        s.pop();
    }
    
    float cost = 0;

    for(int i = 0; i < dfs_path.size(); i+=2){
        cout << dfs_path[i] << "->";
        if ( i+2 < dfs_path.size())
        {
            cost += euclideanDistance(G->nodes[int(dfs_path[i] - 65)], 
                                      G->nodes[int(dfs_path[i + 2] - 65)]);
        }

    }
    cout<<"END\n";

    cout << "Cost: " << cost;

    out_expn<<"from,to\n";
    out_expn<<EXP;
    
    out<<"label\n";
    out<<dfs_path;

    out.close();
    out_expn.close();

}
