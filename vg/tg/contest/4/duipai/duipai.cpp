#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	system("g++ -g std.cpp -o std");
	system("g++ -g my.cpp -o my");
	system("g++ -g t.cpp -o t");
	for(int o=1;;o++){
		system("./t > out");
		system("./std < out > oo");
		system("./my < out > uu");
		if(system("diff oo uu")) exit(0);
		else printf("test=%d GotAcceppted!!\n",o);
	}
	return 0;
}