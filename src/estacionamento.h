#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

typedef struct{
    char id[8];
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

int comparaStrings(char *string1, char *string2);

void consultarVeiculo(Veiculo veiculos[], int qnt_usada);

int buscarPlaca(Veiculo veiculos[], int qnt_usada, Veiculo *buscado);

void atualizarVeiculo(Veiculo veiculos[], int qnt_usada);

void atualizarDescricao(Veiculo *atualizado);

void atualizarCategoria(Veiculo *atualizado);

void moverVeiculo(Veiculo veiculos[], int qnt_usada, int estacionamento[][5]);

int removerVeiculo(Veiculo veiculos[], int qnt_usada, int estacionamento[][5]);

void listarVeiculos(Veiculo veiculos[], int qnt_usada);

void mostrarEstacionamento(int estacionamento[][5]);

void exibirRelatorio(Veiculo veiculos[], int qnt_usada);

#endif