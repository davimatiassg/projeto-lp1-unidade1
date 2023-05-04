#include <iostream>
#include <map>
#include <vector>
using namespace std;
//Função geral para printar informações e agenda guardadas em mapa.
template<typename T1, typename T2>
void printMap(map<T1, T2> m)
{
    for(typename map<T1, T2>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout<<(*it).first << ": " << (*it).second << endl;
    }
}
