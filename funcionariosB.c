/*
  Nome: Gabriel de Brito Abreu
  Disciplina: Estrutura de Dados - Prof. Rodney Carneiro
  Data: 20/10/2026
 
  Objetivo: programa de cadastro de funcionarios usando lista simplesmente
  encadeada. Da pra cadastrar (no inicio, no final ou numa posicao), remover,
  alterar e consultar. Os dados sao salvos no arquivo Funcionario.dat quando
  sai do programa (opcao 9) e carregados de novo quando o programa abre.
 
  Como compilar: gcc funcionarios.c -o funcionarios.exe
  (so funciona no Windows por causa do windows.h e do conio.h)
*/



#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
 
typedef struct {
 
    int cd_funcionario;
    char nm_funcionario[50];
    char endereco[50];
    char dt_nasc[10];
    char telefone[15];
    char cpf[15];
    char cargo[40];
    char depto[30];
    float salario;
 
}reg_funcionario;
 
typedef struct TipoItem *TipoApontador;
 
typedef struct TipoItem {
    reg_funcionario conteudo;
    TipoApontador proximo;
} TipoItem;
 
typedef struct {
    TipoApontador Primeiro;
    TipoApontador Ultimo;
} TipoLista;
 
 
 
 
 
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
 
void tela()
{
    int t;
    system("cls");
    gotoxy(01, 01);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(01, 02);
    printf("| UNICIVE");
    gotoxy(60, 02);
    printf("Estrutura de Dados |");
    gotoxy(01, 03);
    printf("|");
    gotoxy(20, 02);
    printf("SISTEMA DE GESTAO DE FUNCIONARIO");
    gotoxy(79, 03);
    printf("|");
    gotoxy(01, 04);
    printf("+-----------------------------------------------------------------------------+");
 
    for (t = 5; t < 24; t++)
    {
        gotoxy(01, t);
        printf("|");
        gotoxy(79, t);
        printf("|");
    }
 
    gotoxy(01, 22);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(02, 23);
    printf("MSG.:");
    gotoxy(01, 24);
    printf("+-----------------------------------------------------------------------------+");
}
 
int contar(TipoLista *L ) {
 
    int cont = 0;
    TipoApontador A = L->Primeiro;
 
 
    while (A != NULL){
        A = A->proximo;
        cont++;
    }
 
 
    return cont;
}
 
 
 
void limpaMSG(){
    gotoxy(2,23);
    printf("MSG.:                                                                        ");
    gotoxy(2,23);
}
 
int confirmar(){
    int resp = -1;
 
    do{
        limpaMSG();
        printf("Digite 1 para SALVAR ; 2 para CANCELAR ; 0 para VOLTAR.:");
        int ok = scanf("%d", &resp);
 
 
 
        char c = getchar();
        while (c != '\n') {
        c = getchar();
        }
 
        if (ok != 1){
            resp = -1;
        }
    }while (resp != 1  &&   resp != 2   && resp !=0);
 
 
    return resp;
}
 
 
/* Retorna 1 se ja existe funcionario com esse codigo na lista, 0 se nao existe */
int existeCodigo(TipoLista *L, int codigo){
 
    TipoApontador A = L->Primeiro;
 
    while (A != NULL){
        if (A->conteudo.cd_funcionario == codigo){
            return 1;
        }
        A = A->proximo;
    }
 
    return 0;
}
 
 
/* Le o codigo do novo funcionario e repete a pergunta ate o usuario
   digitar um numero valido que ainda nao esteja cadastrado */
