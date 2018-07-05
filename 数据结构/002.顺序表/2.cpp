#include<iostream>
using namespace std;
typedef struct {
	int data[100];
	int length;
}Sqlist;
void create(Sqlist &L){
	cout << "please input the number of data!"<<endl;
	int n;
	cin >> n;
	int dat;
	cout <<  "Please input the number:";
	for(int i =0;i<n;i++){
		cin >>dat;
		L.data[i] = dat;
		L.length++;
	}
} 
void insert(Sqlist &L,int loca,int data){
	if(loca>L.length+1||loca<0){
		return;
	}
	if(loca==L.length+1){
		L.data[L.length++] = data;
	}
	if(loca>=0&&loca<L.length+1){
		for(int i = L.length;i>=loca;i--){
			L.data[i+1] =L.data[i];
		}
		L.data[loca] = data;
		L.length++;
	}
	return;
}
int deletes(Sqlist &L,int loca){
	if(loca>L.length&&loca<0){
		return -1;
	}
	if(loca == L.length){
		L.data[loca] == 0;
		return 0;
	}
	if(loca>=0&&loca<L.length){
		for(int i = loca;i<L.length+1;i++){
			L.data[i] = L.data[i+1];
		}
	}
	L.length--;
	return 0;
}
void show(Sqlist &L){
	cout << "the list data is :";
	if(L.length!=0){
		for(int i = 0;i<L.length;i++){
			cout << L.data[i]<<" ";
		}
	}
}
void findcommon(Sqlist &l,Sqlist &p,Sqlist &q){
	int i =0,j = 0;
	int k =0;
	while(i<=l.length&&j<=p.length){
		if(l.data[i]>p.data[j]){
			j++;
		}
		else if(l.data[i]<p.data[j]){
			i++;
		}
		else{
//			cout << l.data[i] <<" ";
			insert(q,k++,l.data[i]);
			i++;j++;
		}
	}
}
int main()
{
	Sqlist L;
	Sqlist P;
	Sqlist Q;
	L.length = 0;
	P.length= 0;
	Q.length= 0;
	create(L);
	show(L);
	cout << endl;
	create(P);
	show(P);
	cout << endl;
	cout << "l.length:" <<L.length<<"  P.length:"<<P.length<<" " <<endl;
	findcommon(L,P,Q);
	show(Q);
	return 0;
} 
