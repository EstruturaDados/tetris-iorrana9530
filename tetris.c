#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5   // tamanho da fila

// Estrutura de uma peça
typedef struct {
    char tipo;  // tipo da peça
    int id;     // identificador único
} Peca;

// Gera uma nova peça automaticamente
Peca gerarPeca(int id) {
    char tipos[] = {'I','O','T','L'};     // tipos possíveis
    Peca p;
    p.tipo = tipos[rand() % 4];           // escolhe tipo aleatório
    p.id = id;                            // id único
    return p;
}

// Mostra o conteúdo da fila
void mostrarFila(Peca fila[], int ini, int qtd) {
    printf("\nFila: ");
    if (qtd == 0) {                       // fila vazia
        printf("(vazia)\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        int pos = (ini + i) % MAX;        // posição circular
        printf("[%c %d] ", fila[pos].tipo, fila[pos].id);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    Peca fila[MAX];
    int ini = 0, fim = 0;                 // início e fim da fila
    int qtd = 0;                          // quantidade de peças
    int id = 0;                           // id das peças
    int op;                               // opção do menu

    // Inicializa com 5 peças
    for (int i = 0; i < MAX; i++) {
        fila[fim] = gerarPeca(id++);
        fim = (fim + 1) % MAX;
        qtd++;
    }

    // Menu principal
    do {
        mostrarFila(fila, ini, qtd);
        printf("\n1 - Jogar peça\n2 - Inserir nova peça\n0 - Sair\nEscolha: ");
        scanf("%d", &op);

        // Remove peça da frente
        if (op == 1) {
            if (qtd == 0) {
                printf("\nFila vazia!\n");
            } else {
                ini = (ini + 1) % MAX;
                qtd--;
            }
        }

        // Insere nova peça no final
        if (op == 2) {
            if (qtd == MAX) {
                printf("\nFila cheia!\n");
            } else {
                fila[fim] = gerarPeca(id++);
                fim = (fim + 1) % MAX;
                qtd++;
            }
        }

    } while (op != 0);

    return 0;
}
