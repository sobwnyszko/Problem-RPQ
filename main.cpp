#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

class Dane{
  public:
    int id;
    int r;
    int p;
    int q;
};

int timeCmax (int n, vector <Dane> dane)
{
    int sumtime=0, Cmax=0, maxtime=0;
    for(int i=0; i<n; i++){
        if (dane[i].r>sumtime){
            sumtime += (dane[i].r - sumtime);
        }
        sumtime += dane[i].p;
        maxtime = sumtime + dane[i].q;
        if (maxtime > Cmax){
            Cmax = maxtime;
        }
    }
    return Cmax;
}

void przerzuc (int n, vector <Dane> &pierwszy, vector <Dane> &drugi)
{
    for (int i=0; i<n; i++){
        drugi[i] = pierwszy[i];
    }
}

void print (int n, vector <Dane> dane)
{
    for (int i=0; i<n; i++){
        cout << dane[i].id << ' ' << dane[i].r << ' ' << dane[i].p << ' ' << dane[i].q <<endl;
    }
    cout << endl;
}

void sortR (int n, vector <Dane> &dane)
{
    for (int i=0; i<n; i++){
        for (int j=1; j<n-i; j++){
            if (dane[j-1].r > dane[j].r){
                swap(dane[j-1], dane[j]);
            }
        }
    }
}

void sortQueue (int n, vector <Dane> &dane)
{
    int timemin=9999999, timeC;
    vector <Dane> obliczenia(n);
    vector <Dane> wynik(n);
    obliczenia[0] = dane[0];
    for (int i=1; i<n; i++){
        obliczenia[i] = dane[i];
        for (int j=i; j>-1; j--){
            timeC = timeCmax(i+1, obliczenia);
            if(timeC<timemin){
                timemin = timeC;
                przerzuc(i+1, obliczenia, wynik);
            }
            if(j>0){
                swap(obliczenia[j], obliczenia[j-1]);
            }
        }
        timemin=9999999;
        przerzuc(i+1, wynik, obliczenia);
    }
    przerzuc(n, wynik, dane);
}

void sortWstaw (int n, vector <Dane> &dane)
{
    int timemin = timeCmax(n, dane), timeC, udalosie=0;
    vector <Dane> obliczenia(n);
    vector <Dane> wynik(n);
    przerzuc(n, dane, obliczenia);
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (i != j){
                swap(obliczenia[i], obliczenia[j]);
                timeC = timeCmax (n, obliczenia);
                if (timeC < timemin){
                    timemin = timeC;
                    przerzuc(n, obliczenia, wynik);
                    udalosie=1;
                    i=0; j=0;
                } else {
                    swap(obliczenia[i], obliczenia[j]);
                }
            }
        }
    }
    if(udalosie == 1){
        przerzuc(n, wynik, dane);
    }
}

void sorting (int n, vector <Dane> &dane)
{
    vector <Dane> wynik(n);
    sortWstaw(n, dane);
    przerzuc(n, dane, wynik);
    sortR(n, dane);
    for (int i=0; i<n; i++){
        sortQueue(n, dane);
    }
    sortWstaw(n, dane);
    if (timeCmax(n, wynik) < timeCmax(n, dane)){
        przerzuc(n, wynik, dane);
    }
}

int main()
{
    int n;
    cin >> n;
    vector <Dane> dane(n);
    for (int i=0; i<n; i++){
        dane[i].id = i+1;
        cin >> dane[i].r >> dane[i].p >> dane[i].q;
    }

    clock_t start = clock();
    sorting(n, dane);
    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
    cout << endl << "Sortowanie danych: " << elapsed << " sekund"  << endl << endl;

    for (int i=0; i<n; i++){
        cout << dane[i].id << ' ';
    }
    cout << endl << endl;
    cout << timeCmax(n, dane) << endl;


    return 0;
}
