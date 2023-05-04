#include <iostream>
#include <map>
#include <vector>
#include <header.h>
#include <windows.h>

using namespace std;
using namespace management;



int main()
{
	cout<<"Iniciando o sistema\n";

	for(int i = 0; i < 15; i++)
	{
    cout<<"\r[";
    for(int j = 0; j < 15; j++)
    {
      if(i >= j)
      {
        cout<<"=";
      }
      else
      {
        cout<<" ";
      }
      
    }
    cout<<"]";
		Sleep(100);
	}
  	cout<<"\nSistema Online! Iniciando o primeiro acesso."<<endl;

  	std::vector<EmplProfile> accounts;

  	accounts.push_back(ManagerProfile(accounts));

  	EmplProfile logedAs;
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
  				if(tray == "0"){accounts.push_back(EmplProfile());}
  				else if(tray == "1"){accounts.push_back(AccProfile());}
  				else{cout<<"Ação inválida. Tente novamente.\n"}
  			}
  			else if(tray == "1")
  			{
  				cout<<"Insira o nome de usuário"
  				cin>>tray;
  				int x = accounts[0].SearchByName(tray, accounts);
  				cout<<"Insira a senha"
  				cin>>tray;
  				if(x != -1){
  					if(accounts[x].auth(tray)){
  						logedAs = accounts[x];
  						cout<<"Logado com sucesso! Olá, " << logedAs.info["Nome"]<<endl;
  						status = "logado como " + logedAs.info["Login"];

  					}else{cout<<"Informações de entrada não reconhecidas.\n";}
  				}else {cout<<"Informações de entrada não reconhecidas.\n";}
  			}else{cout<<"Ação inválida. Tente novamente.\n"}
  		}
  		else
  		{
  			cout<<"Você pode executar as seguintes ações:"<<logedAs.actionList();
  			cint>>tray;

  			if(tray == "0")
  			{
  				cout<<"Deslogando.\n";
  				status = "deslogado";
  			}
  			else if(tray == "1")
  			{
  				cout<<"Imprimindo informações\n";
  				printMap<string, string>(logedAs.info):
  			}
  			else if(tray == "2")
  			{
  				cout<<"Imprimindo agenda\n";
  				printMap<string, date>(logedAs.schedule):
  			}
  			else if(tray == "3")
  			{
  				cout<<"Imprimindo especialidades disponíveis\n";
  				printMap<string, int>(logedAs.schedule):
  			}
  			else if(tray == "4")
  			{
  				cout<<"Imprimindo especialidades disponíveis\n";
  				vector<EmplProfile> v = logedAs.searchByEmployment("Médico"):
  				for(int i = 0; i < v.size(); i ++)
			    {
			        cout<< v[i]["Especialidade"] << endl;
			    }
  			}
  			else if(tray == "5")
  			{
  				cout<<"Insira o nome do funcionário\n";
  				cin>>tray;
  				logedAs.showEmplSchedule(accounts[tray]);
  			}
  		}
  	}


}