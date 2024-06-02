
#include <stdlib.h>
#include <stdio.h>
int arr[1001];
#define fail 0
#define queue(second, st) arr[st] = second


int main() {
    int n_tests; scanf("%d", &n_tests);
    int n_students, second, comes, goes;
    
    for (int t = 0; t<n_tests; t++){
        second = 1;

        scanf("%d", &n_students);
        for (int st = 0; st < n_students; st++) {
            scanf("%d %d", &comes, &goes);

            if (second < comes) second = comes;
            else if (second > goes){
                figureout(fail, st);
                continue;
            }

            //glupt glupt, tomar chá
            figureout(second, st);
            second++;
        }
        if (n_students){
            printf("%d", arr[0]);
            for (int st = 1; st < n_students; st++)
                printf(" %d",arr[st]);
            puts("");
        }
    }
}
