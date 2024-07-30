#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>
#include <queue>
#define unvisited -1
using namespace std;
#define visited -2

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> &p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

unordered_set<pair<int,int>, pair_hash> que;

vector<vector<int>> m;
vector<pair<int,int>> specs;

int valid(int x, int y){
    if((y>-1) && (y < specs.size()))
        if ((x >= specs[y].first) && (x<= specs[y].second))
            return 1;
    return 0;
    
}

int colChange[] = {-1, 1, -2, 2, -2, 2, -1,1};
int rowChange[] = {-2, -2, -1, -1, 1, 1, 2,2};

//this is 100% flawed, should be erased.
// i just realized that the statement says that a spot should not be visited twice
int bfs(int startx, int starty){
    
    queue<pair<int,int>> q;

    int n = m.size();
    int r, c;

    m[starty][startx] = visited;
    q.push(make_pair(starty,startx));
    que.insert(make_pair(starty,startx));
    while (!q.empty()){
        auto t = q.front(); q.pop();
        int startx = t.second;
        int starty = t.first;

        for (int i = 0;i<8;i++){
            c = startx + colChange[i];
            r = starty + rowChange[i];
            if ( valid(c, r)){
                que.insert(make_pair(r, c));
                if (m[r][c] != visited){
                    m[r][c] = visited;
                    q.push(make_pair(r,c));
                }
                
            }
        
        }
        int k = q.size();
    }
    return 1;
}

int newtraversal(int stx, int sty, int reached){
    int oldreached =  m[sty][stx];
    if (!m[sty][stx]) 
        m[sty][stx] = 1;
    m[sty][stx] *= -1; //////change this
    int maxxer = 0;

    for (int comb = 0; comb<8; comb++){
        int nc = colChange[comb] + stx;
        int ny = rowChange[comb] + sty;

        if (valid(nc, ny)){
            //check if it's not in our recursion:
            if (m[ny][nc] > -1){
                int t = newtraversal(nc,ny, 0);
                maxxer = (t >= maxxer) ? t+1 :maxxer;
                //m[ny][nc] *= -1;
            }
        }
    }

    //return m[sty][stx] = max(oldreached, maxxer);
    m[sty][stx] = max(oldreached, maxxer);
    return maxxer;
    
}





int main(){
    int n;
    int casecount = 1;
    scanf("%d",&n);
    while (n){

        m.resize(10);
        specs.resize(n);
        int area = 0;
        for (int i  =0; i<n;i++){
            int startx, nel;
            scanf("%d %d", &startx, &nel);

            area += nel;
            m[i].resize(10, 0);
            specs[i] = make_pair(startx,startx + nel-1);
        }
        int difference = area - 1 - newtraversal(specs[0].first, 0, 0);
        if (difference == 1)
            printf("Case %d, %d square can not be reached.\n",casecount++,difference);
        else printf("Case %d, %d squares can not be reached.\n",casecount++,difference);
        //printf("%d\n", area - que.size());
        que.clear();

        scanf("%d",&n);
    }

}