#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento.h"
#include <string.h>


// Função para criar uma árvore vazia
No* criarARVORE() {
    return NULL;
}

// Função para inserir uma palavra na árvore ABB
int inserir(No **raiz, char *palavra_ingles, int unidade) {
    if (*raiz == NULL) {
        // Cria um novo nó quando a árvore está vazia ou o espaço é encontrado
        No *novo = (No*)malloc(sizeof(No));
        if (novo == NULL) {
            printf("Erro ao alocar memória para o novo nó\n");
            return 0;  // Falha na inserção
        }
        strcpy(novo->palavra_ingles, palavra_ingles);
        novo->unidade = unidade;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;  // Atualiza a raiz por referência
        return 1;  // Inserção bem-sucedida
    } else {
        
        // Se a palavra é menor, insere na subárvore esquerda
        if (strcmp(palavra_ingles, (*raiz)->palavra_ingles) < 0) {
            return inserir(&((*raiz)->esq), palavra_ingles, unidade);
        } else {
            // Se a palavra é maior, insere na subárvore direita
            return inserir(&((*raiz)->dir), palavra_ingles, unidade);
        }
    }
}



// Função para obter o tamanho da árvore
int tamanho(No *raiz) {
    if (raiz == NULL) {
        return 0;
    } else {
        return 1 + tamanho(raiz->esq) + tamanho(raiz->dir);
    }
}

// Função para buscar uma palavra na árvore
int busca(No *raiz, char *palavra_ingles) {
    if (raiz == NULL) {
        return 0;
    } else {
        if (strcmp(raiz->palavra_ingles, palavra_ingles) == 0) {
            return 1; // Encontrou a palavra
        } else {
            if (strcmp(palavra_ingles, raiz->palavra_ingles) < 0) {
                return busca(raiz->esq, palavra_ingles);
            } else {
                return busca(raiz->dir, palavra_ingles);
            }
        }
    }
}

// Função para imprimir a árvore em pré-ordem
void imprimir_pre_ordem(No *raiz) {
    if (raiz != NULL) {
        printf("%s ", raiz->palavra_ingles);  // Imprime a palavra
        imprimir_pre_ordem(raiz->esq);
        imprimir_pre_ordem(raiz->dir);
    }
}

// Função para imprimir a árvore em ordem
void imprimir_em_ordem(No *raiz) {
    if (raiz != NULL) {
        imprimir_em_ordem(raiz->esq);
        printf("%s ", raiz->palavra_ingles); // Imprime a palavra
        imprimir_em_ordem(raiz->dir);
    }
}

// Função para imprimir a árvore em pós-ordem
void imprimir_pos_ordem(No *raiz) {
    if (raiz != NULL) {
        imprimir_pos_ordem(raiz->esq);
        imprimir_pos_ordem(raiz->dir);
        printf("%s ", raiz->palavra_ingles); // Imprime a palavra
    }
}

// Função para remover uma palavra da árvore
No* remover_abb(No *raiz, char *palavra_ingles) {
    if (raiz == NULL) {
        printf("Palavra não encontrada\n");
        return NULL;
    }
    if (strcmp(raiz->palavra_ingles, palavra_ingles) == 0) {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
        if (raiz->esq == NULL || raiz->dir == NULL) {
            No *aux;
            if (raiz->esq == NULL) {
                aux = raiz->dir;
            } else {
                aux = raiz->esq;
            }
            free(raiz);
            return aux;
        }
        No *aux = raiz->esq;
        while (aux->dir != NULL) {
            aux = aux->dir;
        }
        strcpy(raiz->palavra_ingles, aux->palavra_ingles); // Copia a palavra
        aux->palavra_ingles[0] = '\0'; // Marca como removido
        raiz->esq = remover_abb(raiz->esq, aux->palavra_ingles);
        return raiz;
    }
    if (strcmp(palavra_ingles, raiz->palavra_ingles) < 0) {
        raiz->esq = remover_abb(raiz->esq, palavra_ingles);
    } else {
        raiz->dir = remover_abb(raiz->dir, palavra_ingles);
    }
    return raiz;
}

// Função para buscar um nó contendo uma palavra
No* buscar_no(No *raiz, char *palavra_ingles) {
    if (raiz == NULL || strcmp(raiz->palavra_ingles, palavra_ingles) == 0) {
        return raiz;
    } else if (strcmp(palavra_ingles, raiz->palavra_ingles) < 0) {
        return buscar_no(raiz->esq, palavra_ingles);
    } else {
        return buscar_no(raiz->dir, palavra_ingles);
    }
}

// Função para calcular a altura da árvore
int altura(No *raiz) {
    if (raiz == NULL) {
        return -1; // Altura de uma árvore vazia é -1
    } else {
        int altura_esq = altura(raiz->esq);
        int altura_dir = altura(raiz->dir);
        return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
    }
}

// Função para calcular a altura de um nó específico
int altura_no(No *raiz, char *palavra_ingles) {
    No *no = buscar_no(raiz, palavra_ingles);
    if (no == NULL) {
        return -1; // Nó não encontrado
    }
    return altura(no);
}

// Função para liberar a memória ocupada pela árvore
No* libera_arvore(No *raiz) {
    if (raiz != NULL) {
        libera_arvore(raiz->esq);
        libera_arvore(raiz->dir);
        free(raiz);
    }
    return NULL;
}
