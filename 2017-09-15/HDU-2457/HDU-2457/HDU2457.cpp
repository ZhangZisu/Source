#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 2000
#define INF 2139062143
inline int CInt(char c) {
	if (c == 'A')return 0;
	if (c == 'G')return 1;
	if (c == 'C')return 2;
	if (c == 'T')return 3;
}
int cnt;
struct trie {
	trie *fail, *son[4]; bool danger;
}*root, pool[MAXN];
inline trie* newTrie() {
	trie *cur = &pool[cnt++];
	cur->fail = NULL; cur->danger = false; memset(cur->son, NULL, sizeof(cur->son));
	return cur;
}
char s[MAXN];
inline void insert() {
	trie *p = root;
	for (int i = 0; s[i]; i++) {
		int c = CInt(s[i]);
		if (!p->son[c])p->son[c] = newTrie();
		p = p->son[c];
	}
	p->danger = true;
}
trie *Q[MAXN];
int head, tail;
inline void getFail() {
	Q[head = tail = 0] = root; tail++;
	while (head < tail) {
		trie *p = Q[head++];
		for (int i = 0; i < 4; i++) {
			if (p == root) {
				if (p->son[i]) {
					p->son[i]->fail = root;
					Q[tail++] = p->son[i];
				}
				else p->son[i] = root;
			}
			else {
				if (p->son[i]) {
					p->son[i]->fail = p->fail->son[i];
					p->son[i]->danger |= p->son[i]->fail->danger;
					Q[tail++] = p->son[i];
				}
				else p->son[i] = p->fail->son[i];
			}
		}
	}
}
int f[MAXN][MAXN];
inline int calc() {
	memset(f, 127, sizeof(f));
	f[0][0] = 0; int len = strlen(s), ans = INF;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < cnt; j++) {
			if (f[i][j] == INF)continue;
			for (int k = 0; k < 4; k++) {
				int pos = pool[j].son[k] - pool;
				if (pool[pos].danger)continue;
				f[i + 1][pos] = std::min(f[i + 1][pos], f[i][j] + (CInt(s[i]) != k));
			}
		}
	}
	for (int i = 0; i < cnt; i++)ans = std::min(ans, f[len][i]);
	return ans == INF ? -1 : ans;
}
int n, _case = 0;
int main() {
	while (~scanf("%d", &n) && n) {
		cnt = 0; root = newTrie();
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			insert();
		}
		getFail();
		scanf("%s", s);
		printf("Case %d: %d\n", ++_case, calc());
	}
	system("pause");
	return 0;
}