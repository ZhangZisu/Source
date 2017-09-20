#include<cstdio>
#include<cstring>
#include<cstdlib>
#define BASE 233
#define MOD 999999937
#define MAXN 200000
int po[MAXN], A[MAXN], B[MAXN], __, len;
char s[MAXN], t[MAXN], dic[50], temp[50];
int a(int i, int j) { return ((A[j] - (long long)A[i - 1] * po[j - i + 1] % MOD) + MOD) % MOD; }
int b(int i, int j) { return ((B[j] - (long long)B[i - 1] * po[j - i + 1] % MOD) + MOD) % MOD; }
int main() {
	scanf("%d", &__); po[0] = 1;
	for (int i = 1; i < MAXN; i++)po[i] = (long long)po[i - 1] * BASE % MOD;
	while (__--) {
		memset(A, 0, sizeof(A)); memset(B, 0, sizeof(B));
		memset(s, 0, sizeof(s)); memset(t, 0, sizeof(t));
		scanf("%s%s", temp, s + 1); len = strlen(s + 1);
		for (int i = 0; i < 26; i++)dic[temp[i] - 'a'] = i + 'a';
		for (int i = 1; i <= len; i++)A[i] = ((long long)A[i - 1] * BASE + s[i] - 'a') % MOD;
		for (int i = 1; i <= len; i++)t[i] = dic[s[i] - 'a'];
		for (int i = 1; i <= len; i++)B[i] = ((long long)B[i - 1] * BASE + t[i] - 'a') % MOD;
		int max = len >> 1;
		for (int i = max; i; i--) {
			int pos = len - i + 1;
			if (b(1, i) == a(pos, pos + i - 1)) {
				for (int i = 1; i < pos; i++)putchar(s[i]);
				for (int i = 1; i < pos; i++)putchar(t[i]);
				putchar(10); goto succ;
			}
		}
		printf("%s%s\n", s + 1, t + 1);
	succ:;
	}
	system("pause");
	return 0;
}