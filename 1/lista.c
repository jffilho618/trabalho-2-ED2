#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento.h"


Elemento *criaLista(){
    return NULL;
}

Elemento *addInicio(Elemento *l){
    //criar novo elemento
    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
    //ajustar o valor do ponteiro para o prox elemento
    novo->prox = l;
    scanf("%d", &novo->info);
    return novo;
}

Elemento *addFinal(Elemento *l){
    Elemento *aux,*novo = (Elemento*) malloc(sizeof(Elemento));
    novo->prox=NULL;
    scanf("%d",&novo->info);
    if (l==NULL)
    {
        l=novo;
    }
    
    else
    {
        aux = l;
        while (aux->prox)
        {
            aux=aux->prox;
        }
        aux->prox=novo;
    }
    
    return l;

}

Elemento *addOrdenadoCrescente(Elemento *l) {
    Elemento *aux, *novo = (Elemento*) malloc(sizeof(Elemento));
    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    // Ler o valor para o novo elemento
    scanf("%d", &novo->info);

    // Caso especial: se a lista estiver vazia ou o novo elemento for menor que o primeiro
    if (l == NULL || novo->info < l->info) {
        novo->prox = l;
        l = novo;
    } else {
        // Caso geral: encontrar a posição correta para o novo elemento
        aux = l;
        while (aux->prox != NULL && aux->prox->info < novo->info) {
            aux = aux->prox;
        }
        novo->prox = aux->prox;
        aux->prox = novo;
    }

    return l;
}

Elemento *removerElemento(Elemento *l) {
    Elemento *aux, *remover = NULL;

    // Verificar se a lista está vazia
    if (l == NULL) {
        printf("Lista vazia\n");
        return l;
    }

    // Solicitar o valor a ser removido
    int valor;
    printf("Digite o valor a ser removido: ");
    scanf("%d", &valor);

    // Caso especial: o valor a ser removido está no primeiro elemento
    if (l->info == valor) {
        remover = l;
        l = l->prox;
        free(remover);
        return l;
    }

    // Percorrer a lista para encontrar o elemento a ser removido
    aux = l;
    while (aux->prox != NULL && aux->prox->info != valor) {
        aux = aux->prox;
    }

    // Verificar se o elemento foi encontrado
    if (aux->prox == NULL) {
        printf("Valor não encontrado\n");
        return l;
    }

    // Remover o elemento encontrado
    remover = aux->prox;
    aux->prox = remover->prox;
    free(remover);

    return l;
}

int tamanhoDaLista(Elemento *l){
    int cont = 0;
    Elemento *aux = l;
    while (aux != NULL)
    {
        cont++;
        aux = aux->prox;
    }
    return cont;
}

void mostrarLista(Elemento *l){
    if (l == NULL)
        printf("Lista vazia ");
    else{
        Elemento *aux = l;
        while (aux != NULL)
        {
            printf("%d -> ", aux->info);
            aux = aux->prox;
        }
        printf("\n");
    }
}