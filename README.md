# lpa-trabalho-b2
![C](https://img.shields.io/badge/Linguagem-C-00599C?style=for-the-badge&logo=c&logoColor=white)

Trabalho Institucional de Lógica de Programação e Algoritmos - Sistema de Estacionamento em linguagem C

## 📜 Sobre
 
Aplicação desenvolvida em linguagem de baixo nível C, tendo como base um cenário de cadastro de veículos em um estacionamento, introduzindo informações de identificação e posição de vagas dos mesmos. O trabalho origina-se para avaliação institucional e tinha como possibilidade a sua construção em dupla. Todas as informações presentes neste arquivo `README.md` e nos algoritmos presentes no repositório são principalmente destinados a correção e avaliação em âmbito educacional.
 
| Campo | Informação |
|:--|:--|
| **Disciplina** | Lógica de Programação e Algoritmos |
| **Semestre** | 2026/2 |
| **Avaliação** | Trabalho do 2º Bimestre |
| **Título do trabalho** | Sistema de Estacionamento em linguagem C |
| **Prazo de entrega** | 24/11/2026 |

### 👥 Integrantes

| Nome (conforme o AVA) | Perfil GitHub |
|:--|:--|
| Miguel Gomes dos Santos | [@MiguelGSts](https://github.com/MiguelGSts) |

## 🎯 Cenário e escopo
 
### Cenário
Sistema desenvolvido para execução em terminal, destinado ao controlo de vagas de um estacionamento fictício.
 
### Escopo
**O sistema contempla:**
- Mapa dimensional de ocupação;
- Operações de cadastro de veículos;
- Consulta de veículos;
- Alteração de informações de veículos cadastrados;
- Movimentação de veículos;
- Remoção de veículos;
- Apresentação de relatório sobre estado atual do sistema, envolvendo vagas e quantitativos de veículos.
**O sistema não contempla:**
- Persistência de dados pós encerramento do programa;
- Integração com banco de dados;
- Interface gráfica;
- Serviços web.

## ⚙️ Funcionalidades
 
- **Cadastrar veículo**: solicita e valida dados para cadastro de veículo no vetor de structs dinâmico;
- **Consultar veículo por placa**: solicita placa para o usuário, compara com as já existentes e indica se o veículo buscado existe no sistema, informando placa e localidade de vaga em caso de prescença;
- **Atualizar descrição ou categoria**: solicita placa para o usuário, identificando se ela existe no sistema, e se sim, retorna índice, possibilitando e validando a atualização de descrição e categoria do veículo escolhido;
- **Mover veículo para outra vaga**: permite a movimentação do veículo escolhido na matriz de representação do estacionamento;
- **Remover veículo**: remove o veículo escolhido da lista dinâmica;
- **Listar veículos cadastrados**: lista todos os veículos cadastrados no momento de execução;
- **Exibir mapa de vagas**: exibe de forma bidimensional a matriz 4x5, indicando 0 para vagas livres e 1 para ocupadas;
- **Exibir relatório de ocupação**: imprime no terminal o relatório da ocupação atual do sistema, indicando vagas totais, ocupadas e livres, percentual de ocupação e quantidade de carros e motos presentes no estacionamento.

## 🧱 Estruturas utilizadas
 
### Matriz 4 × 5
- **O que representa:** [4 linhas = fileiras do estacionamento; 5 colunas = colunas do estacionamento];
- **Tipo de dado:** int;
- **Onde é utilizada:** usada principalmente no cadastro de veículos para alocação de posição do veículo na matriz de acordo com a fileira e colunas indicados pelo usuário, além de sua prescença para sua mostragem bidimensional na função `mostrarEstacionamento`.
### Struct
- **Nome:** `Veiculo`;
- **Finalidade:** junção de atributos de uma entidade *veículo*;
- **Campos:**

| Campo | Tipo | Descrição |
|:--|:--|:--|
| id[7] | char  | representa a placa do veículo |
| descricao[60] | char | representa a descrição do veículo |
| categoria | int | representa o tipo de veículo, sendo 1 para carro e 2 para moto |
| fileira | int | indica a fileira onde está a vaga do veículo |
| coluna | int | indica a coluna onde está a vaga do veículo |

### Coleção dinâmica
- **Quantidade (`0`):** no começo da execução, há 0 itens armazenados no vetor dinâmico;
- **Capacidade (`2`):** antes da necessidade de realocação, há a capacidade de 2 itens no vetor;
- **Estratégia de crescimento:** é feito a realoção do vetor por meio de `realloc`, dobrando sua capacidade até o máximo permitido pelo cenário, limite esse sendo 20;
- **Liberação de memória:** a memória é liberada ao final do laço principal no arquivo `main.c`, por meio do comando `free(veiculos)`.

## 🗂️ Arquivos
 
- [`main.c`](main.c): fluxo principal da aplicação;
- [`estacionamento.h`](estacionamento.h): declarações de funções, procedimentos e declaração da struct necessária para o programa;
- [`estacionamento.c`](estacionamento.c): implementação das funções e procedimentos;
- [`Makefile`](Makefile): arquivo necessário para compilação e execução do sistema.

## 🖱️ Compilação e execução
 
**Ambiente utilizado:** Windows 11, GCC, GCC 16.2

### Execução por comandos GCC
 
**1. Compilar**
 
```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c estacionamento.c -o main
```
 
**2. Executar**
 
```bash
./main       # Linux, macOS e Git Bash
./main.exe    # PowerShell
main.exe      # cmd
```
### Execução por meio de Makefile

```bash
make    #compila e executa os arquivos
```

**Exclusão do executável**

```bash
make clean   #compila e executa os arquivos
```

## 🧪 Casos de teste

| # | Entrada / Operação | Resultado esperado | Resultado observado | Situação |
|:-:|:--|:--|:--|:-:|
| 1 | Uso da opção de atualização de descrição ou categoria | valida placa informada e possibilita atualização | valida placa informada pelo usuário até a digitação correta e possibilita atualização até encerramento da operação por parte do usuário | ✅ Aprovado |
| 2 | Entrada inválida de fileira e coluna | recusa e espera nova entrada | recusou a entrada inválida e solicitou novos valores até a validade estar correta | ✅ Aprovado |
| 3 | Lotação da matriz 4 x 5 | se todos os itens forem 1, ou seja, 20 veículos cadastrados, recusar novas inclusões | recusou novos cadastros enquanto a quantidade de cadastros for igual a 20 | ✅ Aprovado |
| 4 | Vetor dinâmico atinge o limite | usar ponteiro temporário e dobrar a capacidade por meio de `realloc` | verificou capacidade e dobrou quando validou a condição de limite do vetor | ✅ Aprovado |
| 5 | Busca de veículo inexistente | informar que a placa do veículo não foi encontrada | validou e comparou a placa informada pelo usuário com as existentes no vetor e informou que não estava cadastrada | ✅ Aprovado |
| 6 | Listagem com coleção vazia | impedir listagem enquanto a coleção esteja vazia | validou a quantidade de cadastros ativos e informou que não haviam veículos cadastrados no momento de execução | ✅ Aprovado |

## 📌 Declaração de autoria, uso de IA e referências

### Declaração individual de autoria

Declaro que todos os algoritmos foram desenvolvidos e validados por mim, e que sou capaz de explicar o funcionamento do código entregue.

### 🤖 Uso de Inteligência Artificial
- **Ferramenta(s) utilizada(s):** Claude Chat;
- **Finalidade:** validação de blocos de código das funções `cadastrarVeiculo` e `cadastrarEstacionamento`;
- **O que foi feito por conta própria:** escrita lógica de todos os algoritmos, testes e decisões do projeto;
- **Como o conteúdo foi validado:** execução de casos de teste e uso de pontos de parada para validação de entradas e saídas.