#include <stdio.h>
#include <algorithm>
#include <vector>


void printmatrix(int *m, int lines, int cols) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", *(m + i * cols + j));
        }
        printf("\n");
    }
}



using namespace std;
int main(){

    int k[2][3];
    k[1][2] = 9;

    int size; int nitems;
    scanf("%d %d", &size, &nitems);
    vector<pair<int,int>> items;
    for (int i = 0; i< nitems;i++){
        int value,wt;
        scanf("%d %d", &wt,&value);
        items.push_back(make_pair(value,wt));
    }
    //sort(items.begin(),items.end());

    nitems++; size++;
    int knp[nitems][size];
    for (int i = 0;i<nitems;i++)for(int j = 0; j<size;j++)knp[i][j] = 0;

    
    for (int l = 1; l<nitems;l++){
        pair<int,int> p = items[l-1];
        for (int c = 1; c<size; c++){
            if(p.second <= c){
                int upperval = knp[l-1][c]; //the maximum weight we obtained WITHOUT this item
                int withval = knp[l-1][max(0, c - p.second)] + p.first; 
                // what we got without this item, since we gonna add it rn, removing enough items
                //so that we free up enough of the knapsack
                int chosen = max(upperval, withval);
                knp[l][c] = chosen;
            }
            else knp[l][c] = knp[l-1][c];
        }
    }

    printf("%d\n", knp[nitems-1][size-1]);


}