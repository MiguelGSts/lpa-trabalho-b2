#include <stdio.h>
#include <stdlib.h>
#include "estacionamento.h"
#include <string.h>
#include <ctype.h>

void limpaTela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void titulo(){
    printf("==========================\n");
    printf("=== ESTACIONAMENTO BSB ===\n");
    printf("==========================\n\n");
}

void limpa_Titulo(){
    limpaTela();
    titulo();
}

int menu(){
    int opcao;

    printf("[1] Cadastrar veículo\n");
    printf("[2] Consultar veículo por placa\n");
    printf("[3] Atualizar descrição ou categoria\n");
    printf("[4] Mover veículo para outra vaga\n");
    printf("[5] Remover veículo\n");
    printf("[6] Listar veículos cadastrados\n");
    printf("[7] Exibir mapa de vagas\n");
    printf("[8] Exibir relatório de ocupação\n");
    printf("[0] Encerrar\n\n");

    printf("=> Informe a opção escolhida: ");
    scanf("%d", &opcao);
    if(opcao < 0 || opcao > 8){
        do{
            puts("[ERRO] Opção inválida!\n");
            printf("=> Informe a opção novamente: ");
            scanf("%d", &opcao);
        }while(opcao < 0 || opcao > 8);
    }

    return opcao;
}

void limpaBuffer(){
    int c;

    while((c = getchar()) != '\n' && c != EOF);
}

int lerTexto(char *destino, int tamanho){
    if(fgets(destino, tamanho, stdin) == NULL) return 0;

    if(strchr(destino, '\n') == NULL) limpaBuffer();
    destino[strcspn(destino, "\n")] = '\0';
    return 1;
}

int lerInt(){
    int valor;

    while(scanf("%d", &valor) != 1){
        limpaBuffer();
        printf("[ERRO] Digite um número: ");
    }
    limpaBuffer();
    
    return valor;
}

void continuar(){
    printf("Pressione Enter para continuar...");
    getchar();
}

int redimensionaQnt(Veiculo **veiculos, int qnt_disponivel){
    int qnt_nova = qnt_disponivel*2;
    const int CAPACIDADE = 20;
    if(qnt_nova > CAPACIDADE){
        qnt_nova = CAPACIDADE;
    }

    Veiculo *temp = realloc(*veiculos, qnt_nova * sizeof *veiculos);
    if(temp == NULL){
        fprintf(stderr, "Falha no redimensionamento do vetor.\n");
        continuar();
        return qnt_disponivel;
    }else{
        *veiculos = temp;
        return qnt_nova;
    }
}

int placaExiste(Veiculo veiculos[], int qnt, const char *placa){
    int i;

    for(i = 0; i < qnt; i++){
        if(strcmp(veiculos[i].id, placa) == 0) return 1;
    }
    
    return 0;
}

int cadastrarVeiculo(Veiculo veiculos[], int estacionamento[][5], int qnt_usada){
    int i;
    Veiculo novo;

    int ok;
    do{
        printf("==> Informe a placa do veículo: ");
        ok = lerTexto(novo.id, sizeof(novo.id));

        if(ok == 0){
            clearerr(stdin);
            puts("[ERRO] Falha na leitura da placa, tente novamente.");
            continue;
        }

        for(i = 0; novo.id[i] != '\0'; i++){
            novo.id[i] = toupper((unsigned char)novo.id[i]);
        }

        if(strlen(novo.id) == 0){
            puts("[ERRO] Placa ausente, tente novamente.");
            ok = 0;
        }else if(placaExiste(veiculos, qnt_usada, novo.id) == 1){
            puts("[ERRO] Placa já cadastrada, tente novamente.");
            ok = 0;
        }

    }while(ok == 0);

    printf("==> Informe a descrição do veículo: ");
    lerTexto(novo.descricao, sizeof(novo.descricao));

    do{
        limpa_Titulo();
        printf("==> Informe a categoria do veículo\n");
        printf("[1] Carro\n");
        printf("[2] Moto\n");
        printf("==> ");
        novo.categoria = lerInt();

        if(novo.categoria < 1 || novo.categoria > 2){
            puts("[ERRO] Categoria inválida, tente novamente.");
            continuar();
        }
    }while(novo.categoria < 1 || novo.categoria > 2);

    cadastrarEstacionamento(&novo, estacionamento);
    veiculos[qnt_usada] = novo;

    printf("Veículo cadastrado com sucesso!\n");
    printf("=> Placa: %s\n", novo.id);
    printf("=> Vaga: Fileira %d | Coluna %d\n", novo.fileira + 1, novo.coluna + 1);
    continuar();

    return qnt_usada + 1;
}

