#include<cstdio>
#include<cstdlib>
#include<set>
using std::set;
#define MAXN 200010
#define MOD 1061109559
#define BASE 2333
int po[MAXN], A[MAXN], B[MAXN], col[MAXN], n, ans, max, tot[MAXN], cur = 0;
inline int a(int x, int y) { return ((A[y] - (long long)A[x - 1] * po[y - x + 1] % MOD) + MOD) % MOD; }
inline int b(int x, int y) { return ((B[x] - (long long)B[y + 1] * po[y - x + 1] % MOD) + MOD) % MOD; }
set<int> s;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)scanf("%d", &col[i]);
	po[0] = 1;
	for (int i = 1; i <= n; i++)po[i] = (long long)po[i - 1] * BASE % MOD;
	for (int i = 1; i <= n; i++)A[i] = ((long long)A[i - 1] * BASE + col[i]) % MOD;
	for (int i = n; i >= 1; i--)B[i] = ((long long)B[i + 1] * BASE + col[i]) % MOD;
	for (int i = 1; i <= n; i++) {
		s.clear(); ans = 0;
		for (int j = 1; j + i - 1 <= n; j += i) {
			int _a = a(j, j + i - 1);
			int _b = b(j, j + i - 1);
			if (!s.count(_a) || !s.count(_b)) {
				ans++; s.insert(_a); s.insert(_b);
			}
		}
		if (ans == max) {
			tot[cur++] = i;
		}
		if (ans > max) {
			tot[cur = 0] = i;
			max = ans; cur++;
		}
	}
	printf("%d %d\n", max, cur);
	for (int i = 0; i < cur; i++)printf("%d ", tot[i]);
	system("pause");
	return 0;
}