
#include <stdio.h>

#include <bsd/stdlib.h>
int comparator(const void * a, const void *b) {
    if (*(int *)a < *(int *)b) return -1;
    else if (*(int *)a == *(int *)b) return 0;
    else return 1;
}

int main() {
    int stuff[] = {9, 5, 25, 28, 27, 2, 15, 18, 26, 14, 13, 6, 16, 10, 12, 29, 23, 8, 19, 1, 17, 20, 22, 11, 7, 21, 24, 3, 4, 14};
    int size = sizeof(stuff)/sizeof(int);

    mergesort(stuff, size, sizeof(int) , &comparator);

    for (int i = 0; i<size; i++) {
        printf("%d, ", stuff[i]);
    }

}
