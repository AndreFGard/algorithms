#include <stdlib.h>
#include <stdio.h>
int max(int a, int b){if (a > b){return a;}else{return b;}}
typedef struct node {
	struct node *l;
	struct node *r;
	int h;
	int val;
	int rank;
	int descendants;
} node;


node * getnode(int val) {
	node *temp = (node*) malloc(sizeof(node));
	temp->h = 0; 
	temp->descendants = 0;
	temp->val = val;
	temp->l = temp->r = NULL;
	return temp;
}


int h(node *rt){
	if (!rt){
		return -1;
	}
	else {
		return rt->h;
	}

}

int updateHeight(node *x) {return max(h(x->l), h(x->r)) + 1;}

int getBalance(node *rt){
	return h(rt->l) - h(rt->r);
}
int getdescendants(node *rt){
	if (rt){
		return rt->descendants;
	}
	return 0;
}

node * rightRotation(node *rt){
	node *l = rt->l;
	node *lr = l->r;

	//we wanna put rt in it`s left child right side, effectively moving
	//the l child up
	l->r = rt;
	rt->l = lr;
	rt->h = updateHeight(rt);
	l->h = updateHeight(l);

	rt->descendants += -getdescendants(l) +getdescendants(lr);
	l->descendants += -getdescendants(lr) +getdescendants(rt);

	return l;
}

node * leftRotation(node *rt){
	node *r = rt->r;
	node *rl = r->l;

	//we want to move the parent to the right son`s left side
	r->l = rt;
	rt->r = rl;

	rt->h = updateHeight(rt);
	r->h = updateHeight(r);

	rt->descendants += -getdescendants(r) +getdescendants(rl);
	r->descendants += -getdescendants(rl) +getdescendants(rt);


	return r;
}
void preorder(node *rt){
    //print root before left and right
    if (rt){
    printf("%d ", rt->val);

    preorder(rt->l);
    preorder(rt->r);}
}

void postorder(node *rt){
    //print root after left and right
if (rt){
    postorder(rt->l);
    postorder(rt->r);
    printf("%d ", rt->val);
}
}

void inorder(node *rt){
if (rt){
    inorder(rt->l);
    printf("%d ", rt->val);
    inorder(rt->r);
}
}


node * insertion(node *rt, int val){
	if (!rt) {
		return getnode(val);
	}

	//if val <= rt
	if (rt->val > val){
		rt->l = insertion(rt->l, val);
	}
	else {
		rt->r = insertion(rt->r, val);
	}

	rt->h = updateHeight(rt);
	int balance = getBalance(rt);
	if (balance < -1 && val >= rt->val){
		return leftRotation(rt);
	}
	if (balance > 1 && val < rt->val){
		return rightRotation(rt);
	}
	if (balance > 1 && val >= rt->val){
		rt->l = leftRotation(rt->l);
		return rightRotation(rt);
	}
	if (balance < -1 && val < rt->val){
		rt->r = rightRotation(rt->r);
		return leftRotation(rt);
	} 

	//if no rotation needed
	int ld = 0; int rd = 0;
	if (getdescendants(rt->l)) ld = getdescendants(rt->l) + 1;
	if (getdescendants(rt->r) )rd = getdescendants(rt->r) + 1;

	rt->descendants = ld + rd;
	return rt;


}

node* search(node *rt, int val){

	node *cur = rt;
	while (cur){
		if (val < cur->val) {
			cur = cur->l;
		}
		if (val == cur->val){
			break;
		}
		if (val > cur->val){
			cur = cur->r;
		}
	}
	return cur;
}

int findindex(node *rt, int val){
	node *temp = search(rt, val);
	if (temp){
		return temp->descendants - getdescendants(temp->r);
	}
	else return -1;

}

int main(){
	node *l = NULL;
	int q;
	scanf("%d", &q);

	for (int i = 0; i<q; i++){
		int t, val;
		scanf("%d %d", &t, &val);
		if (t ==1){
			l = insertion(l, val);
		}
		else{
			int idx = findindex(l, val);
			if (idx != -1){
				printf("%d\n", idx);
			}
			else puts("Data tidak ada");

		}
	}

}