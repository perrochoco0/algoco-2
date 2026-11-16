#include <iostream>
#include <vector>

using namespace std;

int main() {

    int n, b;
    if (!(cin >> n >> b)) return 0;

    vector<int> a(n);
    int idx = -1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] == b) {
            idx = i;
        }
    }

    vector<int> left_counts[2];
    left_counts[0].assign(2 * n + 1, 0);
    left_counts[1].assign(2 * n + 1, 0);

    int sum = 0;
    for (int i = idx; i >= 0; --i) {
        if (a[i] > b) sum += 1;
        else if (a[i] < b) sum -= 1;

        left_counts[i % 2][sum + n]++;
    }

    sum = 0;
    long long ans = 0;
    for (int j = idx; j < n; ++j) {
        if (j > idx) {
            if (a[j] > b) sum += 1;
            else if (a[j] < b) sum -= 1;
        }

        ans += left_counts[j % 2][-sum + n];
    }

    cout << ans << "\n";

    return 0;
}
