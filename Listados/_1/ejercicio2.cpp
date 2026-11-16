#include <bits/stdc++.h>
#include <unistd.h>


using namespace std;

/* Clasico problema del puente
 *
 *
 * Done
 */

int main(){
    long long n;

    cin>>n;

    vector<int> mountains(n);

    //lectura
    for(int i = 0; i < n; i++){
        cin>>mountains[i];
    }


    //algoritmo (terrible sus)
    int candidato = 0;
    // izquierda a derecha
    int select_izq = 0;
    int max_altura_izq = 0;


    for (int i = 0; i < n; i++){
        if(mountains[i] >= max_altura_izq){
            max_altura_izq = mountains[i];
            if(candidato > select_izq){
                select_izq = candidato;
            }
        }
        else{

            int diferencia = max_altura_izq - mountains[i];
            if(diferencia > candidato){
                candidato = diferencia;
            }
        }

    }
    candidato = 0;
    // derecha a izquierda
    int select_der = 0;
    int max_altura_der = 0;

    for(int j = n - 1; j >= 0; j--){
        if(mountains[j] >= max_altura_der){
            max_altura_der = mountains[j];
            if(candidato > select_der){
                select_der = candidato;
            }
        }
        else{

            int diferencia = max_altura_der - mountains[j];
            if(diferencia > candidato){
                candidato = diferencia;
            }
        }

    }

    if(select_der > select_izq){
        cout<<select_der<<endl;
    }
    else{
        cout<<select_izq<<endl;
    }
    return 0;
}
