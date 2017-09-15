#include<cstdio>
#include<cstring>
#define MAXN 
int t, n;
char s[5500000], t[5500000], len, cur;
struct trie {
	trie *fail, *son[26];
	int num;
	trie() {
		fail = NULL; num = 0;
		memset(son, NULL, sizeof(son));
	}
}*root;
inline void insert() {
	trie *p = root;
	for (int i = 0; s[i]; i++) {
		int c = s[i] - 'A';
		if (!p->son[c])p->son[c] = new trie();
		p = p->son[c];
	}
	p->num++;
}
trie *Q[1000000];
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
				while (q && !q->son[i])q = q->fail;
				if (q)p->son[i]->fail = q->son[i];
				else p->son[i]->fail = root;
			}
			Q[tail++] = p->son[i];
		}
	}
}
int main() {
	scanf("%d", &t);
	while (t--) {
		root = new trie();
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			insert();
		}
		getFail();
		len = cur = 0;
		while (s[cur]) {
			if (s[cur] == '[') {

			}
			else {
				t[len++] = s[cur];
			}
		}
	}
	return 0;
}