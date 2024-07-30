#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>
#include <queue>
#define unvisited -1
using namespace std;
#define visited -2
const char spike = 's' * (-1);
const char wall = '#' * (-1);
const char open = '.' * (-1);
const char start = '@' * (-1);
const char treasure = 'x' * (-1);
vector<vector<char>> m;
vector<vector<char>> mback;
vector<vector<int>> stor;
int rows, cols, spikejumps;

// i dont code like this usually, sorry
int backfs(int xo, int yo, int hearts);



int bfs(int xo, int yo, int hearts){
    int result = 0;

    if (m[yo][xo] == spike) hearts--;
    else if(m[yo][xo] == treasure){
        result = backfs(xo,yo,hearts);
        if (result) return result;
        return 0;
    }

    if(hearts<0) return 0;

    int bak = m[yo][xo];
    m[yo][xo] = visited;

    if (((xo -1)>=0)&&(m[yo][xo-1] != visited)&&(m[yo][xo-1] != wall)){
        result = bfs(xo-1,yo,hearts);
        if (result){ m[yo][xo] = bak; return result;}

    }

    if(((xo +1)<cols)&&(m[yo][xo+1] != visited)&&(m[yo][xo+1] != wall)){
        result = bfs(xo+1,yo,hearts);
        if (result){ m[yo][xo] = bak; return result;}
    }

    if((yo+1 < rows)&&(m[yo+1][xo] != visited)&&(m[yo+1][xo] != wall)){
        result = bfs(xo,yo+1,hearts);
        if (result){ m[yo][xo] = bak; return result;}
    }

    if((yo-1 >= 0)&&(m[yo-1][xo] != visited)&&(m[yo-1][xo] != wall)){
        result = bfs(xo,yo-1,hearts);
        if (result){ m[yo][xo] = bak; return result;}
    }

    m[yo][xo] = bak;
    return 0;
}

int backfs(int xo, int yo, int hearts){
    if (mback[yo][xo] == spike) hearts--;
    else if(mback[yo][xo] == start){
        return hearts+1;
    }

    if(hearts<0) return 0;

    int bak = mback[yo][xo];
    mback[yo][xo] = visited;
    
    int result = 0;
    if (((xo -1)>=0)&&(mback[yo][xo-1] != visited)&&(mback[yo][xo-1] != wall)){
        result = backfs(xo-1,yo,hearts);
        if (result){ m[yo][xo] = bak; return result;}

    }

    if(((xo +1)<cols)&&(mback[yo][xo+1] != visited)&&(mback[yo][xo+1] != wall)){
        result = backfs(xo+1,yo,hearts);
        if (result){ mback[yo][xo] = bak; return result;}
    }

    if((yo+1 < rows)&&(mback[yo+1][xo] != visited)&&(mback[yo+1][xo] != wall)){
        result = backfs(xo,yo+1,hearts);
        if (result){ m[yo][xo] = bak; return result;}
    }

    if((yo-1 >= 0)&&(mback[yo-1][xo] != visited)&&(mback[yo-1][xo] != wall)){
        result = backfs(xo,yo-1,hearts);
        if (result){ m[yo][xo] = bak; return result;}
    }

    mback[yo][xo] = bak;
    return 0;
}




int main(){
    
    scanf("%d %d %d", &rows,&cols,&spikejumps);
    queue<pair<int,int>> doors;
    m.resize(rows);
    mback.resize(rows);
    stor.resize(rows);
    for ( int i = 0; i<rows;i++){
        stor[i].resize(cols, unvisited);
        char line[50];
        scanf("%s", line);
        //why didnt i use chars?
        for (int c = 0;c<cols;c++){
            if (((-1) * line[c]) == start)
                doors.push(make_pair(i,c));
            m[i].push_back((-1) * line[c]);
            mback[i].push_back((-1) * line[c]);
        }
    }

    while(!doors.empty())
        {
            auto t = doors.front();doors.pop();
            if (bfs(t.second,t.first, spikejumps))
               { printf("%s\n", "SUCCESS" );return 0;}
                
        }
    printf("%s\n", "IMPOSSIBLE");
}