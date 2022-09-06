#include <iostream>
#include<chrono>
#include <ctime>

#include "DFS.hpp"
#include "BFS.hpp"
#include "hill_climbing.hpp"
#include "AStar.hpp"

using std::cout; using std::cin;
typedef std::chrono::time_point<std::chrono::system_clock> time_point;
typedef std::chrono::duration<double> duration;

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

    time_point startTime; 
    time_point endTime;
    
    startTime = chrono::system_clock::now();
    DFS_t(&G, beg, end);
    endTime = chrono::system_clock::now();
    duration total = endTime - startTime;
    cout << "\t Time: " << total.count() << " ns\n\n";

    startTime = chrono::system_clock::now();
    BFS_t(&G, beg, end);
    endTime = chrono::system_clock::now();
    total = endTime - startTime;
    cout << "\t Time: " << total.count() << " ns\n\n";
    
    startTime = chrono::system_clock::now();
    hill_climbing(&G, beg, end); 
    endTime = chrono::system_clock::now();
    total = endTime - startTime;
    cout << "\t Time: " << total.count() << " ns\n\n";

    startTime = chrono::system_clock::now();
    AStar_t(&G, beg, end);
    endTime = chrono::system_clock::now();
    total = endTime - startTime;
    cout << "\t Time: " << total.count() << " ns\n\n";


    return 0;
}
