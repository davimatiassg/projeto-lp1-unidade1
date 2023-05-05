#include <iostream>
#include <map>
#include <vector>
#include "header.h"
using namespace std;

namespace management
{
    void AccProfile::assignSchedule(EmplProfile medic)
    {
        string desc;
        string dt;
        cout<< "\nInsira a data da consulta: ";
        cin >> dt;
        cout<< "\nInsira a descrição da consulta ";
        cin >> desc;
        string c = "Consulta: ";
        c.append(desc);
        medic.schedule.insert(make_pair(c, dt));
        cout<<c <<":" << dt << " Criada com sucesso\n";
    }
    string AccProfile::actionList()
    {
        string k = UppProfile::actionList();
        k.append("6 - Agendar uma consulta com um médico\n");
        return k;
    }
}
