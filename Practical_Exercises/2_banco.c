#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int id;
    struct node *next;

} node;

typedef struct {
    int *arr;
    int rear;
    int front;
    int size;
    int maxSize;
} Aqueue;

int temp;


int extend(Aqueue *l){
    int m = l->maxSize;
    int *temparr = malloc(2*sizeof(int)*l->maxSize);
    memcpy(temparr, l->arr, sizeof(int)*l->maxSize);
    l->maxSize = l->maxSize * 2;

}

int enqueue(Aqueue *l, int id){
    if (l->size == l->maxSize -1) extend(l);
    l->rear = (l->rear + 1) % l->maxSize;
    l->arr[l->rear] = id;
    l->size++;
    return 5;
} // 

int dequeue(Aqueue *l) {
    if (l->size == 0) return 0;
    l->front = (l->front + 1) % l->maxSize;
    l->size--;
    return 5;
}

int main() {
    char stopper[] = "end";
    char entr[1000] = "linux rocks";

    Aqueue l;
    l.arr = malloc(200*5000*sizeof(int));
    l.maxSize = 200*5000;
    l.front = l.rear = 0;
    l.rear = -1;
    l.size = 0;

    int solved = 0;

    scanf("%s", entr);
    int tempn;
    while (strcmp(entr, stopper) != 0) {
        if (entr[0] == 'a'){
            //ADD
            scanf("%d", &tempn);
            enqueue(&l, tempn);
        }
        else if (entr[0] == 's' && entr[1] == 't') {
            // STATS
            printf("%d %d\n", solved, l.size);

        }
        else if (entr[0] == 's') {
            //SOLVE
            temp = dequeue(&l);
            if (temp) {
                solved++;
            }
        }
        else if (entr[0] == 'p') {
            if (l.size){
                for (int i = l.front; i < l.rear; i++){
                    printf("%d ", l.arr[i]);
                }
                printf("%d\n",l.arr[l.rear]);
            }
            else printf("x\n");

        }
        
        scanf("%s", entr);


    }


}