#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string.h>
#include <algorithm>
#include <string>

#define NODELTA 0

#define VISITED 1
#define UNVISITED 0
#define UNDEFINED 2* 1e9
#define NOPRED -1
int successes = 0;
typedef struct rankel{
    int r;
    std::string s;
} rankEl;

typedef struct graph {
    std::vector<int> *mark; 
    std::vector<std::vector<int>*> m; //graph
    std::vector<int> *distances;
    std::vector<std::string> i_to_s; //same as map<int, char*>
    std::map<std::string, int> s_to_i; // the opposite
    std::vector<int> *curr; //current adjacent vertex idx for each vertex
    int size = -1;
}graph;

void setMark(graph *g, int v, int mark){
    (*g->mark)[v] = mark;
}

int getMark(graph *g, int v){
    return (*g->mark)[v];
}

int first_v(graph *g, int v){
    int w = -1;
    if (g->m[v]->size() > 0){
        w = g->m[v]->front();
    }
    (*g->curr)[v] = 0;
    return w;
}

//returns the next VERTEX
int next_v(graph *g, int v){
    int curr = 1 + (*g->curr)[v]++;
    
    if (g->m[v]->size() > curr){
        return (*g->m[v])[curr];
    }
    (*g->curr)[curr -1] = 0;
    return -1;
}

graph *makeGraphh(int size){
    graph *temp = new graph;

    temp->distances = new std::vector<int> (size, NOPRED);
    temp->curr = new std::vector<int> (size);
    temp->mark = new std::vector<int> (size);
    for (int i = 0; i<size;i++){
        temp->m.push_back(new std::vector<int>);
    }
    
    return temp;
}

int addVertex(graph *g, std::string a){
    int an;
    //int ee = g->s_to_i.end();
    auto ait = g->s_to_i.find(a);
    if (g->s_to_i.find(a) == g->s_to_i.end()) {
        // if a not found
        an = g->size = g->i_to_s.size();
        g->i_to_s.push_back(a);
        g->s_to_i[a] = an;
    }
    else an = ait->second;
    return an;
}

void addEdge(graph *g, int a, int b){
    g->m[a]->push_back(b);
    g->m[b]->push_back(a);
}

void addTeam(graph *g, std::string a, std::string b, std::string c){
    int an,bn,cn;
    an = addVertex(g,a);
    bn = addVertex(g,b);
    cn = addVertex(g,c);

    addEdge(g,an,bn);
    addEdge(g,an,cn);
    addEdge(g,bn, cn);

}

int closest_to_ahmad(graph *g, int a){
    //this is the only function that actually relies on the specification of the problem.
    //hopefully this makes it much faster, and i dont need to 
    // change the types used in the graph
    int v = first_v(g, a);
    std::vector<int> friends;


    while(v != -1){
        if ((*g->distances)[v] != NOPRED){
            // if the vertex's distance has not been calculated
            friends.push_back((*g->distances)[a]);
        }
        else {
            for (auto vv : friends){
                (*g->curr)[v] = 0;
            }
            return -1;
        }
        v = next_v(g, a);
    }

    int distance =  *std::min_element(friends.begin(), friends.end());
    (*g->distances)[a] = distance + 1;
    return distance;

    

}
//i tried to consider the precalculated distances, but it made the program 3x slower
std::vector<int> BFS(graph *g, int a, int b){
    std::queue<int> q;
    q.push(a);

    std::queue<int> oldpath;
    std::vector<int> pred (g->m.size(), NOPRED);
    pred[a] = a; //mark the starting point

    setMark(g, a, VISITED);
    while (!q.empty()){
        //pred[q.front()] = a;

        a = q.front();
        q.pop();
        oldpath.push(a);

        if (a == b){
            return pred;
        }
        
        int w = first_v(g,a);

        while (w!= -1){
            if (getMark(g, w) == UNVISITED){
                setMark(g,w,VISITED);
                q.push(w);
                pred[w] = a;
                
                if (w == b){
                    oldpath.push(w);
                    return pred;
                }
            }
            w = next_v(g,a);
        }

    }
    return pred;
}



#include <stdio.h>

void zeroOutVec(std::vector<int>& v, int n){
    for (int i = 0; i<n; i++){
        v[i] = UNVISITED;
    }
    return;
}

int getNPred(std::vector<int> &pred, int v, int d){
    int n = 0;
    int dad = d;

    if (v == d) return 0;

    if (pred[d] == NOPRED){
        return UNDEFINED;
    }
    while((dad = pred[dad]) != v){
        n++;
    }
    n++;
    return n;
}


int getDistance(graph *g, int a, int b){
    int distance = closest_to_ahmad(g, a);
    if (distance != -1){
        successes++;
        return distance;
    }

   std::vector<int> pred = BFS(g, a, b);

    distance = getNPred(pred, a, b);

    if (distance != UNDEFINED)
        (*g->distances)[a] = distance;
    return distance;

}

void printMap(std::vector<std::pair<int, std::string>> &mp){
    for (auto it:mp){
        std::string rank = std::to_string(it.first);
        if (it.first == UNDEFINED) rank = "undefined";
        std::cout << it.second << " " <<  rank << std::endl;
    }
    return;
}

bool rankElComp(rankEl a, rankEl b){
    if (a.r < b.r){
        return true;
    }
    else if(a.s < b.s){
        return true;
    }
    else return false;
}

int main(){
    
    int c = 2;
    scanf("%d", &c);
    for (int ncase  =0; ncase<c;ncase++){
        int n = 20; //team
        scanf("%d", &n);
        graph *g = makeGraphh(n*3);

        int ahmadPos = -1;
        for (int t = 0; t<n;t++){
            char *name[] = {(char*) malloc(sizeof(char)*60),
                            (char*) malloc(sizeof(char)*60),
                            (char*) malloc(sizeof(char)*60)};

            name[0][0] = name[1][0] = name[2][0] = '\0';
            scanf("%s %s %s", name[0], name[1], name[2]);

            addTeam(g, name[0], name[1], name[2]);

            //ahmad finder
            if (ahmadPos == -1) {
                for (int ahmad = 0; ahmad<3;ahmad++){
                    if (strcmp(name[ahmad], "Ahmad") == 0){
                        ahmadPos = g->s_to_i[name[ahmad]];
                        break;
                    }
                }
            }
        }

        std::vector<std::pair<int, std::string>> vrank;

        //iterate over each 
        for (auto iter = g->s_to_i.begin(); iter != g->s_to_i.end(); iter++){
            //std::vector<int> predecessors = BFS(g, iter->second, ahmadPos);
            
            //std::pair<int, std::string> el (getNPred(predecessors,iter->second, ahmadPos), iter->first);
            std::pair<int, std::string> el (getDistance(g, iter->second,ahmadPos), iter->first);
            zeroOutVec(*g->mark, g->mark->size());
            zeroOutVec(*g->curr, g->curr->size());
            vrank.push_back(el);
        }

        std::sort(vrank.begin(), vrank.end());
        std::cout << vrank.size() << std::endl;

        printMap(vrank);
        delete g;
        
    }
    
}
    

