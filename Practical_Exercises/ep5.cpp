#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
#include <map>
#include <algorithm>

using namespace std;

#define UNVISITED -1
#define VISITED -2
typedef struct graph{
    vector<int> mark;
    vector<vector<int>> adjlist;
    map<int, int> curr;

    graph(int n){
        mark.resize(n, UNVISITED);
        adjlist.resize(n);
    }
} graph;

void addhp(vector<int>& hp, int v){
    hp.push_back(v);
    push_heap(hp.begin(), hp.end(), greater<int>());
    return;
}

int pophp(vector<int> &hp){
    int n = hp.front();
    pop_heap(hp.begin(), hp.end(), greater<int>());
    hp.pop_back();
    return n;
}

void addEdge(graph *g, int v, int w){
    // addhp(g->adjlist[v], w);
    // addhp(g->adjlist[w], v);

    g->adjlist[v].push_back(w);
    g->adjlist[w].push_back(v);
}


void setMark(graph *g, int a, int mark){
    g->mark[a] = mark;
}

int getMark(graph *g, int a){
    return g->mark[a];
}

int first(graph *g, int v){
    if (!g->adjlist[v].empty()){
    g->curr[v] = 0;
    return g->adjlist[v][0];
    }

    return UNVISITED;
}

int next(graph *g, int v){
    
    int size = g->adjlist[v].size();
    g->curr[v]++; 
    int curr = g->curr[v];
    if (curr < size){
        
        int n= g->adjlist[v][curr];
        return n;
    }
    else{
        g->curr[v] = 0;
        return UNVISITED;
    }
}

void markVec(vector<int>* v, int mark ){
    int size = v->size();
    for (int i = 0; i <size; i++){
        (*v)[i] = mark;
    }
}

void markVec(map<int, int>* v, int mark ){
    int size = v->size();
    for (int i = 0; i <size; i++){
        (*v)[i] = mark;
    }
}

vector<int> BFS(graph *g, int a, int b){
    vector<int> hp;
    vector<int> pred (g->adjlist.size(), UNVISITED);
    hp.push_back(a);
    pred[a] = a;
    if (a == b) return pred;

    setMark(g, a, VISITED);


    while (!hp.empty()){
        int p = pophp(hp);


        int s = first(g, p);
        while (s != UNVISITED){
            if (getMark(g, s) != VISITED){
                setMark(g,s, VISITED);
                addhp(hp, s);
                
                pred[s] = p;
                if(s == b) {
                        markVec(&g->curr, 0);
                        markVec(&g->mark, UNVISITED);
                    return pred;
                }
            }
            s = next(g, p);
        }
    }

    markVec(&g->curr, 0);
    markVec(&g->mark, UNVISITED);

    vector<int> fail;
    return fail;
}



vector<int> pathMaker(graph *g, int a, int b){
    vector<int> path;
    vector<int> pred = BFS(g, a ,b);

    if(pred.size() == 0) {
        return path;
    }

    path.push_back(b);
    int parent = pred[b];
    while (parent != -1){
        path.push_back(parent);
        if (parent == a) return path;
        parent = pred[parent];
    }

    path.resize(0);
    return path;
}

void printPath(vector<int> path ){
    int size = path.size();
    if (size == 0){
        puts("-1");
        return;
    }
    if (size == 2){
        printf("%d\n", path[0]);
        return;
    }
    printf("%d",path[size-1]);
    for (int i = size -2; i>-1; i--){
        printf(" %d", path[i]);
    }
    printf("\n");
}

int main(){

    int cases;
    scanf("%d", &cases);
    for (int c = 0; c<cases; c++){
        int v,a;
        scanf("%d %d", &v, &a);
        graph g = {v+1};

        for (int ed = 0; ed<a; ed++){
            int a,b;
            scanf("%d %d", &a, &b);
            addEdge(&g, a, b);
        }

        for (int vv = 0; vv<v; vv++){
            sort(g.adjlist[vv].begin(), g.adjlist[vv].end());
        }

        int p;
        scanf("%d", &p);
        printf("Caso %d\n", c+1);
        for (int pp = 0; pp<p;pp++){
            int a,b;

            scanf("%d %d", &a, &b);

            printPath(pathMaker(&g, a, b));

        }



    }
}