#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, h;
    if (!(cin >> n >> h)) return 0;

    vector<int> stalagmites(h + 2, 0);
    vector<int> stalactites(h + 2, 0);

    for (int i = 0; i < n; i++) {
        int size;
        cin >> size;
        if (i % 2 == 0) {
            stalagmites[size]++;
        } else {
            stalactites[size]++;
        }
    }

    for (int i = h - 1; i >= 1; i--) {
        stalagmites[i] += stalagmites[i + 1];
        stalactites[i] += stalactites[i + 1];
    }

    int min_obstacles = 1e9;
    int count_levels = 0;

    for (int i = 1; i <= h; i++) {
        int total = stalagmites[i] + stalactites[h - i + 1];

        if (total < min_obstacles) {
            min_obstacles = total;
            count_levels = 1;
        } else if (total == min_obstacles) {
            count_levels++;
        }
    }

    cout << min_obstacles << " " << count_levels << "\n";

    return 0;
}
