#include <iostream>
#include <fstream>
#include <queue>

#include "../utils/csv_files_reader.h"

using namespace std;

void BFS_t()
{
    string file_name = "../datasets/BFS.csv", PATH;
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
    bool found = false; 
    
    vector<bool> visited;
    queue<Node> myQueue;

    visited.resize(nodes.size(),false);
    visited[beg] = true;
    
    myQueue.push(nodes[beg]);
    
    while(!myQueue.empty())
    {
        id = myQueue.front().id;
        
        cout << char(id + 65) << "->";
        
        PATH.push_back(char(id + 65));
        PATH.push_back(',');
        
        if (id == end)
        {
            found = true;
            break;
        }

        myQueue.pop();
       
        for (auto x : adj[id])
        {
            if (!visited[x.id])
            {
                visited[x.id] = true;
                myQueue.push(x);
            }
        }
    }

    PATH.pop_back();
    out << PATH;
    
    if (found)
        cout << "\nFound!" << endl;
    else
        cout << "\nNot Found!" << endl;

    out.close();
}
