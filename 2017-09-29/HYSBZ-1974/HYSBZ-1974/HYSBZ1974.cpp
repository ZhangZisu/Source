#include<cstdio>
#include<cstdlib>
#define MOD 999911659
#define MAXN 510
long long n;
int p, val, digit[MAXN], pos[MAXN], s[MAXN], f[10][MAXN], ans;
const int inv[10] = { 0,1,499955830,666607773,249977915,199982332,833259716,571378091,624944787,222202591 };
int main() {
	scanf("%lld%d", &n, &p);
	pos[digit[1] = 1 % p] = 1;
	for (int i = 2; i <= p + 1; i++) {
		digit[i] = ((long long)digit[i - 1] * 10 + 1) % p;
		if (pos[digit[i]]) {
			int B = pos[digit[i]], E = i, L = E - B;
			for (int j = 1; j < B && j <= n; j++)s[j]++;
			for (int j = 0; j < L && B + j <= n; j++)s[digit[B + j]] = (s[digit[B + j]] + (n - B - j) / L + 1) % MOD;
			val = n < B ? digit[n] : digit[B + (n - B) % L]; s[val] = ((long long)s[val] - 1 + MOD) % MOD;
			break;
		}
		pos[digit[i]] = i;
	}
	f[0][0] = 1;
	for (int i = 0; i < p; i++) {
		if (!s[i])continue;
		for (int j = 9; j >= 0; j--) {
			int C = 1;
			for (int k = 1; k <= j && C; k++) {
				C = (long long)C * (s[i] + k - 1) % MOD * inv[k] % MOD;
				for (int l = 0; l < p; l++)
					f[j][(l + k * i) % p] = (f[j][(l + k * i) % p] + (long long)C * f[j - k][l]) % MOD;
			}
		}
	}
	for (int i = 1; i < 10; i++) {
		int res = (p - i * val % p) % p;
		for (int j = 0; i + j < 10; j++)ans = (ans + f[j][res]) % MOD;
	}
	printf("%d\n", ans);
	system("pause");
	return 0;
}