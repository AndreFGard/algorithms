#include <stdio.h>
#include <string.h>
typedef int li;

#define MAX_INSCRITOS 5001
char **nomes; // serao mudados junto com os numeros do array provided
char **nomes_aux;
li *aux_arr;
int notas[MAX_INSCRITOS]; int idades[MAX_INSCRITOS];
int notas_aux[MAX_INSCRITOS]; int aux_moverjunto[MAX_INSCRITOS];

li *moverjunto;
int merge(li nums[], int start, int end, int pivot) {
    int i = start;
    int f = start; int s = pivot + 1;

    while (f <= pivot && s <= end) {
        if (nums[f] > nums[s]) {
            aux_arr[i] = nums[s];
            nomes_aux[i] = nomes[s];
            aux_moverjunto[i] = moverjunto[s];
            s++;
        }
        else {
            aux_arr[i] = nums[f];
            nomes_aux[i] = nomes[f];
            aux_moverjunto[i] = moverjunto[f];
            f++;
        }
        i++;
    }

    // f extrapola, copia o resto pra aux
    if (f > pivot) {
        memcpy(&aux_arr[i], &nums[s], sizeof(li) * (end - s +1));
        memcpy(&aux_moverjunto[i], &moverjunto[s], sizeof(li) * (end - s +1));
        //funciona??????
        memcpy(&nomes_aux[i], &nomes[s], sizeof(char *) * (end - s + 1));
    }
    else {
        memcpy(&aux_arr[i], &nums[f], sizeof(li) * (pivot - f +1));
        memcpy(&aux_moverjunto[i], &moverjunto[f], sizeof(li) * (pivot - f +1));

        memcpy(&nomes_aux[i], &nomes[f], sizeof(char *) * (pivot - f + 1));
    }

    //copiar pros definitivos
    memcpy(&nums[start], &aux_arr[start], sizeof(li) * (end -start + 1) );
    memcpy(&moverjunto[start], &aux_moverjunto[start], sizeof(li) * (end -start + 1) );

    memcpy(&nomes[start], &nomes_aux[start], sizeof(char *) * (end - start + 1));
}

int _mergesort(li nums[], int start, int end) {
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
    //alocacao de memoria para strings
    char *teste[] = {"robi", "rony", "roji", "worb"};

    char *z1[MAX_INSCRITOS]; nomes = z1;
    char *z2[MAX_INSCRITOS]; nomes_aux = z2;
    for (int i = 0; i < MAX_INSCRITOS; i++) {
        nomes[i] = malloc(sizeof(char) * MAX_NOME);
        *nomes[i] = '\0';
        nomes_aux[i] = malloc(sizeof(char) * MAX_NOME);
    }
    for (int i = 0; i<4;i++) strcpy(nomes[i], teste[i]);

    //-------------------------------------------------------
    // alocacao pros inteiros
    li z3[MAX_INSCRITOS]; aux_arr = z3;
    li nums[] = {33, 10, 50, 0};
    //-------------------------------------------------------

    int n_cargos;
    scanf("%d", &n_cargos);
    int inscr_p_cargo[n_cargos];
    int vagas_p_cargo[n_cargos];


    //para cada cargo
    int inscritos;
    for (int i = 0; i < n_cargos; i++) {
        scanf("%d", &inscritos); // inscritos p cargo
        inscr_p_cargo[i] = inscritos;
        scanf("%d", &vagas_p_cargo[i]); // vagas pra cargo
        
        //para cada inscrito
        for (int j = 0; j < inscritos; j++) {
            scanf("%s", nomes[inscritos -1 -j]);
            scanf("%d", &notas[inscritos -1 -j]);
            scanf("%d", &idades[inscritos -1 -j]);
        }

        //terminamos com os inputs, agora vamos ordenar
        //(ja estamos ajustando os nomes e idades)
        moverjunto = notas;
        _mergesort(idades, 0, inscritos -1);
        moverjunto = idades;
        _mergesort(notas, 0, inscritos -1);

        printf("cargo %d:\n", i+1);
        for (int k = 0; k < vagas_p_cargo[i]; k++) {
            if (k < inscritos)
                printf("%s\n", nomes[inscritos -1 -k]);
            else printf("x\n");
        }

    }




    //_mergesort(nums, 0, 3);
    int zll = 44;

}

int mon() {

    int n_cargos;
    scanf("%d", &n_cargos);
    int inscr_p_cargo[n_cargos];
    int vagas_p_cargo[n_cargos];

    for (int i = 0; i < n_cargos; i++) {
        scanf("%d", &inscr_p_cargo[i]); // inscritos p cargo
        scanf("%d", &vagas_p_cargo[i]); // vagas pra cargo
    }


}