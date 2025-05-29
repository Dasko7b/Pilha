#include <stdio.h>
#include <stdbool.h>
#include "pilha.h" 

int main() {
    PilhaChar p; // Declara uma variável do tipo PilhaChar

    inicializar(&p);

    printf("Tentando empilhar A, B, C, D...\n");
    if (pushChar(&p, 'A')) { 
        printf("Empilhou A\n");
    } else {
        printf("Falha ao empilhar A (pilha cheia?)\n");
    }

    if (pushChar(&p, 'B')) {
        printf("Empilhou B\n");
    } else {
        printf("Falha ao empilhar B (pilha cheia?)\n");
    }

    if (pushChar(&p, 'C')) {
        printf("Empilhou C\n");
    } else {
        printf("Falha ao empilhar C (pilha cheia?)\n");
    }

    if (pushChar(&p, 'D')) {
        printf("Empilhou D\n");
    } else {
        printf("Falha ao empilhar D (pilha cheia?)\n");
    }

    printf("\nEstado da pilha apos empilhar:\n");
    exibir(&p);

    printf("\nTopo da pilha: ");
    char topo = topChar(&p);
    if (topo != '\0') { // Verifica se topChar não retornou erro
        printf("'%c'\n", topo);
    }

    printf("\nDesempilhando um elemento: ");
    char removido = popChar(&p);
    if (removido != '\0') { // Verifica se popChar não retornou erro
        printf("'%c'\n", removido);
    }

    printf("\nEstado da pilha apos desempilhar:\n");
    exibir(&p);

    // Teste de esvaziamento
    printf("\nEsvaziando a pilha...\n");
    while (!vazia(&p)) {
        printf("Desempilhou: '%c'\n", popChar(&p));
    }
    
    printf("\nEstado final da pilha:\n");
    exibir(&p);
    
    // Tentando desempilhar de pilha vazia (para ver a mensagem de erro)
    printf("\nTentando desempilhar de pilha vazia novamente:\n");
    popChar(&p);

    return 0;
}