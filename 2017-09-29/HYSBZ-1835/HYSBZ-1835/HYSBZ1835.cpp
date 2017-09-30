#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using std::vector;
#define MAXN 200010
#define INF 0x3F3F3F3F
#define __abs(a) ((a)<0?-(a):(a))
int M[MAXN << 2], T[MAXN << 2], f[MAXN];
inline void pushUp(int x) {
	M[x] = std::min(M[x << 1], M[x << 1 | 1]);
}
inline void pushDown(int x) {
	if (!T[x])return;
	M[x << 1] += T[x]; M[x << 1 | 1] += T[x];
	T[x << 1] += T[x]; T[x << 1 | 1] += T[x];
	T[x] = 0;
}
void Build(int n, int l, int r) {
	T[n] = 0;
	if (l == r) {
		M[n] = f[l]; return;
	}
	int mid = (l + r) >> 1;
	Build(n << 1, l, mid); Build(n << 1 | 1, mid + 1, r);
	pushUp(n);
}
int Min(int n, int l, int r, int L, int R) {
	if (L > R)return 0;
	if (l == L && r == R)return M[n];
	pushDown(n);
	int mid = (l + r) >> 1;
	if (R <= mid)return Min(n << 1, l, mid, L, R);
	else if (L > mid)return Min(n << 1 | 1, mid + 1, r, L, R);
	else return std::min(Min(n << 1, l, mid, L, mid), Min(n << 1 | 1, mid + 1, r, mid + 1, R));
}
void Modify(int n, int l, int r, int L, int R, int v) {
	if (L > R)return;
	if (l == L && r == R) {
		M[n] += v; T[n] += v; return;
	}
	pushDown(n);
	int mid = (l + r) >> 1;
	if (R <= mid)Modify(n << 1, l, mid, L, R, v);
	else if (L > mid)Modify(n << 1 | 1, mid + 1, r, L, R, v);
	else Modify(n << 1, l, mid, L, mid, v), Modify(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	pushUp(n);
}
int n, k, d[MAXN], w[MAXN], c[MAXN], s[MAXN], _l[MAXN], _r[MAXN], ans;
vector<int> pre[MAXN];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 2; i <= n; i++)scanf("%d", &d[i]);
	for (int i = 1; i <= n; i++)scanf("%d", &c[i]);
	for (int i = 1; i <= n; i++)scanf("%d", &s[i]);
	for (int i = 1; i <= n; i++)scanf("%d", &w[i]);
	d[++n] = INF; w[n] = INF; k++;
	for (int i = 1; i <= n; i++) {
		_l[i] = std::lower_bound(d + 1, d + n + 1, d[i] - s[i]) - d;
		_r[i] = std::upper_bound(d + 1, d + n + 1, d[i] + s[i]) - d - 1;
		pre[_r[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		f[i] = c[i] + ans;
		for (vector<int>::iterator it = pre[i].begin(); it != pre[i].end(); it++)
			ans += w[*it];
	}
	ans = f[n];
	for (int i = 2; i <= k; i++) {
		Build(1, 1, n);
		for (int j = 1; j <= n; j++) {
			f[j] = Min(1, 1, n, 1, j - 1) + c[j];
			for (vector<int>::iterator it = pre[j].begin(); it != pre[j].end(); it++) {
				Modify(1, 1, n, 1, _l[*it] - 1, w[*it]);
			}
		}
		ans = std::min(ans, f[n]);
	}
	printf("%d\n", ans);
	system("pause");
	return 0;
}