#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


int cont_id_tarefa = 0, cont_vet_tar = 0;
char user_operacao,  final;

// limpar tela 
void limpar_tela() {
    for (int i = 0; i < 50; i++) printf("\n");
}

//pausa para final de operacoes 
void pausa() {
    printf("Pressione Enter para continuar...\n");
    getchar();
}

//MENU PRINCIPAL DO SISTEMA  
void menu(){
    char buffer[10];
    printf("==========[SISTEMA DE GERENCIAMENTO DE TAREFAS]=========\n");
    printf("            Selecione a operacao desejada:\n");
    printf("              1 - Adicionar uma tarefa.\n");
    printf("              2 - Exibir lista de tarefas.\n");
    printf("              3 - Editar tarefa da lista.\n");
    printf("              4 - Finalizar sistema.\n");
    printf("obs; Caso queira marca uma tarefa como concuida ou edita-la\n          selecione a operacao de 'Exibir tarefa'\n");
    printf("=======================================================\n");
    
    fgets(buffer, sizeof(buffer), stdin);
    user_operacao = buffer[0];
    
    limpar_tela(); 
}

//ESTRUTURA DE ADICIONAR TAREFA
typedef struct{
    int id;
    char titulo[90];
    char descricao[90];
    int dia;
    int mes;
    int ano;
    char status[90];
}adicionar_tarefa;

//CRIANDO VETOR PARA GUARDA TAREFAS
adicionar_tarefa lista_tarefas[100];


//FUNÇÃO PARA CRIAR TAREFAS
void criar_tarefa(){
    adicionar_tarefa *a_t = &lista_tarefas[cont_vet_tar];
    
    cont_id_tarefa++;
    a_t->id = cont_id_tarefa; 
    printf("Insira as informacoes solicitadas\n");
    printf("\nId da tarefa: %d\n", cont_id_tarefa);
    
    
    printf("\nTitulo da tarefa: \n"); 
    fgets(a_t->titulo, sizeof(a_t->titulo), stdin);
    a_t->titulo[strcspn(a_t->titulo, "\n")] = '\0';
    
    printf("\nInsira uma descricao da sua tarefa: \n");
    fgets(a_t->descricao, sizeof(a_t->descricao), stdin);
    a_t->descricao[strcspn(a_t->descricao, "\n")] = '\0';
    
    
    printf("\nDefina uma data para sua tarefa \nOBS:Digite nesse formato, incluindo os tarssos(DD-MM-YYYY): \n");
    scanf("%d-%d-%d", &a_t->dia, &a_t->mes, &a_t->ano);
    
    
    printf("\nAdicione o status de sua tarefa: \n");
    while (getchar() != '\n'); 
    fgets(a_t->status, sizeof(a_t->status), stdin);
    a_t->status[strcspn(a_t->status, "\n")] = '\0';

    cont_vet_tar++;

    limpar_tela();

    printf("Tarefa adicionada com sucesso!!\n");
    pausa();
    limpar_tela();
}

//FUNÇÃO PARA EXIBIR TAREFAS 
void exibir_tarefa(){
    if(cont_vet_tar==0){
        printf("Nenhuma tarefa foi adicionada\n");
        pausa();
    }else{
        printf("TAREFAS CADASTRADA;\n");
        for (int i = 0; i < cont_vet_tar; i++)
        {
            
            printf("ID: %d\n", lista_tarefas[i].id);
            printf("Titulo:: %s\n", lista_tarefas[i].titulo);
            printf("Descrição: %s\n", lista_tarefas[i].descricao);
            printf("Data: %d-%d-%d\n", lista_tarefas[i].dia, lista_tarefas[i].mes, lista_tarefas[i].ano);
            printf("Status: %s\n", lista_tarefas[i].status);
            printf("---------------------------------------------\n");
        }
        printf("Para sair digite 's'");
        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);
        final = buffer[0];
    }
    limpar_tela();
}

//FUNÇÃO PARA EDITAR TAREFAS 
void editar_tarefa() {
    int ident_id, posicao = -1, operacao, operacao_editar;
    adicionar_tarefa *a_t;

    if (cont_vet_tar == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        pausa();
        limpar_tela();
        return;
    }

    printf("Digite o ID da sua tarefa:\n");
    scanf("%d", &ident_id);
    getchar(); 

    for (int i = 0; i < cont_vet_tar; i++) {
        if (ident_id == lista_tarefas[i].id) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        limpar_tela();
        printf("Tarefa não encontrada\n");
        pausa();
        limpar_tela();
        
        return;
    }

    a_t = &lista_tarefas[posicao];

    limpar_tela();
    printf("Tarefa encontrada:\n");
    printf("ID: %d\n", a_t->id);
    printf("Título: %s\n", a_t->titulo);
    printf("Descrição: %s\n", a_t->descricao);
    printf("Data: %02d-%02d-%04d\n", a_t->dia, a_t->mes, a_t->ano);
    printf("Status: %s\n", a_t->status);
    printf("---------------------------------------------\n");

    printf("Qual operação deseja fazer?\n");
    printf("1 - Excluir tarefa\n");
    printf("2 - Editar tarefa\n");
    scanf("%d", &operacao);
    getchar();

    if (operacao == 1) {
        for (int i = posicao; i < cont_vet_tar - 1; i++) {
            lista_tarefas[i] = lista_tarefas[i + 1];
        }
        cont_vet_tar--;
        limpar_tela();
        printf("Tarefa excluída com sucesso!\n");
        pausa();
    } else if (operacao == 2) {
        limpar_tela();
        printf("Informe o que deseja alterar:\n");
        printf("1 - Título\n2 - Descrição\n3 - Data\n4 - Status\n");
        scanf("%d", &operacao_editar);
        getchar();

        switch (operacao_editar) {
            case 1:
                limpar_tela();
                printf("Novo título:\n");
                fgets(a_t->titulo, sizeof(a_t->titulo), stdin);
                a_t->titulo[strcspn(a_t->titulo, "\n")] = '\0';
                break;
            case 2:
                limpar_tela();
                printf("Nova descrição:\n");
                fgets(a_t->descricao, sizeof(a_t->descricao), stdin);
                a_t->descricao[strcspn(a_t->descricao, "\n")] = '\0';
                break;
            case 3:
                limpar_tela();
                printf("Nova data (DD-MM-YYYY):\n");
                scanf("%d-%d-%d", &a_t->dia, &a_t->mes, &a_t->ano);
                getchar();
                break;
            case 4:
                limpar_tela();
                printf("Novo status:\n");
                fgets(a_t->status, sizeof(a_t->status), stdin);
                a_t->status[strcspn(a_t->status, "\n")] = '\0';
                break;
            default:
                limpar_tela();
                printf("Operação inválida\n");
                pausa();
                return;
        }
        limpar_tela();
        printf("Tarefa editada com sucesso!\n");
        pausa();
    } else {
        printf("Operação inválida\n");
        pausa();
    }

    limpar_tela();
}



int main(){
    setlocale(LC_ALL, "Portuguese_Brazil.1252");


    do
    {
        menu();
        switch (user_operacao)
        {
        case '1':
            criar_tarefa();
            break;

        case '2':
            exibir_tarefa();
            break;
        
        case '3':
            editar_tarefa();
            break;
        case '4':
            return 0;
        default:
            printf("OPERÇÃO INVALIDA\n");
            pausa();
            limpar_tela();
            break;
        }
    } while ( user_operacao != '4' );
    
    

    


    return 0;
}