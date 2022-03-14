#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;

void Merge(vector<int> &a , vector<int> b)
{
    vector<int>c;
    int i= 0, j= 0;
    while ( i < a.size() && j < b.size())
    {
        if(a[i] < b[j])
        {
            c.push_back(a[i]);
            i++;
        }
        else
        {
            c.push_back(b[j]);
            j++;
        }
    }
    if(i >= a.size())
        for(int k = j; k<b.size();k++)
            c.push_back(b[k]);
    else
        for(int k = i; k<a.size();k++)
            c.push_back(a[k]);
    a.clear();
    for(int m= 0; m<c.size();m++)
        a.push_back((c[m]));
}

void MergeSort(vector<int> &a)
{
    if (a.size() <= 1)
        return;
    int mid;
    vector<int> left;
    vector<int> right;

    mid = a.size()/2;
    for (int i=0; i<mid; i++)
        left.push_back(a[i]);
    for (int i=mid; i<a.size(); i++)
        right.push_back(a[i]);

    MergeSort(left);
    MergeSort(right);
    Merge(left, right);

    a.clear();
    for (int i=0; i<left.size(); i++)
        a.push_back(left[i]);
}

void CountingSort10 (vector<int> &v, int p)
{
    int digit= 0;
    vector<int>aux(v.size(), 0);
    for (int j=0; j<v.size(); j++)
        if(v[j] % p > digit)
            digit= v[j] % p;
    vector<int>c(digit+1, 0);
    for (int j=0; j<v.size(); j++)
        c[v[j] % p] ++;
    for (int k=1; k<c.size(); k++)
        c[k] = c[k] + c[k-1];
    for (int i=v.size()-1; i>=0; i--)
    {
        aux[c[v[i] % p] - 1] = v[i];
        c[v[i] % p] --;
    }
    // copiem vectorul auxiliar in vectorul v care trebuia sortat
    for (int i=0; i<aux.size(); i++)
        v[i] = aux[i];
}

void CountingSort2_16 (vector<int> &v, int base)
{
    vector<int>aux(v.size(), 0);
    vector<int>c(65535, 0);
    for (int j=0; j<v.size(); j++)
        c[(v[j]>>16*base)&65535] ++;
    for (int k=1; k<c.size(); k++)
        c[k] = c[k] + c[k-1];
    for (int i=v.size()-1; i>=0; i--)
    {
        aux[c[(v[i]>>16*base&65535)] - 1] = v[i];
        c[(v[i]>>16*base)&65535] --;
    }
    for (int i=0; i<aux.size(); i++)
        v[i] = aux[i];
}

void CountingSort2_8 (vector<int> &v, int base)
{
    vector<int>aux(v.size(), 0);
    vector<int>c(255, 0);
    for (int j=0; j<v.size(); j++)
        c[(v[j]>>8*base)&255] ++;
    for (int k=1; k<c.size(); k++)
        c[k] = c[k] + c[k-1];
    for (int i=v.size()-1; i>=0; i--)
    {
        aux[c[(v[i]>>8*base&255)] - 1] = v[i];
        c[(v[i]>>8*base)&255] --;
    }
    for (int i=0; i<aux.size(); i++)
        v[i] = aux[i];
}

void RadixSort10 (vector<int> &v)
{
    int max= v[0], n, p= 1;
    for (int i=1; i<v.size(); i++)
        if(v[i] > max)
            max= v[i];
    n= int(log10(max))+1;
    for (int i=1; i<n+1; i++)
    {
        p= p * 10;
        CountingSort10(v, p);
    }
}

void RadixSort2_16 (vector<int> &v)
{
    int base;
    for (int i=0; i<2; i++)
    {
        base= i;
        CountingSort2_16(v, base);
    }
}

void RadixSort2_8 (vector<int> &v)
{
    int base;
    for (int i=0; i<4; i++)
    {
        base= i;
        CountingSort2_8(v, base);
    }
}

