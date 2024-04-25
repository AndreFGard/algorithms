#include <stdio.h>
#include "library.c"
#include <string.h>

typedef long int li;
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

    aux_arr = alloca(70 * (sizeof(li)));
    for (int i = 0; i < 70; i++) aux_arr[i] = 37;
    li numes[] = {1,0,2};
    li aux[] = {0,0,0,0,0,0};
    merge(numes, 0, 2, 1);
    printarray(numes, sizeof(li), 3, "%ld");

    //li num_n = 0;
    li num_n = 0;
    printf("input: ");
    scanf("%ld", &num_n);
    printf("num of nums is %ld\n", num_n);

    //stop me if you can
    li nums[num_n];

    for (int i =0;i<num_n;i++) {
    	scanf("%ld", &nums[i]);
    }

    //aux_arr = alloca(num_n * (sizeof(li)));
    printarray(nums, sizeof(li), num_n, "%ld ");
    //merge(nums, , 0, num_n -1, num_n/2 );
    _mergesort(nums, 0, num_n - 1);
    printarray(nums, sizeof(li), num_n, "%ld\n");

}

