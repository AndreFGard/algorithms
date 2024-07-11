#include <bits/stdc++.h>

#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define unvisited -1
#define visited -2


typedef struct graph
{
    vector<int> mark;
    vector<vector<pair<int,int>>> adjlist;


    graph(int n){
        adjlist.resize(n);
        mark.resize(n, unvisited);
    }
}graph;


vector<pair<int,int>> dijkstra(graph &g, int s, int dest){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> fringe;
    vector<pair<int,int>> delta (g.mark.size(), make_pair(-1, 1000*1000));

    
    fringe.push(make_pair(0, s));
    for (int i = 0, size = g.mark.size(); i<size; i++){
        pair<int, int> t;
        do{
            if (fringe.size() == 0) break;
            t = fringe.top(); fringe.pop();
            
            }
        while (g.mark[t.second] != unvisited);

        int p = t.second; int pw = t.first;
        g.mark[p] = visited;


        if (p == dest)return delta;
            
        for (auto &adj: g.adjlist[p]){
            int w = adj.first; int b = adj.second;

            if ( g.mark[b] != visited){
                //if it has not been added to our new graph yet or must replace someone else
                if ((delta[b].first == -1)||(delta[b].first > w)){
                    fringe.push(make_pair(w+pw, b));
                    delta[b].first = w + pw; delta[b].second = p;


                }
            }
        }
    }
    vector<pair<int,int>> fail;
    return fail;
}
#define inf 10000000
vector<pair<int,int>> dijkstra_professor(graph &g, int s, int d){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> fringe;
    vector<pair<int,int>> delta (g.mark.size(), make_pair(inf,inf ));
    

    fringe.push(make_pair(0, s));
    delta[s] = make_pair(0, s);
    for (int i = 0, size =g.adjlist.size(); i< size; i++){
        int weightp,v;
        do {
            if(fringe.size() == 0) 
                break;
            pair<int,int> temp = fringe.top(); fringe.pop();
            v = temp.second; weightp = temp.first;
            if (v == d) return delta;
        } while (g.mark[v] != unvisited);

        g.mark[v] = visited;
        int w;
        for (auto t: g.adjlist[v]){
            if ((g.mark[t.second] != visited) && (delta[t.second].first > (weightp + t.first))){
                delta[t.second].first = weightp + t.first;
                delta[t.second].second = v;

                fringe.push(make_pair(weightp + t.first, t.second));
            }
        }
    }
    vector<pair<int,int>> path;
    return path;
}


void addedge(graph &g, int a, int b, int w){
    g.adjlist[a].push_back(make_pair(w,b));
}


void print_path(vector<pair<int,int>> &path, int s, int d){
    int size = path.size() ;
    if ( size  == 0){
        puts("unreachable");
        return;
    }

    int cv = d;
    int w  = path[cv].first;
    printf("%d\n",w);

}
int main(){

    int cases;
    scanf("%d", &cases);
    for (int c = 0; c<cases; c++){
        int vertices, edges, s, t;
        scanf("%d %d %d %d", &vertices, &edges, &s, &t);
        graph g = graph(vertices);
        
        for (int e = 0; e<edges; e++){
            int va, b,w;
            scanf("%d %d %d", &va, &b, &w);
            addedge(g,va,b,w);
            addedge(g,b,va,w);
        }

        for (int i = 0; i< g.adjlist.size(); i++)
            sort(g.adjlist[i].begin(), g.adjlist[i].end());
        

        vector<pair<int,int>> path = dijkstra_professor(g, s, t);
        printf("Case #%d: ", c+1); print_path(path, s, t);
    }
}