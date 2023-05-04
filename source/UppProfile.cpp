#include <iostream>
#include <map>
#include <vector>
#include "header.h"
#include "misc_functions.cpp"
using namespace std;
//using namespace management;
using date = string;


namespace management
{

    map<string, int> UppProfile::getSpecialities(vector<EmplProfile*> employees)
    {
        map<string, int> specialities;

        for(int i = 0; i < employees.size(); i++)
        {
            //ManagerProfile* manager = dynamic_cast<ManagerProfile*>(logedAs);
            if((*(employees[i])).getField("Emprego") == "Médico")
            {
                string spec = (*(employees[i])).getField("Especialidade");
                if(spec != "Desconhecido")
                {
                    auto sp = specialities.find(spec);
                    if(sp == specialities.end())
                    {
                        specialities.insert(make_pair(spec, 1));
                    }
                    else
                    {
                        (*sp).second += 1;
                    }
                }
            }
        }
        return specialities;
    }

    vector<EmplProfile> UppProfile::searchByEmployment(vector<EmplProfile*> employees, const string employment)
    {
        vector<EmplProfile> empls;
        for(int i = 0; i < employees.size(); i++)
        {
            if((*(employees[i])).getField("Emprego") == employment)
            {
                empls.push_back(*(employees[i]));
            }
        }
        return empls;
    }


    int UppProfile::searchByName(vector<EmplProfile*> employees, string name)
    {
        for(int i = 0; i < employees.size(); i++)
        {
            if((*(employees[i])).getField("Nome") == name)
            {
                return i;
            }
        }
        return -1;
    }

    void UppProfile::showEmplSchedule(vector<EmplProfile*> employees, string name)
    {
        int x = searchByName(employees, name);
        if(x != -1)
        {
            printMap<string, date>((*(employees[x])).schedule);
        }
        else
        {
            cout<<"Empregado não encontrado\n";
        }
    }

    string UppProfile::actionList()
    {
        string k = EmplProfile::actionList();
        k.append("3 - Pesquisar especialidades\n4 - Pesquisar médicos\n5 - Visualizar agenda de um médico\n");
        return k;
    }
}

