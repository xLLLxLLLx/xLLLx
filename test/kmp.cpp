#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e6+10;
int pp[N];
char ll[N];

int main(){
	for(;;){
		scanf("%s",ll+1);
		if(ll[1]=='.') break;
		int lenx=strlen(ll+1);
		int lt=0;
		fr(i,2,lenx){
			if(ll[i]==ll[lt+1]){
				pp[i]=++lt;
				continue;
			}
			while(lt&&ll[lt+1]!=ll[i]){
				lt=pp[lt];
			}
			if(ll[lt+1]!=ll[i]) pp[i]=lt=0;
			else pp[i]=++lt;
		}
		int gg=lenx-pp[lenx];
		if(lenx%gg) printf("1\n");
		else printf("%d\n",lenx/gg);
	}
	return 0;
}