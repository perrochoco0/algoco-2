#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {

    string paluria;

    cin>> paluria;

    if (next_permutation(paluria.begin(), paluria.end())) {
        cout << paluria <<endl;
    }
    else {
        cout << 0 <<endl;
    }


    return 0;
}
