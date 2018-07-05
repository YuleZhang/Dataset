#include<iostream>
#include<stdlib.h>
#include<stdio.h> 
#include<vector>
using namespace std;
//二叉树结构体
struct Node
{
	char data;
	struct Node *lchild, *rchild;
};
//递归创建二叉树
void CreatBiTree(Node *tree) {
	char ch = getchar();
	if (ch == '#') {
		return;
	}
	else
	{
		tree->data = ch;
		tree->lchild = new Node();
		tree->rchild = new Node();
		CreatBiTree(tree->lchild);
		CreatBiTree(tree->rchild);
	}
}
//非递归前序遍历
void NonRecursive(Node *tree) {
	Node *p = tree;
	vector<Node*>test;
	while (p ->data !=  0||!test.empty()) {
		while (p->data != 0) {
			cout << p->data;
			test.push_back(p);
			p = p->lchild;
		}
		if (!test.empty())
		{
			p = test[test.size() - 1];
			test.pop_back();
			p = p->rchild;
		}
	}
	return;
}
//递归先序遍历
void PreTraversal(Node *tree) {
	if (tree->lchild!=NULL&&tree->data!='?') {
		cout << tree->data;
		PreTraversal(tree->lchild);
		PreTraversal(tree->rchild);
	}
}
//递归中序遍历
void MidTraversal(Node *tree) {
	if (tree->data != 0) {
		MidTraversal(tree->lchild);
		cout << tree->data;
		MidTraversal(tree->rchild);
	}
}
//递归后序遍历
void PosTraversal(Node *tree) {
	if (tree->data != 0) {
		PosTraversal(tree->lchild);
		PosTraversal(tree->rchild);
		cout << tree->data;
	}
}
//交换二叉树的左右子树
void Exchange(Node *tree) {
	if (tree->data != 0) {
		Node *temp;
		Exchange(tree->lchild);
		Exchange(tree->rchild);
		temp = tree->lchild;
		tree->lchild = tree->rchild;
		tree->rchild = temp;
	}
}
//删除树tree
void Del_Node(Node *tree) {
	if (tree->lchild)Del_Node(tree->lchild);
	if (tree->rchild)Del_Node(tree->rchild);
	free(tree);
}
//删除以元素值值为x的根以及它的所有子节点
void Del_Node_x(Node *tree,char x) {
	if (tree->data == x) {
		Del_Node(tree);
	}
	else
	{
		if (tree->lchild)Del_Node_x(tree->lchild, x);
		if (tree->rchild)Del_Node_x(tree->rchild, x);
	}
}
//主函数
int main() {
	Node *tree = new Node();
	cout << "请输入二叉树的先序序列,例如ABC##DE#G##F###" << endl;
	CreatBiTree(tree);
	//NonRecursive(tree);//非递归先序遍历
	cout << "递归先序：";
	PreTraversal(tree);//递归先序遍历
	cout << endl;
	cout << "递归中序：";
	MidTraversal(tree);
	cout << endl;
	cout << "递归后序：";
	PosTraversal(tree);
	cout << endl;
	//交换左右子树
	//Exchange(tree);
	//非递归遍历
	//NonRecursive(tree);
	char ch;
	cout << "请输入要删除的字符：";
	cin >> ch;
	Del_Node_x(tree,ch);
	cout << endl;
	PreTraversal(tree);
	system("pause");
	return 0;
}

