//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<iostream>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
char lx[N];

int main(){
	int n;cin>>n;
	fr(i,1,n){
		scanf("%s",lx+1);
		int len=strlen(lx+1);
		sort(lx+1,lx+1+len);
		int pos=lx[1]-'a'+1,flg=1;
		fr(i,2,len) if(lx[i]-'a'+1!=pos+i-1) flg=0; 
		if(flg) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}