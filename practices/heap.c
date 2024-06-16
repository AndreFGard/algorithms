#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//a bin tree wehere theres parental domninance and shape (a complete bin tree)
typedef int data;
typedef struct heap{
    int maxsize;
    int currsize;
    data arr[10];
} heap;

int heapify(heap *hp, int i){
    if ((!(hp->arr[i] <= hp->arr[i/2])) && i/2 != 0){
    	int temp = hp->arr[i];
    	hp->arr[i] = hp->arr[i/2];
    	hp->arr[i/2] = temp;
    	return heapify(hp, i/2);
    }
    return 0;
}

int insert(heap *hp, int k, int v){
	hp->arr[(hp->currsize++ +1)] = k;
	heapify(hp, hp->currsize);
}

int print_heap(heap *hp){
//	char stuff = malloc(sizeof(char) * hp->currsize * hp->currsize);
//	memset(" ", hp->currsize * hp->currsize, 1);

	for (int i = 0; i<( 1+ hp->currsize/2);i++ ){
		if (hp->arr[i] != -1) printf("%d:   %d\n%d        %d\n", i, hp->arr[i], hp->arr[i*2],hp->arr[i]*2);
		else puts("ëmpty");
	}
	for (int i = 0; i<10;i++ ) printf("%d ", hp->arr[i]);
}

int main() {
	heap hp;
	hp.currsize = 1;
	int nums[] = {2, 9, 7, 6, 5, 8, 10};
	int n  = 7;
	for (int i = 0; i <10; i++) hp.arr[i]=-1;
	
	hp.arr[1] = 2;
	for (int i = 1; i<n; i++){
		insert(&hp, nums[i], nums[i]);
	}
	print_heap(&hp);
}