int lerCodigo(TipoLista *L){
 
    int codigo = -1;
    int ok;
    int invalido;
 
    do{
        gotoxy(2, 8);
        printf("1 - Digite o codigo do Funcionario.............:                    ");
        gotoxy(2, 8);
        printf("1 - Digite o codigo do Funcionario.............: ");
        ok = scanf("%d", &codigo);
 
        char c = getchar();
        while (c != '\n') {
            c = getchar();
        }
 
        invalido = 0;
 
        if (ok != 1){
            limpaMSG();
            printf("MSG.:Codigo invalido! Pressione qualquer tecla.");
            getch();
            invalido = 1;
        } else if (existeCodigo(L, codigo)){
            limpaMSG();
            printf("MSG.:Ja existe funcionario com esse codigo! Pressione qualquer tecla.");
            getch();
            invalido = 1;
        }
 
    }while(invalido == 1);
 
    limpaMSG();
 
    return codigo;
}
 
 
void cadastroFinal(TipoLista *L) {
 
    tela();
    TipoApontador novo = (TipoApontador)malloc(sizeof(TipoItem));
 
 
    novo->conteudo.cd_funcionario = lerCodigo(L);
 
    gotoxy(2, 9);
    printf("2 - Digite o nome do funcionario...............: ");
    fgets(novo->conteudo.nm_funcionario, 50, stdin);
 
    gotoxy(2, 10);
    printf("3 - Digite o endereco do funcionario...........: ");
    fgets(novo->conteudo.endereco, 50, stdin);
 
    gotoxy(2, 11);
    printf("4 - Digite a data de nascimento do funcionario.: ");
    fgets(novo->conteudo.dt_nasc, 10, stdin);
 
    gotoxy(2, 12);
    printf("5 - Digite o telefone do funcionario...........: ");
    fgets(novo->conteudo.telefone,15, stdin);
 
    gotoxy(2, 13);
    printf("6 - Digite o CPF do funcionario................: ");
    fgets(novo->conteudo.cpf, 15, stdin);
 
    gotoxy(2, 14);
    printf("7 - Digite o cargo do funcionario..............: ");
    fgets(novo->conteudo.cargo, 40, stdin);
 
    gotoxy(2, 15);
    printf("8 - Digite o departamento do funcionario.......: ");
    fgets(novo->conteudo.depto, 30, stdin);
 
    gotoxy(2, 16);
    printf("9 - Digite o salario do funcionario............: ");
    scanf("%f", &novo->conteudo.salario);
    getchar();
 
 
    novo -> proximo = NULL;
 
 
    int resp = confirmar();
 
 
 
    if (resp == 1){
            if(L->Primeiro == NULL){
            L->Primeiro = novo;
            L->Ultimo = novo;
 
        } else {
            L->Ultimo->proximo = novo;
            L->Ultimo = novo;
        }
    } else {
        free(novo);
    }
 
}
 
 
void cadastroInicio(TipoLista *L){
    tela();
    TipoApontador novoInicio = (TipoApontador)malloc(sizeof(TipoItem));
 
    novoInicio->conteudo.cd_funcionario = lerCodigo(L);
 
    gotoxy(2, 9);
    printf("2 - Digite o nome do funcionario...............: ");
    fgets(novoInicio->conteudo.nm_funcionario, 50, stdin);
 
    gotoxy(2, 10);
    printf("3 - Digite o endereco do funcionario...........: ");
    fgets(novoInicio->conteudo.endereco, 50, stdin);
 
    gotoxy(2, 11);
    printf("4 - Digite a data de nascimento do funcionario.: ");
    fgets(novoInicio->conteudo.dt_nasc, 10, stdin);
 
    gotoxy(2, 12);
    printf("5 - Digite o telefone do funcionario...........: ");
    fgets(novoInicio->conteudo.telefone, 15, stdin);
 
    gotoxy(2, 13);
    printf("6 - Digite o CPF do funcionario................: ");
    fgets(novoInicio->conteudo.cpf, 15, stdin);
 
    gotoxy(2, 14);
    printf("7 - Digite o cargo do funcionario..............: ");
    fgets(novoInicio->conteudo.cargo, 40, stdin);
 
    gotoxy(2, 15);
    printf("8 - Digite o departamento do funcionario.......: ");
    fgets(novoInicio->conteudo.depto, 30, stdin);
 
    gotoxy(2, 16);
    printf("9 - Digite o salario do funcionario............: ");
    scanf("%f", &novoInicio->conteudo.salario);
    getchar();
 
 
    int resp = confirmar();
 
    if (resp == 1){
        novoInicio->proximo = L->Primeiro;
        L->Primeiro = novoInicio;
 
        if(L->Ultimo == NULL) {
            L->Ultimo = L->Primeiro;
        }
 
    } else {
        free(novoInicio);
    }
 
 
}
 
 
 
 
void cadastrarPosicao(TipoLista *L, int num){
 
    tela();
    int qtd = contar(L);
    if (num < 1 || num > qtd + 1) {
        gotoxy(8, 23);
        printf("Posicao invalida.");
 
        return;
    }
 
    if (num == 1){
        cadastroInicio(L);
 
        return;
    }
 
    if (num == qtd + 1){
        cadastroFinal(L);
 
        return;
    }
 
 
    TipoApontador cadPos = (TipoApontador)malloc(sizeof(TipoItem));
    TipoApontador p = L->Primeiro;
 
    cadPos->conteudo.cd_funcionario = lerCodigo(L);
 
    gotoxy(2, 9);
    printf("2 - Digite o nome do funcionario...............: ");
    fgets(cadPos->conteudo.nm_funcionario, 50, stdin);
 
    gotoxy(2, 10);
    printf("3 - Digite o endereco do funcionario...........: ");
    fgets(cadPos->conteudo.endereco, 50, stdin);
 
    gotoxy(2, 11);
    printf("4 - Digite a data de nascimento do funcionario.: ");
    fgets(cadPos->conteudo.dt_nasc, 10, stdin);
 
    gotoxy(2, 12);
    printf("5 - Digite o telefone do funcionario...........: ");
    fgets(cadPos->conteudo.telefone, 15, stdin);
 
    gotoxy(2, 13);
    printf("6 - Digite o CPF do funcionario................: ");
    fgets(cadPos->conteudo.cpf, 15, stdin);
 
    gotoxy(2, 14);
    printf("7 - Digite o cargo do funcionario..............: ");
    fgets(cadPos->conteudo.cargo, 40, stdin);
 
    gotoxy(2, 15);
    printf("8 - Digite o departamento do funcionario.......: ");
    fgets(cadPos->conteudo.depto, 30, stdin);
 
    gotoxy(2, 16);
    printf("9 - Digite o salario do funcionario............: ");
    scanf("%f", &cadPos->conteudo.salario);
    getchar();
 
 
 
    int resp = confirmar();
 
 
    if (resp == 1){
        for(int x= 1 ; x<= num -2 ;x++){
        p = p->proximo;
    }
 
 
    cadPos->proximo = p->proximo;
    p->proximo = cadPos;
 
    } else{
        free(cadPos);
    }
 
}
 
 
 
 
void removerInicio(TipoLista *L) {
 
 
    tela();
    if (L->Primeiro == NULL) {
        gotoxy(8, 23);
        printf("Lista vazia, nada para remover.");
        return;
    }
 
    gotoxy(2, 8);
    printf("Codigo do funcionario.............: %d\n", L->Primeiro->conteudo.cd_funcionario);
    gotoxy(2, 9);
    printf("Nome do funcionario...............: %s\n", L->Primeiro->conteudo.nm_funcionario);
    gotoxy(2, 10);
    printf("Endereco do funcionario...........: %s\n", L->Primeiro->conteudo.endereco);
    gotoxy(2, 11);
    printf("Data de nascimento do funcionario.: %s\n", L->Primeiro->conteudo.dt_nasc);
    gotoxy(2, 12);
    printf("Telefone do funcionario...........: %s\n", L->Primeiro->conteudo.telefone);
    gotoxy(2, 13);
    printf("CPF do funcionario................: %s\n", L->Primeiro->conteudo.cpf);
    gotoxy(2, 14);
    printf("Cargo do funcionario..............: %s\n", L->Primeiro->conteudo.cargo);
    gotoxy(2, 15);
    printf("Departamento do funcionario.......: %s\n", L->Primeiro->conteudo.depto);
    gotoxy(2, 16);
    printf("Salario do funcionario............: %.2f\n", L->Primeiro->conteudo.salario);
 
 
    int resp = confirmar();
 
 
    if (resp == 1){
        TipoApontador fumado = L->Primeiro;
        L->Primeiro = fumado->proximo;
 
        if (L->Primeiro == NULL) {
            L->Ultimo = NULL;
        }
        limpaMSG();
        printf("MSG.:Usuario removido!");
 
 
        free(fumado);
    }
 
}
 
 
void removerFinal(TipoLista *L){
 
    tela();
    if (L->Ultimo == NULL) {
        gotoxy(8, 23);
        printf("Lista vazia, nada para remover.");
        return;
    }
 
 
    gotoxy(2, 8);
    printf("Codigo do funcionario.............: %d\n", L->Ultimo->conteudo.cd_funcionario);
    gotoxy(2, 9);
    printf("Nome do funcionario...............: %s\n", L->Ultimo->conteudo.nm_funcionario);
    gotoxy(2, 10);
    printf("Endereco do funcionario...........: %s\n", L->Ultimo->conteudo.endereco);
    gotoxy(2, 11);
    printf("Data de nascimento do funcionario.: %s\n", L->Ultimo->conteudo.dt_nasc);
    gotoxy(2, 12);
    printf("Telefone do funcionario...........: %s\n", L->Ultimo->conteudo.telefone);
    gotoxy(2, 13);
    printf("CPF do funcionario................: %s\n", L->Ultimo->conteudo.cpf);
    gotoxy(2, 14);
    printf("Cargo do funcionario..............: %s\n", L->Ultimo->conteudo.cargo);
    gotoxy(2, 15);
    printf("Departamento do funcionario.......: %s\n", L->Ultimo->conteudo.depto);
    gotoxy(2, 16);
    printf("Salario do funcionario............: %.2f\n", L->Ultimo->conteudo.salario);
 
 
 
    int resp = confirmar();
 
    if(resp == 1){
        if(L->Primeiro == L->Ultimo){
        free(L->Primeiro);
 
        L->Primeiro = NULL;
        L->Ultimo = NULL;
 
        return;
    }
 
        TipoApontador A = L->Primeiro;
        TipoApontador B = A->proximo;
 
        while (B->proximo != NULL){
            B = B->proximo;
            A = A->proximo;
        }
 
 
        limpaMSG();
        printf("MSG.:Usuario removido!");
 
        free(B);
        A->proximo = NULL;
        L->Ultimo = A;
    }
 
 
}
 
