//#include<bits/stdc++.h>
#include<iostream>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
int a[N],b[N],c[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n){
		scanf("%d",&a[i]);
		b[a[i]]++;
		if(b[a[i]]>2) return printf("NO\n"),0;
	}
	printf("YES\n");
	fr(i,0,2e5) if(b[i]) c[++c[0]]=i,b[i]--;
	printf("%d\n",c[0]);
	fr(i,1,c[0]) printf("%d ",c[i]);
	puts("");c[0]=0;
	rf(i,2e5,0) if(b[i]) c[++c[0]]=i;
	printf("%d\n",c[0]);
	fr(i,1,c[0]) printf("%d ",c[i]);
	return 0;
}