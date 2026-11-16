#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {

    set<string> words;
    string w;

    while (cin >> w) {
        words.insert(w);
    }

    set<string> compounds;

    for (auto it1 = words.begin(); it1 != words.end(); ++it1) {
        for (auto it2 = words.begin(); it2 != words.end(); ++it2) {
            if (it1 != it2) {
                compounds.insert(*it1 + *it2);
            }
        }
    }

    for (const string& cw : compounds) {
        cout << cw << "\n";
    }

    return 0;
}
