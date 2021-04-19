
#include<iostream>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<set>
#include<map>
#include<vector>
#include<cstring>
#include<stack>
#include<cmath>
#include<queue>
using namespace std;
#define CL(x,v); memset(x,v,sizeof(x));
#define INF 0x3fffffff
#define LL long long
#define REP(i,r,n) for(int i=r;i<=n;i++)
#define RREP(i,n,r) for(int i=n;i>=r;i--)
#define L ch[x][0]
#define R ch[x][1]
#define KT (ch[ ch[rt][1] ][0])
const int MAXN = 2e5+100;
int num[MAXN];
struct SplayTree {
    int sz[MAXN];
    int ch[MAXN][2];
    int pre[MAXN];
    int rt,top;
    inline void down(int x){
        if(flip[x]) {
            flip[ L ] ^= 1;
            flip[ R ] ^= 1;
            swap(L,R);
            flip[x]=0;
        }
        if(add[x])
        {
            if(L)
            {
                add[L]+=add[x];
                mi[L]+=add[x];
                val[L]+=add[x];
            }
            if(R)
            {
                add[R]+=add[x];
                mi[R]+=add[x];
                val[R]+=add[x];
            }
            add[x]=0;
        }
    }
    inline void up(int x){
        sz[x]=1+sz[ L ] + sz[ R ];
        mi[x]=min(val[x],min(mi[L],mi[R]));
    }
    inline void Rotate(int x,int f){
        int y=pre[x];
        down(y);
        down(x);
        ch[y][!f] = ch[x][f];
        pre[ ch[x][f] ] = y;
        pre[x] = pre[y];
        if(pre[x]) ch[ pre[y] ][ ch[pre[y]][1] == y ] =x;
        ch[x][f] = y;
        pre[y] = x;
        up(y);
    }
    inline void Splay(int x,int goal){//将x旋转到goal的下面
        down(x);////防止pre[x]就是目标点，下面的循环就进不去了，x的信息就传不下去了
        while(pre[x] != goal){
            down(pre[pre[x]]); down(pre[x]);down(x);//在旋转之前需要先下传标记，因为节点的位置可能会发生改变
            if(pre[pre[x]] == goal) Rotate(x , ch[pre[x]][0] == x);
            else   {
                int y=pre[x],z=pre[y];
                int f = (ch[z][0]==y);
                if(ch[y][f] == x) Rotate(x,!f),Rotate(x,f);
                else Rotate(y,f),Rotate(x,f);
            }
        }
        up(x);
        if(goal==0) rt=x;
    }
    inline void RTO(int k,int goal){//将第k位数旋转到goal的下面
        int x=rt;
        down(x);
        while(sz[ L ]+1 != k) {
            if(k < sz[ L ] + 1 ) x=L;
            else {
                k-=(sz[ L ]+1);
                x = R;
            }
            down(x);
        }
        Splay(x,goal);
    }
    void vist(int x){
        if(x){
            printf("结点%2d : 左儿子  %2d   右儿子  %2d   %2d  flip:%d\n",x,L,R,val[x],flip[x]);
            printf("结点%2d mi=%2d\n",x,mi[x]);
            vist(L);
            vist(R);
        }
    }
    void Newnode(int &x,int c,int f){
        x=++top;flip[x]=0;
        L = R = 0;  pre[x] = f;
        sz[x]=1; val[x]=c;
        mi[x]=c; add[x]=0;
    }
    inline void build(int &x,int l,int r,int f){
        if(l>r) return ;
        int m=(l+r)>>1;
        Newnode(x,num[m],f);
        build(L , l , m-1 , x);
        build(R , m+1 , r , x);
        pre[x]=f;
        up(x);
    }

    //终于明白初始化结点0的用处了。就是所有的叶子结点，是终止结点
    inline void init(int n){
        ch[0][0]=ch[0][1]=pre[0]=sz[0]=0;
        rt=top=0; flip[0]=0; val[0]=0;
        add[0]=0;mi[0]=INF;
        Newnode(rt,INF,0);
        Newnode(ch[rt][1],INF,rt);
        sz[rt]=2;
        build(KT,1,n,ch[rt][1]);
        up(ch[rt][1]);up(rt);
    }
    void Del(){
         int t=rt;
         if(ch[rt][1]) {
             rt=ch[rt][1];
             RTO(1,0);
             ch[rt][0]=ch[t][0];
             if(ch[rt][0]) pre[ch[rt][0]]=rt;
         }
         else rt=ch[rt][0];
         pre[rt]=0;
         up(rt);
    }
    void ADD(int a,int b,int d)
    {
        if(a>b)swap(a,b);
       RTO(a,0);
       RTO(b+2,rt);
       add[KT]+=d;
       val[KT]+=d;
       mi[KT]+=d;
    }
    void REVERSE(int a,int b)
    {
        if(a>b)swap(a,b);
        RTO(a,0);
        RTO(b+2,rt);
        flip[KT]^=1;
    }
    //t有可能为负
    void REVOLVE(int x,int y,int t)
    {
        if(x>y)swap(x,y);
        t=t%(y-x+1);
        t=(t+y-x+1)%(y-x+1);
        if(t==0)return;
        int l=y-t+1;
        int r=y+2;
        RTO(l,0);
        RTO(r,rt);
        int tmp=KT;
        KT=0;
        up(ch[rt][1]);up(rt);

        RTO(x,0);
        RTO(x+1,rt);
        KT=tmp;pre[tmp]=ch[rt][1];
        up(ch[rt][1]);up(rt);
    }
    void INSERT(int x,int p)
    {
        RTO(x+1,0);
        RTO(x+2,rt);
        Newnode(KT,p,ch[rt][1]);
        up(ch[rt][1]);up(rt);
    }
    void DELETE(int x)
    {
        RTO(x,0);
        RTO(x+2,rt);
        KT=0;
        up(ch[rt][1]);up(rt);
    }
    int  MIN(int x,int y)
    {
        if(x>y)swap(x,y);
        RTO(x,0);
        RTO(y+2,rt);
        return mi[KT];
    }
    int flip[MAXN];
    int val[MAXN];
    int mi[MAXN];
    int add[MAXN];
}spt;

int main()
{
    int n,m;
    while(~scanf("%d",&n))
    {
        REP(i,1,n)
            scanf("%d",&num[i]);
        scanf("%d",&m);
        spt.init(n);
        char op[10];
        int a,b,c;
        REP(i,1,m)
        {
            scanf("%s",op);
            if(op[0]=='A')
            {
                scanf("%d%d%d",&a,&b,&c);
                spt.ADD(a,b,c);
            }
            else if(op[0]=='I')
            {
                scanf("%d%d",&a,&b);
                spt.INSERT(a,b);
            }
            else if(op[0]=='D')
            {
                scanf("%d",&a);
                spt.DELETE(a);
            }
            else if(op[0]=='M')
            {
                scanf("%d%d",&a,&b);
                int ans=spt.MIN(a,b);
                printf("%d\n",ans);
            }
            else if(strcmp(op,"REVERSE")==0)
            {
                scanf("%d%d",&a,&b);
                spt.REVERSE(a,b);
            }
            else if(strcmp(op,"REVOLVE")==0)
            {
                scanf("%d%d%d",&a,&b,&c);
                spt.REVOLVE(a,b,c);
            }
        }
    }
    return 0;
}