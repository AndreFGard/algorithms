//uva 11857
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <vector>
using namespace std;
typedef long long int lli;
#define visited  -2
#define unvisited -1
typedef struct graph{
    vector<vector<pair<long long int,int>>> adjlist;
    vector<int> mark;
    long long int maxxer = -1;

    graph(int n){
        adjlist.resize(n);
        mark.resize(n, unvisited);
    }
} graph;

long long int inf = 1000*1000*1000 * 2;
inline void addedge(graph &g, int a, int b, int w){
    g.adjlist[a].push_back(make_pair(w, b));
    g.adjlist[b].push_back(make_pair(w, a));
}

vector<pair<lli, int>> primms(graph &g){
    priority_queue<pair<long long int,int>, vector<pair<long long int,int>>, greater<pair<long long int,int>>> fringe;
    vector<pair<long long int, int>> delta (g.mark.size(), make_pair(inf, inf));
    
    fringe.push(make_pair(0, 0));
    delta[0] = make_pair(0, 0);
    for (int i =0, size = g.mark.size(); i<size;i++){
        int p, pw;
        do {
            if (fringe.empty()){
                break;
            }
            pair<lli, int> t = fringe.top();fringe.pop();
            p = t.second; pw = t.first;
        } while (g.mark[p] != unvisited);

        g.mark[p] = visited;
        g.maxxer = pw > g.maxxer ? pw : g.maxxer;
        for (auto t: g.adjlist[p]){
            if ((g.mark[t.second] != visited) && (delta[t.second].first > t.first)){
                delta[t.second] = make_pair(t.first, p);
                fringe.push(make_pair(t.first, t.second));
            }
        }
    }
    return delta;
}

int main(){

    int cities, edges;
    scanf("%d %d", &cities, &edges);
    while (cities || edges) {
        graph g = graph(cities);

        for (int ne = 0; ne < edges; ne++){
            int a, b, w;
            scanf("%d %d %d", &a, &b, &w);
            addedge(g,a,b,w);
        }

        for (int i = 0; i<cities;i++){
            sort(g.adjlist[i].begin(), g.adjlist[i].end()); }

        primms(g);
        int success = 1;
        for (int i = 0; i<cities;i++){
            if (g.mark[i] == unvisited){
                success = 0;
                break;
            }
        }

        if (success){
            printf("%lld\n", g.maxxer);
        }
        else printf("IMPOSSIBLE\n");

        scanf("%d %d", &cities, &edges);
    }


}