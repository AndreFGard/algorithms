#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
#define unvisited -2
#define visited -1
typedef struct graph{
    vector<vector<pair<int,int>>> adjlist;
    vector<int> mark;
    
    graph(int n){
        adjlist.resize(n);
        mark.resize(n, unvisited);
    }
} graph;

void addedge(graph &g, int a, int b, int w){
    g.adjlist[a].push_back(make_pair(w, b));
    g.adjlist[b].push_back(make_pair(w, a));
}
#define inf 1000 * 1000 * 1000
int prim(graph &g){
    int gsize = g.mark.size();
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> hp;
    vector<pair<int,int>> delta (gsize, make_pair(inf,inf));

    delta[0] = make_pair(0, 0);
    hp.push(make_pair(0,0));

    int pathcost = 0;

    for (int zzz = 0; zzz < gsize; zzz++){
        int p, dontuseme_pw;
        do {
            if (hp.empty()) {
                return pathcost;
            }
            auto t = hp.top(); hp.pop();
            p = t.second; dontuseme_pw = t.first;

        } while (g.mark[p] != unvisited);

        g.mark[p] = visited;
        pathcost += dontuseme_pw;

        for (auto t : g.adjlist[p] ){
            if ((g.mark[t.second] != visited) && (delta[t.second].first > t.first)){
                hp.push(make_pair( t.first, t.second));
                delta[t.second] = make_pair(t.first, p);
            }
        }
    }
    return pathcost;
}



int main(){
    int cities, ob;
    int caso_counter = 0;

    scanf("%d %d",&cities,&ob);

    while (cities || ob){
        graph g = graph(cities);        
        for (int jj = 0; jj<ob; jj++){
            int a,b,p;
            scanf("%d %d %d", &a,&b,&p);
            addedge(g, a, b, p);
        }

        //ordenar edges
        for (int adlista = 0; adlista < cities; adlista++){
            sort(g.adjlist[adlista].begin(), g.adjlist[adlista].end());
        }

        int pathcost = prim(g);

        int success = 1;
        for (int vert = 0; vert < cities; vert++){
            if (g.mark[vert] == unvisited) {
                success = 0; 
                break;
            }
        }

        if (success) {
            printf("Caso %d: %d\n", caso_counter+1, pathcost);
        }


        caso_counter++;
        scanf("%d %d",&cities,&ob);
    }


}