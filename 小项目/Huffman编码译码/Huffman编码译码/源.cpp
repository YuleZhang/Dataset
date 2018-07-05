//��Ŀ2�����������������
//����������
//���ù��������������Ϣͨ�ſ��Դ������ŵ������ʣ�������Ϣ����ʱ�䣬���ʹ���ɱ������ǣ���Ҫ���ڷ��Ͷ�ͨ��һ������ϵͳ�Դ�������Ԥ�ȱ��룬�ڽ��ն˽����������ݽ������루��ԭ��������˫���ŵ���������˫������Ϣ���ŵ�����ÿ�˶���Ҫһ�������ı� / ����ϵͳ����Ϊ��������Ϣ�շ�վдһ���������� / ����ϵͳ��
//����Ҫ��
//һ��������ϵͳӦ�������¹��ܣ�
//��1����ʼ�����ı���Ƶ��ͳ�ơ����ն˶����ַ�����Сn���Լ�n���ַ���n��Ȩֵ������ı���Ƶ��ͳ�ơ��������������������������ļ��С�
//��2�����롣�����ѽ��õĹ������������ļ��ж��룬�����Ľ��б��롣Ȼ�󽫽�������ļ�"CodeFile-����"�С�
//��3�����롣�����ѽ��õĹ�������������Ĵ���������룬���ļ�"CodeFile-����"�еĴ���������룬��������ļ�"Decoding-����"�С�
//��4����ӡ�����������������ڴ��еĹ���������ֱ�۵ķ�ʽ��ʾ����Ļ�ϡ�
#include<iostream>
#include "dataset.h"
#include<vector>
#include<stdlib.h>
#include<time.h>
#include <fstream>
#include<map>
#include <sstream>
#include<algorithm>
using namespace std;
int g_valueNum;
char g_word[100];
FILE *g_fp;
map<char, string> g_mapCode;
int g_flag = 1;// ��־λ
//vector����Ȩֵ��С����
bool order(BinaryTree *atree,BinaryTree *btree) {
	return atree->weight < btree->weight;
}
//����huffman���������ļ�
BinaryTree* createHuffman(BinaryTree *root) {
	cout << "�������ַ�����С��";
	cin >> g_valueNum;
	vector <BinaryTree*> Bitree;
	BinaryTree *tree;
	vector<BinaryTree*>::iterator it;
	for (int i = 0; i < g_valueNum; i++) {
		tree = new BinaryTree();
		cout << "�����ַ���";
		cin >> tree->data;
		cout << "����Ȩֵ��";
		cin >> tree->weight;
		Bitree.push_back(tree);
	}
	while (Bitree.size() > 0) {
		sort(Bitree.begin(), Bitree.end(), order);
		if (Bitree.size() == 1) {
			root = Bitree[0];
			return root;
			/*Bitree.erase(Bitree.begin());*/
		}
		else {
			// ȡ��ǰ����
			BinaryTree *node_1 = Bitree[0];
			BinaryTree *node_2 = Bitree[1];
			// ɾ��
			Bitree.erase(Bitree.begin());
			Bitree.erase(Bitree.begin());
			// �����µĽڵ�
			BinaryTree *node = new BinaryTree();
			node->data = '*';
			node->weight = node_1->weight + node_2->weight;
			(node_1->weight < node_2->weight) ? (node->lchild = node_1, node->rchild = node_2) : (node->lchild = node_2, node->rchild = node_1);
			Bitree.push_back(node);
		}
	}
	cout << "����ɹ�" << endl;
	return Bitree[0];
}
//��ȡtxt�ļ����ǵݹ齨��������
BinaryTree* reproHuffman(BinaryTree *tree, int num) {
	BinaryTree *node = new BinaryTree();
	int len = (int)strlen(g_word);
	BinaryTree *temp;
	//BinaryTree *p;
	vector <BinaryTree*> vec;
	node->data = g_word[num];
	node->lchild = NULL;
	node->rchild = NULL;
	vec.push_back(node);
	num++;
	while (num < len) {
		BinaryTree *pNew = NULL;
		if (g_flag == 1) // ��������
		{
			if (g_word[num] == '#')
				g_flag = 2;
			else
			{
				pNew = new BinaryTree();
				//InitTree(pNew);
				pNew->data = g_word[num];
				pNew->lchild = NULL;
				pNew->rchild = NULL;

				temp = vec[vec.size() - 1]; // ջ��Ԫ��(ȡ��ջ��Ԫ�ظ���temp��ע�⣬�ⲻ�ǳ�ջ��������Ϊջ��ָ��topû�б�)
				temp->lchild = pNew;
				vec.push_back(pNew);// ջ��Ԫ�ص���������ջ
			}
		}
		else if (g_flag == 2) // �����Һ���
		{
			if (g_word[num] == '#')
				g_flag = 3;
			else
			{
				pNew = new BinaryTree();
				pNew->data = g_word[num];
				pNew->lchild = NULL;
				pNew->rchild = NULL;
				if(!vec.empty())
				temp = vec[vec.size() - 1]; // ջ��Ԫ��
				temp->rchild = pNew;
				vec.push_back(pNew); // ջ��Ԫ�ص���������ջ
				g_flag = 1;
			}
		}
		else // ���Һ��Ӷ��Ѿ��������
		{
			temp = vec[vec.size() - 1]; // ջ��Ԫ�س�ջ�����޸�ջ��ָ��
			vec.pop_back();
			while (vec.size() > 0 && vec[vec.size() - 1]->rchild == temp) // ����ʱջ�е�Ԫ�ظ����Դ���1�������Ҹոճ�ջ��Ԫ���ǵ�ǰջ��Ԫ�ص����������������ջ��Ԫ�س�ջ�����޸�ջ��ָ�롣
				vec.pop_back();

			g_flag = 2; // ������whileѭ��ʱ��������ǰջ���ڵ���Һ��ӣ���ʱ��i��g_word[]�ж�Ӧ�����ݸպþ�����һ����ʹ�õ����ݣ�����ִ�� --i��Ϊ�˷�ֹ����� ++i�����˸�����(����ǰi��Ӧ�����ݾ���������һ��������������Ӧ��ʹ�õ�����)��
			num--;
		}
		++num;
	}
	//Exchange(node);
	return node;
}
//�ļ�����ȡhuffman��
BinaryTree* readHuffman() {
	ifstream sfile("HuffmanTree.txt");
	if (!sfile)
	{
		cerr << "�޷����ļ�" << endl;
		system("pause");
		return NULL;
	}
	string line;
	getline(sfile, line);
	istringstream line_str(line);
	char ch;
	if (line.length() == 0) {
		cout << "���Ƚ�Huffman�������ļ�" << endl;
		return NULL;
	}
	BinaryTree *node = new BinaryTree();
	for (int i = 0; line_str >> ch; i++) {
		g_word[i] = ch;
	}
	node = reproHuffman(node,0);
	cout << "��ȡ�ɹ�" << endl;
	return node;
}
//�ݹ����
void PreOrder(BinaryTree *tree) {
	if (tree==nullptr) {
		fprintf(g_fp, "%c", '#');
		cout << '#';
		return;
	}
	fprintf(g_fp, "%c", tree->data);
	cout << tree->data;
	PreOrder(tree->lchild);
	PreOrder(tree->rchild);
}
//��������ļ�
void CodeInFile(BinaryTree *tree) {
	g_fp = fopen("HuffmanTree.txt", "w");
	if (!g_fp)cout << "�ļ���ʧ��" << endl;
	if (!tree) {
		cout << "��Ϊ��" << endl;
		return;
	}
	PreOrder(tree);
	cout << "����ɹ�" << endl;
	fclose(g_fp);
}
//��Huffman���������Vector
void code_In_Map(BinaryTree *node) {
	if (node != NULL) {
		code_In_Map(node->rchild);
		if (node->lchild == NULL && node->rchild == NULL)
			g_mapCode[node->data] = node->code;
		code_In_Map(node->lchild);
	}
}
//����Huffman�����ɱ���
void get_huffman_code(BinaryTree *node) {
	if (node->data == 0) {
		cout << "��������Huffman��" << endl;
		return;
	}
	BinaryTree org = *node;
	//org = node;
	//BinaryTree *orginNode = node;
	// ���ò�α���������ÿһ���ڵ�
	BinaryTree *p = node;
	//queue<BinaryTree *> Q;
	queue Q;
	int count = 0;
	Set_NULL(Q);
	En_Queue(Q, *p);
	while (Q.size > 0) {
		*p = front_element(Q);
		De_Queue(Q);
		if (p->lchild != NULL) {
			strcpy((p->lchild)->code, p->code);
			char *ptr = (p->lchild)->code;
			while (*ptr!='\0') {
				ptr++;
			}
			*ptr = '0';
			En_Queue(Q, *(p->lchild));
		}
		if (p->rchild != NULL) {
			strcpy((p->rchild)->code, p->code);
			char *ptr = (p->rchild)->code;
			while (*ptr!='\0') {
				ptr++;
			}
			*ptr = '1';
			En_Queue(Q, *(p->rchild));
		}
	}
	code_In_Map(&org);
	string str;
	string allstr;
	cout << "������Ҫ������ַ���";
	cin >> str;
	g_fp = fopen("CodeFile-����.txt", "wt+");
	for (int i = 0; i < str.length(); i++)
	{
		char chValue = str[i];
		fprintf(g_fp, "%s", g_mapCode[chValue].c_str());
		cout << chValue << g_mapCode[chValue] << endl;
		allstr += g_mapCode[chValue];
	}
	fclose(g_fp); 
	cout << "����ɹ�,������Ϊ" << allstr << endl;
	cout << "�������CodeFile-�����ɹ�" << endl;
	return;
}
//��ȡ�ļ�,����
void ReadFile(BinaryTree *tree) {
	ifstream sfile("CodeFile-����.txt");
	if (!sfile)
	{
		cout << "�޷����ļ�" << endl;
		system("pause");
		return;
	}
	string line;
	getline(sfile, line);
	cout << "��������Ϊ��" << line << endl;
	istringstream line_str(line);
	char ch;
	BinaryTree btree = *tree;
	g_fp = fopen("Decoding-����.txt", "wt+");
	for (int i = 0; line_str >> ch; i++) {
		tree = ch == '0' ? tree->lchild : tree->rchild;
		if (tree) {
			if (tree->data != '*') {
				fprintf(g_fp, "%c",tree->data);
				cout << tree->data;
				tree = &btree;
			}
		}
	}
	fclose(g_fp);
}
//�����ӡ�������� 
void PrintTree(BinaryTree *tree, int depth)
{
	if (!tree&&depth == 0) {
		cout << "���Ƚ���������" << endl;
		return;
	}
	int i;
	if (tree)
	{
		PrintTree(tree->rchild, depth + 1);
		for (i = 0; i < depth; i++)printf("  ");
		if (depth == 0) {
			cout << endl; 
		}
		cout << tree->data;
		cout << endl;
		PrintTree(tree->lchild, depth + 1);
	}
}
//�����ʼ��
void Init_Guide() {
	system("cls");
	cout << "\t\t\t\t���������������\t\t\t\t" << endl;
	cout << "1.����Huffman��" << endl;
	cout << "2.Huffman�������ļ�" << endl;
	cout << "3.��ȡHuffman��" << endl;
	cout << "4.����" << endl;
	cout << "5.����" << endl;
	cout << "6.��ӡHuffman" << endl;
	cout << "7.�˳�" << endl;
	cout << "������Ҫִ�еĲ�����";
}
//���涯��
void Draw() {
	int i, j, k, depth = 4;
	for (j = 0; j < depth; j++) {
		int w = 1 << (depth - j + 1);
		if (j == 0)
			printf("%*c\n", w, '_');
		else {
			for (i = 0; i < 1 << (j - 1); i++) {
				printf("%*c", w + 1, ' ');
				for (k = 0; k < w - 3; k++) printf("_");
				printf("/ \\");
				for (k = 0; k < w - 3; k++) printf("_");
				printf("%*c", w + 2, ' ');
			}
			printf("\n");
			for (i = 0; i < 1 << (j - 1); i++)
				printf("%*c/%*c_%*c", w, '_', w * 2 - 2, '\\', w, ' ');
			printf("\n");
		}
		for (i = 0; i < 1 << j; i++)
			printf("%*c_)%*c", w - 1, '(', w - 1, ' ');
		printf("\n");
	}
	cout << endl;
	string str_welcome = "\t��ӭ�����ҵĽ��棬�������ҽ���һ������С���Ա\t\t\t\t\n";
	string str_introduce = "\t\t�鳤������\n\t\t��Ա��������\n\t\t��Ա���⾩Ե\n";
	string str_project = "\t���������Ŀ�ǡ���������������롱\n";
	for (int i = 0; i < str_welcome.length(); i++) {
		cout << str_welcome[i];
		_sleep(100);
	}
	for (int i = 0; i < str_introduce.length(); i++) {
		cout << str_introduce[i];
		_sleep(100);
	}
	for (int i = 0; i < str_project.length(); i++) {
		cout << str_project[i];
		_sleep(100);
	}
	system("pause");
}   
//������
int main() {
	Draw();
	system("color fc");
	BinaryTree *binaryTree = new BinaryTree();
	BinaryTree BiTree;
	BiTree.data = '0';
	Init_Guide();
	int selectValue;
	int exit = 1; 
	cin >> selectValue;
	while (exit) {
		switch (selectValue)
		{
		case 1:
			//system("color 0b");
			binaryTree = createHuffman(binaryTree);
			BiTree = *binaryTree;
			break;
		case 2:
			//system("color 0c");
			CodeInFile(&BiTree);
			break;
		case 3:
			//system("color 0f");
			binaryTree = readHuffman();
			BiTree = *binaryTree;
			break;
		case 4:
			//system("color 0a");
			BiTree = *binaryTree;
			get_huffman_code(binaryTree);
			break;
		case 5:
			//system("color 0d");
			ReadFile(&BiTree);
			break;
		case 6:
			//system("color 0f");
			if ((&BiTree)->data != '0') {
				PrintTree(&BiTree, 0);
			}
			else
			{
				cout << "��δHuffman��" << endl;
			}
			break;
		case 7:
			exit = 0;
			break;
		default:
			cout << "�����������������" << endl;
			break;
		}
		system("pause");
		Init_Guide();
		if (exit != 0) {
			cin.ignore(1000, '\n');//����Ӱ��
			//scanf("%d", &selectValue);
			cin >> selectValue;
		}
	}
	return 0;
}