void cadastrarEstacionamento(Veiculo *novo, int estacionamento[][5]){
    int validador = -1;
    int fileira;
    int coluna;

    do{
        do{
            limpa_Titulo();
            printf("==> Informe a fileira onde o veículo está estacionado(1 à 4): ");
            fileira = lerInt();
            
            if(fileira > 4 || fileira < 1){
                puts("[ERRO] Fileira inválida, tente novamente.");
                continuar();
            }
        }while(fileira > 4 || fileira < 1);

        do{
            limpa_Titulo();
            printf("==> Informe a coluna onde o veículo está estacionado(1 à 5): ");
            coluna = lerInt();
            
            if(coluna > 5 || coluna < 1){
                puts("[ERRO] Coluna inválida, tente novamente.");
                getchar();
            }
        }while(coluna > 5 || coluna < 1);

        if(estacionamento[fileira - 1][coluna - 1] == 0){
            estacionamento[fileira - 1][coluna - 1] = 1;
            novo->fileira = fileira - 1;
            novo->coluna = coluna - 1;
            validador = 0;
        }else{
            limpa_Titulo();
            puts("A vaga escolhida está ocupada, tente novamente.");
            continuar();
        }
    }while(validador == -1);
}

int comparaStrings(char *string1, char *string2){
    
    if(strcmp(string1, string2) == 0){
        return 0;
    }

    return 1;
}

void consultarVeiculo(Veiculo veiculos[], int qnt_usada){
    Veiculo busca;
    int i, indice = -1, ok;

    do{
        printf("==> Informe a placa do veículo: ");
        ok = lerTexto(busca.id, sizeof(busca.id));
        if(ok == 0){
            clearerr(stdin);
            puts("[ERRO] Falha na leitura da placa, tente novamente.");
            continue;
        }
        for(i = 0; busca.id[i] != '\0'; i++){
            busca.id[i] = toupper((unsigned char)busca.id[i]);
        }
    }while(ok == 0);

    for(i = 0; i < qnt_usada; i++){
        if(comparaStrings(veiculos[i].id, busca.id) == 0){
            indice = i;
            break;
        }
    }

    if(indice != -1){
        printf("== Veículo encontrado ==\n");
        printf("-> Placa: %s\n", veiculos[indice].id);
        printf("-> Descrição: %s\n", veiculos[indice].descricao);
        printf("-> Categoria: %d\n", veiculos[indice].categoria);
        printf("-> Fileira: %d | Coluna: %d\n", veiculos[indice].fileira + 1, veiculos[indice].coluna + 1);
        continuar();
    }else{
        puts("O veículo buscado não foi encontrado.");
        continuar();
    }
}

int buscarPlaca(Veiculo veiculos[], int qnt_usada, Veiculo *buscado){
    int ok, indice, i;
    
     do{
        printf("==> Informe a placa do veículo: ");
        ok = lerTexto(buscado->id, sizeof(buscado->id));
        if(ok == 0){
            clearerr(stdin);
            puts("[ERRO] Falha na leitura da placa, tente novamente.");
            continue;
        }
        for(i = 0; buscado->id[i] != '\0'; i++){
            buscado->id[i] = toupper((unsigned char)buscado->id[i]);
        }
        for(i = 0; i < qnt_usada; i++){
            if(comparaStrings(veiculos[i].id, buscado->id) == 0){
                indice = i;
                return indice;
            }
        }
        if(indice == -1){
            puts("O veículo não foi encontrado, tente novamente.");
            ok = 0;
            continuar();
        }
    }while(ok == 0);
}

void atualizarVeiculo(Veiculo veiculos[], int qnt_usada){
    int op, indice;
    Veiculo atualizado;

    indice = buscarPlaca(veiculos, qnt_usada, &atualizado);
   
    do{
        printf("==> Informe o que deseja atualizar\n");
        printf("[1] Atualizar descrição do veículo\n");
        printf("[2] Atualizar categoria do veículo\n");
        printf("[0] Voltar ao menu\n");
        printf("==> ");
        op = lerInt();

        switch(op){
            case 1:
                limpa_Titulo();
                atualizarDescricao(&atualizado);
                strcpy(veiculos[indice].descricao, atualizado.descricao);
                break;
            case 2:
                limpa_Titulo();
                atualizarCategoria(&atualizado);
                veiculos[indice].categoria = atualizado.categoria;
                break;
            case 0:
                limpa_Titulo();
                printf("== Atualização encerrada ==\n");
                printf("-> Placa: %s\n", veiculos[indice].id);
                printf("-> Descrição %s\n", veiculos[indice].descricao);
                printf("-> Categoria %d\n", veiculos[indice].categoria);
                continuar();
                break;
            default:
                puts("Opção inválida, tente novamente.");
        }
    }while(op != 0);
}

