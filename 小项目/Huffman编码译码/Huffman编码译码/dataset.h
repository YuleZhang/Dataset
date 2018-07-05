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
	int front, rear;    //表示队列的头尾位置
	int size;
};
//置空队列
bool Set_NULL(queue &Q);
//判断队列是否为空
bool Is_NULL(queue Q);

//入队
bool En_Queue(queue &Q, BinaryTree a);

//出队
bool De_Queue(queue &Q);

//取队列头元素
BinaryTree front_element(queue Q);

//显示队列元素
bool show(queue Q);
