#ifndef HOSPITAL_MANAGEMENT
#define HOSPITAL_MANAGEMENT

#include <string>
using namespace std; 
using date = string;

namespace management
{

    //Função geral para printar informações e agenda guardadas em mapa.
    template<typename T1, typename T2>
    void printMap(map<T1, T2> m)
    {
        for(typename map<T1, T2>::iterator it = m.begin(); it != m.end(); it++)
        {
            cout<<(*it).first << ": " << (*it).second << endl;
        }
    }

    //Classe básica para perfis de funcionários gerais (médicos, enfermeiros e afins).
    class EmplProfile{
    private:
        //Senha da conta
        string password;
    public:
        //Agenda do funcionário
        map<string, date> schedule;//TODO
        //Informações adicionais (Nome, Login, Profissão, Documentação...)
        map<string, string> info;     
        //Construtor
        EmplProfile(string pass, string login, string name, string employment);
        //Método de Setup por usuário
        virtual EmplProfile* Create(vector<string> logins);
        //Autenticação de usuário
        bool auth(string pass);
        //Wrapper de consulta aos mapas de informações.
        string getField(string field);
        //Listagem de ações para este funcionário
        virtual string actionList();
        //Método para salvar os dados dessa conta
        virtual void Save();
        //Método de recuperação da conta após reinicialização
        virtual void Reload();

    };

    //Classe base para contas com acesso administrativo, como atendentes e gerentes.
    class UppProfile: public EmplProfile{
    public:
        //Ver todas as especialidades médicas e a quantidade de profissionais para cada uma.
        map<string, int> getSpecialities(vector<EmplProfile*> employees);
        //Retornar um vetor com todos os médicos dentre os funcionários cadastrados.
        vector<EmplProfile> searchByEmployment(vector<EmplProfile*> employees, string employment);
        //Pesquisar um empregado pelo nome e retornar o seu índice no vetor de empregados.
        int searchByName(vector<EmplProfile*> employees, string name);
        //Pesquisar um empregado pelo nome de login e retornar o seu índice no vetor de empregados.
        int searchByLogin(vector<EmplProfile*> employees, string login);
        //Mostra na tela a agenda de um funcionário.
        void showEmplSchedule(vector<EmplProfile*> employees, string name);
        //Listar as ações dessa conta.
        virtual string actionList() override;
    };

    //Classe para contas de atendente
    class AccProfile: public UppProfile
    {
    public:
        //Método de Setup por usuário
        AccProfile* Create(vector<string> logins) final;//TODO
        //Marcar um compromisso na agenda de um médico
        void assignSchedule(EmplProfile medic);
        //Listar as ações dessa conta.
        string actionList() final;
    };

    //Classe para contas de gerentes
    class ManagerProfile: public UppProfile {
    private:
        //Vetor de Empregados
        vector<EmplProfile*>& employees;
    public:
        //Método de Setup por usuário
        ManagerProfile* Create(vector<string> logins) final;
        //Construtor
        ManagerProfile(vector<EmplProfile*>& emp);
        //Adicionar um médico à equipe
        void addMedic();
        //Editar informações de um médico, inclusive sua especialidade
        void editMedic();
        //Remover um médico da equipe
        void removeMedic();
        //Listar as ações dessa conta.
        string actionList() final;
        //Método para salvar os dados dessa conta
        void Save() final;//TODO
        //Método de recuperação da conta após reinicialização
        void Reload() final;//TODO
    };

}



#endif
