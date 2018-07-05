#include<iostream>
#include<vector>
#include<stdlib.h> 
using namespace std;
int n, m;//n为节点数,m为边数
bool visited[20] = {true};
int a = 1;//表示当前节点是否遍历过
struct LinkNode {
	int adjvex;
	struct LinkNode *nextarc;
};
struct VNode {
	char data;
	LinkNode *firstarc;
}AdjList[20];
void CreateLink() {
	LinkNode *ptr1, *ptr2;
	cout << "请输入顶点信息V1-V"<<n << endl;
	for (int i = 1; i <= n; i++) {
		cin >> AdjList[i].data;
		AdjList[i].firstarc = NULL;
	}
	cout << "请输入" << m << "条边之间的关系,格式为a b(a,b为顶点序号)" << endl;
	for (int i = 1; i <= m; i++) {
		ptr1 = new LinkNode();
		cin >> ptr1->adjvex;
		ptr2 = new LinkNode();
		cin >> ptr2->adjvex;
		ptr2->nextarc = AdjList[ptr1->adjvex].firstarc;		
		AdjList[ptr1->adjvex].firstarc = ptr2;
		ptr1->nextarc = AdjList[ptr2->adjvex].firstarc;
		AdjList[ptr2->adjvex].firstarc = ptr1;
	}
}
//广度优先搜索
void ReadBFS() {
	vector<int> v;
	LinkNode *node;
	int vex = 1;
	if (!visited[vex]) {
		visited[vex] = true;
		cout << AdjList[vex].data<<" ";
		v.push_back(vex);
		while (!v.empty()) {
			node = AdjList[v[0]].firstarc;
			while (node != NULL&&!visited[node->adjvex]) {
				cout << AdjList[node->adjvex].data<<" ";
				visited[node->adjvex] = true;
				v.push_back(node->adjvex);
				node = node->nextarc;
			}
			v.erase(v.begin());
		}
	}
}
//图的遍历
void DFSTraverse(int m) {
	void ReadBFS();
	void ReadDFS(int v);
	for (int i = 0; i < 20; i++) {
		visited[i] = true;
	}
	for (int i = 1; i <= n; i++) {
		visited[i] = false;
	}
	if (m == 1) {
		a = 1;
		cout << "无向图深度优先搜索结果为" << endl;
		ReadDFS(1);
	}
	else {
		cout << "无向图广度优先搜索结果为" << endl;
		a = 1;
		ReadBFS();
	}
}
void ReadDFS(int v) {
	LinkNode *node;
	visited[v] = true;
	cout << AdjList[v].data <<" ";
	if (AdjList[v].firstarc == NULL) {
		return;
	}
	for (node = AdjList[v].firstarc; node != NULL; node = node->nextarc) {
		if (!visited[node->adjvex])
			ReadDFS(node->adjvex);
	}
}
void Print()
{
	int i, j;
	LinkNode *node;
	cout << "List Graph:" << endl;
	for (i = 1; i <= n; i++)
	{
		cout << i << "(" << AdjList[i].data << "): ";
		node = AdjList[i].firstarc;
		while (node != NULL)
		{
			cout << node->adjvex << "(" << AdjList[node->adjvex].data << ") ";
			node = node->nextarc;
		}
		cout << endl;
	}
}

int main() {
	cout << "请输入两个整数，n个顶点，m条边" << endl;
	while (cin >> n >> m) {
		if ( m<1 || n<1 ||m <= (n*(n - 1)) / 2) {
			CreateLink();
			break;
		}
		else
		{
			cout << "输入错误，请重新输入" << endl;
		}
	}
	Print();
	DFSTraverse(1);
	cout << endl;
	DFSTraverse(2);
	cout << endl;
	system("pause");
	return 0;
}
