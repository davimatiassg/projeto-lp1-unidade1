#include <iostream>
#include <map>
#include <vector>
#include "header.h"
#include "misc_functions.cpp"
using namespace std;

namespace management{

    ManagerProfile::ManagerProfile(string pass, string login, string name, string employment, vector<EmplProfile*>& emp) : UppProfile(pass, login, name, employment), employees(emp)
    {
        cout<<"Iniciacao da conta de Gerente concluida.\n";
    }
    
    ManagerProfile* ManagerProfile::Create(vector<EmplProfile*>& accs, vector<string> logins)
    {
        string name;
        string pass;

        cout<<"Criando o perfil do usuario 'Gerente'."<<endl;
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
        ManagerProfile * m = new ManagerProfile(pass, "Gerente", name, "Gerente", accs);
        return m;
    }


    void ManagerProfile::addFunc(vector<string> logins)
    {
        string login;
        string name;
        string employment;
        string pass;

        cout<<"Criando um novo funcionario."<<endl;
        bool k = false;
        while(!k)
        {
            cout<<"Digite o nome de usuario do funcionario: ";
            cin>>login;
            k = true;
            for(int i = 0; i < logins.size(); i ++)
            {
                if(login == logins[i])
                {
                    k = false;
                    break;
                    cout<<"Esse nome de usuario ja esta em uso.\n";
                }
                
            }
        }
        
        while(true)
        {
            string passW[2];
            cout<<"Digite a senha do funcionario: ";
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
        cout<<"Digite o nome do funcionario: ";
        cin>>name;

        cout<<"Digite a funcao do funcionario: ";
        cin>>employment;
        EmplProfile * e;
        if(employment == "Atendente")
        {
            e = new AccProfile(pass, login, name, employment);
        }
        else
        {
            e = new EmplProfile(pass, login, name, employment);
            if(employment == "Medico")
            {
                string specialty;
                cout<<"Digite a especialidade do medico: ";
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
        cout<<"\nDigite o nome do funcionario a ser editado:\n";
        cin>>mSel;
        int idx = searchByName(employees, mSel);
        if(idx != -1){
            cout<<"\nInformacoes:\n";
            map<string, string> * FuncInfo = & ((*(employees[idx])).info);
            printMap<string, string>(*FuncInfo);
            cout<<"\nDigite o nome da informacao a ser alterada:\n";
            cin>>mSel;
            auto pt = (*FuncInfo).find(mSel);
            if(pt != (*FuncInfo).end())
            {
                cout<<"\nDigite a nova " << mSel << ":\n";
                cin>>mSel;
                pt->second = mSel;
            }
            cout<<"Informacao alterada com sucesso.\n";
            employees[idx]->Save();
        }
        else
        {
            cout<<"Funcionario nao encontrado.\n";
        }
    }

    void ManagerProfile::removeFunc()
    {
        string mSel;
        cout<<"\nDigite o nome do funcionario a ser editado:\n";
        cin>> mSel;
        int idx = searchByName(employees, mSel);
        if(idx != -1){
            employees.erase(employees.begin() + idx);
            cout<<"Funcionario apagado com sucesso.\n";
        }
        else
        {
            cout<<"Funcionario nao encontrado.\n";
        }

    }
    string ManagerProfile::actionList()
    {
        string k = UppProfile::actionList();
        k.append("6 - Adicionar um funcionario\n7 - Alterar informacoes de um funcionario\n8 - Remover um funcionario\n");
        return k;
    }
};

