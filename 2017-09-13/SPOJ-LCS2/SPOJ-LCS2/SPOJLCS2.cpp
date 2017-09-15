#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAX_SAM_SIZE 500000
#define MAXN 100000
struct state {
	int son[26], len, pre, max, ans;
	state(int len = 0, int pre = 0) :len(len), pre(pre), max(0), ans(0x7FFFFFFF) { memset(son, -1, sizeof(son)); }
}pool[MAX_SAM_SIZE];
int size, last, id[MAX_SAM_SIZE];
inline void init_sam() { pool[size = last = 0] = state(0, -1); size++; }
inline void insert_sam(char _c) {
	int c = _c - 'a';
	int cur = size++, p = last;
	pool[cur] = state(pool[last].len + 1);
	for (; ~p && !~pool[p].son[c]; p = pool[p].pre)pool[p].son[c] = cur;
	if (!~p) {
		pool[cur].pre = 0;
	}
	else {
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
inline int cmp(const int &a, const int &b) { return pool[a].len > pool[b].len; }
char s[MAXN];
inline void build_sam() {
	init_sam();
	for (int i = 0; s[i]; i++)insert_sam(s[i]);
	for (int i = 0; i < size; i++)id[i] = i;
	std::sort(id, id + size, cmp);
}
int main() {
	scanf("%s", s);
	build_sam();
	while (~scanf("%s", s)) {
		int len = 0, ans = 0, p = 0;
		for (int i = 0; s[i]; i++) {
			int c = s[i] - 'a';
			if (~pool[p].son[c]) {
				len++;
				p = pool[p].son[c];
			}
			else {
				while (!~pool[p].son[c])p = pool[p].pre;
				if (~p) {
					len = pool[p].len + 1;
					p = pool[p].son[c];
				}
				else {
					len = p = 0;
				}
			}
			pool[p].max = std::max(pool[p].max, len);
		}
		for (int i = 0; i < size; i++) {
			pool[id[i]].ans = std::min(pool[id[i]].ans, pool[id[i]].max);
			if (pool[id[i]].max && ~pool[id[i]].pre)pool[pool[id[i]].pre].max = pool[pool[id[i]].pre].len;
			pool[id[i]].max = 0;
		}
	}
	int res = 0;
	for (int i = 0; i < size; i++)res = std::max(pool[i].ans, res);
	printf("%d\n", res);
	system("pause");
	return 0;
}