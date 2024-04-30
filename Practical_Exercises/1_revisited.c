#include <stdio.h>
#include <string.h>
typedef int li;

#define MAX_INSCRITOS 5001
typedef struct person {
    int nota;
    char nome[31];
    int idade;
} person;

struct person pessoas[MAX_INSCRITOS];
struct person pessoas_aux[MAX_INSCRITOS];
person *aux_arr = pessoas_aux;




li *moverjunto;
int merge(person nums[], int start, int end, int pivot) {
    int i = start;
    int f = start; int s = pivot + 1;

    while (f <= pivot && s <= end) {

        if (nums[f].nota < nums[s].nota) {
            aux_arr[i] = nums[f];
            f++;
        }
        else if (nums[f].nota == nums[s].nota) {
            if (nums[f].idade <= nums[s].idade) {
                aux_arr[i] = nums[f];
                f++;
            }
            else {
                aux_arr[i] = nums[s];
                s++;
            }
        }
        else {
            aux_arr[i] = nums[s];
            s++;
        }
        i++;
    }

    // f extrapola, copia o resto pra aux
    if (f > pivot) {
        memcpy(&aux_arr[i], &nums[s], sizeof(person) * (end - s +1));
    }
    else {
        memcpy(&aux_arr[i], &nums[f], sizeof(person) * (pivot - f +1));
    }

    //copiar pros definitivos
    memcpy(&nums[start], &aux_arr[start], sizeof(person) * (end -start + 1) );
}

int _mergesort(person nums[], int start, int end) {
    //puts("oi");
    if (start >= end) return 0;
    int pivot = (start + end ) / 2 ;

    _mergesort(nums, start, pivot);
    _mergesort(nums, pivot + 1, end);
    merge(nums, start, end, pivot);
}


#define MAX_NOME 31
char ngm[] = "x";




#include <stdlib.h> // malloc
int main() {

    int n_cargos;
    scanf("%d", &n_cargos);
    //para cada cargo
    int inscritos, vagas;
    for (int i = 0; i < n_cargos; i++) {
        scanf("%d", &inscritos); // inscritos p cargo
        scanf("%d", &vagas); // vagas pra cargo
        
        //para cada inscrito
        for (int j = 0; j < inscritos; j++) {
            scanf("%s", pessoas[inscritos -1 -j].nome);
            scanf("%d", &pessoas[inscritos -1 -j].nota);
            scanf("%d", &pessoas[inscritos -1 -j].idade);
        }

        //terminamos com os inputs, agora vamos ordenar
        //(ja estamos ajustando os nomes e idades)
        _mergesort(pessoas, 0, inscritos -1);

        printf("cargo %d:\n", i+1);
        for (int k = 0; k < vagas; k++) {
            if (k < inscritos)
                printf("%s\n", pessoas[inscritos -1 -k].nome);
            else printf("x\n");
        }

    }
}