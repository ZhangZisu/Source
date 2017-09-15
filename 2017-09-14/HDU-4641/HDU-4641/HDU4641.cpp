#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAX_SAM_SIZE 500000
#define MAXN 60000
int son[MAX_SAM_SIZE][26], pre[MAX_SAM_SIZE], len[MAX_SAM_SIZE], cnt[MAX_SAM_SIZE], size, last;
bool BUILD_SAM;
inline int sam() {
	int cur = size++;
	memset(son[cur], -1, sizeof(son[cur]));
	pre[cur] = 0; len[cur] = 0; cnt[cur] = 1;
	return cur;
}
inline int sam(int old) {
	int cur = size++;
	memcpy(son[cur], son[old], sizeof(son[cur]));
	pre[cur] = pre[old]; len[cur] = len[old]; cnt[cur] = cnt[old];
	return cur;
}
inline void init_sam() {
	memset(son[0], -1, sizeof(son[0]));
	pre[0] = -1; len[0] = 0; size = 1; last = 0;
}
inline int insert_sam(char _c) {
	int c = _c - 'a', p = last, cur = sam(); len[cur] = len[last] + 1;
	for (; ~p && !~son[p][c]; p = pre[p])son[p][c] = cur;
	if (~p) {
		int q = son[p][c];
		if (len[p] + 1 == len[q]) {
			pre[cur] = q;
		}
		else {
			int clone = sam(q);
			if (BUILD_SAM)cnt[clone] = 0;
			len[clone] = len[p] + 1;
			for (; ~p && son[p][c] == q; p = pre[p])son[p][c] = clone;
			pre[q] = pre[cur] = clone;
		}
	}
	return last = cur;
}
char s[MAXN];
inline void build_sam() {
	init_sam(); BUILD_SAM = true;
	for (int i = 0; s[i]; i++)insert_sam(s[i]);
	BUILD_SAM = false;
}
long long ans;
int id[MAX_SAM_SIZE];
inline int cmp(const int &a, const int &b) {
	return len[a] < len[b];
}
int k;
inline void run_sam() {
	for (int i = 0; i < size; i++)id[i] = i;
	std::sort(id, id + size, cmp);
	for (int i = size - 1; i >= 0; i--)
		if (~pre[id[i]])
			cnt[pre[id[i]]] += cnt[id[i]];
	for (int i = 0; i < size; i++)
		if (cnt[i] >= k) {
			ans += len[i];
			if (~pre[i])ans -= len[pre[i]];
		}
}
inline void update_sam(int p) {
	for (; p; p = pre[p]) {
		if (cnt[p] >= k)ans += len[p] - len[pre[p]];
		if (cnt[pre[p]] >= k)break;
		cnt[pre[p]]++;
	}
}
int n, m, op, ap[3];
int main() {
	while (~scanf("%d%d%d", &n, &m, &k)) {
		scanf("%s", s); build_sam(); ans = 0; run_sam();
		while (m--) {
			scanf("%d", &op);
			if (op == 1) {
				scanf("%s", ap);
				update_sam(insert_sam(ap[0]));
			}
			else {
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}