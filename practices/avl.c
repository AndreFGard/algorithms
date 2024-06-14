#include <stdio.h>
#include <math.h>
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
    int h;
} node;

#define updateHeight(x) (if (!x) return -1 else return x->h)

int getnode(int v) {
    node *temp = malloc(sizeof(node));
    temp->val = v;
    temp->l = temp->r = NULL;
    temp->h = 0;
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
    // in order to elevate the grandpa's son over the him.
    r->l = rt;

    //now we must relocate the left grandson of the right son, since it was overwritten
    // we know that it's bigger than it's grandpa too, so it'll go by his right.
    rt->r = rl;

    rt->h = max(height())
}