void removerPosicao(TipoLista *L, int num){
 
 
    int cont = 0;
    int qtd = contar(L);
 
 
 
 
    tela();
    if (num < 1 || num > qtd) {
        gotoxy(8, 23);
        printf("Posicao invalida.");
 
    return;
    }
 
    if (num == 1){
        removerInicio(L);
 
        return;
    }
 
    if (num == qtd ){
        removerFinal(L);
 
        return;
    }
 
 
    TipoApontador A = L->Primeiro;
    TipoApontador B = A->proximo;
 
 
 
    cont = 2;
    while (cont< num) {
        cont = cont + 1;
        A= A->proximo;
        B= B->proximo;
    }
 
 
    gotoxy(2, 8);
    printf("Codigo do funcionario.............: %d\n", B->conteudo.cd_funcionario);
    gotoxy(2, 9);
    printf("Nome do funcionario...............: %s\n", B->conteudo.nm_funcionario);
    gotoxy(2, 10);
    printf("Endereco do funcionario...........: %s\n", B->conteudo.endereco);
    gotoxy(2, 11);
    printf("Data de nascimento do funcionario.: %s\n", B->conteudo.dt_nasc);
    gotoxy(2, 12);
    printf("Telefone do funcionario...........: %s\n", B->conteudo.telefone);
    gotoxy(2, 13);
    printf("CPF do funcionario................: %s\n", B->conteudo.cpf);
    gotoxy(2, 14);
    printf("Cargo do funcionario..............: %s\n", B->conteudo.cargo);
    gotoxy(2, 15);
    printf("Departamento do funcionario.......: %s\n", B->conteudo.depto);
    gotoxy(2, 16);
    printf("Salario do funcionario............: %.2f\n", B->conteudo.salario);
 
 
 
    int resp = confirmar();
 
    if (resp == 1){
        A->proximo = B->proximo;
 
        free(B);
    }
 
 
}
 
 
void alterarCadastro(TipoLista *L, int codigo){
 
 
    tela();
    int desejo = -1;
    TipoApontador controleA = L->Primeiro;
    reg_funcionario rascunho;
 
    while( controleA != NULL && codigo != controleA->conteudo.cd_funcionario){
        controleA = controleA->proximo;
    }
 
    if (controleA == NULL){
        limpaMSG();
        printf("MSG.: Esse codigo nao existe!");
 
        return;
    }
 
    rascunho = controleA->conteudo;
 
 
    do{
    tela();
    gotoxy(2, 8);
    printf("1 - Codigo do funcionario.............: %d\n", rascunho.cd_funcionario);
    gotoxy(2, 9);
    printf("2 - Nome do funcionario...............: %s\n", rascunho.nm_funcionario);
    gotoxy(2, 10);
    printf("3 - Endereco do funcionario...........: %s\n", rascunho.endereco);
    gotoxy(2, 11);
    printf("4 - Data de nascimento do funcionario.: %s\n", rascunho.dt_nasc);
    gotoxy(2, 12);
    printf("5 - Telefone do funcionario...........: %s\n", rascunho.telefone);
    gotoxy(2, 13);
    printf("6 - CPF do funcionario................: %s\n", rascunho.cpf);
    gotoxy(2, 14);
    printf("7 - Cargo do funcionario..............: %s\n", rascunho.cargo);
    gotoxy(2, 15);
    printf("8 - Departamento do funcionario.......: %s\n", rascunho.depto);
    gotoxy(2, 16);
    printf("9 - Salario do funcionario............: %.2f\n", rascunho.salario);
 
 
 
    limpaMSG();
    printf("MSG.: Qual campo deseja alterar?(de 2 a 9 OU 0 para VOLTAR): ");
    scanf("%d", &desejo);
    getchar();
    switch(desejo){
           case(2):
                limpaMSG();
                printf("MSG.: Digite o novo nome do funcionario: ");
                fgets(rascunho.nm_funcionario, 50, stdin);
            break;
 
            case(3):
                limpaMSG();
                printf("MSG.: Digite o novo endereco do funcionario: ");
                fgets(rascunho.endereco, 50, stdin);
            break;
 
            case(4):
                limpaMSG();
                printf("MSG.: Digite a nova data de nascimento do funcionario: ");
                fgets(rascunho.dt_nasc, 10, stdin);
            break;
 
            case(5):
                limpaMSG();
                printf("MSG.: Digite o novo telefone do funcionario: ");
                fgets(rascunho.telefone, 15, stdin);
            break;
 
            case(6):
                limpaMSG();
                printf("MSG.: Digite o novo CPF do funcionario: ");
                fgets(rascunho.cpf, 15, stdin);
            break;
 
            case(7):
                limpaMSG();
                printf("MSG.: Digite o novo cargo do funcionario: ");
                fgets(rascunho.cargo, 40, stdin);
            break;
 
            case(8):
                limpaMSG();
                printf("MSG.: Digite o novo departamento do funcionario: ");
                fgets(rascunho.depto, 30, stdin);
            break;
 
            case(9):
                limpaMSG();
                printf("MSG.: Digite o novo salario do funcionario: ");
                scanf("%f", &rascunho.salario);
                getchar();
            break;
 
            case(0):
                limpaMSG();
                printf("MSG.: ... ");
                getch();
            break;
 
            default:
                limpaMSG();
                printf("MSG.: Digite algo valido!");
                getch();
            break;
        }
 
    }while(desejo != 0);
 
    int resp = confirmar();
    if (resp == 1){
        controleA->conteudo = rascunho;
    }
}
 
 
/* Compara dois nomes letra a letra, sem diferenciar maiuscula de minuscula.
   Retorna > 0 se a vem depois de b, < 0 se a vem antes e 0 se forem iguais. */
