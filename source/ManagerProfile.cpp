#include <iostream>
#include <map>
#include <vector>
#include <header.h>
using namespace std;
using namespace management;

class ManagerProfile: public UppProfile
{
private:
    vector<EmplProfile>& employees;
public:
    ManagerProfile(vector<EmplProfile>& emp) : UppProfile(), employees(emp) 
    {
        cout<<"Criando conta de Gerente\n";
        UppProfile();
        this->employees = emp;
    }


    void addMedic()
    {
        EmplProfile medic = EmplProfile();
        employees.push_back(medic);
    }

    void editMedic()
    {
        string mSel;
        cout<<"\nDigite o nome do médico a ser editado:\n";
        cin>>mSel;
        int idx = searchByName(mSel, employees);
        if(idx != -1){
            cout<<"\nInformações:\n";
            map<string, string>& medicInfo = employees[idx].info;
            printMap<string, string>(medicInfo);
            cout<<"\nDigite o nome da informação a ser alterada:\n";
            cin>>mSel;
            auto pt = medicInfo.find(mSel);
            if(pt != medicInfo.end())
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

    void removeMedic()
    {
        string mSel;
        cout<<"\nDigite o nome do médico a ser editado:\n";
        cin>> mSel;
        int idx = searchByName(mSel, employees);
        if(idx != -1){
            employees.erase(employees.begin() + idx);
            cout<<"Médico apagado com sucesso.\n";
        }
        else
        {
            cout<<"Médico não encontrado.\n";
        }

    }
    string actionList() final
    {
        string k = UppProfile::actionList();
        k.append("6 - Adicionar um médico\n7 - Alterar a especialidade de um médico\n8 - Remover um médico\n");
        return k;
    }
};
