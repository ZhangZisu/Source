#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MOD 1000003
int t, n, k, f[60][32768], st[60][26], len, ans, temp;
char s[15][60];
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &k);
		for (int i = 0; i < n; i++) scanf("%s", s[i]); len = strlen(s[0]);
		memset(st, 0, sizeof(st)); memset(f, 0, sizeof(f));
		for (int i = 1; i <= len; i++) {
			for (char c = 'a'; c <= 'z'; c++) {
				for (int j = 0; j < n; j++)
					st[i][c - 'a'] |= (s[j][i - 1] == c || s[j][i - 1] == '?') << j;
			}
		}
		f[0][(1 << n) - 1] = 1;
		for (int i = 1; i <= len; i++) {
			for (int j = 0; j < (1 << n); j++) {
				if (!f[i - 1][j])continue;
				for (int c = 0; c < 26; c++) {
					f[i][j & st[i][c]] = (f[i][j & st[i][c]] + f[i - 1][j]) % MOD;
				}
			}
		}
		ans = 0;
		for (int i = 0; i < (1 << n); i++) {
			temp = 0; for (int j = i; j; j >>= 1)if (j & 1)temp++;
			if (temp == k)ans = (ans + f[len][i]) % MOD;
		}
		printf("%d\n", ans);
	}
	system("pause");
	return 0;
}