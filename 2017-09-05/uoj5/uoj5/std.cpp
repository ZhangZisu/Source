#include <cstdio>
#define N 1001000
char s[N];
long long pre[N],num[N],ans;
int i,fix1,fix2,n;
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",s+1);
		ans=num[1]=1;
		for(fix1=fix2=0,i=2;s[i];i++)
		{
			while(fix1&&s[i]!=s[fix1+1])fix1=pre[fix1];
			if(s[i]==s[fix1+1])fix1++;
			pre[i]=fix1;
            
			num[i]=num[fix1]+1;
			while(fix2&&s[i]!=s[fix2+1])fix2=pre[fix2];
			if(s[i]==s[fix2+1])fix2++;
			while(fix2>i>>1)fix2=pre[fix2];
			ans*=num[fix2]+1;
			ans%=1000000007;
		}
		printf("%lld\n",ans);
	}
	return 0;
}


