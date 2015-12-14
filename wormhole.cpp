/*
PROG:wormhole
LANG:C++
ID:gzgqllx1
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define maxn 17

int graph[maxn][maxn],N;

struct node
{
    int x,y;
}points[19];

bool visited[19];

bool cmp(node a, node b)
{
    if(a.y != b.y)
	return a.y<b.y;
    else
	return a.x<b.x;
}

int ans;

bool gaocheck[maxn][2];

bool dfs(int id, int type)
{

    if(gaocheck[id][type])
	return true;
    //printf("dfs %d %d\n", id, type);
    gaocheck[id][type]=true;
    for(int i=0;i<N;i++)
    {
	//printf("graph %d %d: %d\n",id, i, graph[id][i]);
	if(graph[id][i]!=0)
	    if(graph[id][i]&(1<<type))
	    {
		if(dfs(i, 1-type))
		    return true;
	    }
    }
    gaocheck[id][type]=false;
    return false;
}

bool check()
{
    memset(gaocheck, false, sizeof(gaocheck));
    for(int i=0;i<N;i++)
    {
	if(dfs(i, 0))
	    return true;
	if(dfs(i, 1))
	    return true;
    }
    return false;
}

void gao(int num)
{
    int i,pre;
    if(num==N)
    {
	if(check()){
	    //puts("OK");
	    ans++;
	}
	return;
    }
    for(i=0;i<N;i++)
	if(!visited[i])
	{
	    pre = i;
	    visited[i]=true;
	    break;
	}
    for(i=0;i<N;i++)
    {
	if(!visited[i])
	{
	    visited[i]=true;
	    graph[i][pre]=(graph[i][pre]|2);
	    graph[pre][i]=(graph[pre][i]|2);
	    /*
	    printf("graph_init %d %d: %d\n", pre, i, graph[pre][i]);
	    printf("graph_init %d %d: %d\n", i, pre, graph[i][pre]);
	    printf("%d %d\n",pre, i);
	    */
	    gao(num+2);
	    graph[i][pre]=(graph[i][pre]^2);
	    graph[pre][i]=(graph[pre][i]^2);
	    visited[i]=false;
	}
    }
    visited[pre]=false;
}

int main()
{
    int i;
    ans = 0;
    freopen("wormhole.in","r",stdin);
    freopen("wormhole.out","w",stdout);
    scanf("%d",&N);
    memset(visited,false,sizeof(visited));
    for(i=0;i<N;i++)
	scanf("%d%d",&points[i].x, &points[i].y);
    sort(points, points+N, cmp);
    for(i=1;i<N;i++)
	if(points[i].y == points[i-1].y)
            graph[i-1][i]=1;
    gao(0);
    printf("%d\n",ans);
    return 0;
}
