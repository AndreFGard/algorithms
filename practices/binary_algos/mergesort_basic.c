#include <stdio.h>
#include "../library.c"
#include <string.h>

typedef long int li;

int merge(li nums[], li aux_arr[], int start, int end, int pivot){

    li holder;

    //first half and second half

    int i = 0;
    int f = start;
    int s = pivot;

    while (f < pivot && s < end) {

        if (nums[f] < nums[s]) {   
            aux_arr[i] = nums[f];
            f++; i++;

            }
        else {
            aux_arr[i] = nums[s];
            s++; i++;

        }
        
    }

    puts("NUMS before");
    printarray(&nums[start], sizeof(li), end-start + 1, "%ld-");

    puts("\naux before");
    printarray(aux_arr, sizeof(li), i, "%ld-");
    if (f == pivot) {
        // here we must add 1 because array[end] is also part of the array, 
        // so we must copy it too
        memcpy(&aux_arr[i], &nums[s], sizeof(li) * (end - s + 1) );
    }
    else {
        memcpy(&aux_arr[i], &nums[f], sizeof(f) * (pivot - f) );
    }
    puts("\nafter:  ");
    printarray(aux_arr, sizeof(li), i + 1 + end - s, "%ld-");

    memcpy(&nums[start], aux_arr, sizeof(li) * (end - start));

}

int _mergesort(li nums[], int start, int end) {
    if (start - end == 1) return 0;

    int pivot = start + (start + end)/2;
    _mergesort (nums, start, pivot);
    _mergesort(nums, pivot + 1, end);



	return 0;
}

#include <stdlib.h>


int main(){

    li numes[] = {24,32,76,48};
    li aux[] = {0,0,0,0,0,0};
    memcpy(&aux[2], &numes[1], sizeof(li));
    printarray(aux, sizeof(li), 6, "%ld - ");

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

    printarray(nums, sizeof(li), num_n, "%ld\n");
    merge(nums, alloca(num_n * (sizeof(li))), 0, num_n -1, num_n/2 );
    printarray(nums, sizeof(li), num_n, "%ld\n");

}

