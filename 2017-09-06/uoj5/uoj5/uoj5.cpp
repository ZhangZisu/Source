#include<cstdio>
#include<cstring>
#include<cstdlib>
#define MOD 1000000007
int n;
char buf[1000010];
long long next[1000010], num[1000010], ans;
int pos1, pos2;
int main()
{
	scanf("%d", &n);
	while (n--) {
		scanf("%s", buf);
		memset(next, 0, sizeof(next));
		memset(num, 0, sizeof(num));
		pos1 = pos2 = -1; ans = 1; num[0] = 1; next[0] = -1;
		for (int i = 1; buf[i]; i++) {
			while (~pos1 && buf[i] != buf[pos1 + 1])pos1 = next[pos1];
			if (buf[i] == buf[pos1 + 1])pos1++;
			next[i] = pos1;
			num[i] = num[pos1] + 1;
			while (~pos2 && buf[i] != buf[pos2 + 1])pos2 = next[pos2];
			if (buf[i] == buf[pos2 + 1])pos2++;
			int h = (i + 1) >> 1;
			while (pos2 + 1 > h)pos2 = next[pos2];
			ans *= num[pos2] + 1;
			ans %= MOD;
		}
		printf("%lld\n", ans);
	}
	//system("pause");
	return 0;
}

