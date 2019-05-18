#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=110;
int a[N],b[N],nm[30],vis[30];
char lx[N];

int main(){
	int T;cin>>T;
	fr(o,1,T){
		scanf("%s",lx+1);
		int len=strlen(lx+1);
		fr(i,1,len) nm[lx[i]-'a'+1]++;
		fr(i,1,26) if(!nm[i]) vis[i]=1;
		int res=1,l=0,r=0;
		int head=100,tail=100;
		for(;;){
			int flg=0,F=0;
			fr(i,1,26){
				if(!vis[i]) flg=1;
				else continue;
				if(!l){
					l=r=i;
					b[++tail]=i;
					F=1;
					vis[i]=1;
					break;
				} else {
					if(abs(l-i)!=1){
						b[--head]=i;
						l=i;
						F=1;
						vis[i]=1;
						break;
					} else if(abs(r-i)!=1){
						b[++tail]=i;
						r=i;
						F=1;
						vis[i]=1;
						break;
					}
				}
			}
			if(!flg) break;
			if(!F) {
				res=0;
				printf("No answer\n");
				break;
			}
		}
		if(res){
			fr(i,head,tail){
				fr(j,1,nm[b[i]]) printf("%c",char(b[i]+'a'-1));
			}
			puts("");
		}
		memset(vis,0,sizeof vis),memset(nm,0,sizeof nm);
	}
	return 0;
}