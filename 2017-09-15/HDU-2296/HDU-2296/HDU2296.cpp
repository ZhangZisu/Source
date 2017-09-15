#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 1000
struct trie {
	trie *fail, *son[26]; int len;
	trie() { fail = NULL; len = 0; memset(son, NULL, sizeof(son)); }
}*root;
char s[MAXN];
inline void insert() {
	trie *p = root;
	for (int i = 0; s[i]; i++) {
		int c = s[i] - 'a';
		if (!p->son[c])p->son[c] = new trie();
		p = p->son[c];
	}
}
trie *Q[10000];
int head, tail;
inline void getFail() {
	Q[head = tail = 0] = root; tail++;
	while (head < tail) {
		trie *p = Q[head++];
		for (int i = 0; i < 26; i++) {
			if (!p->son[i])continue;
			if (p == root) {
				p->son[i]->fail = root;
			}
			else {
				trie *q = p->fail;
				while (q && !q->son[i])q = q->fail; q = q->son[i];
				if (q) {
					p->son[i]->fail = q;
				}
				else {
					p->son[i]->fail = root;
				}
			}
			Q[tail++] = p->son[i];
		}
	}
}
int t;
int main() {
	scanf("%d", &t);
	while (t--) {

	}
	return 0;
}