#define tablesize 101
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define inserted_already -102
#define empty 2
#define previously_full 1
#define full 0

/*
hello, if you are stuck with the hashit problem, please check out my comment on spoj.
I have very strong evidences that this problem has improper inputs in it's testcases. if I were
to remove the else { i--;} line, the code wouldnt be accepted, because thats the line that ignores invalid
inputs and waits for a valid one instead of skipping them. I had to write a testcase maker in python
which ended up being buggy and producing invalid inputs (repeating the number of cases between each case)
in order to notice such issue, and I could only notice it because of this bug. the testcase maker is also
available here on maketest.py. Heres a copy of my comment on spoj:

Ive lost tons of time in this question. What worked out for me was ignoring inputs that werent proper (that is, that didnt start with "ADD:" nor "DEL:") and continuing to receive inputs until some input that started with either ADD: or DEL: appeared. For example, consider this testcase. the improper lines in between should be ignored, otherwise you might ignore or misplace a valid input. for example, make sure that in this testcase, where there is an improper line, your code WILL add Pz3 rather than ignoring it.
2
3
ADD:dOb
ADD:mlnB
ADD:IIaOOP3
3
ADD:zSebQV
ADD:ze
ADD:Pz3 
}

*/

typedef struct {
    short int stat;
    char *s;
} memb;

typedef struct {
    int size;
    memb arr[tablesize];
} hashtable;


int hash(char key[]){
    long int sum = 0;
    for (int i =0; i<17;i++){
        if (key[i] == '\0') break;
        sum +=  key[i]*(i+1);
    }
    sum *= 19;
    return sum % tablesize;
}

int insert(hashtable *t, char key[]) {
    int k = hash(key);
    int possible_slot = -1;
    memb *slot;

    for (int i = 0; i<20; i++) {
        k = (k + i*i + 23*i)%tablesize;
        slot = &t->arr[k];

        if (slot->stat == full) {
            if (strcmp(slot->s, key) == 0){
                //INSERTED ALREADY
                return inserted_already;
            }
        }
        else if (slot->stat == previously_full) {
            if (possible_slot == -1) possible_slot = k;
        }

        else if (slot->stat == empty) {
            //we searched for it, but it wasnt previously inserted
            if (possible_slot == -1) possible_slot = k;
            break;
        }
    }

    //after searching for previous insertions, insert it
    if (possible_slot != -1) {
        slot = &t->arr[possible_slot];
        slot->stat = full;
        slot->s = key;
        t->size++;
    }

    return possible_slot;
}

int find(hashtable *t, char key[]) {
    int k = hash(key);
    int possible_slot = -1;
    memb *slot;


    for (int i = 0; i<20; i++) {
        k = (k + i*i + 23*i)%tablesize;
        slot = &t->arr[k];
        if (slot->stat == full){
            if (strcmp(t->arr[k].s, key) == 0){
                //FOUND
                return k;
            }
        } else if (slot->stat == empty) {
            //not found :( 
            return -1;
        }
    }
    return -1;
}

int delete(hashtable *t, char key[]){
    int location = find(t, key);
    if (location != -1){
        t->arr[location].stat = previously_full;
        t->size--;
    }
    return location;
}

char empty_str = '\0';
int populate(hashtable *t){
    t->size = 0;
    for (int i =0; i<tablesize; i++){
        t->arr[i].stat = empty;
        t->arr[i].s = &empty_str;
    }
}
int main() {
    hashtable t;

    populate(&t);
    int n, ops;
    char space[16*1001];
    char *newstr;

    scanf("%d %d", &n, &ops);
    int location = 0;
    for (int c = 0; c<n;c++){
    for (int i =0; i<ops; i++){
        newstr = malloc(16*4);
        scanf("%s", newstr);
        if (newstr[0] == 'A'){
            //ADD
            newstr= newstr + 4;
            location = insert(&t, newstr);
        }
        else if(newstr[0] == 'D'){
            newstr = newstr +4;
            delete(&t, newstr);

        }
        else{
            i--;
        }
    }
    printf("%d\n",t.size);
    for (int j = 0; j<tablesize;j++){
        if(t.arr[j].stat == full) printf("%d:%s\n",j,t.arr[j].s);
    }
    populate(&t);
    }

}