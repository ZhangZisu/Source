#include<cstdio>
#include<cstring>
#include<cstdlib>
#define MAXN 
int _, n;
char s[5500000], t[5500000];
int len, cur;
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
trie *Q[1500000];
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
inline void del(trie *t) {
	if (t == NULL)return;
	for (int i = 0; i < 26; i++)del(t->son[i]);
	delete t;
}
int main() {
	scanf("%d", &_);
	while (_--) {
		root = new trie(); memset(s, 0, sizeof(s)); memset(t, 0, sizeof(t));
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			insert();
		}
		getFail();
		len = cur = 0;
		scanf("%s", s);
		while (s[cur]) {
			if (s[cur] == '[') {
				register int x = 0; cur++;
				while (s[cur] >= '0' && s[cur] <= '9') { x = (x << 3) + (x << 1) + (s[cur] ^ 48); cur++; }
				while (x--)t[len++] = s[cur]; cur += 2;
			}
			else {
				t[len++] = s[cur++];
			}
		}
		t[len] = '\0'; trie *p = root; int ans = 0;
		for (cur = 0; cur < len; cur++) {
			int c = t[cur] - 'A';
			while (p != root && !p->son[c])p = p->fail;
			p = p->son[c];
			if (!p)p = root;
			trie *q = p;
			while (q != root && q->num >= 0) { ans += q->num; q->num = -1; q = q->fail; }
		}
		p = root;
		for (cur = len - 1; cur >= 0; cur--) {
			int c = t[cur] - 'A';
			while (p != root && !p->son[c])p = p->fail;
			p = p->son[c];
			if (!p)p = root;
			trie *q = p;
			while (q != root && q->num >= 0) { ans += q->num; q->num = -1; q = q->fail; }
		}
		printf("%d\n", ans);
		del(root);
	}
	system("pause");
	return 0;
}