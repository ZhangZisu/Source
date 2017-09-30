#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 2000
int n, m, map[MAXN][MAXN], f[MAXN][MAXN], h[MAXN][MAXN];
int K[MAXN], S[MAXN], top, ans1, ans2;
inline int _2(int a) { return a * a; }
inline void pA(int map[MAXN][MAXN]) {
	printf("PRINT TABLE:\n");
	for (int i = 0; i < n; i++) { for (int j = 0; j < m; j++)printf("%3d", map[i][j]); putchar(10); }
}
inline void slove() {
	memset(f, 0, sizeof(f)); memset(h, 0, sizeof(h));
	for (int i = 0; i < n; i++) {
		h[i][0] = map[i][0];
		for (int j = 1; j < m; j++)h[i][j] = map[i][j] == 1 ? h[i][j - 1] + 1 : 0;
	}
	for (int i = m - 1; i >= 0; i--) {
		top = 0;
		for (int j = 0; j < n; j++) {
			int up = j;
			while (top && S[top] > h[j][i]) {
				ans1 = std::max(ans1, _2(std::min(j - K[top], S[top])));
				ans2 = std::max(ans2, (j - K[top]) * S[top]);
				up = std::min(up, K[top]);
				top--;
			}
			S[++top] = h[j][i]; K[top] = up;
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)for (int j = 0; j < m; j++) {
		scanf("%d", &map[i][j]);
		if ((i + j) & 1)map[i][j] ^= 1;
	}
	slove();
	for (int i = 0; i < n; i++)for (int j = 0; j < m; j++)map[i][j] ^= 1;
	slove();
	printf("%d\n%d\n", ans1, ans2);
	system("pause");
	return 0;
}