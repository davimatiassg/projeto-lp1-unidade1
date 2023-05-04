#include <iostream>
#include <map>
#include <vector>

using namespace std;

using date = string;


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
    }

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

    virtual string actionList()
    {
        return "1 - Ver sua agenda\n2 - Ver suas informações\n";
    }
};

class UppProfile: public EmplProfile
{
protected:
    map<string, int> GetSpecialities(vector<EmplProfile> employees)
    {
        map<string, int> specialities;

        for(int i = 0; i < employees.size(); i++)
        {
            if(employees[i].getField("Emprego") == "Médico")
            {
                string spec = employees[i].getField("Especialidade");
                if(spec != "Desconhecido")
                {
                    auto sp = specialities.find(spec);
                    if(sp == specialities.end())
                    {
                        specialities.insert(make_pair(spec, 1));
                    }
                    else
                    {
                        (*sp).second += 1;
                    }
                }
            }
        }
        return specialities;
    }

    vector<EmplProfile> GetMedics(vector<EmplProfile> employees)
    {
        vector<EmplProfile> medics;
        for(int i = 0; i < employees.size(); i++)
        {
            if(employees[i].getField("Emprego") == "Médico")
            {
                medics.push_back(employees[i]);
            }
        }
        return medics;
    }

    map<string, date> getMedicAgenda(EmplProfile medic)
    {
        if(medic.getField("Emprego") == "Médico")
        {
            return medic.schedule;
        }
        else
        {
            map<string, date> m;
            return m;
        }
    }

    int SearchByName(string name, vector<EmplProfile> employees)
    {
        for(int i = 0; i < employees.size(); i++)
        {
            if(employees[i].getField("Nome") == name)
            {
                return i;
            }
        }
        return -1;
    }

    virtual string actionList() override
    {
        string k = EmplProfile::actionList();
        k.append("3 - Pesquisar especialidades\n4 - Pesquisar médicos\n5 - Visualizar agenda de um médico\n");
        return k;
    }
};


class AccProfile: public UppProfile
{
public:
    void assignSchedule(EmplProfile medic)
    {
        string desc;
        date dt;
        cout<< "\nInsira a data da consulta: ";
        cin >> dt;
        cout<< "\nInsira a descrição da consulta";
        cin >> desc;
        string c = "Consulta: ";
        c.append(desc);
        medic.schedule.insert(make_pair(c, dt));
    }
    string actionList() final
    {
        string k = UppProfile::actionList();
        k.append("6 - Agendar uma consulta com um médico\n");
        return k;
    }
};

class ManagerProfile: public UppProfile
{
private:
    vector<EmplProfile>& employees;
public:
    ManagerProfile(vector<EmplProfile>& emp) : UppProfile(), employees(emp) 
    {
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
        int idx = SearchByName(mSel, employees);
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
    }

    void removeMedic()
    {
        string mSel;
        cout<<"\nDigite o nome do médico a ser editado:\n";
        cin>> mSel;
        int idx = SearchByName(mSel, employees);
        employees.erase(employees.begin() + idx);

    }
    string actionList() final
    {
        string k = UppProfile::actionList();
        k.append("6 - Adicionar um médico\n7 - Alterar a especialidade de um médico\n8 - Remover um médico\n");
        return k;
    }
};

int main()
{

}