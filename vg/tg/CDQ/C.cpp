#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=4e6+10,M=8e4+10,WF=3e4+10;
struct data{
    int tp,x,y,v,rk,flg;
}q[N],b[N];
int ans[M],tr[N];
int n,m;

int lowerbit(int x){ return x&(-x); }

void Upd(int x,int y){
    for(;x<N;x+=lowerbit(x)) tr[x]+=y;
}

int Get(int x){
    int ans=0;
    for(;x;x-=lowerbit(x)) ans+=tr[x];
    return ans;
}

void cdq(int l,int r){
    if(l==r) return ;
    int mid=(l+r)>>1;
    cdq(l,mid),cdq(mid+1,r);
    int pos=l-1,nw=l;
    //printf("l=%d r=%d\n",l,r);
    fr(i,mid+1,r){
        while(pos+1<=mid&&q[pos+1].x<=q[i].x){
            pos++;b[nw++]=q[pos];
            if(q[pos].tp==1) {
      //          cout<<q[pos].y<<" zz"<<q[pos].v<<endl;
                Upd(q[pos].y,q[pos].v);
            }
        }
        if(q[i].tp==2) {
            ans[q[i].rk]+=q[i].flg*Get(q[i].y);
      //      cout<<q[i].rk<<" ??"<<ans[q[i].rk]<<endl;
        }
        b[nw++]=q[i];
    }
    fr(i,pos+1,mid) b[nw++]=q[i];
    fr(i,l,pos) if(q[i].tp==1) Upd(q[i].y,-q[i].v);
    fr(i,l,r) {
        q[i]=b[i];
       // printf("tp=%d x=%d y=%d v=%d flg=%d rk=%d\n",q[i].tp,q[i].x,q[i].y,q[i].v,q[i].flg,q[i].rk);
    }
}

int main(){
    while(scanf("%d",&n)==1&&n){
        scanf("%d",&m);
        int cnt=0,tot=0;
        fr(i,1,m){
            int tp,x,y,v;
            scanf("%d%d%d%d",&tp,&x,&y,&v);
            if(tp==1) q[++tot].tp=tp,q[tot].x=x+y+WF,q[tot].y=x-y+WF,q[tot].v=v;
            else {
                int nx=x+y+WF,ny=x-y+WF;++cnt;
                q[++tot].tp=tp,q[tot].x=nx-v-1,q[tot].y=ny+v,q[tot].rk=cnt,q[tot].flg=-1;
                q[++tot].tp=tp,q[tot].x=nx+v,q[tot].y=ny-v-1,q[tot].rk=cnt,q[tot].flg=-1;
                q[++tot].tp=tp,q[tot].x=nx+v,q[tot].y=ny+v,q[tot].rk=cnt,q[tot].flg=1;
                q[++tot].tp=tp,q[tot].x=nx-v-1,q[tot].y=ny-v-1,q[tot].rk=cnt,q[tot].flg=1;
            }
        }
       /* fr(i,1,tot){
            printf("tp=%d x=%d y=%d v=%d flg=%d rk=%d\n",q[i].tp,q[i].x,q[i].y,q[i].v,q[i].flg,q[i].rk);
        }*/
        cdq(1,tot);
        //TAT
        fr(i,1,cnt) printf("%d\n",ans[i]);
        fr(i,1,cnt) ans[i]=0;
      //  puts("WTF!\n");
    }
    return 0;
}
