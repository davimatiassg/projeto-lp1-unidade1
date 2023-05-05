#include <iostream>
#include <map>
#include <vector>
#include "header.h"
#include "misc_functions.cpp"
#include <fstream>

using namespace std;
using date = string;

namespace management{
    EmplProfile::EmplProfile(string pass, string login, string name, string employment)
    {
        this->password = pass;
        this->info.insert(make_pair("Login", login));
        this->info.insert(make_pair("Nome", name));
        this->info.insert(make_pair("Emprego", employment));
    }

    EmplProfile* EmplProfile::Create(vector<string> logins)
    {

        string login;
        string name;
        string employment;
        string pass;

        cout<<"Criando um novo perfil."<<endl;
        bool k = false;
        while(!k)
        {
            cout<<"Digite o nome de usuario: ";
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
        cout<<"Digite o nome do funcionario: ";
        cin>>name;

        cout<<"Digite a funcao do funcionario: ";
        cin>>employment;
        k = true;
        while(k)
        {
            if(employment == "Medico" || employment == "Atendente")
            {
                cout<<"Contas com essa funcao so podem ser criadas por gerentes.\nPor favor, digite a funcao do funcionario: ";
                cin>>employment;
            }
            else
            {
                k = false;
            }
        }
        
        cout<<"Conta criada.\n";
        EmplProfile * e = new EmplProfile(pass, login, name, employment);
        return e;
    }

    void EmplProfile::Save()
    {
        //.dss e um tipo de arquivo customizado. Significa "data storage sucks :("
        string n = this->info["Login"];
        ofstream file;
        saveMap<string, string>(this->info, "./database/info/" + n + ".dss");
        saveMap<string, date>(this->schedule , "./database/schedule/" + n + ".dss");
        file.open("./database/info/" + n + ".dss", fstream::app);
        file<<"Senha;"<<this->password<<endl;
       
    }

    //Autenticacao de usuario
    bool EmplProfile::auth(string pass){
        //cout<<"Senha contest\n"<< "'"<<pass<<"' vs '"<<password<<"'\n";
        return (pass == this->password);
    }

    //Wrapper de consulta aos mapas de informacoes.
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

    //Listagem de acoes para este funcionario
    string EmplProfile::actionList()
    {
        return "\n0 - Deslogar\n1 - Ver sua agenda\n2 - Ver suas informacoes\n";
    }

}
