#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string.h>
#include <algorithm>
#include <string>

#define NODELTA 0

#define VISITED 1
#define UNVISITED 0



typedef struct rankel{
    int r;
    std::string s;
} rankEl;

typedef struct graph {
    std::vector<int> *mark; 
    std::vector<int> *delta; //distances
    std::vector<std::vector<int>*> m; //graph
    std::vector<std::string> i_to_s; //same as map<int, char*>
    std::map<std::string, int> s_to_i; // the opposite
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
    (*g->curr)[v] = 0;
    return w;
}

//returns the next VERTEX
int next_v(graph *g, int v){
    int curr = 1 + (*g->curr)[v]++;
    
    if (g->m[v]->size() > curr){
        return (*g->m[v])[curr];
    }
    (*g->curr)[curr -1] = 0;
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

int addVertex(graph *g, std::string a){
    int an;
    //int ee = g->s_to_i.end();
    auto ait = g->s_to_i.find(a);
    if (g->s_to_i.find(a) == g->s_to_i.end()) {
        // if a not found
        an = g->size = g->i_to_s.size();
        g->i_to_s.push_back(a);
        g->s_to_i[a] = an;
    }
    else an = ait->second;

    return an;

}

void addEdge(graph *g, int a, int b){
    g->m[a]->push_back(b);
    g->m[b]->push_back(a);
}

void __addTeam(graph *g, std::string a, std::string b, std::string c){

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

void addTeam(graph *g, std::string a, std::string b, std::string c){
    int an,bn,cn;
    an = addVertex(g,a);
    bn = addVertex(g,b);
    cn = addVertex(g,c);

    addEdge(g,an,bn);
    addEdge(g,an,cn);
    addEdge(g,bn, cn);

}

std::vector<int> BFS(graph *g, int a, int b){
    std::queue<int> q;
    q.push(a);

    std::queue<int> oldpath;
    std::vector<int> pred (g->m.size());
    pred[a] = a; //mark the starting point

    setMark(g, a, VISITED);
    while (!q.empty()){
        //pred[q.front()] = a;

        a = q.front();
        q.pop();
        oldpath.push(a);

        if (a == b){
            return pred;
        }
        
        int w = first_v(g,a);

        while (w!= -1){
            if (getMark(g, w) == UNVISITED){
                setMark(g,w,VISITED);
                q.push(w);
                pred[w] = a;
                
                if (w == b){
                    oldpath.push(w);
                    return pred;
                }
            }
            w = next_v(g,a);
        }

    }
    return pred;
}
#include <stdio.h>
int test() {

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

    std::vector<int> qq =BFS(g, g->s_to_i[g->i_to_s[0]], g->s_to_i[g->i_to_s[2]]);
    std::cout <<"Khalid" << " " << qq.size() -1 << std::endl;
    delete g;
    puts("aaa");
    return 0;
}

bool cmpRank(rankel a, rankel b){
    if (a.r > b.r) return true;
    else return false;
}

void zeroOutVec(std::vector<int>& v, int n){
    for (int i = 0; i<n; i++){
        v[i] = UNVISITED;
    }
    return;
}

int getNPred(std::vector<int> &pred, int v, int d){
    int n = 0;
    int dad = d;

    if (pred[d] == 0) return -1;
    while((dad = pred[dad]) != v){
        n++;
    }
    n++;
    return n;
}

int main(){
    
    int c = 1;
    scanf("%d", &c);
    for (int i  =0; i<c;i++){
        int n = 20; //team
        scanf("%d", &n);
        graph *g = makeGraphh(n*3);

        int ahmadPos = -1;
        for (int t = 0; t<n;t++){
            char *name[] = {(char*) malloc(sizeof(char)*60),
                            (char*) malloc(sizeof(char)*60),
                            (char*) malloc(sizeof(char)*60)};

            name[0][0] = name[1][0] = name[2][0] = '\0';
            scanf("%s %s %s", name[0], name[1], name[2]);

            addTeam(g, name[0], name[1], name[2]);

            //ahmad finder
            if (ahmadPos == -1) {
                for (int ahmad = 0; i<3;i++){
                    if (strcmp(name[i], "Ahmad") == 0){
                        ahmadPos = g->s_to_i[name[i]];
                    }
                }
            }
        }

        std::map<std::string, int> rank;
        std::vector<rankel> vrank;
        int j = 0;
        for (std::map<std::string, int>::iterator iter = g->s_to_i.begin(); iter != g->s_to_i.end(); iter++){
            //rank[iter->first] = BFS(g, iter->second, ahmadPos).size();
            std::vector<int> predecessors = BFS(g, iter->second, ahmadPos);
            rankel el = {getNPred(predecessors,iter->second, ahmadPos), iter->first};
            zeroOutVec(*g->mark, g->mark->size());
            zeroOutVec(*g->curr, g->curr->size());
            vrank.push_back(el);
        }

        std::make_heap(vrank.begin(), vrank.end(), cmpRank);

        puts("eae");
    

        
        
    }
}