int compararNomes(char *a, char *b){
 
    int i = 0;
    int ca, cb;
 
    while (a[i] != '\0' && b[i] != '\0'){
        ca = a[i];
        cb = b[i];
 
        if (ca >= 'A' && ca <= 'Z'){
            ca = ca + 32;
        }
        if (cb >= 'A' && cb <= 'Z'){
            cb = cb + 32;
        }
 
        if (ca != cb){
            return ca - cb;
        }
        i++;
    }
 
    return a[i] - b[i];
}
 
 
/* Retorna 1 se o elemento x deve ficar depois do elemento y no criterio escolhido
   (1 = nome, 2 = codigo, 3 = salario) */
int foraDeOrdem(TipoApontador x, TipoApontador y, int criterio){
 
    if (criterio == 1){
        return compararNomes(x->conteudo.nm_funcionario, y->conteudo.nm_funcionario) > 0;
    }
 
    if (criterio == 2){
        return x->conteudo.cd_funcionario > y->conteudo.cd_funcionario;
    }
 
    return x->conteudo.salario > y->conteudo.salario;
}
 
 
/* Mostra os funcionarios um por vez.
   criterio: 0 = ordem de cadastro, 1 = nome, 2 = codigo, 3 = salario.
   A lista encadeada NAO e alterada: a ordenacao e feita em um vetor de ponteiros,
   assim a ordem de cadastro continua a mesma ao gravar no arquivo. */
