#include <iostream>
#include <map>
#include <vector>
#include "header.h"
using namespace std;
//using namespace management;
using date = string;

namespace management{

    ManagerProfile::ManagerProfile(vector<EmplProfile*>& emp) : employees(emp)
    {
        cout<<"Criação da conta de Gerente concluida.\n";
    }


    void ManagerProfile::addMedic()
    {
        cout<<"\nCriando um novo médico. Quando a função do funcionário for perguntada, por favor, digite '_'.\n";
        EmplProfile * medic = new EmplProfile();
        string tray;
        cout<<"Digite a especialidade do médico: ";
        cin>>tray;
        (*medic).info["Emprego"] = "Médico";
        //(*medic).info.insert(make_pair("Emprego", "Médico"));
        (*medic).info.insert(make_pair("Especialidade", tray));
        employees.push_back(medic);
    }

    void ManagerProfile::editMedic()
    {
        string mSel;
        cout<<"\nDigite o nome do médico a ser editado:\n";
        cin>>mSel;
        int idx = searchByName(employees, mSel);
        if(idx != -1){
            cout<<"\nInformações:\n";
            map<string, string> * medicInfo = & ((*(employees[idx])).info);
            printMap<string, string>(*medicInfo);
            cout<<"\nDigite o nome da informação a ser alterada:\n";
            cin>>mSel;
            auto pt = (*medicInfo).find(mSel);
            if(pt != (*medicInfo).end())
            {
                cout<<"\nDigite a nova " << mSel << ":\n";
                cin>>mSel;
                pt->second = mSel;
            }
            cout<<"Informação alterada com sucesso.\n";
        }
        else
        {
            cout<<"Médico não encontrado.\n";
        }
    }

    void ManagerProfile::removeMedic()
    {
        string mSel;
        cout<<"\nDigite o nome do médico a ser editado:\n";
        cin>> mSel;
        int idx = searchByName(employees, mSel);
        if(idx != -1){
            employees.erase(employees.begin() + idx);
            cout<<"Médico apagado com sucesso.\n";
        }
        else
        {
            cout<<"Médico não encontrado.\n";
        }

    }
    string ManagerProfile::actionList()
    {
        string k = UppProfile::actionList();
        k.append("6 - Adicionar um médico\n7 - Alterar informações de um funcionário\n8 - Remover um médico\n");
        return k;
    }
};

