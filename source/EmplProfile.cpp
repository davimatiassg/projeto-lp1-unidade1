#include <iostream>
#include <map>
#include <vector>
#include "header.h"
using namespace std;
using date = string;

namespace management{
    EmplProfile::EmplProfile(string pass, string login, string name, string employment)
    {
        this->password = pass;
        this->info.insert(make_pair("Login", login));
        this->info.insert(make_pair("Nome", name));
        this->info.insert(make_pair("Emprego", employment));
        return EmplProfile;
    }

    EmplProfile::Create(vector<string> logins)
    {

        string login;
        string name;
        string employment;
        string pass;

        cout<<"Criando um novo perfil."<<endl;
        bool k = false;
        while(!k)
        {
            cout<<"Digite o nome de usuário: ";
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
            cout<<"Digite a sua senha: ";
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
        bool k = true;
        while(k)
        {
            if(employment == "Médico" || employment == "Atendente")
            {
                cout<<"Contas com essa função só podem ser criadas por gerentes.\nPor favor, digite a função do funcionário: ";
                cin>>employment;
            }
            else
            {
                k = false;
            }
        }
        
        cout<<"Conta criada.\n";

        return new EmplProfile::EmplProfile(pass, login, name, employment);
    }

    //Autenticação de usuário
    bool EmplProfile::auth(string pass){
        //cout<<"Senha contest\n"<< "'"<<pass<<"' vs '"<<password<<"'\n";
        return (pass == this->password);
    }

    //Wrapper de consulta aos mapas de informações.
    string EmplProfile::getField(string field)
    {
        if(info.find(field) != info.end())
        {
            return info[field];
        }
        else
        {
            return "Desconhecido";
        }
    }

    //Listagem de ações para este funcionário
    string EmplProfile::actionList()
    {
        return "\n0 - Deslogar\n1 - Ver sua agenda\n2 - Ver suas informações\n";
    }

    void 

}
