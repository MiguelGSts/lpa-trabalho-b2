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

void limpaBuffer();

int lerTexto(char *destino, int tamanho);

int lerInt();

void continuar();

int redimensionaQnt(Veiculo **veiculos, int qnt_disponivel);

int placaExiste(Veiculo veiculos[], int qnt, const char *placa);

int cadastrarVeiculo(Veiculo veiculos[], int estacionamento[][5], int qnt_usada);

void cadastrarEstacionamento(Veiculo *novo, int estacionamento[][5]);

void consultarVeiculo(Veiculo veiculos[], int qnt_usada);

#endif