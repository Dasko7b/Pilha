#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_DISCOS_PILHA 20

typedef struct {
    int dados[MAX_DISCOS_PILHA];
    int topo;
} PilhaEstatica;

void inicializarPilha(PilhaEstatica* p) {
    p->topo = -1;
}

bool estaVaziaPilha(PilhaEstatica* p) {
    return p->topo == -1;
}

bool estaCheiaPilha(PilhaEstatica* p) {
    return p->topo == MAX_DISCOS_PILHA - 1;
}

bool pushPilha(PilhaEstatica* p, int valor) {
    if (estaCheiaPilha(p)) {
        fprintf(stderr, "ERRO: Pilha cheia ao tentar empilhar %d!\n", valor);
        return false;
    }
    p->topo++;
    p->dados[p->topo] = valor;
    return true;
}

int popPilha(PilhaEstatica* p) {
    if (estaVaziaPilha(p)) {
        fprintf(stderr, "ERRO: Pilha vazia ao tentar desempilhar!\n");
        return -1;
    }
    int valor = p->dados[p->topo];
    p->topo--;
    return valor;
}

int topPilha(PilhaEstatica* p) {
    if (estaVaziaPilha(p)) {
        fprintf(stderr, "ERRO: Pilha vazia ao tentar ver o topo!\n");
        return -1;
    }
    return p->dados[p->topo];
}

typedef struct {
    PilhaEstatica torre[3];
    int num_discos;
} JogoHanoi;

void inicializarHanoi(JogoHanoi* jogo, int n) {
    if (n <= 0) {
        fprintf(stderr, "Erro na inicialização: Número de discos deve ser positivo. Fornecido: %d\n", n);
        jogo->num_discos = 0;
        return;
    }
    if (n > MAX_DISCOS_PILHA) {
        fprintf(stderr, "Erro na inicialização: Número de discos (%d) excede a capacidade máxima da pilha (%d).\n", n, MAX_DISCOS_PILHA);
        jogo->num_discos = 0;
        return;
    }

    jogo->num_discos = n;

    inicializarPilha(&jogo->torre[0]);
    inicializarPilha(&jogo->torre[1]);
    inicializarPilha(&jogo->torre[2]);

    for (int i = n; i >= 1; i--) {
        if (!pushPilha(&jogo->torre[0], i)) {
            fprintf(stderr, "Erro crítico na inicialização: Falha ao empilhar disco %d na torre A.\n", i);
            jogo->num_discos = 0; 
            return;
        }
    }
}

bool moverDisco(JogoHanoi* jogo, int origem, int destino) {
    if (origem < 0 || origem > 2 || destino < 0 || destino > 2) {
        fprintf(stderr, "Movimento inválido: Índice de torre inválido (origem=%d, destino=%d). Use 0, 1 ou 2.\n", origem, destino);
        return false;
    }
    if (origem == destino) {
        return false;
    }

    PilhaEstatica* pOrigem = &jogo->torre[origem];
    PilhaEstatica* pDestino = &jogo->torre[destino];

    if (estaVaziaPilha(pOrigem)) {
        return false;
    }

    int discoDoTopoOrigem = topPilha(pOrigem);

    if (!estaVaziaPilha(pDestino)) {
        int discoDoTopoDestino = topPilha(pDestino);
        if (discoDoTopoOrigem > discoDoTopoDestino) {
            return false;
        }
    }

    int discoMovido = popPilha(pOrigem);
    if (discoMovido == -1) {
        return false;
    }

    if (!pushPilha(pDestino, discoMovido)) {
        fprintf(stderr, "Erro crítico: Falha ao empilhar disco %d na torre %c após desempilhar da torre %c.\n",
                discoMovido, 'A' + destino, 'A' + origem);
        return false;
    }

    printf("Mover disco %d da torre %c para a torre %c\n",
           discoMovido,
           (char)('A' + origem),
           (char)('A' + destino));
    return true;
}

void resolverHanoi(JogoHanoi* jogo, int n_discos_a_mover, int origem, int destino, int auxiliar) {
    if (n_discos_a_mover <= 0) {
        return;
    }

    if (n_discos_a_mover == 1) {
        moverDisco(jogo, origem, destino);
    } else {
        resolverHanoi(jogo, n_discos_a_mover - 1, origem, auxiliar, destino);
        moverDisco(jogo, origem, destino);
        resolverHanoi(jogo, n_discos_a_mover - 1, auxiliar, destino, origem);
    }
}