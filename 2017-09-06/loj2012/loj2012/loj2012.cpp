#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using std::vector;
#define MAXN 520000
int n, len;
char s[MAXN];
int root, f[MAXN], son[MAXN][26], size[MAXN], ans[MAXN], idx[MAXN], cnt, dfn;
vector<int> nxt[MAXN];
inline void insert(int x, int p, int k) {
	if (s[x] == '\0') {
		idx[p] = k;
		return;
	}
	if (!~son[p][s[x] - 'a']) {
		son[p][s[x] - 'a'] = cnt++;
	}
	insert(x + 1, son[p][s[x] - 'a'], k);
}
int head[MAXN], next[MAXN], to[MAXN], tot;
inline void addEdge(int u, int v) {
	next[tot] = head[u]; to[tot] = v; head[u] = tot++;
}
inline void rebuild(int p, int fa) {
	if (~idx[p]) {
		addEdge(fa, idx[p]);
		f[idx[p]] = fa;
		fa = idx[p];
	}
	for (int i = 0; i < 26; i++)if (~son[p][i])rebuild(son[p][i], fa);
}
inline void dfs(int p) {
	size[p] = 1;
	for (int i = head[p]; ~i; i = next[i]) {
		dfs(to[i]);
		size[p] += size[to[i]];
		nxt[p].push_back(to[i]);
	}
	std::sort(nxt[p].begin(), nxt[p].end(), [](int a, int b) {return size[a] < size[b]; });
}
inline void slove(int x) {
	ans[x] = dfn++;
	for (vector<int>::iterator it = nxt[x].begin(); it != nxt[x].end(); it++)slove(*it);
}
int main() {
	scanf("%d", &n);
	memset(f, -1, sizeof(f));
	memset(son, -1, sizeof(son));
	memset(head, -1, sizeof(head));
	memset(idx, -1, sizeof(idx));
	root = cnt++;
	for (int i = 0; i < n; i++) {
		scanf("%s", s);
		len = strlen(s);
		for (int j = 0; j < (len >> 1); j++)std::swap(s[j], s[len - j - 1]);
		insert(0, root, i);
	}
	rebuild(root, n);
	dfs(n);
	slove(n);
	long long tot = 0;
	for (int i = 0; i < n; i++)tot += ans[i] - ans[f[i]];
	printf("%lld\n", tot);
	return 0;
}