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

void consultarVeiculo(Veiculo veiculos[], int qnt_usada){
    Veiculo busca;
    int i, indice = -1;

    printf("==> Informe a placa do veículo buscado: ");
    lerTexto(busca.id, sizeof(busca.id));
    for(i = 0; busca.id[i] != '\0'; i++){
        busca.id[i] = toupper((unsigned char)busca.id[i]);
    }

    for(i = 0; i < qnt_usada; i++){
        if(strcmp(veiculos[i].id, busca.id) == 0){
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