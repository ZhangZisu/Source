#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAX_SAM_SIZE 1000000
int pre[MAX_SAM_SIZE], len[MAX_SAM_SIZE], son[MAX_SAM_SIZE][26], sum[MAX_SAM_SIZE], _sum[MAX_SAM_SIZE];
int size, last;
inline int newState(int _len, int _pre) {
	int cur = size++; sum[cur] = 1;
	pre[cur] = _pre; len[cur] = _len; memset(son[cur], -1, sizeof(son[cur]));
	return cur;
}
inline int newState(int old) {
	int cur = size++; sum[cur] = 0;
	pre[cur] = pre[old]; len[cur] = len[old]; memcpy(son[cur], son[old], sizeof(son[cur]));
	return cur;
}
inline void init_sam() {
	pre[0] = -1; len[0] = 0; memset(son[0], -1, sizeof(son[0])); sum[0] = 1;
	size = 1; last = 0;
}
inline void insert_sam(char _c) {
	int c = _c - 'a', cur = newState(len[last] + 1, 0), p = last;
	for (; ~p && !~son[p][c]; p = pre[p])son[p][c] = cur;
	if (~p) {
		int q = son[p][c];
		if (len[p] + 1 == len[q]) {
			pre[cur] = q;
		}
		else {
			int clone = newState(q); len[clone] = len[p] + 1;
			for (; ~p && son[p][c] == q; p = pre[p])son[p][c] = clone;
			pre[q] = pre[cur] = clone;
		}
	}
	last = cur;
}
char s[1000000];
int id[MAX_SAM_SIZE];
inline int cmp(const int &a, const int &b) { return len[a] < len[b]; }
int t, k;
inline void build_sam() {
	init_sam();
	for (int i = 0; s[i]; i++)insert_sam(s[i]);
	for (int i = 0; i < size; i++)id[i] = i;
	std::sort(id, id + size, cmp);
	for (int i = size - 1; i >= 0; i--) {
		if (t == 1) {
			if (~pre[id[i]])sum[pre[id[i]]] += sum[id[i]];
		}
		else {
			sum[i] = 1;
		}
	}
	sum[0] = 0;
	for (int i = size - 1; i >= 0; i--) {
		_sum[id[i]] = sum[id[i]];
		for (int I = 0; I < 26; I++)if (~son[id[i]][I])_sum[id[i]] += _sum[son[id[i]][I]];
	}
}
inline void query(int p, int k) {
	if (k <= sum[p])return;
	k -= sum[p];
	for (int i = 0; i < 26; i++) {
		if (!~son[p][i])continue;
		if (k <= _sum[son[p][i]]) {
			putchar(i + 97);
			query(son[p][i], k);
			return;
		}
		k -= _sum[son[p][i]];
	}
}
int main() {
	scanf("%s", s);
	scanf("%d%d", &t, &k);
	build_sam();
	if (k > _sum[0]) {
		printf("-1\n");
		return 0;
	}
	query(0, k); putchar(10);
	system("pause");
	return 0;
}