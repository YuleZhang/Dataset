#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct node
{
	int data;
	struct node *next;
}LINKLIST;
LINKLIST *Nodelist = new node();
void ListInsert(int e) {
	node *firnode = Nodelist;
	while (firnode->next!=NULL)
	{
		firnode = firnode->next;
	}
	firnode->data = e;
	node *insenode = new node();
	insenode->next = NULL;
	firnode->next = insenode;
}
void ListDelete(int e) {
	node *firnode = Nodelist;
	node *delnode = NULL;
	if (firnode == NULL)
	{
		cout << "链表为空" << endl;
		return;
	}
	else
	{
		if (firnode->data == e) {
			Nodelist = Nodelist->next;
			free(firnode);
			return;
		}
		else
		{
			while (firnode!=NULL)
			{
				delnode = firnode;
				delnode = delnode->next;
				if (firnode->data==e)
				{
					firnode->next = delnode->next;
					free(delnode);
					cout << "删除成功" << endl;
					return;
				}
				firnode = firnode->next;
			}
			cout << "不存在该数" << endl;
			return;
		}
	}
}
void ListPrint() {
	node *firnode = Nodelist;
	if (firnode == NULL) {
		cout << "链表为空" << endl;
		return;
	}
	while (firnode->next!=NULL)
	{
		cout <<int(firnode->data)<< " ";
		firnode = firnode->next;
	}
	cout << endl;
}
int ListSearchNum(int searchNum){
	node *firNode = Nodelist;
	int i = 0;
	if (firNode == NULL)
	{
		cout << "链表为空" << endl;
		return NULL;
	}
	for (i = 1; i <= searchNum; i++)
	{
		if (firNode->next!=NULL)
		{
			firNode = firNode->next;
		}
		else
		{
			return NULL;
		}
	}
	return firNode->data;
}
int ListSearchValues(int dataValues) {
	node *firNode = Nodelist;
	int i = 0;
	if (firNode == NULL)
	{
		cout << "链表为空" << endl;
		return NULL;
	}
	while (firNode != NULL)
	{
		i++;
		if (firNode->data == dataValues) {
			return i;
		}
		firNode = firNode->next;
	}
	return NULL;
}
int main() {
	int choose = 10,results,searchResult;
	cout << "※请选择要执行的操作※" << endl;
	cout << "0.退出" << endl;
	cout << "1.插入一个元素" << endl;
	cout << "2.删除一个元素" << endl;
	cout << "3.按序号查找" << endl;
	cout << "4.按值查找" << endl;
	cout << "5.显示所有元素" << endl;
	while (choose!=0) {
		//system("Cls");
		cin >> choose;
		switch (choose)
		{
		case 0:
			break;
		case 1:
			cout << "输入要插入的元素:";
			int dataInsert;
			cin >> dataInsert;
			ListInsert(dataInsert);
			cout << "插入成功" << endl;
			//system("Cls");
			break;
		/*default:
			break;*/
		case 2:
			cout << "输入要删除的元素:";
			int dataDelete;
			cin >> dataDelete;
			ListDelete(dataDelete);
			//system("Cls");
			break;
		case 3:
			cout << "请输入要查的序号:";
			int dataNum;
			cin >> dataNum;
			results = ListSearchNum(dataNum-1);
			if (results == NULL) {
				cout << "未找到" << endl;
			}
			else
			{
				cout << "该位置元素为"<<results << endl;
			}
			//system("Cls");
			break;
		case 4:
			cout << "请输入要查找的值";
			int dataValues;
			cin >> dataValues;
			searchResult = ListSearchValues(dataValues);
			if (searchResult ==NULL)
			{
				cout << "未找到";
			}
			else
			{
				cout << searchResult << endl;
			}
			
			break;
		case 5:
			ListPrint();
			//system("Cls");
			break;
		default:
			cout << "输入错误，请重新输入";
			break;
		}
	}
	system("pause");
	return 0;
}
