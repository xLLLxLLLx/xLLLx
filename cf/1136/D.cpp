#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5e5+10;
int p[N],mk[N];
vector<int>qx[N];

int main(){
    int n,m;scanf("%d%d",&n,&m);
    fr(i,1,n) scanf("%d",&p[i]);
    fr(i,1,m){
        int x,y;scanf("%d%d",&x,&y);
        qx[x].push_back(y);
    }
    int ans=0,now=1;
    mk[p[n]]=1;
    rf(i,n-1,1){
        int len=qx[p[i]].size();
        int pos=0;
        fr(j,0,len-1){
            if(mk[qx[p[i]][j]]) pos++;
        }
        if(pos==now) ans++;
        else {
            now++;
            mk[p[i]]=1;
        }
    }
    cout<<ans<<endl;
    return 0;
}
