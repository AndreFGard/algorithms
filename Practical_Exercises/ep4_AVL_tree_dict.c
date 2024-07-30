#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
    if (a>b) return a;
    else return b;
}

#define updateH(x) 1 + max(h(x->l), h(x->r))

typedef struct node {
    struct node *l;
    struct node *r;
    int h;
    int val;
} node;

int h(node *rt){
    if (rt){
        return rt->h;
    }
    return -1;
}


int getbalance(node *rt){
    return h(rt->l) - h(rt->r);
}

node *getNode(int val){
    node *temp = malloc(sizeof(node));
    temp->h = 0;
    temp->val = val;
    temp->l = temp->r = NULL;
    return temp;
}

node *rightRotate(node *rt){
    node *l = rt->l;
    node *lr = l->r;

    //move dad to left son's right
    l->r = rt;
    //put what was in the left sons right to the dads left, which
    // is now nothing since the ex-child will move up
    rt->l = lr;

    rt->h = updateH(rt);
    l->h = updateH(l);

    //move the left child up
    return l;

}


node *leftRotate(node *rt){
    node *r = rt->r;
    node *rl = r->l;

    //move dad to right sons's left, and put
    // what was in Right son left in dad's right, which
    // was freed because the right son will move up

    r->l = rt;
    rt->r = rl;

    rt->h = updateH(rt);
    r->h = updateH(r);

    return r;

}

node *insertion(node *rt, int val){
    if (!rt) return getNode(val);

    if (rt->val > val){
        rt->l = insertion(rt->l, val);
    }
    else {
        rt->r = insertion(rt->r, val);
    }


    rt->h = updateH(rt);
    int balance = getbalance(rt);

    //tends to r and inserted in r to r subtree
    if (balance < -1 && val >= rt->r->val){
        return leftRotate( rt);
    }
    if(balance > 1 && val < rt->l->val){
        //tends to left and inserted l to the in l subtree
        return rightRotate(rt);
    }
    if (balance > 1 && val >= rt->l->val){
        rt->l = leftRotate(rt->l);
        return rightRotate(rt);
    }
    if (balance <-1 && val < rt->r->val){
        rt->r = rightRotate(rt->r);
        return leftRotate(rt);
    }

    return rt;

}

void preoder(node *rt){
    if (!rt) return;
    printf("%d\n", rt->val);
    preoder(rt->l);
    preoder(rt->r);

}

int main(){
    int nc;
    char buff[80];
    scanf("%d", &nc);

    node *rt = NULL;

    for (int i  =0; i<nc; i++){
        int n = 0;
        scanf("%d", &n);

        int val =0;
        for (int j = 0; j<n; j++){
            scanf("%d", &val);
            rt = insertion(rt, val);

        }
        preoder(rt);
        puts("END");
        rt = NULL;

    }
}