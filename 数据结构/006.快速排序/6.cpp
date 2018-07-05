#include<iostream>
#include<time.h>
#include<stdlib.h> 
using namespace std;
int L[11] = {1,12,34,2,45,6,5,9,14,23,24};
int pivotkey;
int Partition(int low, int high) {
	L[0] = L[low];
	pivotkey = L[low];
	while (low < high) {
		while (low<high&&L[high]>=pivotkey)--high;
		int mid = L[low];
		L[low] = L[high];
		L[high] = mid;
		while (low<high&&L[low]<=pivotkey)++low;
		mid = L[low];
		L[low] = L[high];
		L[high] = mid;
	}
	L[low] = L[0];
	return low;
}
int pivotloc;
void Qsort(int low, int high) {
	if (low < high) {
		pivotloc = Partition(low, high);
		Qsort(low, pivotloc - 1);
		Qsort(pivotloc + 1, high);
	}
}
int main() {
	clock_t startTime, endTime;
	startTime = clock();
	int midValue;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10 - i; j++)// j开始等于0，  
		{
			if (L[j] > L[j + 1])
			{
				int temp = L[j];
				L[j] = L[j + 1];
				L[j + 1] = temp;
			}
		}
	}
	for (int i = 1; i < 11; i++) {
		cout << L[i] << " ";
	}
	cout << endl;
	cout<< "冒泡排序："; 
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	cout << endl;
	Qsort(1,10);
	for (int i = 1; i < 11; i++) {
		cout << L[i] << " ";
	}
	cout << endl;
	cout<< "快速排序："; 
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}
