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

int _binary_search(li nums[], int start, int end, long long int num) {
    int size = end - start + 1;
    int middle = (end + start)/2;
    if (size <= 1 &&  nums[middle] != num) return -1;

    if (nums[middle] > num) {
        return _binary_search(nums,start, middle -1, num);
    } 
    if (nums[middle] < num) {
        return _binary_search(nums, middle + 1, end, num);
    }
    else return middle;
}

#define not_found -1

int main() {
    int n, k;
    scanf("%d %d", &n, &k );
    //eba, mais vla
    int nums[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int z[n]; aux_arr = z; //aux array do mergesort
    _mergesort(nums, 0, n - 1);

    //checando somente pra trás:
    // 1- Se houver, o par de nums[i] está em [i-k, i] (nâo há duplicatas)
    //pode existir par mesmo que i - k < 0, se houver numeros negativos
    //checar somente os números [0,k], para nao acessar indices negativos
    long long int searching; int bs_result; long int n_pairs = 0;

    for (int i=0; i!=k; i++){
        searching = nums[i] -k;
        bs_result = _binary_search(nums, 0, i, searching);
        
        if (bs_result != not_found) {
            //Dprintf("[%d] pair :%d: [%d][%d]\n", i, bs_result, nums[i], nums[bs_result]);
            n_pairs += 1;
        }  
    }
    //mesmo loop, mas otimizado aqui -----v (i-k)
    for (int i=k; i<n; i++){
        searching = nums[i] -k;
        bs_result = _binary_search(nums, i-k, i, searching);
        
        if (bs_result != not_found) {
            //Dprintf("[%d] pair :%d: [%d][%d]\n", i, bs_result, nums[i], nums[bs_result]);
            n_pairs += 1;
        }  
    }   

    printf("%ld\n", n_pairs);



    return 0;
}