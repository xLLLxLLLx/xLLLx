#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	system("g++ -std=c++11 -o std std.cpp\n");
	system("g++ -g my.cpp -o my\n");
	system("g++ -g tt.cpp -o tt\n");
	for(int i=1;;i++){
		system("./tt > out\n");
		system("./std < out > oo\n");
		system("./my < out > uu\n");
		if(system("diff oo uu\n")) return printf("WAI!!!\n"),0;
		else printf("test%d:AC!\n",i);
	}
	return 0;
}