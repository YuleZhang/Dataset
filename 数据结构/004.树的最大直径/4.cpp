//seek the maximum path
#include<iostream>
#include<vector>
#include<stdlib.h> 
#include<string.h>
using namespace std;
#define INF 1000000
//recording the input
vector<int> point[10000];
vector<int> dis[10000];
int d[10000];
bool flag[10000];   //to make sure this point whether be visit
void digui(int x) {
	flag[x] = true;
	int size = point[x].size();
	for (int i = 0; i < size; i++) {
		int v = point[x][i];
		if (!flag[v]) {
			d[v] = d[x] + dis[x][i];
			digui(v);
		}
	}
}
int main() {
	int n;
	int fir, sec, disValue;
	cout << "please input the number of node" << endl;
	cin >> n;
	for (int i = 0; i < n-1; i++) {
		cin >> fir >> sec >> disValue;
		point[fir - 1].push_back(sec-1);
		dis[fir - 1].push_back(disValue);
		point[sec - 1].push_back(fir-1);
		dis[sec - 1].push_back(disValue);
	}
	memset(flag, 0, sizeof(flag));//init flag
	//init length to 0 and Infinity
	for (int i = 0; i < n - 1; i++) {
		d[i] = (i==0?0:INF);
	}
	digui(0);
	int max = -1;
	int start = 0;
	for (int i = 0; i < n; i++) {
		if (d[i] > max&&d[i] != INF) {
			max = d[i];
			start = i;
		}
	}
	memset(flag, 0, sizeof(flag));
	for (int i = 0; i < n; i++) {
		d[i] = (i == start ? 0 : INF);
	}
	digui(start);
	int ans = 0;
	for (int i = 0; i < n-1;i++) {
		if (d[i]>max&&d[i]!=INF) {
			ans = d[i];
		}
	}
	cout << ans << endl;
	system("pause");
	return 0;
}
