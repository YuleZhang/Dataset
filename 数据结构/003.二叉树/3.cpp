#include<iostream>
#include<stdlib.h>
#include<stdio.h> 
#include<vector>
using namespace std;
//�������ṹ��
struct Node
{
	char data;
	struct Node *lchild, *rchild;
};
//�ݹ鴴��������
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
//�ǵݹ�ǰ�����
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
//�ݹ��������
void PreTraversal(Node *tree) {
	if (tree->lchild!=NULL&&tree->data!='?') {
		cout << tree->data;
		PreTraversal(tree->lchild);
		PreTraversal(tree->rchild);
	}
}
//�ݹ��������
void MidTraversal(Node *tree) {
	if (tree->data != 0) {
		MidTraversal(tree->lchild);
		cout << tree->data;
		MidTraversal(tree->rchild);
	}
}
//�ݹ�������
void PosTraversal(Node *tree) {
	if (tree->data != 0) {
		PosTraversal(tree->lchild);
		PosTraversal(tree->rchild);
		cout << tree->data;
	}
}
//��������������������
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
//ɾ����tree
void Del_Node(Node *tree) {
	if (tree->lchild)Del_Node(tree->lchild);
	if (tree->rchild)Del_Node(tree->rchild);
	free(tree);
}
//ɾ����Ԫ��ֵֵΪx�ĸ��Լ����������ӽڵ�
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
//������
int main() {
	Node *tree = new Node();
	cout << "���������������������,����ABC##DE#G##F###" << endl;
	CreatBiTree(tree);
	//NonRecursive(tree);//�ǵݹ��������
	cout << "�ݹ�����";
	PreTraversal(tree);//�ݹ��������
	cout << endl;
	cout << "�ݹ�����";
	MidTraversal(tree);
	cout << endl;
	cout << "�ݹ����";
	PosTraversal(tree);
	cout << endl;
	//������������
	//Exchange(tree);
	//�ǵݹ����
	//NonRecursive(tree);
	char ch;
	cout << "������Ҫɾ�����ַ���";
	cin >> ch;
	Del_Node_x(tree,ch);
	cout << endl;
	PreTraversal(tree);
	system("pause");
	return 0;
}

