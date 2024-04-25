#include <stdio.h>
#define li long int

int binary_search(li nums[], int start, int end, li num) {
    int size = end - start + 1;
    int middle = (end + start)/2;
    if (size == 1 &&  nums[middle] != num) return -1;

    if (nums[middle] > num) {
        return binary_search(nums,start, middle -1, num);
    } 
    if (nums[middle < num]) {
        return binary_search(nums, middle + 1, end, num);
    }
    else return middle;
}

int main() {
    li numes[] = {0,1,2,3,4,5,6,7};
    int num;
    scanf("%d", &num);
    return binary_search(numes, 0, sizeof(numes)/sizeof(li) -1, num);
}