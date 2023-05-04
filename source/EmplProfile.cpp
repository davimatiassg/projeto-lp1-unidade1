#include <iostream>
#include <map>
#include <vector>
#include <header.h>
using namespace std;
using namespace management;

//Classe básica, contém componentes do perfil de qualquer usuário.
class EmplProfile {

protected: 
    string password; //Senha da conta
public:
    
    map<string, date> schedule;  //Agenda do funcionário
    map<string, string> info;       //Informações adicionais
    
    
    EmplProfile()
    {
        cout<<"Criando um novo perfil.\nDigite o nome de usuário: ";
        string tray;
        cin>>tray;
        
        this->info.insert(make_pair("Login", tray));
        
        while(true)
        {
            string passW[2];
            cout<<"Digite a sua senha: ";
            cin>>passW[0];
            cout<<"Confirme a senha: ";
            cin>>passW[1];
            if(passW[0] == passW[1])
            {
                this->password = passW[0];
                break;
            }
            else
            {
                cout<<"As senhas devem ser iguais!\n";
            }
        }
        cout<<"Digite o nome do funcionário: ";
        cin>>tray;
        info.insert(make_pair("Nome", tray));

        cout<<"Digite a função do funcionário: ";
        cin>>tray;
        info.insert(make_pair("Emprego", tray));
        if(tray == "Médico")
        {
            cout<<"Digite a especialidade do médico: ";
            cin>>tray;
            info.insert(make_pair("Especialidade", tray));
        }
    }

    //Autenticação de usuário
    bool auth(string pass){
        return (pass == this->password);
    }

    //Wrapper de consulta aos mapas de informações.
    string getField(string field)
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
    virtual string actionList()
    {
        return "\n0 - Deslogar\n1 - Ver sua agenda\n2 - Ver suas informações\n";
    }
};
