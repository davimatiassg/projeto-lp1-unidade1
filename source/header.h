#ifndef HOSPITAL_MANAGEMENT
#define HOSPITAL_MANAGEMENT
#include "misc_functions.cpp"

using date = string;


namespace management
{

    //Classe básica para perfis de funcionários gerais (médicos, enfermeiros e afins).
    class EmplProfile{
    protected:
        //Senha da conta
        string password;
    public:
        //Agenda do funcionário
        map<string, date> schedule;
        //Informações adicionais (Nome, Login, Profissão, Documentação...)
        map<string, string> info;     
        //Construtor
        EmplProfile();
        //Autenticação de usuário
        bool auth(string pass);
        //Wrapper de consulta aos mapas de informações.
        string getField(string field);
        //Listagem de ações para este funcionário
        virtual string actionList();
    };

    //Classe base para contas com acesso administrativo, como atendentes e gerentes.
    class UppProfile: public EmplProfile{
    public:
        //Ver todas as especialidades médicas e a quantidade de profissionais para cada uma.
        map<string, int> getSpecialities(vector<EmplProfile> employees);
        //Retornar um vetor com todos os médicos dentre os funcionários cadastrados.
        vector<EmplProfile> searchByEmployment(vector<EmplProfile> employees, string employment);
        //Pesquisar um empregado pelo nome e retornar o seu índice no vetor de empregados.
        int searchByName(string name, vector<EmplProfile> employees);
        //Mostra na tela a agenda de um funcionário.
        void showEmplSchedule(string name, vector<EmplProfile> employees);
        //Listar as ações dessa conta.
        virtual string actionList() override;
    };

    //Classe para contas de atendente
    class AccProfile: public UppProfile
    {
    public:
        //Marcar um compromisso na agenda de um médico
        void assignSchedule(EmplProfile medic);
        //Listar as ações dessa conta.
        string actionList() final;
    };

    //Classe para contas de gerentes
    class ManagerProfile: public UppProfile {
    private:
        //Vetor de Empregados
        vector<EmplProfile>& employees;
    public:
        //Construtor
        ManagerProfile(vector<EmplProfile>& emp) : UppProfile(), employees(emp);
        //Adicionar um médico à equipe
        void addMedic();
        //Editar informações de um médico, inclusive sua especialidade
        void editMedic();
        //Remover um médico da equipe
        void removeMedic();
        //Listar as ações dessa conta.
        string actionList() final;
    };

}



#endif