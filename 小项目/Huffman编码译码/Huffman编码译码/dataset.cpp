#include "dataset.h"
#include<iostream>
using namespace std;
bool Set_NULL(queue & Q)
{
	Q.front = 0;
	Q.rear = 0;
	Q.size = 0;
	return true;
}

bool Is_NULL(queue Q)
{
	if (Q.front == Q.rear) {
		return true;
	}
	return false;
}

bool En_Queue(queue & Q, BinaryTree a)
{
	if (Q.rear - Q.front >= MAXSIZE - 1) {
		cout << "队已满";
		return false;
	}
	Q.treeData[Q.rear] = a;
	Q.rear += 1;
	Q.size += 1;
	return false;
}

bool De_Queue(queue & Q)
{
	if (Is_NULL(Q)) {
		cout << "队为空";
		return false;
	}
	Q.front += 1;
	Q.size -= 1;
	return true;
}

BinaryTree front_element(queue Q)
{
	if (Is_NULL(Q)) {
		cout << "队列为空";
		return *(BinaryTree*)NULL;  //逻辑空
	}
	return Q.treeData[Q.front];
}
