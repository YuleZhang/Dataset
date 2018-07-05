#pragma once
#define MAXSIZE 100
#define MAX_CODE_LENGTH 100
//#define MAX_CODE_LENGTH 100
struct BinaryTree {
	char data;
	int weight;
	char code[MAX_CODE_LENGTH];
	struct BinaryTree *lchild, *rchild;
};
struct queue{
	BinaryTree treeData[MAXSIZE];
	int front, rear;    //��ʾ���е�ͷβλ��
	int size;
};
//�ÿն���
bool Set_NULL(queue &Q);
//�ж϶����Ƿ�Ϊ��
bool Is_NULL(queue Q);

//���
bool En_Queue(queue &Q, BinaryTree a);

//����
bool De_Queue(queue &Q);

//ȡ����ͷԪ��
BinaryTree front_element(queue Q);

//��ʾ����Ԫ��
bool show(queue Q);
