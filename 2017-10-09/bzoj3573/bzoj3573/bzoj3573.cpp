#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 500010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void addEdge(int u, int v) {
	next[tot] = head[u]; to[tot] = v; head[u] = tot++;
}
int n, _x, _y, dg[MAXN], ans, now;
double a[MAXN], dis[MAXN];
void DFS(int x, int fa) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa)continue;
		dis[to[i]] += dis[x] + log(double(dg[x]));
		DFS(to[i], x);
	}
}
int main() {
	scanf("%d", &n); memset(head, -1, sizeof(head));
	for (int i = 1; i <= n; i++) {
		scanf("%d", &_x);
		a[i] = log((double)_x);
	}
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &_x, &_y);
		addEdge(_x, _y); addEdge(_y, _x);
		dg[_x]++; dg[_y]++;
	}
	for (int i = 2; i <= n; i++) {
		dg[i]--;
	}
	DFS(1, -1);
	for (int i = 1; i <= n; i++)a[i] += dis[i];
	std::sort(a + 1, a + n + 1); now = 1;
	for (int i = 2; i <= n; i++) {
		if (a[i] - a[i - 1] < 1e-5)now++;
		else ans = std::max(ans, now), now = 1;
	}
	ans = std::max(ans, now);
	printf("%d\n", n - ans);
	system("pause");
	return 0;
}
