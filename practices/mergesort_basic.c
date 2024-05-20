#include <stdio.h>
#include <string.h>

typedef int li;
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


#include <stdlib.h>
int main(){
    int stuff[] = {9, 5, 25, 28, 27, 2, 15, 18, 26, 14, 13, 6, 16, 10, 12, 29, 23, 8, 19, 1, 17, 20, 22, 11, 7, 21, 24, 3, 4, 14};
    int size = sizeof(stuff)/sizeof(int);
    aux_arr = alloca(size * sizeof(int));
    _mergesort(stuff,0, size -1);

    
    for (int i = 0; i<size; i++) {
        printf("%d, ", stuff[i]);
    }

}

