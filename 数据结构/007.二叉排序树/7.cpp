#include<iostream>
#include<stdlib.h>
using namespace std;
struct orderTree {
	int data;
	struct orderTree *lchild, *rchild;
};
orderTree* create(orderTree* tree, int data) {
	if (tree == NULL) {
		tree = new orderTree();
		tree->data = data;
		return tree;
	}
	if (data < tree->data) {
		tree->lchild = create(tree->lchild, data);
	}
	else if (data > tree->data) {
		tree->rchild = create(tree->rchild, data);
	}
	else {
		cout << "already existed" << endl;
	}
	return tree;
}
void searchNode(orderTree* tree,int data){
	if(tree == NULL){
		return;
	}
	if(data > tree->data){
		searchNode(tree->rchild,data);
	}
	else if(data < tree->data){
		searchNode(tree->lchild,data);
	}
	else {
	cout << "ур╣╫"<<data<<"ак"<<endl;
	return;		
		} 
} 
void deleteNode(orderTree* tree, int data) {
	orderTree *substitute = tree, *father = NULL, *pre = NULL, *mid, *p;
	while (substitute) {
		if (data == substitute->data) {
			break;
		}
		father = substitute;
		substitute = data > substitute->data ? substitute->rchild : substitute->lchild;
	}
	if (!substitute)return;
	if (substitute->lchild == NULL && substitute->rchild == NULL) {
		if (substitute == tree) {
			tree = NULL;
			//return NULL;
		}
		if (father->lchild == substitute) {
			father->lchild = substitute->lchild;
			//return father;
		}
		else { 
			father->rchild = substitute->rchild;
			//return father;
		}
	}
	else if (substitute->lchild != NULL && substitute->rchild == NULL) {
		if (father == NULL) {
			substitute->data = substitute->lchild->data;
			substitute->lchild = substitute->lchild->lchild;
		}
		else {
			father->lchild = substitute->lchild;
		}
	}
	else if (substitute->lchild == NULL && substitute->rchild != NULL) {
		if (father == NULL) {
			substitute->data = substitute->rchild->data;
			substitute->rchild = substitute->rchild->rchild;
		}
		else {
			father->rchild= substitute->rchild;
		}
	}
	else {
		pre = substitute;
		mid = substitute->lchild;
		while (mid->rchild != NULL) {
			pre = mid;
			mid = mid->rchild;
		}
		substitute->data = mid->data;
		if (pre->lchild == mid) {
			pre->lchild = mid->lchild;
		}
		else {
			pre->rchild = mid->rchild;
		}
		free(mid);
	}
}
void printTree(orderTree* tree) {
	if (tree == NULL) {
		return;
	}
	printTree(tree->lchild);
	cout << tree->data << " ";
	printTree(tree->rchild);
	return;
}
int main() {
	orderTree *seqTree = NULL;
	cout << "please input the data num:";
	int n, x;
	cin >> n;
	for (int i = 0; i<n; i++) {
		cin >> x;
		seqTree = create(seqTree, x);
	}
	printTree(seqTree);
	cout << endl;
	cout << "input the search num:";
	cin  >> x;
	searchNode(seqTree,x); 
	cout << endl;
	cout << "input the delete num:";
	cin >> x;
	deleteNode(seqTree, x);
	cout << endl;
	printTree(seqTree);
	system("pause");
	return 0;
}
