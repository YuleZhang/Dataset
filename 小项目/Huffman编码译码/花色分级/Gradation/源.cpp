#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
char cardsColor[5];  //�����ƵĻ�ɫ
int cardsNum[5]; //�����Ƶ���ֵ
//int times = 0;    
int vex = 0;  //���ض��Ӹ���
int three;  //�Ƿ�����������ͬ
int four; //�Ƿ����ĸ�����ͬ
//�ж������ɫ�Ƿ���ͬ
bool judgeColor() {
	int initNum = 0;
	char oriColor = cardsColor[0];
	for (int i = 0; i < 5; i++) {
		if (cardsColor[i] == oriColor) {
			initNum++;
		}
	}
	if (initNum == 5) return true;
	return false;
}
//����
void sort()//��������  
{
	int temp = 0;
	for (int i = 0; i<4; ++i)
		for (int j = i + 1; j<5; ++j)
		{
			if (cardsNum[i]>cardsNum[j])
			{
				temp = cardsNum[i];
				cardsNum[i] = cardsNum[j];
				cardsNum[j] = temp;
			}
		}
}
//�ж��Ƿ�Ϊ˳��
bool IsOrderly()
{
	int n = 5;
	sort();//��������  
	//�Ƴ����ظ������  
	for (int i = 0; i<n - 1; ++i)
		for (int j = i + 1; j<n ; ++j)
			if (cardsNum[i] == cardsNum[j])
				return false;
	if (cardsNum[4] - cardsNum[0] == 4) {
		return true;
	}
	return false;
}
//���Һ��������ĸ��ַ�
void search() {
	int init;//��ʼֵ
	int count;//����
	for (int j = 0; j < 5; j++) {
		count = 0;
		init = cardsNum[j];
		for (int i = 0; i < 5; i++) {
			if (cardsNum[i] == init) {
				count++;
			}
		}
		if (count == 2) {
			vex++;
		}
		if (count == 3) {
			three = 1;
		}
		if (count == 4) {
			four = 1;
		}
	}
}
//������ϲ��ҵȼ�
int Grade() {
	bool isOrder = IsOrderly();//��������  
	if (cardsNum[0] == 1 && cardsNum[1] == 10 && cardsNum[2] == 11 && cardsNum[3] == 12 && cardsNum[4] == 13) isOrder = true; //1��'A'ʹ
	search();
	if (judgeColor()) {
		if (isOrder)
		{
			if (cardsNum[0] == 1&&cardsNum[1] == 10)
				return 9;
			else return 8;
		}
		else return 5;
	}
	else if (four == 1)
	{
		return 7;
	}
	else if (three == 1) {
		if (vex/2 == 1) {
			return 6;
		}
		else
		{
			return 1;
		}
	}
	else{
		if (isOrder)return 4;
		else if (vex/2 == 2) {
			return 2;
		}
		else if (vex/2 == 1)
		{
			return 3;
		}
		else
		{
			return 0;
		}
	}
}
//������
int main() {
	int k = 0; int m = 0;
	FILE *fp;
	fp = fopen("why.txt", "w");
	ifstream sfile("training.txt");
	if (!sfile)
	{
		cerr << "�޷����ļ�" << endl;
		system("pause");
		return -1;
	}

	string line;
	vector<string> word;
	while (getline(sfile, line))
	{
		word.push_back(line);
	}
	sfile.close();
	//for (auto it :word)
	vector<string>::const_iterator it = word.begin();
	while (it != word.end())//����
	{
		istringstream line_str(*it);
		char words[2];
		for (int i = 0; line_str >> words; i++) {
			if (i % 2 == 0) {
				cardsColor[k] = words[0];
				k++;
			}
			else {
				if (words[1] == '0') cardsNum[m] = 10;
				else if (words[0] == 'J') cardsNum[m] = 11;
				else if (words[0] == 'Q') cardsNum[m] = 12;
				else if (words[0] == 'K') cardsNum[m] = 13;
				else cardsNum[m] = words[0] - '0';
				m++;
			}
		}
		int asss = Grade();
		cout << asss << endl;
		fprintf(fp, "%d\n", asss);
		k = 0;
		m = 0;
		three = 0;
		four = 0;
		vex = 0;
		++it;
	}
	fclose(fp);
	system("pause");
	return 0;
}
