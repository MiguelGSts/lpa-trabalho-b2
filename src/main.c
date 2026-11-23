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
        }

    }while(op != 0);

    free(veiculos);
    return 0;
}