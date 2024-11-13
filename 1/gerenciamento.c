#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciamento.h"

void menu_principal()
{
    printf("\n");
    printf("╔═══════════════════════TRABALHO═════════════════════╗\n");
    printf("║ [1] PREENCHER ÁRVORE 2-3 / ABB                     ║\n");
    printf("║ [2] IMPRIMIR ÁRVORE 2-3                            ║\n");
    printf("║ [3] IMPRIMIR ABB                                   ║\n");
    printf("║ [4] XXX                                            ║\n");
    printf("║ [5] XXX                                            ║\n");
    printf("║ [6] XXX                                            ║\n");
    printf("║ [0] SAI                                            ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
}

void ler_dados(Arv23 **raiz2_3) {
    FILE *arquivo;
    char palavra_ingles[50];
    char linha[100];
    int unidade = 0; // Unidade atual sendo lida
    arquivo = fopen("vocabulary.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    // Loop para ler o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remover o caractere de nova linha no final da linha, se houver
        linha[strcspn(linha, "\n")] = '\0';

        // Verificar se é o início de uma unidade
        if (linha[0] == '%') {
            sscanf(linha, "%% Unidade %d", &unidade); // Lê o número da unidade
            printf("%% Unidade %d\n", unidade); // Exibe qual unidade está sendo lida
        } else if (strlen(linha) > 0) {
            // Processar a linha para extrair a palavra em inglês e suas traduções
            char *token = strtok(linha, ":"); // Primeira parte é a palavra em inglês
            if (token != NULL) {
                strcpy(palavra_ingles, token);

                // Segunda parte: as traduções em português, separadas por vírgula e terminando com ponto-e-vírgula
                token = strtok(NULL, ";");
                if (token != NULL) {
                    // Declaração da variável para armazenar a chave promovida
                    info23 promove;
                    Arv23 *pai = NULL;

                    // Extrair e processar cada tradução em português separada por vírgulas
                    char *traducao = strtok(token, ",");
                    while (traducao != NULL) {
                        // Remover espaços em branco no início da tradução
                        while (*traducao == ' ') traducao++;

                        // Criar um novo info23 para cada tradução em português
                        info23 novaInfo;
                        novaInfo.Abb = NULL; // Inicializar o ponteiro da ABB
                        strcpy(novaInfo.palavra_portugues, traducao);

                        // Inserir a palavra em inglês na ABB da tradução
                        if (inserir(&(novaInfo.Abb), palavra_ingles, unidade) == 0) {
                            printf("Erro ao inserir a palavra %s na ABB da tradução %s unidade: %d \n", palavra_ingles, traducao, unidade);
                        }

                        // Inserção da tradução na árvore 2-3
                        insere(raiz2_3, novaInfo, &promove, &pai);

                        // Avançar para a próxima tradução em português
                        traducao = strtok(NULL, ",");
                    }
                }
            }
        }
    }

    fclose(arquivo);
}





// void adicionar_palavra_ingles(Arv23 **raiz2_3, char *palavra_portugues1, char *palavra_portugues2, char *palavra_ingles, int unidade) {
    
//     if ((*raiz2_3) != NULL){
//         if(strcmp((*raiz2_3)->info1.palavra_portugues, palavra_portugues1) == 0 || strcmp((*raiz2_3)->info2.palavra_portugues, palavra_portugues1) == 0){
//             strcpy((*raiz2_3)->info1.ingles->palavra_ingles, palavra_ingles);
//             (*raiz2_3)->info1.ingles->unidade = unidade;
//         }

//         if(strcmp((*raiz2_3)->info1.palavra_portugues, palavra_portugues2) == 0 || strcmp((*raiz2_3)->info2.palavra_portugues, palavra_portugues2) == 0){
//             (*raiz2_3)->info2.ingles = (No*)malloc(sizeof(No));
//             strcpy((*raiz2_3)->info2.ingles->palavra_ingles, palavra_ingles);
//             (*raiz2_3)->info2.ingles->unidade = unidade;
//         }

//         adicionar_palavra_ingles(&(*raiz2_3)->Esq, palavra_portugues1, palavra_portugues2, palavra_ingles, unidade);
//         adicionar_palavra_ingles(&(*raiz2_3)->Cen, palavra_portugues1, palavra_portugues2, palavra_ingles, unidade);
//         adicionar_palavra_ingles(&(*raiz2_3)->Dir, palavra_portugues1, palavra_portugues2, palavra_ingles, unidade);
//     }

    
// }

void imprimir_arvore_23(Arv23 *raiz) {
    if (raiz != NULL) {
        printf("Info1: %s\n", raiz->info1.palavra_portugues);
        if (raiz->info2.palavra_portugues[0] != '\0'){
            printf("Info2: %s\n", raiz->info2.palavra_portugues);
        }
        imprimir_arvore_23(raiz->Esq);
        imprimir_arvore_23(raiz->Cen);
        imprimir_arvore_23(raiz->Dir);
    }
}

void imprimir_palavras_ingles(Arv23 *raiz2_3) {
    if (raiz2_3 != NULL) {
        imprimir_arvore_abb(raiz2_3->info1.Abb);
        imprimir_palavras_ingles(raiz2_3->Esq);
        imprimir_palavras_ingles(raiz2_3->Cen);
        imprimir_palavras_ingles(raiz2_3->Dir);
    }
}

void imprimir_abb_p_unidade(No *raiz, int unidade, char *palavra_portugues) {
    if (raiz != NULL) {
        imprimir_abb_p_unidade(raiz->esq, unidade, palavra_portugues);
        if(raiz->unidade == unidade){
            printf("%s: ", palavra_portugues);
            printf("%s, \n", raiz->palavra_ingles);
        }
        imprimir_abb_p_unidade(raiz->dir, unidade, palavra_portugues);
    }
}

void imprimir_portugues_ingles(Arv23 *raiz2_3, int unidade) {
    if (raiz2_3 != NULL) {

        if (raiz2_3->Ninfos >0){
            
            imprimir_abb_p_unidade(raiz2_3->info1.Abb, unidade, raiz2_3->info1.palavra_portugues);
        }
        if (raiz2_3->Ninfos >1){
            imprimir_abb_p_unidade(raiz2_3->info2.Abb, unidade, raiz2_3->info2.palavra_portugues);
        }
        imprimir_portugues_ingles(raiz2_3->Esq, unidade);
        imprimir_portugues_ingles(raiz2_3->Cen, unidade);
        imprimir_portugues_ingles(raiz2_3->Dir, unidade);
    }
}

void imprimir_arvore_abb(No *raiz) {
    if (raiz != NULL) {
        imprimir_arvore_abb(raiz->esq);
        printf("%s ", raiz->palavra_ingles); // Imprime a palavra
        printf("Unidade: %d\n", raiz->unidade);
        imprimir_arvore_abb(raiz->dir);
    }
}

void mostrar_tudo_ingles(Arv23 *raiz2_3, char *palavra_portugues) {
    if (raiz2_3 != NULL) {
        // Verifica se o nó possui ao menos uma chave (info1) e se há correspondência com a palavra
        if (raiz2_3->Ninfos > 0) {
            if (strcmp(raiz2_3->info1.palavra_portugues, palavra_portugues) == 0) {
                printf("%s: ", palavra_portugues);
                imprimir_arvore_abb(raiz2_3->info1.Abb);
                return;  // Palavra encontrada, interrompe a busca
            }
            // Verifica a segunda chave (info2) se existir (Ninfos == 2)
            if (raiz2_3->Ninfos == 2 && strcmp(raiz2_3->info2.palavra_portugues, palavra_portugues) == 0) {
                printf("%s: ", palavra_portugues);
                imprimir_arvore_abb(raiz2_3->info2.Abb);
                return;  // Palavra encontrada, interrompe a busca
            }
        }

        // Caso a palavra não tenha sido encontrada neste nó, busca nos filhos
        mostrar_tudo_ingles(raiz2_3->Esq, palavra_portugues);
        mostrar_tudo_ingles(raiz2_3->Cen, palavra_portugues);
        mostrar_tudo_ingles(raiz2_3->Dir, palavra_portugues);
    }
}
