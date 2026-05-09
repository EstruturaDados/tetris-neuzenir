
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5

//-----------------------------------------------------------------------------
// STRUCT DA PEÇA
//-----------------------------------------------------------------------------
typedef struct {
    char nome; // Tipo da peça: I, O, T, L
    int id;    // Identificador único
} Peca;

//-----------------------------------------------------------------------------
// STRUCT DA FILA
//-----------------------------------------------------------------------------
typedef struct {
    Peca itens[TAMANHO_FILA];

    int inicio;   // Índice do primeiro elemento
    int fim;      // Índice do último elemento
    int quantidade; // Quantidade atual de peças
} Fila;

//-----------------------------------------------------------------------------
// VARIÁVEL GLOBAL PARA CONTROLE DOS IDs
//-----------------------------------------------------------------------------
int proximoId = 0;

//-----------------------------------------------------------------------------
// FUNÇÃO: gerarPeca
// Gera automaticamente uma peça aleatória
//-----------------------------------------------------------------------------
Peca gerarPeca() {

    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca novaPeca;

    // Escolhe um tipo aleatório
    novaPeca.nome = tipos[rand() % 4];

    // Define ID único
    novaPeca.id = proximoId++;

    return novaPeca;
}

//-----------------------------------------------------------------------------
// FUNÇÃO: inicializarFila
// Inicializa os índices da fila
//-----------------------------------------------------------------------------
void inicializarFila(Fila *fila) {

    fila->inicio = 0;
    fila->fim = -1;
    fila->quantidade = 0;
}

//-----------------------------------------------------------------------------
// FUNÇÃO: filaCheia
// Retorna 1 se a fila estiver cheia
//-----------------------------------------------------------------------------
int filaCheia(Fila *fila) {

    return fila->quantidade == TAMANHO_FILA;
}

//-----------------------------------------------------------------------------
// FUNÇÃO: filaVazia
// Retorna 1 se a fila estiver vazia
//-----------------------------------------------------------------------------
int filaVazia(Fila *fila) {

    return fila->quantidade == 0;
}

//-----------------------------------------------------------------------------
// FUNÇÃO: enqueue
// Insere uma peça no final da fila
//-----------------------------------------------------------------------------
void enqueue(Fila *fila, Peca novaPeca) {

    if (filaCheia(fila)) {
        printf("\nA fila está cheia!\n");
        return;
    }

    // Atualiza posição do fim circularmente
    fila->fim = (fila->fim + 1) % TAMANHO_FILA;

    // Insere a peça
    fila->itens[fila->fim] = novaPeca;

    fila->quantidade++;

    printf("\nPeça [%c %d] inserida na fila!\n",
           novaPeca.nome,
           novaPeca.id);
}

//-----------------------------------------------------------------------------
// FUNÇÃO: dequeue
// Remove a peça da frente da fila
//-----------------------------------------------------------------------------
void dequeue(Fila *fila) {

    if (filaVazia(fila)) {
        printf("\nA fila está vazia!\n");
        return;
    }

    // Guarda peça removida
    Peca removida = fila->itens[fila->inicio];

    // Atualiza início circularmente
    fila->inicio = (fila->inicio + 1) % TAMANHO_FILA;

    fila->quantidade--;

    printf("\nPeça [%c %d] jogada!\n",
           removida.nome,
           removida.id);
}

//-----------------------------------------------------------------------------
// FUNÇÃO: exibirFila
// Mostra todas as peças da fila
//-----------------------------------------------------------------------------
void exibirFila(Fila *fila) {

    printf("\n====================================");
    printf("\nFila de peças:\n");

    if (filaVazia(fila)) {
        printf("[Fila vazia]");
    }
    else {

        // Percorre a fila circular
        for (int i = 0; i < fila->quantidade; i++) {

            int indice =
                (fila->inicio + i) % TAMANHO_FILA;

            printf("[%c %d] ",
                   fila->itens[indice].nome,
                   fila->itens[indice].id);
        }
    }

    printf("\n====================================\n");
}

//-----------------------------------------------------------------------------
// FUNÇÃO PRINCIPAL
//-----------------------------------------------------------------------------
int main() {

    // Inicializa gerador aleatório
    srand(time(NULL));

    Fila fila;

    // Inicializa fila
    inicializarFila(&fila);

    // Preenche fila inicial com 5 peças
    for (int i = 0; i < TAMANHO_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {

        // Mostra estado atual
        exibirFila(&fila);

        // Menu
        printf("\nEscolha uma opção:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");

        printf("Opção: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                dequeue(&fila);
                break;

            case 2:
                enqueue(&fila, gerarPeca());
                break;

            case 0:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}