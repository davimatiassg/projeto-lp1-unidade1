#include <iostream>
#include <map>
#include <vector>
#include "header.h"
#include "misc_functions.cpp"
using namespace std;
//using namespace management;


namespace management
{
    UppProfile::UppProfile(string pass, string login, string name, string employment) : EmplProfile(pass, login, name, employment)
    {}
    map<string, int> UppProfile::getSpecialities(vector<EmplProfile*> employees)
    {
        map<string, int> specialities;

        for(int i = 0; i < employees.size(); i++)
        {   
            /*
            cout<<"Printando informações do usuário:\n";
            printMap<string, string>((*(employees[i])).info);
            */
            if((*(employees[i])).getField("Emprego") == "Medico")
            {
                string spec = (*(employees[i])).getField("Especialidade");
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

    int UppProfile::searchByLogin(vector<EmplProfile*> employees, string login)
    {
        for(int i = 0; i < employees.size(); i++)
        {
            if((*(employees[i])).getField("Login") == login)
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
            printMap<string, string>((*(employees[x])).schedule);
        }
        else
        {
            cout<<"Empregado nao encontrado\n";
        }
    }

    string UppProfile::actionList()
    {
        string k = EmplProfile::actionList();
        k.append("3 - Visualizar todas as especialidades\n4 - Visualizar todos os medicos\n5 - Visualizar agenda de um medico\n");
        return k;
    }
}

