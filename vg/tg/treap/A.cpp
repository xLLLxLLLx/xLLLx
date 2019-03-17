#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls q[x].ch[0]
#define rs q[x].ch[1]
#define LL long long
using namespace std;
const int N=1e5+10;
const LL inf=3e9;
struct data{
    int ch[2],rd,sz,cnt;
    LL val;
}q[N];
int cnt=0;

void up(int x){
    q[x].sz=q[ls].sz+q[rs].sz+q[x].cnt;
}

void rotate(int &x,int d){
    int son=q[x].ch[d];
    q[x].ch[d]=q[son].ch[d^1];
    q[son].ch[d^1]=x;
   // printf("x%d son%d\n",x,son);
    up(x),up(x=son);
}

void insert(int &x,LL val){
    if(!x){
        x=++cnt;
        q[x].val=val,q[x].sz=q[x].cnt=1;
        q[x].rd=rand()%inf;
        return ;
    }
    q[x].sz++;
    if(q[x].val==val){ q[x].cnt++;return ; }
    int d=q[x].val<val;
    insert(q[x].ch[d],val);
    if(q[q[x].ch[d]].rd<q[x].rd) rotate(x,d);
}

void del(int &x,LL val){
    if(!x) return ;
    if(q[x].val==val){
        if(q[x].cnt>=2) q[x].cnt--,q[x].sz--;
        else {
            if(ls==0||rs==0) x=ls+rs;
            else {
                int d=q[ls].rd>q[rs].rd;
                rotate(x,d),del(x,val);
            }
        }
    }
    else q[x].sz--,del(q[x].ch[val>q[x].val],val);
}

LL qq(int x,LL val){
    if(!x) return -inf;
    if(q[x].val>=val) return qq(ls,val);
    return max(q[x].val,qq(rs,val));
}

LL hj(int x,LL val){
   // printf("%d %lld\n",x,val);
    if(!x) return inf;
    if(q[x].val<=val) return hj(rs,val);
    return min(hj(ls,val),q[x].val);
}

int rk(int x,LL val){
    if(!x) return 0;
    if(q[x].val==val) return q[ls].sz+1;
    if(q[x].val>val) return rk(ls,val);
    if(q[x].val<val) return q[ls].sz+q[x].cnt+rk(rs,val);
}

LL kth(int x,int k){
    int nm=q[ls].sz+q[x].cnt;
    if(k>q[ls].sz&&k<=nm) return q[x].val;
    if(nm>k) return kth(ls,k);
    else return kth(rs,k-nm);
}

int main(){
    int n;scanf("%d",&n);
    int rt=0;
    fr(i,1,n){
        int tp;LL z;
        scanf("%d%lld",&tp,&z);
        //printf("rt=%d\n",rt);
        if(tp==1) insert(rt,z);
        if(tp==2) del(rt,z);
        if(tp==3) printf("%d\n",rk(rt,z));
        if(tp==4) printf("%lld\n",kth(rt,z));
        if(tp==5) printf("%lld\n",qq(rt,z));
        if(tp==6) printf("%lld\n",hj(rt,z));
    }
    return 0;
}
