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