
#include <stdio.h>

typedef long int li;
int quicksort(li nums[], int start, int end) {

    int p = nums[start];
    int i = start + 1;
    int j = end;

    li holder;
    while ( i<j) {

        //procurar até achar um maior igual
        while (i <= end && nums[i] < p) {
            i++;
        }

        //  procurar ate achar um menor igual
        while (nums[j] > p) {
            j--;
        }


        // trocar os elementos
        holder = nums[i]; nums[i] = nums[j];
        nums[j] = holder;
        i++; j--;
        }
        //desfazer ultimo swap que foi feito inadequadamente
        holder = 37;
        i--; j++;
        holder = nums[i];
        nums[i] = nums[j];
        nums[j] = holder;
        

        //ele se cruzaram, nao ha mais nada pra fazer aqui
        //swapping
        nums[start] = nums[j];
        nums[j] = p;

    // IMPLEMENTAR RECURSAO

}

int main() {
    puts("EAE");
    li numes[] = {1,2,4,0,5,25,-2,-1,32};
    quicksort(numes,0, sizeof(numes)/sizeof(li) -1);

    int num_n = sizeof(numes) / sizeof(li);
    for(int i = 0; i < num_n; i++) {
    printf("%ld ", numes[i]);
    }
    puts("eee");
    return 0;

}