void ShellSort (vector<int> &v)
{
    int interval, aux, j, n= v.size();
    interval = n/2;
    while (interval > 0)
    {
        for(int i=interval; i+interval < n; i= i+ interval)
        {
            aux= v[i];
            j= i;
            while(j >= interval && v[j- interval] > aux)
            {
                v[j]= v[j-interval];
                j= j- interval;
            }
            v[j]= aux;
        }
        interval= interval/2;
    }
}

void BubbleSort (vector<int> &v)
{
    int aux, n= v.size();
    for (int i=0; i< n; i++)
        for (int j= 0; j<n-i-1; j++)
            if(v[j] > v[j+1])
            {
                aux= v[j];
                v[j]= v[j+1];
                v[j+1]= aux;
            }
}

void CountingSort(vector<int> &v)
{
    int n= v.size(), max= v[0];
    for (int i=1; i<n; i++)
        if (v[i] > max)
            max=v[i];
    vector<int>fr(max+1, 0);
    vector<int>aux(n, 0);
    for (int i=0; i<n; i++)
        fr[v[i]]++;
    for (int i=1; i<max+1; i++)
        fr[i]= fr[i] + fr[i-1];
    for (int i=0; i<n; i++)
    {
        aux[fr[v[i]]-1]= v[i];
        fr[v[i]]--;
    }
    for (int i=0; i<n; i++)
        v[i]= aux[i];
}

string test_sort(vector<int> v)
{
    for (int i=0; i<v.size()-1; i++)
        if(v[i] > v[i+1])
            return "Nu";
    return "Da";
}

void Test(string Sortare, int T, int N, int Max)
{
    vector<int>v;
    string test= "Da";
    double S=0, MS=0;
    double medieS, medieMS;
    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    for (int j=0; j<T; j++)
    {
        srand(time(0));
        for (int i = 0; i < N; i++)
            v.push_back((rand() * rand() % Max));
        if (Sortare == "MergeSort")
        {
            start = chrono::steady_clock::now();
            MergeSort(v);
            end = chrono::steady_clock::now();
        }
        else
            if(Sortare == "RadixSort10")
            {
                start = chrono::steady_clock::now();
                RadixSort10(v);
                end = chrono::steady_clock::now();
            }
            else
                if (Sortare == "RadixSort2_8")
                {
                    start = chrono::steady_clock::now();
                    RadixSort2_8(v);
                    end = chrono::steady_clock::now();
                }
                else
                    if (Sortare == "RadixSort2_16")
                        {
                            start = chrono::steady_clock::now();
                            RadixSort2_16(v);
                            end = chrono::steady_clock::now();
                        }
                    else
                            if (Sortare == "ShellSort")
                                {
                                    start = chrono::steady_clock::now();
                                    ShellSort(v);
                                    end = chrono::steady_clock::now();
                                }
                            else
                                    if (Sortare == "BubbleSort")
                                        {
                                            start = chrono::steady_clock::now();
                                            BubbleSort(v);
                                            end = chrono::steady_clock::now();
                                        }
                                    else
                                            if (Sortare == "CountingSort")
                                                {
                                                    start = chrono::steady_clock::now();
                                                    CountingSort(v);
                                                    end = chrono::steady_clock::now();
                                                }
                                            else
                                            {
                                                cout<<"String-ul introdus este gresit";
                                                return;
                                            }
        S= S + chrono::duration_cast<chrono::seconds>(end - start).count();
        MS= MS + chrono::duration_cast<chrono::milliseconds>(end - start).count();
        if (test_sort(v) == "Nu")
            test= "Nu";
    }

    medieS= (double) S/T;
    medieMS= (double) MS/T;
    cout<<"Sortare:"<<Sortare<<"---";
    cout<<"Nr. Teste:"<<T<<"---";
    cout<<"Durata medie in secunde:"<<medieS<<"---";
    cout<<"Durata medie in milisecunde:"<<medieMS<<"---";
    cout<<"Sortare corecta:"<<test;
    cout<<"\n";
}

int main()
{
    using namespace std;
    //Stringurile pentru functia test trebuie introduse exact ca urmatoarele:
    //MergeSort     RadixSort10     RadixSort2_8    RadixSort2_16   ShellSort   BubbleSort  CountingSort
    Test("MergeSort", 5 , 1000000, 1000000);
    return 0;
}
