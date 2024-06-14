#include <stdlib.h>
#include <stdio.h>
typedef struct node {
    struct node *l;//eft
    struct node *r;//right
    int e;
    int k;
} node;

node *getnode(int k, int e) {
    node *temp = (node*) malloc(sizeof(node));
    temp->l = temp->r = NULL;
    temp->e = e;
    temp->k = k;
    return temp;
}


void preoder(node *root){
    if (root){
        printf(" %d", root->e);
        preoder(root->l);
        preoder(root->r);
        return;
    }
    return;
}


void inorder(node *root){
    if (root){
        
        inorder(root->l);
        printf(" %d", root->e);
        inorder(root->r);
        return;
    }
    return;
}

void postorder(node *root){
    if (root){
        
        postorder(root->l);
                postorder(root->r);
        printf(" %d", root->e);

        return;
    }
    return;
}

node *add(node *h, int k, int e){
    if (h){
        if (k < h->k) {
            h->l = add(h->l, k, e);
        }
        else {
            h->r = add(h->r, k, e);
        }
    }
    else {
        // if null
        return getnode(k, e);
    }
    return h;

}

node *find(node *r, int k){
    if (!r) {
        return NULL;
    }
    if (k > r->k) {return find(r->r, k);}
    else if (k  == r->k) {return r;}
    else return find(r->l, k);
}

int main(){
    node *start = NULL;
    int n, t;
    scanf("%d", &n);
    for (int i = 0; i<n; i++){
        scanf("%d", &t);
        if (!start) {
            start = getnode(t,t);
        } else{
            add(start, t,t);

        }
    }
    
    for(;;){
        printf("find: ");
        scanf("%d", &t);
        printf("\n%x\n", find(start, t));
    }
}