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



std::queue<int>& BFS_minimum_edge_path(graph *g, int a, int b){
    std::queue<int> q;
    q.push(a);

    static std::queue<int> path;
    setMark(g,a,VISITED);
    while (!q.empty()){
        a = q.front();
        q.pop();
        path.push(a);

        if (a == b) {
            return path;
        }

        int w = first_v(g,a);
        while (w!= -1){
            if (getMark(g,w) == UNVISITED){
                setMark(g,w,VISITED);
                q.push(w);
                if (w == b) {
                    path.push(w);
                    return path;
                }
            }
            w = next(g,a,w);
        }


    }

    return path;
}

int test(){
    graph *g = create_graph();
    int (*m)[10] = g->m;
    m[1][2] = m[2][3] = m[3][4] = m[4][5] = m[2][5] = 1;
    std::queue<int>& q =  BFS_minimum_edge_path(g,1,5);
    cout << "over";

    while (!q.empty()) {
        printf("%d ", q.front());
        q.pop();
    }
    return 0;

}

int main(){
 test();    
}