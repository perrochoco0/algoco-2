#include <bits/stdc++.h>
#include <unistd.h>
#define ll long long;


using namespace std;


int main(){
    int n, m;
    cin>>n>>m;

    vector<int> views(m);

    for(int i = 0; i < m; i++){
        cin>>views[i];
    }

    int index = 0;

    for(int i = 0 ; i < n; i++){
        if(index < m){
            if(views[index] == i){
                index += 1;
            }
            else{
                cout<<i<<endl;
            }
        }
        else{
            cout<<i<<endl;
        }

    }


    cout<<"Mario got "<<m<<" of the dangerous obstacles.";
    return 0;
}
