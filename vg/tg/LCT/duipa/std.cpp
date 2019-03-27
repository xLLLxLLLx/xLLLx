#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pi;

namespace LCT
{
struct Node
{
    Node *ch[2],*fa;
    bool rev;
    bool d;Node *dd;
    int id;
    void upd()
    {
        if(ch[0]&&ch[0]->dd)    dd=ch[0]->dd;
        else if(d)    dd=this;
        else dd=ch[1]?ch[1]->dd:0;
    }
    void pd()
    {
        if(rev)
        {
            swap(ch[0],ch[1]);
            if(ch[0])    ch[0]->rev^=1;
            if(ch[1])    ch[1]->rev^=1;
            rev=0;
        }
    }
}nodes[300100];
int mem;
Node *getnode()
{
    return nodes+(mem++);
}
bool isroot(Node *x)
{
    return (!x->fa)||((x->fa->ch[0]!=x)&&(x->fa->ch[1]!=x));
}
bool gson(Node *o)    {return o==o->fa->ch[1];}
void rotate(Node *o,bool d)
{
    Node *k=o->ch[!d];if(!isroot(o))    o->fa->ch[gson(o)]=k;
    o->ch[!d]=k->ch[d];k->ch[d]=o;
    o->upd();k->upd();
    k->fa=o->fa;o->fa=k;if(o->ch[!d])    o->ch[!d]->fa=o;
}
Node *st[300100];int top;
void solvetag(Node *o)
{
    while(!isroot(o))    st[++top]=o,o=o->fa;
    st[++top]=o;
    while(top)    st[top--]->pd();
}
void splay(Node *o)
{
    solvetag(o);
    Node *fa,*fafa;bool d1,d2;
    while(!isroot(o))
    {
        fa=o->fa;d1=(o==fa->ch[0]);
        if(isroot(fa))    rotate(fa,d1);
        else
        {
            fafa=o->fa->fa;d2=(fa==fafa->ch[0]);//要保证fa不是root之后才能获取这两个值，曾错过
            if(d1==d2)    rotate(fafa,d1),rotate(fa,d1);//zig-zig，两次相同方向的单旋，先把父亲转上去，再把自己转上去
            else    rotate(fa,d1),rotate(fafa,d2);//zig-zag，两次相反方向的单旋，连续两次把自己转上去
        }
    }
}
void access(Node *o)
{
    for(Node *lst=NULL;o;lst=o,o=o->fa)
    {
        splay(o);//此处不pushdown是由于splay中保证进行过了
        o->ch[1]=lst;o->upd();//注意upd
    }
}
Node *gtop(Node *o)
{
    access(o);splay(o);
    for(;o->ch[0];o=o->ch[0],o->pd());//此处不在开始前pushdown(o)是由于splay中保证进行过了
    splay(o);return o;//听说这里不splay一下也很难卡掉
}
void mtop(Node *o)    {access(o);splay(o);o->rev^=1;}
void link(Node *x,Node *y)
{
    if(gtop(x)==gtop(y))    return;
    mtop(y);y->fa=x;
}
void cut(Node *x,Node *y)
{
    mtop(x);access(y);splay(y);
    if(y->ch[0]!=x||x->ch[1])    return;//如果x、y之间直接有边，那么上面一行的操作之后应当是x与y在单独一棵splay中，那么一定保证y左子节点是x且x没有右子节点
    x->fa=y->ch[0]=NULL;//注意，改的是x的父亲和y的子节点(虽然x的确是树的根，但是此时在splay上是y的子节点，不能搞混)
    y->upd();//注意
}
void change(Node *y)
{
    access(y);splay(y);
    y->d^=1;y->upd();
}
int query(Node *x,Node *y)
{
    mtop(x);access(y);splay(y);
    return y->dd?y->dd->id:-1;
}
}
LCT::Node *nd[300100];
int n,q;
int main()
{
    int i,idx,x,a,b;
    scanf("%d%d",&n,&q);
    for(i=1;i<=n;i++)    nd[i]=LCT::getnode(),nd[i]->id=i;
    for(i=1;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        LCT::link(nd[a],nd[b]);
    }
    while(q--)
    {
        scanf("%d%d",&idx,&x);
        if(idx==0)    LCT::change(nd[x]);
        else    printf("%d\n",LCT::query(nd[1],nd[x]));
    }
    return 0;
}
