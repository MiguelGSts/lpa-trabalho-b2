#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "estacionamento.h"

#ifdef _WIN32
    #include <windows.h>
#endif

#define CAPACIDADE 20

int main(){
    setlocale(LC_ALL, ".UTF8");
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    int op;
    int qnt_usada = 0, qnt_disponivel = 2;
    Veiculo *veiculos = malloc(qnt_disponivel * sizeof *veiculos);
    int estacionamento[4][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    do{
        limpa_Titulo();
        op = menu();

        switch(op){
            case 1:
                limpa_Titulo();
                limpaBuffer();
                if(qnt_usada >= CAPACIDADE){
                    puts("Limite de cadastro de veículos atingido.\n");
                    break;
                }
                while(qnt_usada == qnt_disponivel){
                    qnt_disponivel = redimensionaQnt(&veiculos, qnt_disponivel);
                    if(qnt_usada == qnt_disponivel){
                        break;
                    }
                }

                qnt_usada = cadastrarVeiculo(veiculos, estacionamento, qnt_usada);
                break;

            case 2:
                limpa_Titulo();
                limpaBuffer();
                consultarVeiculo(veiculos, qnt_usada);
                break;

            case 3:
                limpa_Titulo();
                limpaBuffer();
                atualizarVeiculo(veiculos, qnt_usada);
                break;

            case 4:
                limpa_Titulo();
                limpaBuffer();
                moverVeiculo(veiculos, qnt_usada, estacionamento);
                break;

            case 5:
                limpa_Titulo();
                limpaBuffer();
                qnt_usada = removerVeiculo(veiculos, qnt_usada, estacionamento);
                break;

            case 6:
                limpa_Titulo();
                limpaBuffer();
                if(qnt_usada == 0){
                    printf("Não há veículos cadastrados no momento, tente novamente mais tarde.\n");
                    break;
                }
                listarVeiculos(veiculos, qnt_usada);
                break;
            
            case 7:
                limpa_Titulo();
                limpaBuffer();
                mostrarEstacionamento(estacionamento);
                break;

            case 8:
                limpa_Titulo();
                limpaBuffer();
        }

    }while(op != 0);

    free(veiculos);
    return 0;
}