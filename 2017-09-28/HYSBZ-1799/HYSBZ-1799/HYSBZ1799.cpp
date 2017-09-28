#include<cstdio>
#include<cstdlib>
#include<cstring>
long long a, b, f[21][165][165][2], stk[25], top, ans = 0;
inline long long calc(long long x, int mod) {
	if (!x)return 0; memset(f, 0, sizeof(f)); top = 0;
	while (x) {
		stk[++top] = x % 10; x /= 10;
	}
	f[top + 1][0][0][1] = 1;
	for (int i = top + 1; i > 1; i--) {
		for (int j = 0; j <= mod; j++) {
			for (int k = 0; k < mod; k++) {
				if (!f[i][j][k][0] && !f[i][j][k][1])continue;
				for (int p = 0; p < 10; p++) {
					if (j + p > mod)break;
					if (p < stk[i - 1])f[i - 1][j + p][(10 * k + p) % mod][0] += f[i][j][k][1];
					else if (p == stk[i - 1])f[i - 1][j + p][(10 * k + p) % mod][1] += f[i][j][k][1];
					f[i - 1][j + p][(10 * k + p) % mod][0] += f[i][j][k][0];
				}
			}
		}
	}
	return f[1][mod][0][0] + f[1][mod][0][1];
}
int main() {
	scanf("%lld%lld", &a, &b);
	for (int i = 1; i <= 9 * 18; i++)ans += calc(b, i) - calc(a - 1, i);
	printf("%lld\n", ans);
	system("pause");
	return 0;
}