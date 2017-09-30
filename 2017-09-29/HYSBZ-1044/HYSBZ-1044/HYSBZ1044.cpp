#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define MAXN 50010
#define MOD 10007
int n, k, a[MAXN], max;
bool check(int x) {
	if (x < max) return false;
	int s = 0, S = 0;
	for (int i = 1; i <= n; i++) {
		if (s + a[i] > x) {
			S++; s = 0;
			if (S > k) return false;
		}
		s += a[i];
	}
	return true;
}
int f[2][MAXN], s[MAXN], ans = 0;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)scanf("%d", &a[i]), s[i] = s[i - 1] + a[i], max = std::max(max, a[i]);
	int l = 0, r = 60000000;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid))r = mid - 1; else l = mid + 1;
	}
	printf("%d ", l = r + 1);
	for (int i = 1; i <= n; i++)f[0][i] = (s[i] <= l); ans = f[0][n];
	for (int i = 1; i <= k; i++) {
		int k = 1, sum = 0;
		for (int j = 1; j <= n; j++) {
			while ((k < j) && (s[j] - s[k] > l))sum = (sum - f[!(i & 1)][k] + MOD) % MOD, k++;
			f[i & 1][j] = sum;
			sum = (sum + f[!(i & 1)][j]) % MOD;
		}
		ans = (ans + f[i & 1][n]) % MOD;
	}
	printf("%d\n", ans);
	system("pause");
	return 0;
}