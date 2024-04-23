
#include <stdio.h>

typedef long int li;

int partitioning(li nums[], int start, int end) {
    int p = nums[start];
    int i = start + 1;
    int j = end;
    //hoares partitioning
    li holder;
    //executar o passo ANTES de checar se i<j, para que façamos um movimento desnecessário para desfazermos-no depois
    do {

        //procurar até achar um maior igual
        while (i < end && nums[i] < p) {
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
    } while ( i<j);
    
    //desfazer ultimo swap que foi feito inadequadamente
    i--; j++;
    holder = nums[i];
    nums[i] = nums[j];
    nums[j] = holder;
    

    // como i e j se cruzaram, trocar nums[j] com o pivot
    nums[start] = nums[j];
    nums[j] = p;
    return j;
}


int quicksort(li nums[], int start, int end) {

    if (start >= end) return 0;

    int j = partitioning(nums, start, end);

    quicksort(nums, j + 1, end);
    quicksort(nums, start, j -1); 
    
    
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

