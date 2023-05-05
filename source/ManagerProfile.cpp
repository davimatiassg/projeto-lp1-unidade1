#include <iostream>
#include <map>
#include <vector>
#include "header.h"
using namespace std;

namespace management{

    ManagerProfile::ManagerProfile(string pass, string login, string name, string employment, vector<EmplProfile*>& emp) : UppProfile(pass, login, name, employment), employees(emp)
    {
        cout<<"Iniciação da conta de Gerente concluida.\n";
    }
    
    EmplProfile::Create(vector<string> logins, vector<EmplProfile*>& accs)
    {
        string name;
        string pass;

        cout<<"Criando o perfil do usuário 'Gerente'."<<endl;
        bool k = false;
        while(true)
        {
            string passW[2];
            cout<<"Digite a senha para o Gerente: ";
            cin>>passW[0];
            cout<<"Confirme a senha: ";
            cin>>passW[1];
            if(passW[0] == passW[1])
            {
                pass = passW[0];
                break;
            }
            else
            {
                cout<<"As senhas devem ser iguais!\n";
            }
        }
        cout<<"Digite o nome do Gerente: ";
        cin>>name;
        return new EmplProfile::ManagerProfile(pass, "Gerente", name, "Gerente", accs);
    }


    void ManagerProfile::addFunc()
    {
        string login;
        string name;
        string employment;
        string pass;

        cout<<"Criando um novo funcionário."<<endl;
        bool k = false;
        while(!k)
        {
            cout<<"Digite o nome de usuário do funcionário: ";
            cin>>login;
            k = true;
            for(int i = 0; i < logins.size(); i ++)
            {
                if(login == logins[i])
                {
                    k = false;
                    break;
                    cout<<"Esse nome de usuário já está em uso.\n";
                }
                
            }
        }
        
        while(true)
        {
            string passW[2];
            cout<<"Digite a senha do funcionário: ";
            cin>>passW[0];
            cout<<"Confirme a senha: ";
            cin>>passW[1];
            if(passW[0] == passW[1])
            {
                pass = passW[0];
                break;
            }
            else
            {
                cout<<"As senhas devem ser iguais!\n";
            }
        }
        cout<<"Digite o nome do funcionário: ";
        cin>>name;

        cout<<"Digite a função do funcionário: ";
        cin>>employment;
        EmplProfile e*;
        if(employment == "Atendente")
        {
            e = new EmplProfile::AccProfile(pass, login, name, employment);
        }
        else
        {
            e = new EmplProfile::EmplProfile(pass, login, name, employment);
            if(employment == "Médico")
            {
                string specialty;
                cout<<"Digite a especialidade do médico: ";
                cin>>specialty;
                e->info.insert(make_pair("Especialidade", specialty));
            }
        }

        cout<<"Novo " << employment  <<"adicionado."<<endl;
        employees.push_back(e);
    }

    void ManagerProfile::editFunc()
    {
        string mSel;
        cout<<"\nDigite o nome do funcionário a ser editado:\n";
        cin>>mSel;
        int idx = searchByName(employees, mSel);
        if(idx != -1){
            cout<<"\nInformações:\n";
            map<string, string> * FuncInfo = & ((*(employees[idx])).info);
            printMap<string, string>(*FuncInfo);
            cout<<"\nDigite o nome da informação a ser alterada:\n";
            cin>>mSel;
            auto pt = (*FuncInfo).find(mSel);
            if(pt != (*FuncInfo).end())
            {
                cout<<"\nDigite a nova " << mSel << ":\n";
                cin>>mSel;
                pt->second = mSel;
            }
            cout<<"Informação alterada com sucesso.\n";
            employees[idx]->Save();
        }
        else
        {
            cout<<"Funcionário não encontrado.\n";
        }
    }

    void ManagerProfile::removeFunc()
    {
        string mSel;
        cout<<"\nDigite o nome do funcionário a ser editado:\n";
        cin>> mSel;
        int idx = searchByName(employees, mSel);
        if(idx != -1){
            employees.erase(employees.begin() + idx);
            cout<<"Funcionário apagado com sucesso.\n";
        }
        else
        {
            cout<<"Funcionário não encontrado.\n";
        }

    }
    string ManagerProfile::actionList()
    {
        string k = UppProfile::actionList();
        k.append("6 - Adicionar um funcionário\n7 - Alterar informações de um funcionário\n8 - Remover um funcionário\n");
        return k;
    }
};

