#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

typedef struct{
    char id[7];
    char descricao[60];
    int categoria;
    int fileira;
    int coluna;
}Veiculo;

void limpaTela();

void titulo();

void limpa_Titulo();

#endif