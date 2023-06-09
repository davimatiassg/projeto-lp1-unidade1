# Descrição do projeto

Este projeto foi realizado como requisito para obtenção de nota referente à matéria de LINGUAGENS DE PROGRAMAÇÃO 1, do curso de BACHARELADO EM TECNOLOGIA DA INFORMAÇÃO.
Consiste na emulação de um sistema básico para a gerência de um hospital. Cada um dos funcionários tem direito a criar uma conta, mas apenas atendentes e a conta de gerência possuem acesso à ações admnistrativas.

O projeto foi construido inteiramente utilizando C++, para o sistema Windows. Funcionalidade em demais S.O.'s não garantida.

## Instruções de compilação

Na pasta raiz do repositório, execute o seguinte comando para compilar o projeto:

```
g++ -o HospitalSystem.exe ./source/*.cpp
```
Em seguida, execute o arquivo pelo seguinte comando (ou abra-o como um aplicativo comum, na pasta do projeto)
```
HospitalSystem.exe
```
##Estrutura

O sistema separa os arquivos das contas dos usuários nas duas pastas encontradas no diretório "database". Uma das pastas contém informações sobre a conta, enqusnto a outra contém a agenda de cada usuário.

Os arquivos são salvos com a extensão customiada ".dss", que em nada difere de um arquivo de texto comum.
O nome de login e a senha são armazenados nesses arquivos (nos da pasta info). Os mesmos login e senha usados para acessar a conta.

Deletar o arquivo "./database/info/Gerente.dss" remove a conta de gerente do programa, o que faz com que a próxima inicialização dele ative, justamente, a criação de uma nova conta Gerente.


# Descrição da atividade


Suzyene é gestora de RH de uma grande rede de hospitais e deseja criar um sistema simplificado de visualização de médicos e suas especialidades.  O sistema deverá ter as seguintes características:

1.	Ter dois perfis de usuários habilitados para utilizar o sistema (atendentes e  gestores);

a.	O perfil de atendente deve ter um menu com as seguintes opções:
    
    i.	Listar todos os médicos por nome e suas respectivas funções;

    ii.	Listar todas as especialidades disponíveis e a quantidade de profissionais de cada uma;

    iii.	Agendar horário para um determinado médico (nome e dia/horário);

    iv.	Ver todos os agendamentos de uma determinado médico (pesquisar pelo nome);
  
b.	O perfil de gestor deverá ter uma senha de acesso (admin) para evitar que estranhos acessem informações indevidas e conter os seguintes itens de menu:
    
    i.	Listar todos os médicos por nome e suas respectivas funções;

    ii.	Listar todas as especialidades disponíveis e a quantidade de profissionais de cada uma;

    iii.	Adicionar um novo médico;

    iv.	Ver todos os agendamentos de uma determinado médico (pesquisar pelo nome);

    v.	Alterar a especialidade de um médico;

    vi.	Excluir um médico;

Para o projeto você deverá considerar os seguintes aspectos:
1.	Utilizar um arquivo para armazenar todos os médicos (nome do médico e sua especialidade);
2.	Utilizar um arquivo para armazenar todos os agendamentos (nome do médico e dia/horário da consulta (Esse último pode ser apenas uma string contendo as informações do dia e horário - ex: “terça - das 11h às 13h” );
3.	Utilizar pelo menos uma estrutura STL (vector, list, set, map, stack, queue);
4.	Utilizar a modularização do código (Arquivos .hpp e .cpp)
5.	Criar um código organizado e comentado.
6.	O arquivo deverá ser lidos sempre que o programa for inicializado para que as informações sejam retomadas;
7.	O arquivo que armazena os médicos e os agendamentos deverá conter pelo menos cinco elemento de cada salvos;
8.	Seu programa deverá ter um README (um arquivo externo explicado o funcionamento e as funcionalidades do seu sistema);
9.	Antes de finalizar o programa você deverá atualizar os arquivos para que as exclusões saiam do arquivo original. Você pode fazer isso sobrescrevendo o arquivo original e copiando para ele os dados carregados do programa (basta não utilizar a opção ios::app).

Esquema de pontuação do projeto:
1,5 pts - Utilizar corretamente arquivos (leitura e escrita);
1,0 pts - Utilizar corretamente estruturas STL (importação, criação e uso);
1,5 pts - Utilizar a modularização  (arquivos de corpo e de cabeçalho);
1,0 pts - Organização do código e comentários nas funções;
1,0 pts - Executando corretamente  (sem erros);

Total: 6,0 pts.
