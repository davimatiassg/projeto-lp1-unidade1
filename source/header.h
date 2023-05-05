#ifndef HOSPITAL_MANAGEMENT
#define HOSPITAL_MANAGEMENT

#include <string>
using namespace std; 

namespace management
{

    //Classe básica para perfis de funcionários gerais (médicos, enfermeiros e afins).
    class EmplProfile{
    private:
        //Senha da conta
        string password;
    public:
        //Agenda do funcionário
        map<string, string> schedule;//TODO
        //Informações adicionais (Nome, Login, Profissão, Documentação...)
        map<string, string> info;     
        //Construtor
        EmplProfile(string pass, string login, string name, string employment);
        //Método de Setup por usuário
        static EmplProfile* Create(vector<string> logins);
        //Autenticação de usuário
        bool auth(string pass);
        //Wrapper de consulta aos mapas de informações.
        string getField(string field);
        //Listagem de ações para este funcionário
        virtual string actionList();
        //Método para salvar os dados dessa conta
        virtual void Save();
        //Método de recuperação da conta após reinicialização

    };

    //Classe base para contas com acesso administrativo, como atendentes e gerentes.
    class UppProfile: public EmplProfile{
    public:
        //Construtor
        UppProfile(string pass, string login, string name, string employment);
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
        //Construtor
        AccProfile(string pass, string login, string name, string employment);
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
    
        //Construtor
        ManagerProfile(string pass, string login, string name, string employment, vector<EmplProfile*>& emp);
        //Método de Setup por usuário
        static ManagerProfile* Create(vector<EmplProfile*>& accs, vector<string> logins);
        //Adicionar um médico à equipe
        void addFunc(vector<string> logins);
        //Editar informações de um médico, inclusive sua especialidade
        void editFunc();
        //Remover um médico da equipe
        void removeFunc();
        //Listar as ações dessa conta.
        string actionList() final;
    };

}



#endif
