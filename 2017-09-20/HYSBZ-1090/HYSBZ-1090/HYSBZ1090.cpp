#include<cstdio>
#include<cstdlib>
#include<cstring>
#undef __max
#undef __min
#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define __min(a,b) (((a) < (b)) ? (a) : (b))
#define MAXN 200
#define BASE 233
#define MOD 100000007
int Hash[MAXN], po[MAXN], f[MAXN][MAXN], n, len[MAXN];
inline int hash(int i, int j) {
	return ((Hash[j] - (long long)Hash[i - 1] * po[j - i + 1] % MOD) + MOD) % MOD;
}
char s[MAXN];
int main() {
	po[0] = 1;
	for (int i = 1; i < MAXN; i++)po[i] = (long long)po[i - 1] * BASE % MOD;
	for (int i = 1; i < MAXN; i++)len[i] = len[i / 10] + 1;
	scanf("%s", s); n = strlen(s);
	for (int i = 1; i <= n; i++)Hash[i] = ((long long)Hash[i - 1] * BASE + s[i - 1]) % MOD;
	for (int i = 1; i <= n; i++)f[i][i] = 1;
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i + k <= n; i++) {
			f[i][i + k] = k + 1;
			for (int j = i; j < i + k; j++)f[i][i + k] = __min(f[i][i + k], f[i][j] + f[j + 1][i + k]);
			for (int j = 1; j <= n; j++) {
				if ((k + 1) % j)continue;
				if (hash(i, i + k - j) != hash(i + j, i + k))continue;
				f[i][i + k] = __min(f[i][i + k], f[i][i + j - 1] + len[(k + 1) / j] + 2);
			}
		}
	}
	printf("%d\n", f[1][n]);
	system("pause");
	return 0;
}