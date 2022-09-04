#include <iostream>

#include "DFS.hpp"
#include "BFS.hpp"
#include "hill_climbing.hpp"
#include "AStar.hpp"

using std::cout; using std::cin;

int main()
{
    
    Graph G(65.80f);
    G.adj_list = get_adj_list_from_file(G.nodes);

    //Input
    char beg_c, end_c;
    cout << "Start: ";
    cin >> beg_c;

    cout << "End: ";
    cin >> end_c;

    int beg{int(beg_c) - 65}, end{int(end_c) - 65}, id;

    DFS_t(&G, beg, end);
    BFS_t(&G, beg, end);
    
    hill_climbing(&G, beg, end); 
    AStar_t(&G, beg, end);

    return 0;
}
