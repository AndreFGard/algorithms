#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max(int a, int b){ if (a < b) return b; else return a;}
/*
h(tree) = height if exists, 0 if only root element and -1 if no tree at all

Balance : h(left) - h(right), is balanced when we get to 2 or -2.
therefore, +1 = h(left) = h(right) + 1. +2 = h(right) + 2

R Rotation: key inserted in left subtree of left child of rt, the root of unbalanced tree,
with balance 2, that is, pending to left. we must rotate to right.

L Rotation: key in right subtree of right  child of the root of the unbalanbced tree with balance -2

Double rotations happen whe we insert an inner node (Rather than in the sides) and
    unbalance the tree.ç the first balance operation is 
*/

typedef struct node {
    struct node *l;
    struct node *r;
    int val;
    int k;
    int h;
} node;

#define updateHeight(x) (if (!x) return -1 else return x->h)

node * getnode(int k, int v) {
    node *temp = (node*) malloc(sizeof(node));
    temp->val = v;
    temp->l = temp->r = NULL;
    temp->h = 0;
    temp->k = k;
    return temp;
}

/* 
h = 0 if leave/childless node, or -1 if empty
*/
int height(node *rt){
    if (!rt) return -1;
    else return rt->h;
}

int getBalance(node *rt) {
    if (!rt) return 0;
    return height(rt->l) - height(rt->r);
}

node *rightRotation(node *rt) {
    node *l = rt->l;
    node *lr = l->r;


    //the right son of the left child receives it's grandpa, the unbalanced
    //node. This happens because the left child is obviously smaller than the
    //grandparent, so he must move to it's right
    l->r = rt;

    //now the grandparent's left (which is now empty) will have to receive the right son of the
    // (used to be) left child, which we overwrote and was stored in lr.
    //this happens because it IS smaller than rt.
    rt->l = lr;

    rt->h = max(height(rt->l), height(rt->r)) + 1;
    l->h = max(height(l->l), height(l->r)) + 1;

    return l;
}   

node *leftRotation(node *rt) {
    node *r = rt->r;
    node *rl = r->l;

    //we wanna put the grandpa in the left side of it's right son (the son is bigger)
    // in order to elevate the grandpa's son over him.
    r->l = rt;

    //now we must relocate the left grandson of the right son, since it was overwritten
    // we know that it's bigger than it's grandpa too, so it'll go by his right.
    rt->r = rl;

    rt->h = max(height(rt->l), height(rt->r)) + 1;
    r->h = max(height(r->l), height(r->r)) + 1;

    return r;
}

node *insert(node *rt, int k, int val) {
    if (!rt) return getnode(k,val);

    if (rt->k > k ) {
        //left
        //the balancing updates every node when the recursion is returning
        // note that this is where the assgnment happens
        rt->l = insert(rt->l, k, val);
    } else {
        //right
        rt->r = insert(rt->r, k, val);
    }

    rt->h = 1 + max(height(rt->l), height(rt->r));
    int balance = getBalance(rt);
    //why doesnt this segfault?
    if (balance < -1 && k >= rt->r->k) {
        // if tends to the right and k was added to the right of our right son/subtree
        return leftRotation(rt);
    }
    if (balance > 1 && k < rt->l->k) {
        //tends to left and k added to the left of our left son/subtree
        return rightRotation(rt);
    }
    if (balance > 1 && k >= rt->l->k) {
        //on double rotations, we begin by updating the sontree.
        //if tends to Left but was inserted to the Right of the Left sontree
        rt->l = leftRotation(rt->l); //first we update the 
        return rightRotation(rt);
    }
    if (balance < -1 && k < rt->r->k) {
        //when it tends to the right but was inserted to the left of the right sontree
        rt->r = rightRotation(rt->r);
        return leftRotation(rt);
    }
    return rt;
}


//now about the traversals, the prefix refers to the relative
//position of the root in the sequence of operations
int preorder(node *rt){
    //print root before left and right
    if (rt){
    printf("%d ", rt->val);

    preorder(rt->l);
    preorder(rt->r);}
}

int postorder(node *rt){
    //print root after left and right
if (rt){
    postorder(rt->l);
    postorder(rt->r);
    printf("%d ", rt->val);
}
}

int inorder(node *rt){
if (rt){
    inorder(rt->l);
    printf("%d ", rt->val);
    inorder(rt->r);
}
}

int main() {
    node *l = NULL;
    char trashbin[78];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n-3; i++ ){
        int j;
        scanf("%s", trashbin);
        scanf("%d", &j);
        l = insert(l, j, j);

    }
    preorder(l);
    puts("");
    inorder(l);puts("");
    postorder(l);puts("");

}
