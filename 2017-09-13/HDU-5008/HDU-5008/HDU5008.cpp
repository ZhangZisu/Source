#include<vector>
using std::vector;
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAX_SAM_SIZE 400020
#define MAXN 200010
struct state {
	int len, pre, pos, son[26];
	state(int len = 0, int pre = -1) :len(len), pre(pre), pos(-1) { memset(son, -1, sizeof(son)); }
}pool[MAX_SAM_SIZE];
int size, last, id[MAX_SAM_SIZE];
vector<int> next[MAX_SAM_SIZE];
inline void init_sam() {
	pool[size = last = 0] = state();
	size++;
}
inline void insert_sam(char _c) {
	int c = _c - 'a', cur = size++, p = last;
	pool[cur] = state(pool[last].len + 1, 0);
	for (; ~p && !~pool[p].son[c]; p = pool[p].pre)pool[p].son[c] = cur;
	if (~p) {
		int q = pool[p].son[c];
		if (pool[p].len + 1 == pool[q].len) {
			pool[cur].pre = q;
		}
		else {
			int clone = size++;
			pool[clone] = state(pool[q]);
			pool[clone].len = pool[p].len + 1;
			for (; ~p && pool[p].son[c] == q; p = pool[p].pre)pool[p].son[c] = clone;
			pool[q].pre = pool[cur].pre = clone;
		}
	}
	last = cur;
}
inline int cmp(const int &a, const int &b) {
	return pool[a].len > pool[b].len;
}
char s[MAXN];
int len;
inline void build_sam() {
	init_sam(); len = strlen(s);
	for (int i = 0; i < (len >> 1); i++)std::swap(s[i], s[len - i - 1]);
	for (int i = 0; i < len; i++)insert_sam(s[i]);
	for (int i = 0; i < size; i++)id[i] = i;
	std::sort(id, id + size, cmp);
}
long long sz[MAX_SAM_SIZE], cnt;
inline void dfs(int x) {
	cnt += pool[x].len; if (~pool[x].pre)cnt -= pool[pool[x].pre].len;
	sz[x] = cnt;
	for (vector<int>::iterator it = next[x].begin(); it != next[x].end(); it++)dfs(*it);
}
inline int Cmp(const int &a, const int &b) {
	return s[pool[a].pos - pool[pool[a].pre].len] < s[pool[b].pos - pool[pool[b].pre].len];
}
int idx[MAX_SAM_SIZE];
inline int CMp(const int &a, const int &b) {
	return sz[a] < sz[b];
}
int n;
long long k, a = 0, b = 0;
int main() {
	while (~scanf("%s%d", s, &n)) {
		a = b = cnt = 0;
		build_sam(); cnt = 0;
		for (int i = 0; i < size; i++)next[i].clear();
		for (int i = 0; i < size; i++) {
			if (~pool[i].pre)next[pool[i].pre].push_back(i);
		}
		register int p = 0;
		for (int i = 0; i < len; i++) {
			int c = s[i] - 'a';
			p = pool[p].son[c];
			pool[p].pos = i;
		}
		for (int i = 0; i < size; i++) {
			if (~pool[id[i]].pre) {
				pool[pool[id[i]].pre].pos = std::max(pool[pool[id[i]].pre].pos, pool[id[i]].pos);
			}
		}
		for (int i = 0; i < size; i++) { std::sort(next[i].begin(), next[i].end(), Cmp); idx[i] = i; }
		dfs(0);
		std::sort(idx, idx + size, CMp);
		while (n--) {
			scanf("%lld", &k);
			k = (k ^ a ^ b) + 1;
			if (k > cnt) {
				a = b = 0;
			}
			else {
				int l = 0, r = size - 1;
				while (l <= r) {
					int mid = (l + r) >> 1;
					if (sz[idx[mid]] >= k)r = mid - 1; else l = mid + 1;
				}
				r = l;
				int p = idx[r];
				if (r)k -= sz[idx[r - 1]];
				a = len - pool[p].pos;
				b = a + pool[pool[p].pre].len + k - 1;
			}
			printf("%lld %lld\n", a, b);
		}
	}
	return 0;
}