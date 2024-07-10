#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define unvisited -1
#define visited 1


typedef struct graph
{
    vector<int> mark;
    vector<vector<pair<int,int>>> adjlist;


    graph(int n){
        adjlist.resize(n);
        mark.resize(n, unvisited);
    }
}graph;


#define added -3
vector<int> dijkstra(graph &g, int s, int dest){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> fringe;
    vector<pair<int,int>> delta (g.mark.size(), make_pair(-1, 1000*1000));
    vector<int> newpath;
    
    fringe.push(make_pair(0, s));
    while (!fringe.empty()){
        pair<int, int> t;
        do{
            t = fringe.top(); fringe.pop();}
        while (g.mark[t.second] == added);

        int p = t.second; int pw = t.first;
        g.mark[p] = added;
        newpath.push_back(p);

        if (p == dest)return newpath;
            
        for (auto &adj: g.adjlist[p]){
            int w = adj.first; int b = adj.second;

            if ( g.mark[b] != added){
                //if it has not been added to our new graph yet or must replace someone else
                if ((delta[b].first == -1)||(delta[b].first > w)){
                    fringe.push(make_pair(w+pw, b));
                    delta[b].first = w + pw; delta[b].second = p;


                }
            }
        }
    }
    vector<int> fail;
    return fail;
}
void addedge(graph &g, int a, int b, int w){
    g.adjlist[a].push_back(make_pair(w,b));
}
int main(){
    graph a = graph(5);
    
    addedge(a, 0, 3, 20);
    addedge(a, 0, 1, 10);
    addedge(a, 0, 2, 3);

    addedge(a, 2, 1, 2);
    addedge(a, 2, 4, 15);

    addedge(a, 1, 3, 5);

    addedge(a, 3, 4, 11);
    


    for (int i = 0; i< a.adjlist.size(); i++)
        sort(a.adjlist[i].begin(), a.adjlist[i].end());
    
    vector<int> path = dijkstra(a, 0, 4);
    int gg = 4;
}