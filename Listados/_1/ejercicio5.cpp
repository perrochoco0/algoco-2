#include <bits/stdc++.h>
#include <unistd.h>
#define ll long long;



using namespace std;

void solve() {
    int n;
    cin >> n;

    map<int, int> asks;
    map<int, int, greater<int>> bids;

    int stock_price = -1;

    for (int i = 0; i < n; ++i) {
        string type, word_shares, word_at;
        int x, y;

        cin >> type >> x >> word_shares >> word_at >> y;

        if (type == "buy") {
            bids[y] += x;
        } else {
            asks[y] += x;
        }

        while (!bids.empty() && !asks.empty()) {
            auto highest_bid = bids.begin();
            auto lowest_ask = asks.begin();

            if (highest_bid->first >= lowest_ask->first) {
                int trade_qty = min(highest_bid->second, lowest_ask->second);

                stock_price = lowest_ask->first;

                highest_bid->second -= trade_qty;
                lowest_ask->second -= trade_qty;

                if (highest_bid->second == 0) {
                    bids.erase(highest_bid);
                }
                if (lowest_ask->second == 0) {
                    asks.erase(lowest_ask);
                }
            } else {
                break;
            }
        }

        if (asks.empty()) cout << "- ";
        else cout << asks.begin()->first << " ";

        if (bids.empty()) cout << "- ";
        else cout << bids.begin()->first << " ";

        if (stock_price == -1) cout << "-\n";
        else cout << stock_price << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
