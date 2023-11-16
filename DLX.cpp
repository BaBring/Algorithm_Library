#include<stdio.h>
int n,m,x;

struct DLXnode
{
    int Row,Col;
    int Left,Right,Up,Down;
};
int cnt=0;
DLXnode node[6000];//DLX中的所有元素，包括head元素和列元素
int row[510];//每行第一个元素
int ans[510];//记录答案
int lcnt[510];//每列元素个数(提速)


void init()//初始化
{
    for(int i=0;i<=m;i++)
    {
        node[i].Left=i-1;
        node[i].Right=i+1;
        node[i].Up=i;
        node[i].Down=i;
        lcnt[i]=0;
    }
    node[0].Left=m;
    node[m].Right=0;
    cnt=m;
}


void addnode(int r,int c)//添加点
{
    node[++cnt].Row=r;
    node[cnt].Col=c;
    //修改该结点所在列链
    node[cnt].Up=node[c].Up;
    node[cnt].Down=c;
    node[node[cnt].Up].Down=cnt;
    node[c].Up=cnt;
    //修改该结点所在行链
    if(!row[r])//该结点是其所在行的第一个元素
    {
        node[cnt].Left=cnt;
        node[cnt].Right=cnt;
        row[r]=cnt;
    }
    else//该结点不是其所在行的第一个元素
    {
        node[cnt].Left=node[row[r]].Left;
        node[cnt].Right=row[r];
        node[node[cnt].Left].Right=cnt;
        node[node[cnt].Right].Left=cnt;
    }
    lcnt[c]++;//对应列元素个数++
}


void remove(int c)//移除对应的列及列上有 1 的行
{
    for(int i=node[c].Down;i!=c;i=node[i].Down)//枚举列链中元素
        for(int j=node[i].Right;j!=i;j=node[j].Right)//枚举列链中元素所对应行链中元素并删除
        {
            node[node[j].Down].Up=node[j].Up;
            node[node[j].Up].Down=node[j].Down;
            lcnt[node[j].Col]--;
        }
   	//删除列链（仅需删除列元素即可删除整个列链）
    node[node[c].Left].Right=node[c].Right;
    node[node[c].Right].Left=node[c].Left;
}


void resume(int c)//回溯恢复被【remove】的元素 
{
    //恢复列链（仅需恢复列元素即可恢复整个列链）
    node[node[c].Left].Right=c;
    node[node[c].Right].Left=c;
    for(int i=node[c].Down;i!=c;i=node[i].Down)//枚举列链中元素
        for(int j=node[i].Right;j!=i;j=node[j].Right)//枚举列链中元素所对应行链中元素并恢复
        {
            node[node[j].Down].Up=j;
            node[node[j].Up].Down=j;
            lcnt[node[j].Col]++;
        }
}


bool dance(int dep)//开蹈！【dep表示答案的个数（搜索的层数）】
{
    if(node[0].Right==0)//如果head.right==head，说明有解，输出答案
    {
        for(int i=1;i<dep-1;i++)
            printf("%d ",ans[i]);
        printf("%d\n",ans[dep-1]);
        return true;
    }
    int C=node[0].Right;//取列元素 c=head.right 。
    for(int i=node[0].Right;i;i=node[i].Right)//(提速)
    {
        if(lcnt[i]<lcnt[C])
            C=i;
    }
    remove(C);//删除列链(提速)
    for(int i=node[C].Down;i!=C;i=node[i].Down)//枚举选择行
    {
        ans[dep]=node[i].Row;
        for(int j=node[i].Right;j!=i;j=node[j].Right)//删除选择行链元素所在列链
            remove(node[j].Col);
        if(dance(dep+1))return true;
        for(int j=node[i].Right;j!=i;j=node[j].Right)//恢复选择行链元素所在列链
            resume(node[j].Col);
    }
    resume(C);//恢复列链(提速)
    return false;
}


int main()
{
    scanf("%d%d",&n,&m);
    init();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&x);
            if(x==1)addnode(i,j);
        }
    if(!dance(1)) printf("No Solution!\n");
    return 0;
}