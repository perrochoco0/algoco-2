#include <bits/stdc++.h>
#include <unistd.h>
#define ll long long;


using namespace std;



int main(){
    int n_students;
    int m_commands;

    cin>>n_students;
    cin>>m_commands;

    int egg = 0;
    string command;
    string last_command;

    for(int i = 0; i < m_commands; i++){
        cin>>command;

        if(command == "undo"){

            int lc = stoi(last_command);
            egg = (egg + lc)% n_students;
        }
        else{
            int c = stoi(command);
            egg = (egg + c )% n_students;
            last_command = command;

        }

    }

    cout<<egg<<endl;
   return 0;
}