void consultarOrdenado(TipoLista *L, int criterio){
 
    int qtd = contar(L);
    int i, j;
    TipoApontador *vet;
    TipoApontador aux;
    TipoApontador A;
 
    tela();
    if (qtd == 0) {
        gotoxy(8, 23);
        printf("Lista vazia, nada para consultar.");
        getch();
        return;
    }
 
    vet = (TipoApontador *)malloc(qtd * sizeof(TipoApontador));
 
    A = L->Primeiro;
    for (i = 0; i < qtd; i++){
        vet[i] = A;
        A = A->proximo;
    }
 
    if (criterio != 0){
        for (i = 0; i < qtd - 1; i++){
            for (j = 0; j < qtd - 1 - i; j++){
                if (foraDeOrdem(vet[j], vet[j + 1], criterio)){
                    aux = vet[j];
                    vet[j] = vet[j + 1];
                    vet[j + 1] = aux;
                }
            }
        }
    }
 
    for (i = 0; i < qtd; i++){
 
        tela();
        gotoxy(2, 6);
        if (criterio == 0){
            printf("Ordem: Cadastro");
        } else if (criterio == 1){
            printf("Ordem: Alfabetica (nome)");
        } else if (criterio == 2){
            printf("Ordem: Codigo");
        } else {
            printf("Ordem: Salario (menor para maior)");
        }
 
        gotoxy(2, 8);
        printf("Codigo do funcionario.............: %d\n", vet[i]->conteudo.cd_funcionario);
        gotoxy(2, 9);
        printf("Nome do funcionario...............: %s\n", vet[i]->conteudo.nm_funcionario);
        gotoxy(2, 10);
        printf("Endereco do funcionario...........: %s\n", vet[i]->conteudo.endereco);
        gotoxy(2, 11);
        printf("Data de nascimento do funcionario.: %s\n", vet[i]->conteudo.dt_nasc);
        gotoxy(2, 12);
        printf("Telefone do funcionario...........: %s\n", vet[i]->conteudo.telefone);
        gotoxy(2, 13);
        printf("CPF do funcionario................: %s\n", vet[i]->conteudo.cpf);
        gotoxy(2, 14);
        printf("Cargo do funcionario..............: %s\n", vet[i]->conteudo.cargo);
        gotoxy(2, 15);
        printf("Departamento do funcionario.......: %s\n", vet[i]->conteudo.depto);
        gotoxy(2, 16);
        printf("Salario do funcionario............: %.2f\n", vet[i]->conteudo.salario);
 
        limpaMSG();
        printf("MSG.:Funcionario %d de %d - Pressione qualquer tecla para continuar", i + 1, qtd);
        getch();
    }
 
    free(vet);
}
 
 
void consultar(TipoLista *L){
 
    int op = -1;
 
    do{
        tela();
        gotoxy(2, 8);
        printf("1 - Consultar na ordem de cadastro");
        gotoxy(2, 9);
        printf("2 - Consultar em ordem alfabetica (nome)");
        gotoxy(2, 10);
        printf("3 - Consultar em ordem de codigo");
        gotoxy(2, 11);
        printf("4 - Consultar em ordem de salario (menor para maior)");
        gotoxy(2, 12);
        printf("0 - Voltar");
 
        limpaMSG();
        printf("MSG.:Qual opcao deseja?.:");
        int ok = scanf("%d", &op);
 
        char c = getchar();
        while (c != '\n') {
            c = getchar();
        }
 
        if (ok != 1){
            op = -1;
        }
 
        if (op >= 1 && op <= 4){
            consultarOrdenado(L, op - 1);
        }
 
    }while(op != 0);
 
}
 
 
void gravar (TipoLista *L){
    FILE *PTR;
    char *filename = "Funcionario.dat";
    char *modo_gravacao = "wb";
    TipoApontador p;
    reg_funcionario reg_func;
 
 
    PTR = fopen(filename, modo_gravacao);
 
 
    p = L->Primeiro;
    if(L->Primeiro == NULL){
        printf("A lista esta vazia");
        getch();
        fclose(PTR);
 
        return;
    }
 
    while (p != NULL){
        reg_func = p->conteudo;
        fwrite(&reg_func, sizeof(reg_funcionario), 1, PTR);
        p = p->proximo;
    }
 
    fclose(PTR);
 
}
 
 
void leitura(TipoLista *L){
    FILE *PTR;
    char *filename = "Funcionario.dat";
    char *modo_gravacao = "rb";
    TipoApontador p;
    reg_funcionario reg_func;
 
 
    L->Primeiro = NULL;
    L->Ultimo = NULL;
 
    PTR = fopen(filename, modo_gravacao);
 
    if (PTR == NULL){
        return;
    }
 
    while (fread(&reg_func, sizeof(reg_funcionario), 1, PTR) == 1){
 
        p = (TipoApontador)malloc(sizeof(TipoItem));
        p->conteudo = reg_func;
        p->proximo = NULL;
 
        if (L->Primeiro == NULL){
            L->Primeiro = p;
            L->Ultimo = p;
        } else {
            L->Ultimo->proximo = p;
            L->Ultimo = p;
        }
    }
 
    fclose(PTR);
 
}
 
 
 
 
int main() {
    // criação da Lista e aterramento dos ponteiros
    TipoLista L;
    L.Primeiro = NULL;
    L.Ultimo = NULL;
 
    // carrega os funcionarios gravados em disco
    leitura(&L);
 
 
    // variaveis
    int resp = -1;
    int codigo = -1;
    int num = -1;
    int outro = -1;
 
 
 
 
    do{
 
 
        tela();
        gotoxy(2, 8);
        printf("1 - Cadastrar Funcionario no Final da Lista");
        gotoxy(2, 9);
        printf("2 - Cadastrar Funcionario no Inicio da Lista");
        gotoxy(2, 10);
        printf("3 - Cadastrar Funcionario em uma Posicao da Lista");
        gotoxy(2, 11);
        printf("4 - Remover Funcionario no Final da Lista");
        gotoxy(2, 12);
        printf("5 - Remover Funcionario no Inicio da Lista");
        gotoxy(2, 13);
        printf("6 - Remover Funcionario em uma Posicao da Lista");
        gotoxy(2, 14);
        printf("7 - Alteracao do Cadastro de Funcionarios");
        gotoxy(2, 15);
        printf("8 - Consultar Funcionarios");
        gotoxy(2, 16);
        printf("9 - Sair do programa");
 
 
        do{
            limpaMSG();
            printf("MSG.:Qual opcao deseja?.:");
            int ok = scanf("%d", &resp);
 
 
 
            char c = getchar();
            while (c != '\n') {
            c = getchar();
            }
 
            if (ok != 1){
                resp = -1;
            }
        }while (resp != 1  &&   resp != 2   && resp !=3  && resp != 4  &&   resp != 5   && resp !=6 && resp != 7  &&   resp != 8   && resp !=9);
 
 
 
        switch(resp) {
            case(1):
 
            do{
 
                cadastroFinal(&L);
 
                limpaMSG();
                printf("MSG.:Cadastrar outro? 1 para sim, 0 para voltar: ");
                scanf("%d", &outro);
                getchar();
            }while(outro == 1);
                break;
 
            case(2):
                cadastroInicio(&L);
                break;
 
            case(3):
 
                limpaMSG();
                printf("MSG.:Qual posicao deseja cadastrar?(0 para VOLTAR).:");
                scanf("%d", &num);
                getchar();
 
                if (num == 0){
                    break;
                }
                cadastrarPosicao(&L, num);
                getch();
                break;
 
            case(4):
                removerFinal(&L);
                getch();
                break;
 
            case(5):
                removerInicio(&L);
                getch();
                break;
 
            case(6):
                limpaMSG();
                printf("MSG.:Qual posicao deseja remover?.:");
                scanf("%d", &num);
                getchar();
                removerPosicao(&L, num);
                getch();
                break;
 
            case(7):
                limpaMSG();
                printf("MSG.:Qual codigo deseja alterar?.:");
                scanf("%d", &codigo);
                getchar();
                alterarCadastro(&L, codigo);
                getch();
                break;
 
            case(8):
                consultar(&L);
                break;
 
            case(9):
                break;   // a gravacao em disco e feita logo depois do laco
 
 
            default:
                limpaMSG();
                printf("MSG.: Digite algo valido!");
                getch();
        }
 
 
 
    }while(resp != 9);
 
    // opcao 9: grava a lista em disco antes de sair
    gravar(&L);
 
 
    return 0;
}