#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
  int nt,to;
}a[N<<1];
int f[N],g[N],w[N],s[N];

template <class T>
void read(T &x){
    char ch=getchar();bool t=0;
    for(;ch<'0'||ch>'9';ch=getchar()) t|=(ch=='-');
    for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
}

int main(){
  int n;read(n);
  for(int i=1,x,y;i<n;++i) scanf("%d%d",&x,&y),add(x,y);
   
  return 0;
}
