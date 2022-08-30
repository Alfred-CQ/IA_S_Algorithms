#include <iostream>
#include <vector>

using namespace std;
struct Node {
    int x, y;
    bool visited;
    vector<Node*> edges;
    Node(bool v=false){
        visited=v;
    }
    Node(int _x, int _y, bool v=false) {
        x = _x;
        y = _y;
        visited=v;
    }
};

void new_Edge(Node &a, Node &b) {
    a.edges.push_back(&b);
    b.edges.push_back(&a);
}

bool found=false;
void DFS(Node* v,Node* end){ 
    v->visited = true;
    cout<<"->"<<v->x;
    if(v==end){
        cout<<"ENCONTRADO";
        found=true;
        return;
    }
    for (int i = 0; !found && i < v->edges.size(); i++ ){
        if (v->edges[i]->visited==false){
            DFS(v->edges[i],end);
        }
    }
}

int main() {
    Node* Nodes= new Node[20];

    for(int i=0;i<20;i++){
        Nodes[i].x=i;
        Nodes[i].y=rand()%100;
    }
    
    new_Edge(Nodes[0],Nodes[1]);
    new_Edge(Nodes[1],Nodes[2]);
    new_Edge(Nodes[2],Nodes[3]);
    new_Edge(Nodes[3],Nodes[4]);
    new_Edge(Nodes[4],Nodes[5]);
    new_Edge(Nodes[5],Nodes[6]);
    new_Edge(Nodes[6],Nodes[7]);
    new_Edge(Nodes[7],Nodes[8]);
    new_Edge(Nodes[8],Nodes[9]);
    new_Edge(Nodes[8],Nodes[10]);
    new_Edge(Nodes[10],Nodes[11]);

    cout<<"Visited\n";
    found=false;
    DFS(&Nodes[8],&Nodes[1]);
    






    return 0;
}
