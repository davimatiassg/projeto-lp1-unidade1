#include <iostream>
#include <map>
#include <vector> 
#include <fstream>

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

template<typename T1, typename T2>
void saveMap(map<T1, T2> m, string FileName)
{
    ofstream file(FileName);
    for(typename map<T1, T2>::iterator it = m.begin(); it != m.end(); it++)
    {
        file<<(*it).first << ";" << (*it).second << endl;
    }
    file.close();
}

template<typename T1, typename T2>
void recoverMap(map<T1, T2> * m, string FileName)
{
    ifstream file(FileName);
    while(true)
    {

        string field;
        file>>field;
        if(file.eof()) break;
        string l, r, del;
        del = ";";
        l = field.substr(0, field.find(del));
        r = field.substr(field.find(del), field.size());
        (*m).insert(make_pair(l, r));
    }
    file.close();
}
