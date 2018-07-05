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
		cout << "����Ϊ��" << endl;
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
					cout << "ɾ���ɹ�" << endl;
					return;
				}
				firnode = firnode->next;
			}
			cout << "�����ڸ���" << endl;
			return;
		}
	}
}
void ListPrint() {
	node *firnode = Nodelist;
	if (firnode == NULL) {
		cout << "����Ϊ��" << endl;
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
		cout << "����Ϊ��" << endl;
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
		cout << "����Ϊ��" << endl;
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
	cout << "����ѡ��Ҫִ�еĲ�����" << endl;
	cout << "0.�˳�" << endl;
	cout << "1.����һ��Ԫ��" << endl;
	cout << "2.ɾ��һ��Ԫ��" << endl;
	cout << "3.����Ų���" << endl;
	cout << "4.��ֵ����" << endl;
	cout << "5.��ʾ����Ԫ��" << endl;
	while (choose!=0) {
		//system("Cls");
		cin >> choose;
		switch (choose)
		{
		case 0:
			break;
		case 1:
			cout << "����Ҫ�����Ԫ��:";
			int dataInsert;
			cin >> dataInsert;
			ListInsert(dataInsert);
			cout << "����ɹ�" << endl;
			//system("Cls");
			break;
		/*default:
			break;*/
		case 2:
			cout << "����Ҫɾ����Ԫ��:";
			int dataDelete;
			cin >> dataDelete;
			ListDelete(dataDelete);
			//system("Cls");
			break;
		case 3:
			cout << "������Ҫ������:";
			int dataNum;
			cin >> dataNum;
			results = ListSearchNum(dataNum-1);
			if (results == NULL) {
				cout << "δ�ҵ�" << endl;
			}
			else
			{
				cout << "��λ��Ԫ��Ϊ"<<results << endl;
			}
			//system("Cls");
			break;
		case 4:
			cout << "������Ҫ���ҵ�ֵ";
			int dataValues;
			cin >> dataValues;
			searchResult = ListSearchValues(dataValues);
			if (searchResult ==NULL)
			{
				cout << "δ�ҵ�";
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
			cout << "�����������������";
			break;
		}
	}
	system("pause");
	return 0;
}
