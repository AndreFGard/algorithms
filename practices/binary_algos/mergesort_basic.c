#include <stdio.h>
#include "../library.c"

typedef long int li;

int mergesort(li nums[], int start, int end) {
    if (start - end == 1) return 0;

    int pivot = start + (start + end)/2;
    mergesort (nums, start, pivot);
    mergesort(nums, pivot + 1, end);


	return 0;
}



int main(){

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

}

