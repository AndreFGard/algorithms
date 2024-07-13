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
int inf = 10000000;
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

vector<pair<int,int>> primms(graph &g){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> fringe;
    vector<pair<int,int>> delta (g.mark.size(), make_pair(inf,inf ));

    fringe.push(make_pair(0,0));
    delta[0] = make_pair(0,0);
    for (int i = 0, size = g.mark.size(); i<size; i++){
        int p,pw;
        do{
            pair<int,int> t = fringe.top(); fringe.pop();
            pw = t.second; p = t.first;
        } while (g.mark[p] != unvisited);
        g.mark[p] = visited; //the vertice's parent was already added in delta

        for (auto t: g.adjlist[p]){
            if ((g.mark[t.second] != visited) && (delta[t.second].first > (pw + t.first))){
                delta[t.second].first = pw + t.first;
                delta[t.second].second = p;

                fringe.push(make_pair(pw + t.first, t.second));
            }
        }

    }
    return delta;
}



void addedge(graph &g, int a, int b, int w){
    g.adjlist[a].push_back(make_pair(w,b));
}
int main(){
    graph a = graph(10);
    
    addedge(a, 0, 3, 20);
    addedge(a, 0, 1, 10);

    
    addedge(a, 0, 2, 3);

    addedge(a, 2, 1, 2);
    addedge(a, 2, 4, 15);

    addedge(a, 1, 3, 5);

    addedge(a, 3, 4, 11);
    // addedge(a, 4, 5, 100);
    // addedge(a, 4, 6, 10);
    // addedge(a, 5, 6, 10);
    // addedge(a, 5, 7, 5);
    // addedge(a, 6, 7, 120);


    for (int i = 0; i< a.adjlist.size(); i++)
        sort(a.adjlist[i].begin(), a.adjlist[i].end());
    
    vector<pair<int,int>> path = dijkstra(a, 0, 8);
    printf("%d\n", path.size());

    int gg = 4;
}