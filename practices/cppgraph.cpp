#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string.h>

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

int addVertex(graph *g, char a[]){
    int an;
    if (an = g->s_to_i.find(a) == g->s_to_i.end()) {
    // if a not found
    an = g->size = g->i_to_s.size();
    g->i_to_s.push_back(a);
    g->s_to_i[a] = an;
    }

    return an;

}

void addEdge(graph *g, int a, int b){
    g->m[a]->push_back(b);
    g->m[b]->push_back(a);
}

void __addTeam(graph *g, char a[], char b[], char c[]){

    //wow, this is is such an ugly piece of code...
    
    int an, bn, cn;

    if (an = g->s_to_i.find(a) == g->s_to_i.end()) {
        // if a not found
        an = g->size = g->i_to_s.size();
        g->i_to_s.push_back(a);
        g->s_to_i[a] = an;

    }

    if (bn = g->s_to_i.find(b) == g->s_to_i.end()) {
        // if b not found
        bn = g->size = g->i_to_s.size();
        g->i_to_s.push_back(b);
        g->s_to_i[b] = bn;
    }

    if (cn = g->s_to_i.find(c) == g->s_to_i.end()) {
        // if c not found
        cn = g->size = g->i_to_s.size();
        g->i_to_s.push_back(c);
        g->s_to_i[c] = cn;
    }
        
    g->m[an]->push_back(bn) ;
    g->m[an]->push_back(cn) ;

    g->m[bn]->push_back(an);
    g->m[bn]->push_back(cn);

    g->m[cn]->push_back(an);
    g->m[cn]->push_back(bn);

}

void addTeam(graph *g, char a[], char b[], char c[]){
    int an,bn,cn;
    an = addVertex(g,a);
    bn = addVertex(g,b);
    cn = addVertex(g,c);

    addEdge(g,an,bn);
    addEdge(g,an,cn);
    addEdge(g,bn, cn);

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

        while (w!= -1){
            if (getMark(g, w) == UNVISITED){
                setMark(g,w,VISITED);
                q.push(w);
                
                if (w == b){
                    path.push(w);
                    return path;
                }
            }
            w = next_v(g,a);
        }

    }
    return path;
}
#include <stdio.h>
int main() {

    graph *g = makeGraphh(18);
    std::cout << (*g->mark)[0] << g->m[0]->size() << std::endl;
    char *a, *b,*c;
    // PROBLEM: map<char* comapres stuff by their addresses, not by their values, somehow
    addTeam(g, a = strdup("Ahmad"), b = strdup("Mousaab"), c = strdup("Khalid")); //error with khalid
    // addTeam(g,"Ali", "Mousaab", "Nizar");
    // addTeam(g, "Ali", "Bassel", "Nizar");
    // addTeam(g,"Kassem", "Ahmad", "Mousaab");
    // addTeam(g,"Saeed", "Kassem", "Fadel");
    // addTeam(g,"Salwa", "Saeed", "Samer");
    // //addTeam(g,"Mona", "Abdo", "Qussi");

    // //std::queue<int>& q = BFS(g,g->s_to_i["Mona"], g->s_to_i["Ahmad"]);
    // std::vector<const char*> names = {"Ahmad", "Mousaab", "Khalid", "Ali", "Mousaab", "Nizar", "Ali", "Bassel", "Nizar", "Kassem", "Ahmad", "Mousaab", "Saeed", "Kassem", "Fadel", "Salwa", "Saeed", "Samer", "Mona", "Abdo", "Qussi"};
    
    // std::map<char *, int> rank;
    // for (auto name: names){
    //     std::cout <<name << " " << BFS(g,g->s_to_i[strdup(name)], g->s_to_i[strdup(names[0])]).size() -1 << std::endl;
    // }
        int kkk = g->s_to_i[strdup("Khalid")];

    std::queue<int> & qq =BFS(g,g->s_to_i[a], g->s_to_i[c]);
    std::cout <<"Khalid" << " " << qq.size() -1 << std::endl;

    puts("aaa");
    return 0;
}
