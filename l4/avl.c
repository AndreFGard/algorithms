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
int subtree_size(node *rt){
	int size = 0;
	if (rt){
		size = 1;
		size += getdescendants(rt);
	}
	else return 0;
	return size;
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

	rt->descendants = subtree_size(rt->l) +subtree_size(rt->r);
	l->descendants = subtree_size(l->l) +subtree_size(l->r);

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

	rt->descendants = subtree_size(rt->l) + subtree_size(rt->r);
	r->descendants = subtree_size(r->l) +subtree_size(r->r);


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
	//if tends to the right and was inserted to the right
	// of the righternmosst subtree
	if (balance < -1 && val >= rt->r->val){
		return leftRotation(rt);
	}
	if (balance > 1 && val < rt->l->val){
		return rightRotation(rt);
	}
	if (balance > 1 && val >= rt->l->val){
		rt->l = leftRotation(rt->l);
		return rightRotation(rt);
	}
	if (balance < -1 && val < rt->r->val){
		rt->r = rightRotation(rt->r);
		return leftRotation(rt);
	} 

	//if no rotation was needed
	int rd, ld;
	ld = subtree_size(rt->l);
	rd = subtree_size(rt->r);

	rt->descendants = ld + rd;
	return rt;


}

int search(node *rt, int val){
	int smallernodes = 0;
	int found = 0;
	node *cur = rt;
	while (cur){
		if (val < cur->val) {
			//no one smaller here
			cur = cur->l;
		}
		else if (val == cur->val){
			found = 1;
			smallernodes += subtree_size(cur->l);
			break;
		}
		else if (val > cur->val){
			//larger than the current and it`s whole left subtree
			
			smallernodes += subtree_size(cur->l) + 1;
			cur = cur->r;
			
		}
	}
	if (found)
		return smallernodes + 1;
	else return -1;
}

int findindex(node *rt, int val){
	return search(rt, val);

	//those are the nodes in the subtree, which is not enough.

}

void test(){
	node *l = NULL;
	int j, idx;
	l = insertion(l, 100);
	l = insertion(l, 74
	);
	printf("%d\n", findindex(l, 100));
	printf("%d\n", findindex(l, 70));



	l = insertion(l, 152);
	/* j = findindex(l, 5);
	j = findindex(l, 4);
	j = findindex(l, 3);*/
	l = insertion(l, 21); 
	l = insertion(l, 33); 
	printf("%d\n", findindex(l, 100));
	printf("%d\n", findindex(l, 21));
	printf("%d\n", findindex(l, 1));
}
int main(){
	//test();
	node *l = NULL;
	int q ;
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
