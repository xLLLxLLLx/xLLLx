#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
char lx[N];
int vis[N],b[N],c[N];

int main(){
	int k;scanf("%d",&k);
	scanf("%s",lx+1);
	int len=strlen(lx+1);
	int res=0;
	fr(i,1,len){
		int pos=lx[i]-'a'+1;
		if(!vis[pos]) vis[pos]=i,b[i]=1,res++;
	}
	if(res<k) printf("NO\n");
	else {
		int res=0;
		printf("YES\n");
		fr(i,1,len){
			if(b[i]) c[++res]=i;
		}
		c[k+1]=len+1;
		fr(i,1,k){
			fr(j,c[i],c[i+1]-1) {
				cout<<lx[j];
			}
			cout<<endl;
		}
	}
	return 0;
}
