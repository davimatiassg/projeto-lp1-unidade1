#include <iostream>
#include <map>
#include <vector>
#include "header.h"
#include "misc_functions.cpp"
using namespace std;

namespace management
{

    AccProfile::AccProfile(string pass, string login, string name, string employment) : UppProfile(pass, login, name, employment)
    {}

    void AccProfile::assignSchedule(EmplProfile medic)
    {
        string desc;
        string dt;
        cout<< "\nInsira a data da consulta: ";
        cin >> dt;
        cout<< "\nInsira a descricao da consulta ";
        cin >> desc;
        string c = "Consulta: ";
        c.append(desc);
        medic.schedule.insert(make_pair(c, dt));
        cout<<c <<":" << dt << " Criada com sucesso\n";
    }
    string AccProfile::actionList()
    {
        string k = UppProfile::actionList();
        k.append("6 - Agendar uma consulta com um medico\n");
        return k;
    }
}
