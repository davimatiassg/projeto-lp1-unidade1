#include <iostream>
#include <map>
#include <vector>
#include <header.h>
using namespace std;
using namespace management;

class AccProfile: public UppProfile
{
public:
    void assignSchedule(EmplProfile medic)
    {
        string desc;
        date dt;
        cout<< "\nInsira a data da consulta: ";
        cin >> dt;
        cout<< "\nInsira a descrição da consulta";
        cin >> desc;
        string c = "Consulta: ";
        c.append(desc);
        medic.schedule.insert(make_pair(c, dt));
    }
    string actionList() final
    {
        string k = UppProfile::actionList();
        k.append("6 - Agendar uma consulta com um médico\n");
        return k;
    }
};