#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <iostream>
#include <stack>
#include <algorithm>
#include <map>

#define UNVISITED -1
#define VISITED 1
using namespace std;
typedef struct graph{
    vector<int> mark;
    vector<int> n_ancestors;

    vector<vector<int>> adjList; //PRIORITy QUEUE
    graph(int n){
        adjList.resize(n);
        mark.resize(n, UNVISITED);
        n_ancestors.resize(n);

    }
}graph;

void setMark (graph *g, int v, int mark){
    g->mark[v] = mark;
}

int getMark(graph *g, int v){
    return g->mark[v];

}

void addhp(vector<int>& h, int n){
    h.push_back(n); push_heap(h.begin(), h.end(), greater<int>());
}

int pophp(vector<int>&h){
    if (h.size() > 0){
        pop_heap(h.begin(), h.end(), greater<int>());
        int n = h.back(); 
        h.pop_back();
        return n;
    }
    else
        return UNVISITED;
}

void add_edge(graph *g, int v, int w){
    //g->adjList[v].push(w);
    addhp(g->adjList[v], w);

    g->n_ancestors[w]++;
    return;
}

//returns the n ancestors of the son of the passed father
int remove_ancestry(graph *g, int f, int s){
    //the edge has actually been removed already by first()
    g->n_ancestors[s]--;
    return g->n_ancestors[s];
}

vector<int> getFatherlessnodes(graph *g, int gsize){
    vector<int>v;
    for (int i = 0; i<gsize; i++){
        if (g->n_ancestors[i] == 0){
            addhp(v, i);
        }
    }
    return v;
}

int first(graph *g, int v){
    if (!g->adjList[v].empty()){
        //v = g->adjList[v].top();
        //g->adjList[v].pop();
        int n = pophp(g->adjList[v]);

        return n;
    }
    return UNVISITED;
}

int next(graph *g, int v){
    return first(g,v);
}

void printTopo(queue<int> &toprint, int expected_size){
    if (toprint.size() != expected_size) {
        cout << "Sandro fails.";
        return;
    }
    for (int v = toprint.front(); !toprint.empty(); v = toprint.front()){
        toprint.pop();
        cout << v+1 << " ";
    }
    cout <<endl;
}


queue<int> BFS(graph *g){
    queue<int> toprint;
    vector<int> fatherless = getFatherlessnodes(g, g->n_ancestors.size());

    while (!fatherless.empty()){
        int p = pophp(fatherless);
        setMark(g, p, VISITED);

        int w = first(g, p);
        while(w != UNVISITED){
            int ances;
            if (getMark(g, w) == UNVISITED){
                setMark(g, w, VISITED);
                ances = remove_ancestry(g, p, w);
                if (ances == 0){
                    addhp(fatherless, w);
                }
                else {
                    setMark(g,w, UNVISITED);
                }
            }

            w = next(g, p);
        }
        toprint.push(p);
    }
    //if (toprint.size() != g->mark.size()) cout << "FAIL ";

    printTopo(toprint, g->mark.size());
    return toprint;
}


/*
precisamos dordenadoeixar a lista de adjacencia sempre ordenada. alem disso, precisamos começar a partir de um no
que nao tenha dependencias, logo no "inicio" da arvore de busca do grafo porque o grafo é dirigido e 
portanto iniciar a busca em um outro nó seria pouco eficiente.
pra deixar a adjlist sempre ordenada, o ideal é usar uma heap, porque a remocao do maior elemento torna
facil iterar sobre ela, dispensando um array de current indices que seria necessario se usassemos um 
vector.

a bfs precisa ser alterada pq nos só podemos analisar os filhos dos nós que não tem antepassados. esses filhos
tem que ser analisados por ordem crescente, tambem usando uma heap. conforme os pais  sem antepassados iniciais vao sendo removidos, 
novos nos sem antepassados aparecem, sendo necessário adicioná-los à fila tambem, mas respeitando a ordenacao. portanto, vale a pena usar uma 
heap tambem aqui



*/

int test(){
    graph g(6);
    add_edge(&g, 2,3);
    add_edge(&g, 2,4);
    add_edge(&g, 2,5);
    add_edge(&g, 0,1);
    
    

    BFS(&g);

    int vertices, lines;
    scanf("%d %d", &vertices, &lines);

    for (int l = 0; l<lines; l++){
        int v, w;
        scanf("%d %d", &v, &w);
    }
    return 0;
}

int main(){
    
    int n,m;
    
    scanf("%d %d", &n,&m);
    graph g = {n};
    for (int j = 0; j<m; j++){
        int x,y;
        scanf("%d %d", &x, &y);
        add_edge(&g, x-1, y-1);
    }
    BFS(&g);
}