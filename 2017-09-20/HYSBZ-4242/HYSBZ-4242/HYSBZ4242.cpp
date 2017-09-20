#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<deque>
using std::deque;
#define MAXN 2005
#define MAXM 200010
#define MAXE 4000020
int n, m, p, q, u, v;
int map[MAXN][MAXN], dis[MAXN][MAXN];
char buf[MAXN];
struct EDGE {
	int head[MAXM], to[MAXE], from[MAXE], val[MAXE], next[MAXE], tot;
	inline void clear() {
		memset(head, -1, sizeof(head)); tot = 0;
	}
	inline void addEdge(int x, int y, int w) {
		next[tot] = head[x]; to[tot] = y; from[tot] = x; val[tot] = w; head[x] = tot++;
	}
}A, B;
struct point {
	int x, y;
	point(int x = 0, int y = 0) :x(x), y(y) {}
};
deque<point> Q;
inline void BFS() {
	while (!Q.empty()) {
		point p = Q.front(); Q.pop_front();
		if (~map[p.x - 1][p.y]) {
			if (map[p.x - 1][p.y]) {
				if (map[p.x - 1][p.y] != map[p.x][p.y])
					A.addEdge(map[p.x - 1][p.y], map[p.x][p.y], dis[p.x - 1][p.y] + dis[p.x][p.y] + 1);
			}
			else {
				map[p.x - 1][p.y] = map[p.x][p.y];
				dis[p.x - 1][p.y] = dis[p.x][p.y] + 1;
				Q.push_back(point(p.x - 1, p.y));
			}
		}
		if (~map[p.x][p.y - 1]) {
			if (map[p.x][p.y - 1]) {
				if (map[p.x][p.y - 1] != map[p.x][p.y])
					A.addEdge(map[p.x][p.y - 1], map[p.x][p.y], dis[p.x][p.y - 1] + dis[p.x][p.y] + 1);
			}
			else {
				map[p.x][p.y - 1] = map[p.x][p.y];
				dis[p.x][p.y - 1] = dis[p.x][p.y] + 1;
				Q.push_back(point(p.x, p.y - 1));
			}
		}
		if (~map[p.x + 1][p.y]) {
			if (map[p.x + 1][p.y]) {
				if (map[p.x + 1][p.y] != map[p.x][p.y])
					A.addEdge(map[p.x + 1][p.y], map[p.x][p.y], dis[p.x + 1][p.y] + dis[p.x][p.y] + 1);
			}
			else {
				map[p.x + 1][p.y] = map[p.x][p.y];
				dis[p.x + 1][p.y] = dis[p.x][p.y] + 1;
				Q.push_back(point(p.x + 1, p.y));
			}
		}
		if (~map[p.x][p.y + 1]) {
			if (map[p.x][p.y + 1]) {
				if (map[p.x][p.y + 1] != map[p.x][p.y])
					A.addEdge(map[p.x][p.y + 1], map[p.x][p.y], dis[p.x][p.y + 1] + dis[p.x][p.y] + 1);
			}
			else {
				map[p.x][p.y + 1] = map[p.x][p.y];
				dis[p.x][p.y + 1] = dis[p.x][p.y] + 1;
				Q.push_back(point(p.x, p.y + 1));
			}
		}
	}
}
int id[MAXE];
inline int cmp(const int &a, const int &b) { return A.val[a] < A.val[b]; }
int _p[MAXM];
inline int find(int x) { return x == _p[x] ? x : _p[x] = find(_p[x]); }
int belong[MAXM], deep[MAXM], fa[MAXM][20], st[MAXM][20], cnt = 0;
void dfs(int x) {
	belong[x] = cnt;
	for (int i = 1; i < 20; i++) {
		if (deep[x] > (1 << i)) {
			fa[x][i] = fa[fa[x][i - 1]][i - 1];
			st[x][i] = std::max(st[x][i - 1], st[fa[x][i - 1]][i - 1]);
		}
	}
	for (int i = B.head[x]; ~i; i = B.next[i]) {
		if (B.to[i] != fa[x][0]) {
			fa[B.to[i]][0] = x;
			st[B.to[i]][0] = B.val[i];
			deep[B.to[i]] = deep[x] + 1;
			dfs(B.to[i]);
		}
	}
}
inline int query(int x, int y) {
	if (deep[x] < deep[y])std::swap(x, y);
	int ret = 0, delta = deep[x] - deep[y];
	for (int i = 19; i >= 0; i--) {
		if ((delta >> i) & 1) {
			ret = std::max(ret, st[x][i]);
			x = fa[x][i];
		}
	}
	if (x == y)return ret;
	for (int i = 19; i >= 0; i--) {
		if (fa[x][i] != fa[y][i]) {
			ret = std::max(ret, st[x][i]); x = fa[x][i];
			ret = std::max(ret, st[y][i]); y = fa[y][i];
		}
	}
	if (fa[x][0]) {
		ret = std::max(ret, st[x][0]);
		ret = std::max(ret, st[y][0]);
	}
	return ret;
}
int main() {
	A.clear(); B.clear(); memset(map, -1, sizeof(map));
	scanf("%d%d%d%d", &n, &m, &p, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%s", buf);
		for (int j = 1; j <= m; j++)map[i][j] = buf[j - 1] == '.' ? 0 : -1;
	}
	for (int i = 1; i <= p; i++) {
		scanf("%d%d", &u, &v);
		map[u][v] = i;
		Q.push_back(point(u, v));
	}
	BFS();
	for (int i = 0; i < A.tot; i++)id[i] = i;
	std::sort(id, id + A.tot, cmp);
	for (int i = 1; i <= p; i++)_p[i] = i;
	for (int i = 0; i < A.tot; i++) {
		int U = find(A.from[id[i]]), V = find(A.to[id[i]]);
		if (U != V) {
			B.addEdge(A.from[id[i]], A.to[id[i]], A.val[id[i]]);
			B.addEdge(A.to[id[i]], A.from[id[i]], A.val[id[i]]);
			_p[U] = V;
		}
	}
	for (int i = 1; i <= p; i++) {
		if (!belong[i]) {
			cnt++;
			deep[i] = 1;
			dfs(i);
		}
	}
	while (q--) {
		scanf("%d%d", &u, &v);
		if (belong[u] != belong[v]) {
			printf("-1\n"); continue;
		}
		printf("%d\n", query(u, v) - 1);
	}
	system("pause");
	return 0;
}