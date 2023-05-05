#include <iostream>
#include <map>
#include <vector>
#include "header.h"
#include <boost\filesystem.hpp>
#include <string>
#include "misc_functions.cpp"


using namespace std;
using namespace management;


void initializeDatabase(std::vector<management::EmplProfile*>& out, vector<string>& logins)
{
  for (const auto& entry : filesystem::directory_iterator("./database/info/")) 
  {
      if (entry.is_regular_file()) 
      {
        string name = entry.path().filename().string();
        
        map<string, string> info;
        map<string, string> schedule;
        EmplProfile * employee;
        recoverMap(info, "./database/info/" + name);
        if(info["Emprego"] == "Gerente")
        {
          employee = new ManagerProfile(info["Senha"], info["Login"], info["Nome"], info[Emprego], out);
        }
        else if (info["Emprego"] == "Atendente")
        {
         employee = new AccProfile(info["Senha"], info["Login"], info["Nome"], info[Emprego]);
        }
        else
        {
          employee = new EmplProfile(info["Senha"], info["Login"], info["Nome"], info[Emprego]);
        }
      
        recoverMap(employee->schedule, "./database/schedule/" + name);
        recoverMap(employee->info, "./database/info/" + name);
        (employee->info).erase("Senha");
        out.push_back(employee);
        logins.push_back(name.substr(0, field.find(".")));
      } 
  }
}


int main()
{
    cout<<"\nIniciando Sistema"<<endl;
    vector<management::EmplProfile*> accounts;
    vector<string> logins;
    initializeDatabase(accouts, logins);
  	cout<<"\nSistema Online!"<<endl;
    if(accounts.size() == 0) cout<< " Iniciando o primeiro acesso."<<endl;

  	    ManagerProfile m = ManagerProfile::Create(logins, accounts);
  	accounts.push_back(&m);

  	EmplProfile *logedAs;
  	string status = "deslogado";
  	string tray;

    //Loop padrão do sistema
  	while(true)
  	{
  		cout<<"\nVocê está atualmente " << status << ".\n";

      //Opções caso deslogado
  		if(status == "deslogado")
  		{
  			cout<<"Selecione a sua ação\n0 - Criar uma nova conta\n1 - Logar numa conta existente\n";
  			cin>>tray;

        //Criar nova conta
  			if(tray == "0")
  			{
  				EmplProfile *e = new EmplProfile(); 
          accounts.push_back(e);
  			}

        //Logar numa conta
  			else if(tray == "1")
  			{
  				cout<<"Insira o nome de usuário ";
  				cin>>tray;
          ManagerProfile* manager = dynamic_cast<ManagerProfile*>(accounts[0]);
          if(manager != nullptr)
          {
            int x = (*manager).searchByLogin(accounts, tray);
            cout<<"Insira a senha ";
            cin>>tray;
            if(x != -1){
              if((*(accounts[x])).auth(tray)){
                logedAs = accounts[x];
                cout<<"Logado com sucesso! Olá, " << (*logedAs).info["Nome"]<<endl;
                status = "logado como " + (*logedAs).info["Login"];

              }else{cout<<"Informações de entrada não reconhecidas.\n" << "p<<" << tray<< ">>";}
            }else {cout<<"Informações de entrada não reconhecidas.\n"<< "u<<" << tray<< ">>";}
          }
          else{cout<<"Ocorreu um erro: referência à conta de gerente é nula.\n";}
  				
  			}else{cout<<"Ação inválida. Tente novamente.\n";}
  		}

      //Opções caso logado:
  		else
  		{

  			cout<<"Você pode executar as seguintes ações:"<<(*logedAs).actionList(); //Mostra as opções de acordo com o tipo de conta
  			cin>>tray;

        //Deslogar
  			if(tray == "0")
  			{
  				cout<<"Deslogando.\n";
  				status = "deslogado";
          logedAs = nullptr;
  			}


        //Mostrar agenda
  			else if(tray == "1")
  			{
          cout<<"Imprimindo agenda\n";
          printMap<string, string>((*logedAs).schedule);
  				
  			}
        
        //Mostrar informações básicas
  			else if(tray == "2")
  			{
  				cout<<"Imprimindo informações\n";
          printMap<string, string>((*logedAs).info);
  			}

        //Mostrar todas as especialidades (Acesso superior)
  			else if(tray == "3")
  			{
          UppProfile* upperUser = dynamic_cast<UppProfile*>(logedAs);
          if(upperUser != nullptr){
    				cout<<"Imprimindo especialidades disponíveis\n";
    				printMap<string, int>((*upperUser).getSpecialities(accounts));
          }else{cout<<"Ocorreu um erro: a opção selecionada está limitada à contas de acesso superior.\n";}
  			}

        //Mostrar o nome de todos os médicos (Acesso superior)
  			else if(tray == "4")
  			{
          UppProfile* upperUser = dynamic_cast<UppProfile*>(logedAs);
          if(upperUser != nullptr){
    				cout<<"Imprimindo todos os médicos\n";
  				  vector<EmplProfile> v = (*upperUser).searchByEmployment(accounts, "Médico");
    				for(int i = 0; i < v.size(); i ++)
  			    {
  			        cout<< v[i].getField("Nome") << ":-:"<< v[i].getField("Especialidade") << endl;
            }
          }else{cout<<"Ocorreu um erro: a opção selecionada está limitada à contas de acesso superior.\n";}
  			}

        //Mostrar agenda de um funcionário (Acesso superior)
  			else if(tray == "5")
  			{
          UppProfile* upperUser = dynamic_cast<UppProfile*>(logedAs);
          if(upperUser != nullptr)
          {
            cout<<"Insira o nome do funcionário\n";
            cin>>tray;
            (*upperUser).showEmplSchedule(accounts, tray);
          }else{cout<<"Ocorreu um erro: a opção selecionada está limitada à contas de acesso superior.\n";}	
  			}

        else if(tray == "6")
        {

          //Marcar consulta para um médico (Acesso de atendente)
          AccProfile* accountant = dynamic_cast<AccProfile*>(logedAs);
          if(accountant != nullptr)
          {
            cout<<"Insira o nome do médico\n";
            cin>>tray;
            EmplProfile * func = accounts[ (*accountant).searchByName(accounts, tray) ]; 
            (*accountant).assignSchedule( *func );
          }

          //Adicionar um novo médico (Acesso de gerente)
          else
          {
            ManagerProfile* manager = dynamic_cast<ManagerProfile*>(logedAs);
            if(manager != nullptr)
            {
              (*manager).addFunc();
            }else{cout<<"Ocorreu um erro: a opção selecionada está limitada às contas de gerência.\n";} 
          }
        }

        //Editar informações de um funcionário (Acesso de gerente)
        else if(tray == "7")
        {

          ManagerProfile* manager = dynamic_cast<ManagerProfile*>(logedAs);
          if(manager != nullptr)
          {
            (*manager).editFunc();
          }else{cout<<"Ocorreu um erro: a opção selecionada está limitada às contas de gerência.\n";} 

        }

        //Remover um médico (Acesso de gerente)
        else if(tray == "8")
        {

          ManagerProfile* manager = dynamic_cast<ManagerProfile*>(logedAs);
          if(manager != nullptr)
          {
            (*manager).removeFunc();
          }else{cout<<"Ocorreu um erro: a opção selecionada está limitada às contas de gerência.\n";} 
        }
        else{cout<<"Operação inválida\n";}
  		}
  	}


}
