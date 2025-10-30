#include "PE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funções Pilha Estática

//função para criar uma pilha
void cria_pilha(Pilha *p) {
    p->topo = -1;
}

//função que verifica se a pilha está vazia
int p_vazia(Pilha *p){
    return p->topo == -1;
}

//função que verifica se a pilha está cheia
int p_cheia(Pilha *p){
    return p->topo == MAX_HISTORICO - 1;
}

//função que insere um elemento na pilha
int push_p(Pilha *p, URL url){
    if (p_cheia(p)){
        return 0; //pilha cheia
    }
    else{
        p->topo++;
        strcpy(p->info[p->topo], url);
        return 1;
    }
}

//função que remove um elemento da pilha
int pop_p(Pilha *p, URL url){
    if(p_vazia(p)){
        return 0; //pilha vazia
    }
    else{
        strcpy(url, p->info[p->topo]);
        p->topo--;
        return 1;
    }
}

//função que remove a base elemento da pilha
int remove_base(Pilha *p) {
    if (p_vazia(p)) {
        return 0; // Pilha vazia
    }
    if (p->topo + 1 < MAX_HISTORICO) {
        return 0;
    }
    for (int i = 0; i < p->topo; i++) {//desloca todos os elementos do índice 1 para cima
        strcpy(p->info[i], p->info[i + 1]); //copia o elemento i+1 para a posição i
    }
    p->topo--;//O topo diminui
    return 1;
}

//função que retorna o tamanho da pilha
int p_tam(Pilha *p){
    return p-> topo + 1;
}

//função que libera a pilha
void free_p(Pilha *p){
    //não faz nada já que a pilha é estática
}
