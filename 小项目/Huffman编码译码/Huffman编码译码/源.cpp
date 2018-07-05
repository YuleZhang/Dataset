//题目2：哈夫曼编码和译码
//问题描述：
//利用哈夫曼编码进行信息通信可以大大提高信道利用率，缩短信息传输时间，降低传输成本。但是，这要求在发送端通过一个编码系统对待传数据预先编码，在接收端将传来的数据进行译码（复原）。对于双工信道（即可以双向传输信息的信道），每端都需要一个完整的编 / 译码系统。试为这样的信息收发站写一个哈夫曼编 / 译码系统。
//基本要求：
//一个完整的系统应具有以下功能：
//（1）初始化及文本的频率统计。从终端读入字符集大小n，以及n个字符和n个权值，完成文本的频率统计。建立哈夫曼树，并将它存于文件中。
//（2）编码。利用已建好的哈夫曼树，从文件中读入，对正文进行编码。然后将结果存入文件"CodeFile-姓名"中。
//（3）译码。利用已建好的哈夫曼树将输入的代码进行译码，将文件"CodeFile-姓名"中的代码进行译码，结果存入文件"Decoding-姓名"中。
//（4）打印哈夫曼树。将已在内存中的哈夫曼树以直观的方式显示在屏幕上。
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
int g_flag = 1;// 标志位
//vector根据权值大小排序
bool order(BinaryTree *atree,BinaryTree *btree) {
	return atree->weight < btree->weight;
}
//建立huffman树并存入文件
BinaryTree* createHuffman(BinaryTree *root) {
	cout << "请输入字符集大小：";
	cin >> g_valueNum;
	vector <BinaryTree*> Bitree;
	BinaryTree *tree;
	vector<BinaryTree*>::iterator it;
	for (int i = 0; i < g_valueNum; i++) {
		tree = new BinaryTree();
		cout << "输入字符：";
		cin >> tree->data;
		cout << "输入权值：";
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
			// 取出前两个
			BinaryTree *node_1 = Bitree[0];
			BinaryTree *node_2 = Bitree[1];
			// 删除
			Bitree.erase(Bitree.begin());
			Bitree.erase(Bitree.begin());
			// 生成新的节点
			BinaryTree *node = new BinaryTree();
			node->data = '*';
			node->weight = node_1->weight + node_2->weight;
			(node_1->weight < node_2->weight) ? (node->lchild = node_1, node->rchild = node_2) : (node->lchild = node_2, node->rchild = node_1);
			Bitree.push_back(node);
		}
	}
	cout << "构造成功" << endl;
	return Bitree[0];
}
//读取txt文件，非递归建立二叉树
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
		if (g_flag == 1) // 创建左孩子
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

				temp = vec[vec.size() - 1]; // 栈顶元素(取出栈顶元素赋予temp，注意，这不是出栈操作，因为栈顶指针top没有变)
				temp->lchild = pNew;
				vec.push_back(pNew);// 栈顶元素的左子树入栈
			}
		}
		else if (g_flag == 2) // 创建右孩子
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
				temp = vec[vec.size() - 1]; // 栈顶元素
				temp->rchild = pNew;
				vec.push_back(pNew); // 栈顶元素的右子树入栈
				g_flag = 1;
			}
		}
		else // 左右孩子都已经创建完毕
		{
			temp = vec[vec.size() - 1]; // 栈顶元素出栈，并修改栈顶指针
			vec.pop_back();
			while (vec.size() > 0 && vec[vec.size() - 1]->rchild == temp) // 若此时栈中的元素个数仍大于1个，并且刚刚出栈的元素是当前栈顶元素的右子树，则继续让栈顶元素出栈，并修改栈顶指针。
				vec.pop_back();

			g_flag = 2; // 跳出此while循环时，创建当前栈顶节点的右孩子，此时的i在g_word[]中对应的数据刚好就是下一个待使用的数据，所以执行 --i是为了防止下面的 ++i跳过了该数据(即当前i对应的数据就是我们下一步创建右子树所应该使用的数据)。
			num--;
		}
		++num;
	}
	//Exchange(node);
	return node;
}
//文件流读取huffman树
BinaryTree* readHuffman() {
	ifstream sfile("HuffmanTree.txt");
	if (!sfile)
	{
		cerr << "无法打开文件" << endl;
		system("pause");
		return NULL;
	}
	string line;
	getline(sfile, line);
	istringstream line_str(line);
	char ch;
	if (line.length() == 0) {
		cout << "请先将Huffman树插入文件" << endl;
		return NULL;
	}
	BinaryTree *node = new BinaryTree();
	for (int i = 0; line_str >> ch; i++) {
		g_word[i] = ch;
	}
	node = reproHuffman(node,0);
	cout << "读取成功" << endl;
	return node;
}
//递归存入
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
//先序存入文件
void CodeInFile(BinaryTree *tree) {
	g_fp = fopen("HuffmanTree.txt", "w");
	if (!g_fp)cout << "文件打开失败" << endl;
	if (!tree) {
		cout << "树为空" << endl;
		return;
	}
	PreOrder(tree);
	cout << "存入成功" << endl;
	fclose(g_fp);
}
//将Huffman结点编码存入Vector
void code_In_Map(BinaryTree *node) {
	if (node != NULL) {
		code_In_Map(node->rchild);
		if (node->lchild == NULL && node->rchild == NULL)
			g_mapCode[node->data] = node->code;
		code_In_Map(node->lchild);
	}
}
//根据Huffman树生成编码
void get_huffman_code(BinaryTree *node) {
	if (node->data == 0) {
		cout << "请先生成Huffman树" << endl;
		return;
	}
	BinaryTree org = *node;
	//org = node;
	//BinaryTree *orginNode = node;
	// 利用层次遍历，构造每一个节点
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
	cout << "请输入要编码的字符：";
	cin >> str;
	g_fp = fopen("CodeFile-姓名.txt", "wt+");
	for (int i = 0; i < str.length(); i++)
	{
		char chValue = str[i];
		fprintf(g_fp, "%s", g_mapCode[chValue].c_str());
		cout << chValue << g_mapCode[chValue] << endl;
		allstr += g_mapCode[chValue];
	}
	fclose(g_fp); 
	cout << "编码成功,编码结果为" << allstr << endl;
	cout << "编码存入CodeFile-姓名成功" << endl;
	return;
}
//读取文件,译码
void ReadFile(BinaryTree *tree) {
	ifstream sfile("CodeFile-姓名.txt");
	if (!sfile)
	{
		cout << "无法打开文件" << endl;
		system("pause");
		return;
	}
	string line;
	getline(sfile, line);
	cout << "待译码结果为：" << line << endl;
	istringstream line_str(line);
	char ch;
	BinaryTree btree = *tree;
	g_fp = fopen("Decoding-姓名.txt", "wt+");
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
//横向打印哈夫曼树 
void PrintTree(BinaryTree *tree, int depth)
{
	if (!tree&&depth == 0) {
		cout << "请先建立二叉树" << endl;
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
//界面初始化
void Init_Guide() {
	system("cls");
	cout << "\t\t\t\t哈夫曼编码和译码\t\t\t\t" << endl;
	cout << "1.构造Huffman树" << endl;
	cout << "2.Huffman树存入文件" << endl;
	cout << "3.读取Huffman树" << endl;
	cout << "4.编码" << endl;
	cout << "5.译码" << endl;
	cout << "6.打印Huffman" << endl;
	cout << "7.退出" << endl;
	cout << "请输入要执行的操作：";
}
//界面动画
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
	string str_welcome = "\t欢迎来到我的界面，下面给大家介绍一下我们小组成员\t\t\t\t\n";
	string str_introduce = "\t\t组长：张宇\n\t\t组员：郭宇轩\n\t\t组员：吴京缘\n";
	string str_project = "\t我们组的项目是“哈夫曼编码和译码”\n";
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
//主函数
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
				cout << "暂未Huffman树" << endl;
			}
			break;
		case 7:
			exit = 0;
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
			break;
		}
		system("pause");
		Init_Guide();
		if (exit != 0) {
			cin.ignore(1000, '\n');//消除影响
			//scanf("%d", &selectValue);
			cin >> selectValue;
		}
	}
	return 0;
}