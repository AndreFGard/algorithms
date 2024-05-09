#include <stdio.h>
#include <inttypes.h>
#include <string.h>
typedef int li;

int partitioning(li nums[], int start, int end) {
    int p = nums[start];
    int i = start + 1;
    int j = end;
    //hoares partitioning
    li holder;
    //executar o passo ANTES de checar se i<j, para que façamos
    // um movimento desnecessário para desfazermos-no depois
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
    } while ( i<j);
    
    //desfazer ultimo swap que foi feito inadequadamente
    holder = nums[i];
    nums[i] = nums[j];
    nums[j] = holder;
    

    // como i e j se cruzaram, trocar nums[j] com o pivot
    nums[start] = nums[j];
    nums[j] = p;
    return j;
}


int _quicksort(li nums[], int start, int end) {
 
    if (start >= end) return 0;

    int j = partitioning(nums, start, end);

    _quicksort(nums, j + 1, end);
    _quicksort(nums, start, j -1); 
}


li *aux_arr;
int merge(li nums[], int start, int end, int pivot){

    li holder;

    //first half and second half
    li *debugarr = aux_arr;
    int i = 0;
    int f = start;
    int s = pivot;

    //smaller equal  because arr[end] is part of the array
    //it's important not to mix the length of the array with it`s last index
    while (f < pivot && s <= end) {

        if (nums[f] < nums[s]) {   
            aux_arr[i] = nums[f];
            f++; i++;

            }
        else {
            aux_arr[i] = nums[s];
            s++; i++;

        }
        
    }

    //puts("NUMS before");
    //printarray(&nums[start], sizeof(li), end-start + 1, "%ld-");

    //puts("\taux before");
    //printarray(aux_arr, sizeof(li), end-start + 1, "%ld-");
    if (f == pivot) {
        // here we must add 1 because array[end] is also part of the array, 
        // so we must copy it too
        memcpy(&aux_arr[i], &nums[s], sizeof(li) * (end - s + 1) );
    }
    else {
        // pivot is not part of the first half
        memcpy(&aux_arr[i], &nums[f], sizeof(f) * (pivot - f) );
    }
    //puts("\tafter:  ");
    //printarray(aux_arr, sizeof(li), end - start + 1, "%ld-");

    memcpy(&nums[start], aux_arr, sizeof(li) * (end - start + 1));

}

int _mergesort(li nums[], int start, int end) {
    int pivot = (start + end + 1) / 2;
    if (start == end) {return 0;}

    // nao queremos incluir o pivot, entao removemos ele
    _mergesort(nums, start, pivot - 1);
    //deve incluir o end e o pivot
    _mergesort(nums, pivot, end);
    merge(nums, start, end, pivot);

	return 0;
}



struct thing {
    unsigned int id;
    unsigned int value;
};


int main(){

    //get onput 
    int n_bars, n_coup;
    scanf("%d", &n_bars );
    //can get away with allocating on the stack on this one
    unsigned int bars[n_bars];
    for (int i = 0; i < n_bars; i++) {
        scanf("%d", &bars[i]);
    }


    scanf("%d", &n_coup);
    unsigned int coups[n_coup];
    for (int i = 0; i < n_coup; i++) {
        scanf("%d", &coups[i]);
    }
    
    // pare-me, se conseguir: alocando array  do mergesort
    li hold[n_bars]; aux_arr = hold;

    //sortear as barras
    //TODO: garantir que ja nao está sorteado
    //essa porcaria nao funciona se ja estiver ordenado, mergesort SOLA
    _mergesort(bars, 0, n_bars -1);
    
    //PRINTAR ARRAY DE BARS
    //for (int i = n_bars -1; i > n_bars -15; i++) printf("%d ", bars[i]);

    long long unsigned int sum = 0;
    for (int i = 0; i < n_bars; i++) sum += bars[i];
    //DEBUGprintf("sum is: %ld\n", sum);


    int xx, discount;
    for (int i = 0; i < n_coup;  i++) {
        // n de barras que eu vou comprar a priori
        xx = coups[i];
        discount = bars[n_bars -xx];
        printf("%llu\n", sum - discount);
    }


   //DEBUGputs("acabou-se");

}