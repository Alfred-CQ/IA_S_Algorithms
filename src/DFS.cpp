#include <iostream>
#include <fstream>
#include <vector>
#include "../utils/csv_files_reader.h" 

bool found=false;

void DFS(IA_NODES nodes,IA_ADJ_LIST adj_list, vector<bool> visited, int cur, int end, string& PATH){ 
    visited[cur]=1;
    PATH.push_back(char(cur+65));
    PATH.push_back(',');
    cout<<char(cur+65)<<"->";
    if(cur==end){
        cout<<"\nFound!";
        found=true;
        return;
    }
    for (int i = 0; !found && i < adj_list[cur].size(); i++ ){
        if (visited[adj_list[cur][i].id]==false){
            DFS(nodes,adj_list,visited,adj_list[cur][i].id,end,PATH);
        }
    }
}

void DFS_t(){
    string file_name = "../datasets/DFS.csv", PATH;
    ofstream out(file_name);
    IA_NODES nodes=get_nodes_from_file();
    IA_ADJ_LIST adj_list=get_adj_list_from_file(nodes);
    vector<bool> visited(nodes.size(),0);
    found=false;

    char beg_c, end_c;
    cout << "Start: ";
    cin >> beg_c;

    cout << "End: ";
    cin >> end_c;

    int beg{int(beg_c) - 65}, end{int(end_c) - 65};
    
    DFS(nodes,adj_list,visited,beg,end,PATH);
    out<<PATH;
}

int main() {
    DFS_t();
    return 0;
}
