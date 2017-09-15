/*Backup*/
/*
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 30010
#define BASE 233
#define MOD 10000007
char s[MAXN];
int t, len, po[MAXN], Hash[MAXN], u[MAXN], v[MAXN];
long long ans;
inline int hash(int x, int y) { return ((Hash[y] - (long long)Hash[x] * po[y - x] % MOD) + MOD) % MOD; }
int main() {
	po[0] = 1;
	for (int i = 1; i < MAXN; i++)po[i] = (long long)po[i - 1] * BASE % MOD;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", s + 1); len = strlen(s + 1); memset(u, 0, sizeof(u)); memset(v, 0, sizeof(v)); ans = 0;
		for (int i = 1; i <= len; i++)Hash[i] = ((long long)Hash[i - 1] * BASE + s[i] - 'a') % MOD;
		for (int i = 1; (i << 1) <= len; i++) {
			for (int j = 1; j + i <= len; j += i) {
				int l = 0, r = std::min(i, j);
				while (l != r) {
					if (hash(i + j - ((l + r + 1) >> 1), i + j) == hash(j - ((l + r + 1) >> 1), j))l = (l + r + 1) >> 1;
					else r = ((l + r + 1) >> 1) - 1;
				}
				int L = j - l + 1;
				l = 0; r = std::min(i - 1, len - i - j);
				while (l != r) {
					if (hash(i + j, i + j + ((l + r + 1) >> 1)) == hash(j, j + ((l + r + 1) >> 1)))l = (l + r + 1) >> 1;
					else r = ((l + r + 1) >> 1) - 1;
				}
				int R = j + l + 1;
				if (L + i <= R) {
					u[L]++; v[R + i]--;
					u[R - i + 1]--; v[L + (i << 1) - 1]++;
				}
			}
		}
		for (int i = 1; i <= len; i++) { u[i] += u[i - 1]; v[i] += v[i - 1]; ans += (long long)u[i] * v[i - 1]; }
		printf("%lld\n", ans);
	}
	system("pause");
	return 0;
}
*/