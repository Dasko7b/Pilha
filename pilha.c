#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"


void inicializar(PilhaChar* p){
    p->topo = -1;
}
bool pushChar(PilhaChar* p, char c){
    if (p->topo < 50)
    {
        p->topo= p->topo + 1;
        p->dados[p->topo] = c;
        return true;
    }
    return false;
    
}
char popChar(PilhaChar* p){
    if (vazia(p))
    {
        printf("pilha vazia, pop impossível\n");
        return '\0';
    }

    char aux = p->dados[p->topo];
    p->topo = p->topo - 1;
    return aux;
}
char topChar(PilhaChar* p){
    if(vazia(p)){
        printf("pilha sem elementos");
        return '\0';
    }
    return p->dados[p->topo];
}
bool vazia(PilhaChar* p){
    if (p->topo == -1)
    {
        return true;
    }
    return false;
}
void exibir(PilhaChar* p){
    if (vazia(p))
    {
        printf("lista vazia\n");
    }else{
        int i = 0;
        for (i = 0; i <= p->topo; i++)
        {
            printf("Elemento: %c\n",p->dados[i]);
        }
        
    }
    
}