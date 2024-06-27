#include <stdio.h>
#include <stdlib.h>
#include "matrix_graph.c"
//sorry, i need a queue
#include <iostream>
#include <queue>
using namespace std;

//breadth first search, a cautious traversal.
//uses a queue and has the same efficiency as DFS.
/*  it can be used to find the path with the smallest
n of edges between two vertices by stopping as soon as the other vertex is reached.
cannot, however, find articulation points like the dfs can

algorithm:
    push every vertex whose children we must 
    find to the queue, including the starting v.
    Then, for each child of the vertex we took from the queue,
    mark each of it's children as visited and add it to the queue,
    so that it's children will be found in the future.
*/



void BFS(graph *g, int v){
    std::queue<int> q;
    q.push(v);
    setMark(g,v,VISITED);
    while (!q.empty()){
        v = q.front();
        q.pop();
        int w = first_v(g,v);
        while (w != -1){
            if (getMark(g,w) == UNVISITED){
                setMark(g,w,VISITED);
                q.push(w);
            }
            w = next(g,v,w);
        }
    }
}

int test(){
    graph *g = create_graph();
    int (*m)[10] = g->m;
    m[4][2] = m[2][4] = m[1][2] = m[1][4] = 1;
    BFS(g,1);
    cout << "over";
    return 0;

}

int main(){
    return test();
}