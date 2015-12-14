/*
PROG: buylow
LANG: C++
ID: gzgqllx1
*/
#include<cstdio>
#include<map>
#include<iostream>
#include<cstring>
#include<ctime>
using namespace std;
#define maxn 5100

int dp[maxn],num[maxn];
//map<int, int> dic;

int dic[100000];

struct BigNum
{
    int dig[100];
    int size;
    BigNum(int t = 0){
	memset(dig, 0, sizeof(dig));
	size=1;
	dig[0]=t;
    };
    void copy(BigNum b){
        int i;
	for(i=0;i<max(size, b.size);i++)
	    dig[i]=b.dig[i];
	size=b.size;
    }
    void print(){
	int i;
	for(i=size-1;i>=0;i--){
	    printf("%d",dig[i]);
	}
    };
    void println(){
	print();
	puts("");
    };
    void clean(){
	memset(dig, 0, sizeof(dig));
	size=1;
    };
}cnt[maxn];

void add(BigNum a, BigNum b, BigNum& c)
{
    int i,add=0;
    //c.clean();
    for(i=0;i<max(a.size,b.size);i++)
    {
        c.dig[i]=a.dig[i]+b.dig[i]+add;
	add=c.dig[i]/10;
	c.dig[i]=c.dig[i]%10;
    }
    //puts("one add");
    c.size=max(a.size,b.size);
    if(add)
	c.dig[c.size++]=add;
    //a.println();
    //b.println();
    //c.println();
}

int main()
{
    freopen("buylow.in","r",stdin);
    freopen("buylow.out","w",stdout);
    //double t1=clock(), t2;
    int N, i, ans, j;
    BigNum one(1), zero(0), ansn(0), tmp;
    scanf("%d",&N);
    memset(dp, 0, sizeof(dp));
    for(i=0;i<N;i++)
	scanf("%d",num+i);
    memset(dic, 0, sizeof(dic)); 
    for(i=N-1;i>=0;i--)
	if(!dic[num[i]])
	{
	    dp[i]=1;
	    cnt[i]=one;
	    dic[num[i]]=1;
	}
    ans=0;
    for(i=N-1;i>=0;i--)
    {
	if(!dp[i])
	    continue;
	memset(dic,0,sizeof(dic));
        for(j=i-1;j>=0;j--)
	{
	    if(num[j]>num[i]&&!dic[num[j]])
	    {
		dic[num[j]]=1;
		if(dp[j]<dp[i]+1)
		{
		    dp[j]=dp[i]+1;
		    cnt[j].copy(cnt[i]);
		}
		else if(dp[j]==dp[i]+1)
		{
                    add(cnt[j], cnt[i], cnt[j]);
		}
	    }
	}
	//printf("%d ", i);
	//cnt[i].println();
        //printf("%d %d %d %d\n", i, dp[i], cnt[i], num[i]);
	ans=max(dp[i], ans);
    }
    for(i=0;i<N;i++)
	if(dp[i]==ans)
	{
	    tmp = ansn;
	    add(tmp, cnt[i], ansn);
	}
    printf("%d ", ans);
    ansn.println();
    //puts("");
    //t2=clock();
    //printf("%lf\n",t2-t1);
    return 0;
}

