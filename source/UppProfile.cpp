#include <iostream>
#include <map>
#include <vector>
#include <header.h>
using namespace std;
using namespace management;

class UppProfile: public EmplProfile
{
public:
    map<string, int> getSpecialities(vector<EmplProfile> employees)
    {
        map<string, int> specialities;

        for(int i = 0; i < employees.size(); i++)
        {
            if(employees[i].getField("Emprego") == "Médico")
            {
                string spec = employees[i].getField("Especialidade");
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

    vector<EmplProfile> searchByEmployment(vector<EmplProfile> employees, string employment)
    {
        vector<EmplProfile> empls;
        for(int i = 0; i < employees.size(); i++)
        {
            if(employees[i].getField("Emprego") == employment)
            {
                empls.push_back(employees[i]);
            }
        }
        return empls;
    }


    int searchByName(string name, vector<EmplProfile> employees)
    {
        for(int i = 0; i < employees.size(); i++)
        {
            if(employees[i].getField("Nome") == name)
            {
                return i;
            }
        }
        return -1;
    }

    void showEmplSchedule(string name, vector<EmplProfile> employees)
    {
        int x = searchByName(name, employees);
        if(x != -1)
        {
            printMap<string, date>(employees[x]);
        }
        else
        {
            cout<<"Empregado não encontrado\n";
        }
    }

    virtual string actionList() override
    {
        string k = EmplProfile::actionList();
        k.append("3 - Pesquisar especialidades\n4 - Pesquisar médicos\n5 - Visualizar agenda de um médico\n");
        return k;
    }
};
