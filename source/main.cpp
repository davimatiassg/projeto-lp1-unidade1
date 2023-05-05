#include <iostream>
#include <map>
#include <vector>
#include "header.h"
#include <filesystem>
#include <string>
#include "misc_functions.cpp"


using namespace std;
using namespace management;


void initializeDatabase(std::vector<management::EmplProfile*>& out, vector<string>& logins)
{
  for (const auto& entry : filesystem::directory_iterator("./database/info/")) 
  {
    string name = entry.path().filename().string();
    map<string, string> info;
    map<string, string> schedule;
    recoverMap<string, string>(&info, "./database/info/" + name);
    EmplProfile * employee;
    if(info["Emprego"] == "Gerente")
    {
       employee = new ManagerProfile(info["Senha"], info["Login"], info["Nome"], info["Emprego"], out);
    }
    else if (info["Emprego"] == "Atendente")
    {
     employee = new AccProfile(info["Senha"], info["Login"], info["Nome"], info["Emprego"]);
    }
    else
    {
      employee = new EmplProfile(info["Senha"], info["Login"], info["Nome"], info["Emprego"]);
    }
    recoverMap<string, string>(&(employee->schedule), "./database/schedule/" + name);
    recoverMap<string, string>(&(employee->info), "./database/info/" + name);
    (employee->info).erase("Senha");
    out.push_back(employee);
    logins.push_back(name.substr(0, name.find(".")));
    
  }
}


int main()
{
    cout<<"\nIniciando Sistema"<<endl;
    vector<management::EmplProfile*> accounts;
    vector<string> logins;
    initializeDatabase(accounts, logins);
    cout<<accounts.size()<<" Contas cadastradas\n";
  	cout<<"\nSistema Online!"<<endl;
    if(accounts.size() == 0)
    { 
      cout<< " Iniciando o primeiro acesso."<<endl;
    	ManagerProfile * m = ManagerProfile::Create(accounts, logins);
    	accounts.push_back(m);
    }

  	EmplProfile *logedAs;
  	string status = "deslogado";
  	string tray;

    //Loop padrao do sistema
  	while(true)
  	{
  		cout<<"\nVoce esta atualmente " << status << ".\n";

      //Opcoes caso deslogado
  		if(status == "deslogado")
  		{
  			cout<<"Selecione a sua acao\n0 - Criar uma nova conta\n1 - Logar numa conta existente\n2 - Fechar o sistema";
  			cin>>tray;

        //Criar nova conta
  			if(tray == "0")
  			{
  				EmplProfile *e = EmplProfile::Create(logins); 
          accounts.push_back(e);
  			}

        //Logar numa conta
  			else if(tray == "1")
  			{
  				cout<<"Insira o nome de usuario ";
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
                cout<<"Logado com sucesso! Ola, " << (*logedAs).info["Nome"]<<endl;
                status = "logado como " + (*logedAs).info["Login"];

              }else{cout<<"Informacoes de entrada nao reconhecidas.\n" << "p<<" << tray<< ">>";}
            }else {cout<<"Informacoes de entrada nao reconhecidas.\n"<< "u<<" << tray<< ">>";}
          }
          else{cout<<"Ocorreu um erro: referencia a conta de gerente e nula.\n";}
  				
  			}else if (tray == "2")
        {
          for(int i = 0; i < accounts.size(); i++)
          {
            accounts[i]->Save();
          }
          break;
        }
  		}

      //Opcoes caso logado:
  		else
  		{

  			cout<<"Voce pode executar as seguintes acoes:"<<(*logedAs).actionList(); //Mostra as opcoes de acordo com o tipo de conta
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
        
        //Mostrar informacoes basicas
  			else if(tray == "2")
  			{
  				cout<<"Imprimindo informacoes\n";
          printMap<string, string>((*logedAs).info);
  			}

        //Mostrar todas as especialidades (Acesso superior)
  			else if(tray == "3")
  			{
          UppProfile* upperUser = dynamic_cast<UppProfile*>(logedAs);
          if(upperUser != nullptr){
    				cout<<"Imprimindo especialidades disponiveis\n";
    				printMap<string, int>((*upperUser).getSpecialities(accounts));
          }else{cout<<"Ocorreu um erro: a opcao selecionada esta limitada a contas de acesso superior.\n";}
  			}

        //Mostrar o nome de todos os medicos (Acesso superior)
  			else if(tray == "4")
  			{
          UppProfile* upperUser = dynamic_cast<UppProfile*>(logedAs);
          if(upperUser != nullptr){
    				cout<<"Imprimindo todos os medicos\n";
  				  vector<EmplProfile> v = (*upperUser).searchByEmployment(accounts, "Medico");
    				for(int i = 0; i < v.size(); i ++)
  			    {
  			        cout<< v[i].getField("Nome") << ":-:"<< v[i].getField("Especialidade") << endl;
            }
          }else{cout<<"Ocorreu um erro: a opcao selecionada esta limitada a contas de acesso superior.\n";}
  			}

        //Mostrar agenda de um funcionario (Acesso superior)
  			else if(tray == "5")
  			{
          UppProfile* upperUser = dynamic_cast<UppProfile*>(logedAs);
          if(upperUser != nullptr)
          {
            cout<<"Insira o nome do funcionario\n";
            cin>>tray;
            (*upperUser).showEmplSchedule(accounts, tray);
          }else{cout<<"Ocorreu um erro: a opcao selecionada esta limitada a contas de acesso superior.\n";}	
  			}

        else if(tray == "6")
        {

          //Marcar consulta para um medico (Acesso de atendente)
          AccProfile* accountant = dynamic_cast<AccProfile*>(logedAs);
          if(accountant != nullptr)
          {
            cout<<"Insira o nome do medico\n";
            cin>>tray;
            EmplProfile * func = accounts[ (*accountant).searchByName(accounts, tray) ]; 
            accountant->assignSchedule( *func );
          }

          //Adicionar um novo medico (Acesso de gerente)
          else
          {
            ManagerProfile* manager = dynamic_cast<ManagerProfile*>(logedAs);
            if(manager != nullptr)
            {
              (*manager).addFunc(logins);
            }else{cout<<"Ocorreu um erro: a opcao selecionada esta limitada as contas de gerencia.\n";} 
          }
        }

        //Editar informacoes de um funcionario (Acesso de gerente)
        else if(tray == "7")
        {

          ManagerProfile* manager = dynamic_cast<ManagerProfile*>(logedAs);
          if(manager != nullptr)
          {
            (*manager).editFunc();
          }else{cout<<"Ocorreu um erro: a opcao selecionada esta limitada as contas de gerencia.\n";} 

        }

        //Remover um medico (Acesso de gerente)
        else if(tray == "8")
        {

          ManagerProfile* manager = dynamic_cast<ManagerProfile*>(logedAs);
          if(manager != nullptr)
          {
            (*manager).removeFunc();
          }else{cout<<"Ocorreu um erro: a opcao selecionada esta limitada as contas de gerencia.\n";} 
        }
        else{cout<<"Operacao invalida\n";}
  		}
  	}
  cout<<"Fechando o programa\n";
}
