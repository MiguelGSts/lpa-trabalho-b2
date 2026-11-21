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
    Veiculo *veiculo = malloc(2 * sizeof(Veiculo));
    int estacionamento[4][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    do{
        limpa_Titulo();
        op = menu();

    }while(op != 0);

    return 0;
}