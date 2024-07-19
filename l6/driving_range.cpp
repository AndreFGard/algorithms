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


/*kruskal creates many connected acyclic components, and new edges are only added 
if they dont connect edges previously connected. One way to check if two nodes are connected is to check
if the root of their tree is the same, and this should be done before any addition. 
*/
int setfind(vector<int>&set, int s){
    if (set[s] == s) return s;
    int newparent = setfind(set, set[s]);
    return set[s] = newparent;

}

void unionset(vector<int>&set, int a, int b){
    int ra = setfind(set, a); int rb = setfind(set, b);
    if (ra != rb) set[ra] = rb;
}

void kruskal(graph &g){
    int edgecnt = 1;
    int size= g.mark.size();
    //vector<pair<pair<lli,int>, int>> hp (size);
    priority_queue<pair<pair<lli,int>, int>, vector<pair<pair<lli,int>, int>>, greater<pair<pair<lli,int>, int>>> hp;
    //graph newgraph = graph(size);

    // //pegar todas as edges e ordenar
    // for (int i = 0;i<size;i++){
    //     for (auto w: g.adjlist[i]){
    //         hp[edgecnt++] = make_pair(make_pair(w.first, w.second), i);
    //     }
    // }
    // make_heap(hp.begin(), hp.end(), greater<pair<pair<lli,int>,int>>());

    //pegar todas as edges e ordenar
    for (int i = 0;i<size;i++){
        for (auto w: g.adjlist[i]){
             hp.push(make_pair(make_pair(w.first, w.second), i));
        }
    }



    int numMST = size;
    vector<int> set (size);
    for (int j = 0; j<size;j++){ set[j]=j;}

    while (numMST > 1){
        if (hp.empty()) break;
        //auto t = hp.back(); pop_heap(hp.begin(),hp.end()); hp.pop_back();
        auto t = hp.top(); hp.pop();
        int a = t.first.second; int b = t.second; lli w = t.first.first;
        if (setfind(set, a) != setfind(set,b)){
            unionset(set, a,b);
            //newgraph.adjlist[a].push_back(make_pair(w, b ));
            numMST -= 1;

            //store maximum weight found
            g.maxxer = w > g.maxxer ? w : g.maxxer;
            }
    }
    //mark if all vertices are connected
    int fd = setfind(set, 0);
    for (int i  = 0; i<size; i++){
        if (setfind(set, i) != fd){
            g.mark[0] = unvisited;
            //puts("went wrong");
            break;
        }
        else g.mark[i] = visited;
    }

    
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

        kruskal(g);
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