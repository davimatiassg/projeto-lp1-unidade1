#include <iostream>
#include <map>
#include <vector>
#include "header.h"

#include <string>
//#include <windows.h>

using namespace std;
using namespace management;



int main()
{
  	cout<<"\nSistema Online! Iniciando o primeiro acesso."<<endl;

  	std::vector<management::EmplProfile*> accounts;
    ManagerProfile m = ManagerProfile(accounts);
  	accounts.push_back(&m);

  	EmplProfile *logedAs;
  	string status = "deslogado";
  	string tray;
  	while(true)
  	{
  		cout<<"\nVocê está atualmente " << status << ".\n";
  		if(status == "deslogado")
  		{
  			cout<<"Selecione a sua ação\n0 - Criar uma nova conta\n1 - Logar numa conta existente";
  			cin>>tray;
  			if(tray == "0")
  			{
  				cout<<"Selecione o tipo de conta:\n0 - Conta de funcionário\n1 - Conta de atendente";
  				cin>>tray;
          
  				if(tray == "0"){EmplProfile *e = new EmplProfile(); accounts.push_back(e);}
  				else if(tray == "1"){AccProfile *a = new AccProfile(); accounts.push_back(a);}
  				else{cout<<"Ação inválida. Tente novamente.\n";}
  			}
  			else if(tray == "1")
  			{
  				cout<<"Insira o nome de usuário";
  				cin>>tray;
          ManagerProfile* manager = dynamic_cast<ManagerProfile*>(accounts[0]);
          if(manager != nullptr)
          {
            int x = (*manager).searchByName(accounts, tray);
            cout<<"Insira a senha";
            cin>>tray;
            if(x != -1){
              if((*(accounts[x])).auth(tray)){
                logedAs = accounts[x];
                cout<<"Logado com sucesso! Olá, " << (*logedAs).info["Nome"]<<endl;
                status = "logado como " + (*logedAs).info["Login"];

              }else{cout<<"Informações de entrada não reconhecidas.\n";}
            }else {cout<<"Informações de entrada não reconhecidas.\n";}
          }
          else{cout<<"Ocorreu um erro: referência à conta de gerente é nula.\n";}
  				
  			}else{cout<<"Ação inválida. Tente novamente.\n";}
  		}
  		else
  		{
  			cout<<"Você pode executar as seguintes ações:"<<(*logedAs).actionList();
  			cin>>tray;

  			if(tray == "0")
  			{
  				cout<<"Deslogando.\n";
  				status = "deslogado";
  			}
  			else if(tray == "1")
  			{
  				cout<<"Imprimindo informações\n";
  				printMap<string, string>((*logedAs).info);
  			}
  			else if(tray == "2")
  			{
  				cout<<"Imprimindo agenda\n";
  				printMap<string, date>((*logedAs).schedule);
  			}
  			else if(tray == "3")
  			{
          UppProfile& upperUser = dynamic_cast<UppProfile&>((*logedAs));
          if(upperUser != nullptr){
    				cout<<"Imprimindo especialidades disponíveis\n";
    				printMap<string, int>((*upperUser).getSpecialities(accounts));
          }else{cout<<"Ocorreu um erro: a opção selecionada está limitada à contas de acesso superior.\n";}
  			}
  			else if(tray == "4")
  			{
          UppProfile& upperUser = dynamic_cast<UppProfile&>((*logedAs));
          if(upperUser != nullptr){
    				cout<<"Imprimindo especialidades disponíveis\n";
  				  vector<EmplProfile> v = (*upperUser).searchByEmployment(accounts, "Médico");
    				for(int i = 0; i < v.size(); i ++)
  			    {
  			        cout<< v[i].getField("Especialidade") << endl;
            }
          }else{cout<<"Ocorreu um erro: a opção selecionada está limitada à contas de acesso superior.\n";}
  			}
  			else if(tray == "5")
  			{
          UppProfile& upperUser = dynamic_cast<UppProfile&>((*logedAs));
          if(upperUser != nullptr)
          {
            cout<<"Insira o nome do funcionário\n";
            cin>>tray;
            (*upperUser).showEmplSchedule(accounts, tray);
          }else{cout<<"Ocorreu um erro: a opção selecionada está limitada à contas de acesso superior.\n";}	
  			}
        else if(tray == "6")
        {
          UppProfile& accountant = dynamic_cast<AccProfile&>((*logedAs));
          if(accountant != nullptr)
          {
            cout<<"Insira o nome do funcionário\n";
            cin>>tray;
            (*accountant).showEmplSchedule((*accountant).searchByName(accounts, tray));
          }else{cout<<"Ocorreu um erro: a opção selecionada está limitada às contas de atendentes.\n";}

          ManagerProfile& manager = dynamic_cast<ManagerProfile&>((*logedAs));
          if(manager != nullptr)
          {
            (*manager).addMedic();
          }else{cout<<"Ocorreu um erro: a opção selecionada está limitada às contas de gerência.\n";} 
        }
        else if(tray == "7")
        {

          ManagerProfile& manager = dynamic_cast<ManagerProfile&>((*logedAs));
          if(manager != nullptr)
          {
            (*manager).editMedic();
          }else{cout<<"Ocorreu um erro: a opção selecionada está limitada às contas de gerência.\n";} 

        }
        else if(tray == "8")
        {

          ManagerProfile& manager = dynamic_cast<ManagerProfile&>((*logedAs));
          if(manager != nullptr)
          {
            (*manager).removeMedic();
          }else{cout<<"Ocorreu um erro: a opção selecionada está limitada às contas de gerência.\n";} 
        }
        else{cout<<"Operação inválida\n";}
  		}
  	}


}
