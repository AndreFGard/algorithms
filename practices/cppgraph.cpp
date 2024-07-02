#include <iostream>
#include <vector>
#include <queue>
#include <map>

#define NODELTA 0

#define VISITED 1
#define UNVISITED 0





typedef struct graph {
    std::vector<int> *mark; 
    std::vector<int> *delta; //distances
    std::vector<std::vector<int>*> m; //graph
    std::vector<char *> i_to_s; //same as map<int, char*>
    std::map<char *, int> s_to_i; // the opposite
    std::vector<int> *curr; //current adjacent vertex idx for each vertex
    int size = -1;
}graph;

void setMark(graph *g, int v, int mark){
    (*g->mark)[v] = mark;
}

int getMark(graph *g, int v){
    return (*g->mark)[v];
}

int first_v(graph *g, int v){
    int w = -1;
    if (g->m[v]->size() > 0){
        w = g->m[v]->front();
    }
    return (*g->curr)[v] = w;
}

//returns the next VERTEX
int next_v(graph *g, int v){
    int curr = (*g->curr)[v]++;
    
    if (g->m[v]->size() > curr){
        return (*g->m[v])[curr];
    }
    (*g->curr)[v] = 0;
    return -1;
}

graph *makeGraphh(int size){
    graph *temp = new graph;

    temp->delta = new std::vector<int> (size);
    temp->curr = new std::vector<int> (size);
    temp->mark = new std::vector<int> (size);
    for (int i = 0; i<size;i++){
        temp->m.push_back(new std::vector<int>);
    }
    
    return temp;
}

void addTeam(graph *g, char a[], char b[], char c[]){

    //wow, this is is such an ugly piece of code...
    
    int an, bn, cn;

    if (an = g->s_to_i.find(a) == g->s_to_i.end()) {
        // if a not found
        an = g->size = g->i_to_s.size();
        g->i_to_s.push_back(a);

    }

    if (bn = g->s_to_i.find(b) == g->s_to_i.end()) {
        // if b not found
        bn = g->size = g->i_to_s.size();
        g->i_to_s.push_back(b);
    }

    if (cn = g->s_to_i.find(c) == g->s_to_i.end()) {
        // if c not found
        cn = g->size = g->i_to_s.size();
        g->i_to_s.push_back(c);
    }
        
    g->m[an]->push_back(bn) ;
    g->m[an]->push_back(cn) ;

    g->m[bn]->push_back(an);
    g->m[bn]->push_back(cn);

    g->m[cn]->push_back(an);
    g->m[cn]->push_back(bn);

}

std::queue<int>& BFS(graph *g, int a, int b){
    std::queue<int> q;
    q.push(a);

    static std::queue<int> path;
    setMark(g, a, VISITED);
    while (!q.empty()){
        a = q.front();
        q.pop();
        path.push(a);

        if (a == b){
            return path;
        }

        int w = first_v(g,a);

    }
    return path;
}

int main() {

    graph *g = makeGraphh(10);
    std::cout << (*g->mark)[0] << g->m[0]->size();
    addTeam(g, "fernando", "robs", "klebs");


    return 0;
}
