#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 5002
typedef struct heap{
    int *data;
    int cursize;
    int maxsize;
}heap;

void fix_parental_dominance(heap *hp, int i){
    int *H = hp->data;
    int n = hp->cursize;

    int k = i;
    int v = H[k];
    int done = 0;

    while (!done && 2*k <= n){
        int j = 2*k;
        
        //choose the smalest of the brothers
        if (j<n){// if brother exists
            if (H[j] > H[j+1]){
                j++;
                }
        }

        //if parent smaler than smalest child
        if (v <= H[j]){
            done = 1;
        }
        else {
            H[k] = H[j]; //put son in fathers place
            k = j; // switch focus to the used-to-be son's place
        }
    }
    H[k] = v; // put father in sons place, if needed    
}

void bottomup(heap *hp, int nums[], int n){
    if (n <= 0) return;
    hp->cursize = n;

    int *H = hp->data;
    
    //if nums not copied already
    if (nums) memcpy(&hp->data[1], nums, n*sizeof(int));

    //heapify
    for (int i = n/2; i>0;i--){
        fix_parental_dominance(hp, i);

    }
    return;
    
}

void topdown_insert(heap *hp, int x){
    int *H = hp->data;
    if (hp->cursize + 1 < hp->maxsize) {
        H[hp->cursize+1] = x;
        hp->cursize++;
    } else return;

    int done = 0; int parent = hp->cursize/2; int child = hp->cursize;
    while (!done && parent != 0){
        if (x >= H[parent]){
            done = 1;
        }
        if (x < H[parent]){
            H[child] = H[parent];
            H[parent] = x;
            child = parent;
        }
        parent = parent/2;
    }
}

int root_deletion(heap *hp){
    if (hp->cursize <= 0) return 0;
    int *H = hp->data;
    int v = H[1];

    H[1] = H[hp->cursize];
    H[hp->cursize] = v;
    hp->cursize--;

    //parental dominance
    fix_parental_dominance(hp, 1);
    return v;
    
}

int *heapsort(heap *hp, int n){
    for (int i = 0; i<n-1;i++){
        root_deletion(hp);
    }
    return &hp->data[1];
}

int sumArr(int *data, int n){
    long long int total = 0;
    for (int i = 0; i<n;i++)
        total += data[i];
    return total;
}

long long getCost_old(int *data, int n){
    long long int cost = 0;
    long long int past = data[0];
    for (int i =1; i<n-1; i++){
        cost += data[i] + past;
        past = data[i] + past;
    }
    return cost;
}

long long getCost(heap *hp, int n){

    long long int cost = 0;
    int a, b;
    for (int i = 0; i<(n-1);i++){
        a = root_deletion(hp);
        b = root_deletion(hp);

        cost += a + b;
        //hp->data[hp->cursize+1] = a + b;
        //hp->cursize++;
        topdown_insert(hp, a + b); //using this instead
        // of bottom-upping always makes the code 10 times faster!

        
    }

    return cost;
}

void test(){
    int n = -1;
    //scanf("%d", &n);
    
    heap hp;
    hp.data = (int *) malloc(sizeof(int)*MAX_SIZE);
    hp.cursize = 0;
    hp.maxsize = 5000; 

    int nums[] = {6,5,4,3,2,1};
    bottomup(&hp, nums, sizeof(nums)/sizeof(int));
    int j;// = root_deletion(&hp);
    j = getCost(&hp,sizeof(nums)/sizeof(int) );
    printf("%d\n", j);
    //root_deletion(&hp);
    //root_deletion(&hp);
    //int *sorted = heapsort(&hp, sizeof(nums)/sizeof(int));
    //int cost = getCost(sorted, sizeof(nums)/sizeof(int));

   nums[1] = 9;
}

int main(){
    //test();
    heap hp;
    hp.data = (int *) malloc(sizeof(int)*MAX_SIZE);
    hp.cursize = 0;
    hp.maxsize = 5000; 

    int n = 0;
    scanf("%d", &n);
    while(n != 0){

        //fill array
        for (int i = 0; i<n;i++){
            scanf("%d", &hp.data[i+1]);
        }
        //heapify it
        bottomup(&hp, NULL, n);
        
        //int *sorted = heapsort(&hp, n);
        printf("%lld\n", getCost(&hp, n));

        hp.cursize = 0;
        scanf("%d", &n);
    } 

}