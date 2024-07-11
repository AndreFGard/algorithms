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
vector<pair<int,int>> dijkstra(graph &g, int s, int dest){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> fringe;
    vector<pair<int,int>> delta (g.mark.size(), make_pair(-1, 1000*1000));

    
    fringe.push(make_pair(0, s));
    while (!fringe.empty()){
        pair<int, int> t;
        do{
            t = fringe.top(); fringe.pop();}
        while (g.mark[t.second] == added);

        int p = t.second; int pw = t.first;
        g.mark[p] = added;


        if (p == dest)return delta;
            
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
int main(){
    graph a = graph(8);
    
    addedge(a, 0, 3, 20);
    addedge(a, 0, 1, 10);

    
    addedge(a, 0, 2, 3);

    addedge(a, 2, 1, 2);
    addedge(a, 2, 4, 15);

    addedge(a, 1, 3, 5);

    addedge(a, 3, 4, 11);
    addedge(a, 4, 5, 100);
    addedge(a, 4, 6, 10);
    addedge(a, 5, 6, 10);
    addedge(a, 5, 7, 5);
    addedge(a, 6, 7, 120);


    for (int i = 0; i< a.adjlist.size(); i++)
        sort(a.adjlist[i].begin(), a.adjlist[i].end());
    
    vector<pair<int,int>> path = dijkstra_professor(a, 0, 7);

    int gg = 4;
}