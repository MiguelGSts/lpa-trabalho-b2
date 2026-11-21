#include <stdio.h>
#include <stdlib.h>

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