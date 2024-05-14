#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct { 
    int front;
    int rear;
    int size;
    datatype *arr;
}ArrayQueue;
// the arr must be allocated with an extra space

datatype Aenqueue (ArrayQueue *q, datatype value) {
    if (((q->rear + 2)% q->size) == q->front % q->size) puts("GIGA WHOOPS");
    q->rear = (q->rear + 1 ) % q->size;
    q->arr[(q->rear)%q->size] = value;
    return value;
}

datatype Adequeue(ArrayQueue *q) {
    //empty queue condition 
    if (((q->rear + 1 - q->front) % q->size) == 0) puts("whoops"); //what should i return?
    datatype el = q->arr[q->front % q->size];
    q->front = (q->front + 1) % q->size;
    return el;
    
}


ArrayQueue make_queue(int size, datatype arr[]) {
    ArrayQueue temp;
    temp.size = size + 1;
    temp.front = 1; temp.rear = 0;
    if (!arr) temp.arr = alloca(sizeof(int) * size + 1);
        else temp.arr = arr;

    return temp;
}

int main() {

    int test[] = {877, 9,8,7,6,5};
    ArrayQueue q = make_queue(5, NULL);
    int el;
    for (int i = 0; i < 5; i++) {
        el = Aenqueue(&q, test[i]);
    }
    el = Adequeue(&q);
    el = Aenqueue(&q, 656);
    el = Aenqueue(&q, 9999);
}