#include <iostream>
#include <cstdio>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <map>


#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define abs(x) ((x)>=0?(x):-(x))
#define i64 long long
#define u32 unsigned int
#define u64 unsigned long long
#define clr(x,y) memset(x,y,sizeof(x))
#define CLR(x) x.clear()
#define ph(x) push(x)
#define pb(x) push_back(x)
#define Len(x) x.length()
#define SZ(x) x.size()
#define PI acos(-1.0)
#define sqr(x) ((x)*(x))
#define MP(x,y) make_pair(x,y)

#define FOR0(i,x) for(i=0;i<x;i++)
#define FOR1(i,x) for(i=1;i<=x;i++)
#define FOR(i,a,b) for(i=a;i<=b;i++)
#define DOW0(i,x) for(i=x;i>=0;i--)
#define DOW1(i,x) for(i=x;i>=1;i--)
#define DOW(i,a,b) for(i=a;i>=b;i--)
using namespace std;


void RD(int &x){scanf("%d",&x);}
void RD(i64 &x){scanf("%I64d",&x);}
void RD(u32 &x){scanf("%u",&x);}
void RD(double &x){scanf("%lf",&x);}
void RD(int &x,int &y){scanf("%d%d",&x,&y);}
void RD(i64 &x,i64 &y){scanf("%I64d%I64d",&x,&y);}
void RD(u32 &x,u32 &y){scanf("%u%u",&x,&y);}
void RD(double &x,double &y){scanf("%lf%lf",&x,&y);}
void RD(int &x,int &y,int &z){scanf("%d%d%d",&x,&y,&z);}
void RD(i64 &x,i64 &y,i64 &z){scanf("%I64d%I64d%I64d",&x,&y,&z);}
void RD(u32 &x,u32 &y,u32 &z){scanf("%u%u%u",&x,&y,&z);}
void RD(double &x,double &y,double &z){scanf("%lf%lf%lf",&x,&y,&z);}
void RD(char &x){x=getchar();}
void RD(char *s){scanf("%s",s);}
void RD(string &s){cin>>s;}


void PR(int x) {printf("%d\n",x);}
void PR(i64 x) {printf("%I64d\n",x);}
void PR(u32 x) {printf("%u\n",x);}
void PR(u64 x) {printf("%llu\n",x);}
void PR(double x) {printf("%.4lf\n",x);}
void PR(char x) {printf("%c\n",x);}
void PR(char *x) {printf("%s\n",x);}
void PR(string x) {cout<<x<<endl;}


const int p[9][9]=
{
    1,1,1,1,1,1,1,0,0,
    1,0,0,0,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,
    1,1,1,0,0,0,0,0,0,
    1,1,1,0,0,0,0,0,0,
    1,1,1,0,0,0,0,0,0,
    1,1,1,1,1,1,1,0,0,
    1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1
};

string s;
char str[205];
map<string,string> Map;

string init(string s)
{
    string ans="";
    int i;
    for(i=0;i<s.length();i++)
    {
        if(isupper(s[i])) ans+=s[i]-'A'+'a';
        else if(s[i]!=' ') ans+=s[i];
    }
    return ans;
}

string findParent(string s)
{
    if(Map.find(s)==Map.end()) return s;
    Map[s]=findParent(Map[s]);
    return Map[s];
}

void dealDefine(string s)
{
    int i=0;
    string s1="",s2="";
    while(s[i]==' ') i++;
    while(s[i]!=' ') s1+=s[i++];
    while(s[i]==' ') i++;
    while(i<s.length()&&s[i]!=' ') s2+=s[i++];
    s1=init(s1);
    s2=init(s2);
    if(Map.find(s1)!=Map.end()||s1==s2) return;
    if(findParent(s2)!=s1)
    {
        Map[s1]=s2;
    }
}


int isLetter(char x)
{
    return x>='a'&&x<='z';
}

string preDeal(string s)
{
    string ans="";
    int i,j,flag=1;
    for(i=0;i<s.length();i++)
    {
        if(isdigit(s[i])) ans+=s[i],flag=0;
        else if(isLetter(s[i])) ans+=s[i],flag=0;
        else if(s[i]=='(') ans+=s[i],flag=1;
        else if(s[i]==')') ans+=s[i],flag=0;
        else if(s[i]=='%'||s[i]=='*'||s[i]=='/'||s[i]=='^') ans+=s[i],flag=1;
        else if(s[i]=='+')
        {
            if(!flag) ans+=s[i],flag=1;
            else ans+='$';
        }
        else if(s[i]=='-')
        {
            if(!flag) ans+=s[i],flag=1;
            else ans+='#';
        }
    }
    return ans;
}

int get(char c)
{
    if(c=='(') return  0;
    else if(c=='+') return 1;
    else if(c=='-') return 2;
    else if(c=='*') return 3;
    else if(c=='/') return 4;
    else if(c=='%') return 5;
    else if(c=='^') return 6;
    else if(c=='$') return 7;
    else if(c=='#') return 8;
    else if(c==')') return 9;
    else return 10;
}

stack<int> st1,st2;

int sgn(int x)
{
    if(x<0) return -1;
    if(x>0) return 1;
    return 0;
}

int power(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1) ans=ans*a;
        a=a*a;
        b>>=1;
    }
    return ans;
}

int pop()
{
    int x,y,op=st1.top();
    st1.pop();
    if(op==8)
    {
        x=st2.top(); st2.pop();
        st2.push(-x);
    }
    else if(op>=1&&op<=6)
    {
        y=st2.top(); st2.pop();
        x=st2.top(); st2.pop();
        if(op==1) x+=y;
        else if(op==2) x-=y;
        else if(op==3) x*=y;
        else if(op==4) x=sgn(x)*sgn(y)*abs(x)/abs(y);
        else if(op==5) x=sgn(x)*sgn(y)*(abs(x)%abs(y));
        else if(op==6) x=power(x,y);
        st2.push(x);
    }
}


int cal(string s,int pos,string &s1)
{
    int i;
    s1="";
    for(i=pos;i<s.length()&&(isdigit(s[i])||isLetter(s[i]));i++)
    {
        s1+=s[i];
    }
    return i;
}


string replace(string s)
{
    if(Map.find(s)!=Map.end()) return findParent(s);
    return s;
}

int stringToint(string s)
{
    int ans=0,i;
    for(i=0;i<s.length();i++)
    {
        if(isdigit(s[i])) ans=ans*10+s[i]-'0';
        else return 0;
    }
    return ans;
}

void dealPrint(string s)
{
    s=preDeal(s);
    string s1,s2;
    int i,j,k;
    for(i=0;i<s.length();i++)
    {
        k=get(s[i]);
        if(k==0||k==7||k==8) st1.push(k);
        else if(k<=6)
        {
            while(!st1.empty()&&!p[k][st1.top()])
            {
                pop();
            }
            st1.push(k);
        }
        else if(k==9)
        {
            while(st1.top()!=0)
            {
                pop();
            }
            st1.pop();
        }
        else
        {
            j=cal(s,i,s1);
            i=j-1;
            s1=replace(s1);
            st2.push(stringToint(s1));
        }
    }
    while(!st1.empty())
    {
        pop();
    }
    PR(st2.top());
}

int main()
{
    while(gets(str))
    {
        s=str;
        while(!st1.empty()) st1.pop();
        while(!st2.empty()) st2.pop();
        if(s[0]=='p'||s[0]=='P')
        {
            s=s.substr(5,s.length()-5);
            s=init(s);
            dealPrint(s);
        }
        else
        {
            s=s.substr(6,s.length()-6);
            dealDefine(s);
        }
    }
    return 0;
}