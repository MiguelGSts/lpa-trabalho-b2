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

int menu();

static void limpaBuffer();

static int lerTexto(char *destino, int tamanho);

static int lerInt();

void continuar();

#endif