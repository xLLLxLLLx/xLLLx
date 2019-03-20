#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
vector<int>g[N];
queue<int>q;
int mk[N];

void pd(bool b){
  if(!b){
    printf("No\n");
    exit(0);
  }
}

int main(){
  int n,k;scanf("%d%d",&n,&k);
  for(int i=1,x,y;i<n;++i)
    scanf("%d%d",&x,&y),
    g[x].push_back(y),
    g[y].push_back(x);
  fr(i,1,n) if(g[i].size()==1) q.push(i),mk[i]=1;
  int res=0;
  while(!q.empty()){
    ++res;
    int sz=q.size();
    fr(i,1,sz){
      int h=q.front();q.pop();
      int len=g[h].size();
      fr(i,0,len-1){
        if(!mk[g[h][i]]) mk[g[h][i]]=mk[h]+1,q.push(g[h][i]);
      }
    }
  }
  pd(res-1==k);
  //fr(i,1,n) printf("%d mk=%d\n",i,mk[i]);
  fr(i,1,n){
    int len=g[i].size();
    int pos=0,tmp=0;
    fr(j,0,len-1){
      int k=g[i][j];
      if(mk[k]==mk[i]+1) pos++;
      else if(mk[k]+1==mk[i]) tmp++;
      else pd(0);
    }
    if(mk[i]==res) pd(tmp>=3);
    else if(mk[i]==1) pd(pos==1);
    else pd((pos==1)&&(tmp>=3));
  }
  printf("Yes\n");
  return 0;
}
