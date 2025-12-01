#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5    // tamanho fixo da fila
#define MAX_PILHA 3   // tamanho máximo da pilha

// Estrutura da peça (tipo e id)
typedef struct {
    char tipo;
    int id;
} Peca;

// Gera uma nova peça automaticamente
Peca gerarPeca(int id) {
    char tipos[] = {'I','O','T','L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

// Mostra o conteúdo da fila
void mostrarFila(Peca fila[], int ini, int qtd) {
    printf("Fila: ");
    for (int i = 0; i < qtd; i++) {
        int pos = (ini + i) % MAX_FILA;
        printf("[%c %d] ", fila[pos].tipo, fila[pos].id);
    }
    if (qtd == 0) printf("(vazia)");
    printf("\n");
}

// Mostra o conteúdo da pilha (de cima para baixo)
void mostrarPilha(Peca pilha[], int topo) {
    printf("Pilha (Topo -> Base): ");
    if (topo == -1) {
        printf("(vazia)\n");
        return;
    }
    for (int i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].tipo, pilha[i].id);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    Peca fila[MAX_FILA];
    Peca pilha[MAX_PILHA];

    int ini = 0, fim = 0, qtd = 0;        // controle da fila
    int topo = -1;                        // topo da pilha
    int id = 0;                           // id único das peças
    int op;                               // opção do menu

    // Inicializa a fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        fila[fim] = gerarPeca(id++);
        fim = (fim + 1) % MAX_FILA;
        qtd++;
    }

    do {
        printf("\n=== ESTADO ATUAL ===\n");
        mostrarFila(fila, ini, qtd);
        mostrarPilha(pilha, topo);

        printf("\n1 - Jogar peça");
        printf("\n2 - Reservar peça");
        printf("\n3 - Usar peça reservada");
        printf("\n0 - Sair");
        printf("\nOpção: ");
        scanf("%d", &op);

        // Jogar peça (remove da fila)
        if (op == 1) {
            if (qtd == 0) {
                printf("\nFila vazia!\n");
            } else {
                ini = (ini + 1) % MAX_FILA;
                qtd--;
            }
        }

        // Reservar peça (fila -> pilha)
        if (op == 2) {
            if (qtd == 0) {
                printf("\nFila vazia!\n");
            } else if (topo == MAX_PILHA - 1) {
                printf("\nPilha cheia!\n");
            } else {
                pilha[++topo] = fila[ini];
                ini = (ini + 1) % MAX_FILA;
                qtd--;
            }
        }

        // Usar peça reservada (pop da pilha)
        if (op == 3) {
            if (topo == -1) {
                printf("\nPilha vazia!\n");
            } else {
                topo--;
            }
        }

        // Sempre gera uma nova peça para manter a fila cheia
        if (op == 1 || op == 2) {
            fila[fim] = gerarPeca(id++);
            fim = (fim + 1) % MAX_FILA;
            qtd++;
        }

    } while (op != 0);

    return 0;
}
