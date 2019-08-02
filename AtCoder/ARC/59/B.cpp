#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	int w,id;
	bool operator < (const data &C) const {
		return w>C.w;
	}
}a[N];
priority_queue<data>q;
char lx[N];

int main(){
	scanf("%s",lx+1);
	int n=strlen(lx+1);
	fr(o,1,26){
		while(!q.empty()) q.pop();
		int nw=0;a[0]=(data){nw,0};
		fr(i,1,n){
			int pos=lx[i]-'a'+1;
			if(pos==o) nw++;
			else nw--;
			a[i]=(data){nw,i};
		}
		fr(i,2,n){
			q.push(a[i-2]);
			data h=q.top();
			if(a[i].w-h.w>0) return printf("%d %d\n",h.id+1,i),0;
		}
	}
	printf("-1 -1\n");
	return 0;
}