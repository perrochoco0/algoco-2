#include <bits/stdc++.h>
#include <unistd.h>
#define ll long long;
using namespace std;

const int MAXN = 1000005;
int prv[MAXN], nxt[MAXN];
char val[MAXN];
char s[MAXN], out[MAXN];

int main() {
    int T;
    cin>>T;
    while (T--) {
        scanf("%s", s);
        int n = strlen(s);

        nxt[0] = -1;
        prv[0] = -1;

        int tail = 0;
        int cursor = 0;
        int cnt = 0;

        for (int i = 0; i < n; i++) {
            char c = s[i];
            if (c == '<') {
                if (cursor != 0) {
                    int p = prv[cursor];
                    int q = nxt[cursor];
                    nxt[p] = q;
                    if (q != -1) prv[q] = p;
                    else tail = p;
                    cursor = p;
                }
            }
            else if (c == '[') {
                cursor = 0;
            }
            else if (c == ']') {
                cursor = tail;
            }
            else {
                int nd = ++cnt;
                val[nd] = c;
                int q = nxt[cursor];
                nxt[cursor] = nd;
                prv[nd] = cursor;
                nxt[nd] = q;
                if (q != -1) prv[q] = nd;
                else tail = nd;
                cursor = nd;
            }
        }

        int oi = 0;
        for (int cur = nxt[0]; cur != -1; cur = nxt[cur])
            out[oi++] = val[cur];
        out[oi] = '\0';
        puts(out);
    }
    return 0;
}
