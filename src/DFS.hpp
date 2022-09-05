#include <iostream>
#include <fstream>
#include <vector>

#include "../utils/csv_files_reader.h" 
#include "../utils/graph.h"

bool found = false;

void DFS(IA_NODES nodes,IA_ADJ_LIST adj_list, vector<bool> visited, int cur, int end, string& EXP, string& PATH)
{ 
    visited[cur] = 1;
    
    PATH.push_back(char(cur+65));
    PATH.push_back('\n');
    
    cout<<char(cur+65)<<"->";
    
    if(cur==end)
    {
        cout << "END\nFound!\n";
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

            DFS(nodes,adj_list,visited,adj_list[cur][i].id,end, EXP, PATH);
        }
        
    }
}

void DFS_t(Graph* G, int beg, int end)
{
    string file_name = "../datasets/DFS_path.csv", PATH, EXP,
           file_exp  = "../datasets/DFS_expn.csv";

    ofstream out(file_name);
    ofstream out_expn(file_exp);
    
    vector<bool> visited(G->nodes.size(),0);
    found = false;
    
    cout << " -- DFS algorithm --" << '\n';

    DFS(G->nodes,G->adj_list,visited,beg,end,EXP,PATH);
    
    out_expn<<"from,to\n";
    out_expn<<EXP;

    out<<"label\n";
    out<<PATH;

    out.close();
    out_expn.close();

}
