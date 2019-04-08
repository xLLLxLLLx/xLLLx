#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
const int N = 100010;
ll h[N],R[N],L[N],sta[N];
 
int main(){
        int n;scanf("%d",&n);
        for (int i = 1; i <= n; ++i){
            scanf("%lld", &h[i]);h[i]++;
        }
        int top=0,cur;
        for(int i=1;i<=n+1;++i){
            while(1){
                cur=sta[top];
                if(h[cur]<=h[i]) break;
                R[cur]=i;
                top--;
            }
            cur=sta[top];
            L[i]=cur;
            sta[++top]=i;
        }
        ll ans = n/2*1LL*(n+1)*1LL*(n-1);
        for(int i=1;i<=n;++i){
            int len=R[i]-L[i]-1;
            ans-=(h[i]-1)*(len*(len+1));
        }
        printf("%lld\n", ans);
        return 0;
}