void atualizarDescricao(Veiculo *atualizado){
    int ok;

    do{
        printf("==> Informe a nova descrição do veículo: ");
        ok = lerTexto(atualizado->descricao, sizeof(atualizado->descricao));
        if(ok == 0){
            clearerr(stdin);
            puts("[ERRO] Falha na leitura da placa, tente novamente.");
            continuar();
            continue;
        }
        if(atualizado->descricao[0] == '\0' || strlen(atualizado->descricao) == 0){
            puts("[ERRO] Descrição vazia, tente novamente.");
            ok = 0;
            continuar();
            continue;
        }
    }while(ok == 0);
}

void atualizarCategoria(Veiculo *atualizado){
    int ok, num;

    do{
        printf("==> Informe a nova categoria do veículo: ");
        num =  lerInt();
        if(num < 1 || num > 2){
            ok = 0;
            puts("[ERRO] Categoria inválida, tente novamente.");
            continuar();
            continue;
        }

        atualizado->categoria = num;
    }while(ok == 0);
}

void moverVeiculo(Veiculo veiculos[], int qnt_usada, int estacionamento[][5]){
    int fileira, coluna, indice;
    int op;
    Veiculo veiculo;

    do{
        indice = buscarPlaca(veiculos, qnt_usada, &veiculo);
        do{
            printf("=> Informe a fileira para a mudança (1 à 4): ");
            fileira = lerInt();
            if(fileira > 4 || fileira < 1){
                puts("Fileira inválida, tente novamente.");
                continuar();
            }
        }while(fileira > 4 || fileira < 1);
        do{
            printf("=> Informe a coluna para a mudança (1 à 5): ");
            coluna = lerInt();
            if(coluna > 5 || coluna < 1){
                puts("Coluna inválida, tente novamente.");
                continuar();
            }
        }while(coluna > 5 || coluna < 1);

        if(estacionamento[fileira - 1][coluna - 1] == 0){
            estacionamento[fileira - 1][coluna - 1] = 1;
            estacionamento[veiculos[indice].fileira][veiculos[indice].coluna] = 0;
            veiculos[indice].fileira = fileira - 1;
            veiculos[indice].coluna = coluna - 1;
        }else if(veiculos[indice].fileira == fileira && veiculos[indice].coluna == coluna){
            limpa_Titulo();
            puts("A vaga já está ocupada pelo veículo escolhido.");
            continuar();
        }else{
            limpa_Titulo();
            puts("A vaga escolhida está ocupada por outro veículo.");
            continuar();
        }
        printf("Deseja fazer outra mudança?\n");
        printf("[1] para Sim\n[0] para Não\n=> ");
        op = lerInt();
    }while(op != 0);
}

int removerVeiculo(Veiculo veiculos[], int qnt_usada, int estacionamento[][5]){
    Veiculo veiculo;
    int i;
    int posicao = buscarPlaca(veiculos, qnt_usada, &veiculo);

    if(posicao < 0 || posicao >= qnt_usada){
        return qnt_usada;
    }

    if(posicao != -1){
        estacionamento[veiculos[posicao].fileira][veiculos[posicao].coluna] = 0;

        for(int i = posicao; i < qnt_usada - 1; i++){
            veiculos[i] = veiculos[i + 1];
        }

        puts("Veículo removido com sucesso.");
        continuar();

        return qnt_usada - 1;
    }
}

void listarVeiculos(Veiculo veiculos[], int qnt_usada){
    int i;

    for(i = 0; i < qnt_usada; i++){
        printf("\n=== Veiculo %d ===\n", (i+1));
        printf("=> Placa: %s\n", veiculos[i].id);
        printf("=> Descrição: %s\n", veiculos[i].descricao);
        printf("=> Categoria: %d\n", veiculos[i].categoria);
        printf("=> Vaga: Fileira %d | Coluna %d\n", veiculos[i].fileira + 1, veiculos[i].coluna + 1);
    }
}