#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "estacionamento.h"

#ifdef _WIN32
    #include <windows.h>
#endif

int main(){
    setlocale(LC_ALL, ".UTF8");
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    int op;

    do{
        limpa_Titulo();

    }while(op != 0);

    return 0;
}