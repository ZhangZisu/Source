#include<cstdio>
#include<cstring>
#include<cstdlib>
#define MSS 1000100
struct SAM {
	int son[MSS][26], len[MSS], pre[MSS], size, last;
	int sam(int old) {
		int cur = size++;
		len[cur] = len[old]; pre[cur] = pre[old]; memcpy(son[cur], son[old], sizeof(son[cur]));
		return cur;
	}
	int sam(int _len, int _pre) {
		int cur = size++;
		len[cur] = _len; pre[cur] = _pre; memset(son[cur], -1, sizeof(son[cur]));
		return cur;
	}
	void init() {
		size = last = 0; sam(0, -1);
	}
	void insert(char _c) {
		int c = _c - 'a', p = last, cur = sam(len[last] + 1, 0);
		for (; ~p && !~son[p][c]; p = pre[p])son[p][c] = cur;
		if (~p) {
			int q = son[p][c];
			if (len[p] + 1 == len[q]) {
				pre[cur] = q;
			}
			else {
				int clone = sam(q);
				len[clone] = len[p] + 1;
				for (; ~p && son[p][c] == q; p = pre[p])son[p][c] = clone;
				pre[q] = pre[cur] = clone;
			}
		}
		last = cur;
	}
}A, B;
unsigned long long _A[MSS], _B[MSS];
unsigned long long b(int x) {
	if (!~x)return 0;
	if (~_B[x])return _B[x];
	_B[x] = 1;
	for (int i = 0; i < 26; i++)_B[x] += b(B.son[x][i]);
	return _B[x];
}
unsigned long long a(int x) {
	if (!~x)return 0;
	if (~_A[x])return _A[x];
	_A[x] = 1;
	for (int i = 0; i < 26; i++) {
		if (~A.son[x][i])_A[x] += a(A.son[x][i]);
		else _A[x] += b(B.son[0][i]);
	}
	return _A[x];
}
int t;
char s[MSS];
int main() {
	scanf("%d", &t);
	while (t--) {
		memset(_A, -1, sizeof(_A));
		memset(_B, -1, sizeof(_B));
		scanf("%s", s);
		A.init();
		for (int i = 0; s[i]; i++)A.insert(s[i]);
		scanf("%s", s);
		B.init();
		for (int i = 0; s[i]; i++)B.insert(s[i]);
		printf("%llu\n", a(0));
	}
	system("pause");
	return 0;
}