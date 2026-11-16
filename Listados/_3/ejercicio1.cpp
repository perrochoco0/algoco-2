#include <bits/stdc++.h>
using namespace std;

const int M = 1000;
int memo[M + 1];
vector<int> mv;

bool win(int n) {
    if (n == 0) return false;
    if (memo[n] != -1) return memo[n];
    bool r = false;
    for (int m : mv) {
        if (m > n) break;
        if (!win(n - m)) { r = true; break; }
    }
    return memo[n] = r;
}

int main() {
    memset(memo, -1, sizeof(memo));
    for (int p = 2; p <= M + 1; p++) {
        bool pr = true;
        for (int d = 2; d * d <= p; d++)
            if (p % d == 0) { pr = false; break; }
        if (pr) mv.push_back(p - 1);
    }
    int q;
    scanf("%d", &q);
    vector<int> a(q);
    for (int i = 0; i < q; i++) scanf("%d", &a[i]);
    for (int i = 0; i < q; i++) {
        bool w = (a[i] > M) ? true : win(a[i]);
        puts(w ? "Alice" : "Bob");
    }
    return 0;
}
