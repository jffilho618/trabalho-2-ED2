#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento.h"
#include <string.h>

// Função para criar um novo nó
Arv23 *criaNo(info23 info1, Arv23 *filho_esq, Arv23 *filho_cen, Arv23 *filho_dir) {
    Arv23 *no = (Arv23*)malloc(sizeof(Arv23));
    if (no != NULL) {
        no->info1 = info1;
        no->info2.palavra_portugues[0] = '\0';  // Inicializa a segunda chave como vazia
        no->info2.Abb = NULL;  // Inicializa o ponteiro `Abb` da segunda chave como NULL
        no->Ninfos = 1;  // Indica que o nó tem uma chave
        no->Esq = filho_esq;
        no->Cen = filho_cen;
        no->Dir = filho_dir;
    }
    return no;
}

// Função para verificar se o nó é folha
int ehFolha(Arv23 *raiz) {
    return raiz->Esq == NULL;  // Se o nó não tem filhos, é folha
}

// Função para adicionar uma chave no nó
Arv23 *adicionaChave(Arv23 *raiz, info23 novaInfo, Arv23 *ptr) {
    if (strcmp(novaInfo.palavra_portugues, raiz->info1.palavra_portugues) > 0) {
        raiz->info2 = novaInfo;
        raiz->Dir = ptr;
        raiz->Ninfos = 2;  // Agora o nó tem duas chaves
    } else {
        raiz->info2 = raiz->info1;
        raiz->info1 = novaInfo;
        raiz->Dir = raiz->Cen;
        raiz->Cen = ptr;
        raiz->Ninfos = 2;
    }
    return raiz;
}

// Função para quebrar um nó quando ele está cheio
Arv23 *quebraNo(Arv23 *raiz, info23 novaInfo, info23 *promove, Arv23 *ptr) {
    Arv23 *novo;

    // Verifica onde inserir a nova chave
    if (strcmp(novaInfo.palavra_portugues, raiz->info1.palavra_portugues) < 0) {
        *promove = raiz->info1;
        novo = criaNo(raiz->info2, raiz->Cen, raiz->Dir, NULL);
        raiz->info1 = novaInfo;
        raiz->Cen = ptr;
    } else if (strcmp(novaInfo.palavra_portugues, raiz->info2.palavra_portugues) < 0) {
        *promove = novaInfo;
        novo = criaNo(raiz->info2, ptr, raiz->Dir, NULL);
    } else {
        *promove = raiz->info2;
        novo = criaNo(novaInfo, raiz->Dir, ptr, NULL);
    }

    raiz->info2.palavra_portugues[0] = '\0';  // Limpa info2
    raiz->info2.Abb = NULL;  // Limpa o ponteiro `Abb` da segunda chave
    raiz->Ninfos = 1;  // Marca o nó como com uma chave
    raiz->Dir = NULL;

    return novo;
}

// Função para inserir uma chave na árvore
Arv23 *insere(Arv23 **raiz, info23 novaInfo, info23 *promove, Arv23 **pai) {
    Arv23 *MaiorNo = NULL;
    info23 promove1;

    if (*raiz == NULL) {
        *raiz = criaNo(novaInfo, NULL, NULL, NULL);
    } else {
        if (strcmp(novaInfo.palavra_portugues, (*raiz)->info1.palavra_portugues) == 0) {
            if (inserir(&((*raiz)->info1.Abb), novaInfo.Abb->palavra_ingles, novaInfo.Abb->unidade)) {
                printf("Palavra %s adicionada para a tradução %s unidade: %d\n", novaInfo.Abb->palavra_ingles, novaInfo.palavra_portugues, novaInfo.Abb->unidade);
            }
            return NULL;
        }
        if ((*raiz)->Ninfos == 2 && strcmp(novaInfo.palavra_portugues, (*raiz)->info2.palavra_portugues) == 0) {
            if (inserir(&((*raiz)->info2.Abb), novaInfo.Abb->palavra_ingles, novaInfo.Abb->unidade)) {
                printf("Palavra %s adicionada para a tradução %s unidade: %d\n", novaInfo.Abb->palavra_ingles, novaInfo.palavra_portugues, novaInfo.Abb->unidade);
            }
            return NULL;
        }


        if (ehFolha(*raiz)) {
            if ((*raiz)->Ninfos == 1) {
                *raiz = adicionaChave(*raiz, novaInfo, NULL);
            } else {
                MaiorNo = quebraNo(*raiz, novaInfo, promove, NULL);
                if (*pai == NULL) {
                    *raiz = criaNo(*promove, *raiz, MaiorNo, NULL);
                    MaiorNo = NULL;
                }
            }
        } else {
            if (strcmp(novaInfo.palavra_portugues, (*raiz)->info1.palavra_portugues) < 0) {
                MaiorNo = insere(&((*raiz)->Esq), novaInfo, promove, raiz);
            } else if ((*raiz)->Ninfos == 1 || strcmp(novaInfo.palavra_portugues, (*raiz)->info2.palavra_portugues) < 0) {
                MaiorNo = insere(&((*raiz)->Cen), novaInfo, promove, raiz);
            } else {
                MaiorNo = insere(&((*raiz)->Dir), novaInfo, promove, raiz);
            }

            if (MaiorNo != NULL) {
                if ((*raiz)->Ninfos == 1) {
                    *raiz = adicionaChave(*raiz, *promove, MaiorNo);
                    MaiorNo = NULL;
                } else {
                    MaiorNo = quebraNo(*raiz, *promove, &promove1, MaiorNo);
                    *promove = promove1;
                    if (*pai == NULL) {
                        *raiz = criaNo(promove1, *raiz, MaiorNo, NULL);
                        MaiorNo = NULL;
                    }
                }
            }
        }
    }

    return MaiorNo;
}



// void imprimir(Arv23 *raiz){//Imprime todos os elementos da arvore em pre-ordem
//     if(raiz != NULL){
//         printf(" |%d", raiz->info1);
//         if(raiz->info2){//verifica se a info2 esta vazia
//             printf(" %d|", raiz->info2);
//         }else{
//             printf("|");
//         }
//         imprimir(raiz->Esq);
//         imprimir(raiz->Cen);
//         imprimir(raiz->Dir);
//     }
// }

// int remover(Arv23 **raiz, Arv23 **pai, info23 valor) {
//     int removeu = 0;
//     Arv23 *noMenorInfoDir = NULL;

//     if (*raiz != NULL) {
//         // Verifica se o valor corresponde a info1 ou info2
//         if (strcmp(valor.palavra_portugues, (*raiz)->info2.palavra_portugues) == 0 ||
//             strcmp(valor.palavra_portugues, (*raiz)->info1.palavra_portugues) == 0) {
            
//             if (strcmp(valor.palavra_portugues, (*raiz)->info2.palavra_portugues) == 0) { // Caso o elemento a ser removido esteja em info2
//                 if (ehFolha(*raiz)) { // Se for folha, apenas remove o nó
//                     removeu = removeInfo2Folha(*raiz);
//                 } else if (ehFolha((*raiz)->Dir)) {
//                     removeu = removeInfo2ComDirFolha((*raiz)->Dir, *raiz);
//                 } else {
//                     if (numeroInfosArv((*raiz)->Dir) > 3) {
//                         noMenorInfoDir = obterMenorNo((*raiz)->Dir);
//                         (*raiz)->info2 = noMenorInfoDir->info1; // Substitui info2 pelo menor nó na subárvore direita
//                         removeu = remover(&((*raiz)->Dir), raiz, noMenorInfoDir->info1);
//                     } else {
//                         removeu = removeInfo2NaoFolha(*raiz);
//                     }
//                 }
//             } else { // Caso o elemento a ser removido esteja em info1
//                 if (ehFolha(*raiz)) {
//                     removeu = removeInfo1Folha(*raiz, *pai);
//                     if (removeu == 3) {
//                         free(*raiz);
//                         *raiz = NULL;
//                     }
//                 } else {
//                     removeu = removeInfo1NaoFolha(*raiz);
//                 }
//             }
//         } else if (strcmp(valor.palavra_portugues, (*raiz)->info1.palavra_portugues) < 0) {
//             removeu = remover(&((*raiz)->Esq), raiz, valor); // Percorre a esquerda
//         } else if ((*raiz)->Ninfos == 1 || strcmp(valor.palavra_portugues, (*raiz)->info2.palavra_portugues) < 0) {
//             removeu = remover(&((*raiz)->Cen), raiz, valor); // Percorre o centro
//         } else if (strcmp(valor.palavra_portugues, (*raiz)->info2.palavra_portugues) > 0 && (*raiz)->Ninfos == 2) {
//             removeu = remover(&((*raiz)->Dir), raiz, valor); // Percorre a direita
//         }

//         // Realiza o balanceamento se necessário
//         if (removeu == 2) {
//             removeu = balancear(raiz, pai, removeu);
//         }
//     }

//     return removeu;
// }


int balancear(Arv23 **raiz, Arv23 **pai, int removeu) {
    if ((*pai) == NULL) {
        (*raiz) = (*raiz)->Esq;
        removeu = 1;
    } else {
        if ((*pai)->Esq == (*raiz)) {
            if ((*pai)->Cen->Ninfos == 2) {
                (*raiz)->info1 = (*pai)->info1;
                (*raiz)->Cen = (*pai)->Cen->Esq;
                (*pai)->info1 = (*pai)->Cen->info1;
                (*pai)->Cen->info1 = (*pai)->Cen->info2;
                memset((*pai)->Cen->info2.palavra_portugues, 0, sizeof((*pai)->Cen->info2.palavra_portugues));
                (*pai)->Cen->Ninfos = 1;
                (*pai)->Cen->Esq = (*pai)->Cen->Cen;
                (*pai)->Cen->Cen = (*pai)->Cen->Dir;
                (*pai)->Cen->Dir = NULL;
                removeu = 1;
            } else {
                if ((*pai)->Ninfos == 2) {
                    (*raiz)->info1 = (*pai)->info1;
                    (*raiz)->info2 = (*pai)->Cen->info1;
                    (*raiz)->Ninfos = 2;
                    (*raiz)->Cen = (*pai)->Cen->Esq;
                    (*raiz)->Dir = (*pai)->Cen->Cen;
                    free((*pai)->Cen);
                    (*pai)->info1 = (*pai)->info2;
                    memset((*pai)->info2.palavra_portugues, 0, sizeof((*pai)->info2.palavra_portugues));
                    (*pai)->Ninfos = 1;
                    (*pai)->Cen = (*pai)->Dir;
                    (*pai)->Dir = NULL;
                    removeu = 1;
                } else {
                    (*raiz)->info1 = (*pai)->info1;
                    (*raiz)->info2 = (*pai)->Cen->info1;
                    (*raiz)->Ninfos = 2;
                    (*raiz)->Cen = (*pai)->Cen->Esq;
                    (*raiz)->Dir = (*pai)->Cen->Cen;
                    free((*pai)->Cen);
                    (*pai)->Cen = NULL;
                }
            }
        } else if ((*pai)->Cen == (*raiz)) {
            if ((*pai)->Esq->Ninfos == 2) {
                (*raiz)->info1 = (*pai)->info1;
                (*pai)->info1 = (*pai)->Esq->info2;
                (*raiz)->Cen = (*raiz)->Esq;
                (*raiz)->Esq = (*pai)->Esq->Dir;
                (*pai)->Esq->Dir = NULL;
                (*pai)->Esq->Ninfos = 1;
                memset((*pai)->Esq->info2.palavra_portugues, 0, sizeof((*pai)->Esq->info2.palavra_portugues));
                removeu = 1;
            } else {
                if ((*pai)->Ninfos == 2) {
                    (*pai)->Esq->info2 = (*pai)->info1;
                    (*pai)->Esq->Ninfos = 2;
                    (*pai)->Esq->Dir = (*raiz)->Esq;
                    free(*raiz);
                    *raiz = NULL;
                    free((*pai)->Cen);
                    (*pai)->Cen = NULL;
                    (*pai)->info1 = (*pai)->info2;
                    memset((*pai)->info2.palavra_portugues, 0, sizeof((*pai)->info2.palavra_portugues));
                    (*pai)->Ninfos = 1;
                    (*pai)->Cen = (*pai)->Dir;
                    (*pai)->Dir = NULL;
                    removeu = 1;
                } else {
                    (*pai)->Esq->info2 = (*pai)->info1;
                    (*pai)->Esq->Ninfos = 2;
                    (*pai)->Esq->Dir = (*pai)->Cen->Esq;
                    free((*pai)->Cen);
                    (*pai)->Cen = NULL;
                }
            }
        } else {
            if ((*pai)->Cen->Ninfos == 2) {
                (*raiz)->info1 = (*pai)->info2;
                (*raiz)->Cen = (*raiz)->Esq;
                (*raiz)->Esq = (*pai)->Cen->Dir;
                (*pai)->info2 = (*pai)->Cen->info2;
                memset((*pai)->Cen->info2.palavra_portugues, 0, sizeof((*pai)->Cen->info2.palavra_portugues));
                (*pai)->Cen->Ninfos = 1;
                (*pai)->Cen->Dir = NULL;
            } else {
                (*pai)->Cen->info2 = (*pai)->info2;
                (*pai)->Cen->Ninfos = 2;
                (*pai)->Cen->Dir = (*raiz)->Esq;
                free(*raiz);
                *raiz = NULL;
                memset((*pai)->info2.palavra_portugues, 0, sizeof((*pai)->info2.palavra_portugues));
                (*pai)->Ninfos = 1;
                free((*pai)->Dir);
                (*pai)->Dir = NULL;
            }
            removeu = 1;
        }
    }
    return removeu;
}


int removeInfo2Folha(Arv23 *raiz){
    raiz->info2.palavra_portugues[0] = '\0'; // Marca info2 como vazio
    raiz->Ninfos = 1;
    return 1;
}

// int removeInfo2ComDirFolha(Arv23 *raiz, Arv23 *pai) {
//     int removeu = 0;

//     // Caso o nó raiz tenha 2 informações
//     if (raiz->Ninfos == 2) {
//         // Transfere palavra_portugues de raiz->info1 para pai->info2
//         strcpy(pai->info2.palavra_portugues, raiz->info1.palavra_portugues);
//         pai->info2.ingles = raiz->info1.ingles; // Transferir o ponteiro "ingles"
        
//         // Limpa o valor de info1 no nó raiz
//         raiz->info1.palavra_portugues[0] = '\0'; // Marca palavra_portugues como vazio
//         raiz->info1.ingles = NULL;               // Limpa o ponteiro ingles

//         raiz->Ninfos = 1; // Ajusta o número de informações no nó raiz
//         removeu = 1;
//     } else { // Caso o nó raiz tenha apenas 1 informação
//         // Verifica se o nó Cen do pai tem 2 informações
//         if (pai->Cen->Ninfos == 2) {
//             // Transfere palavra_portugues de Cen->info2 para pai->info2
//             strcpy(pai->info2.palavra_portugues, pai->Cen->info2.palavra_portugues);
//             pai->info2.ingles = pai->Cen->info2.ingles; // Transfere o ponteiro "ingles"
            
//             // Limpa o valor de Cen->info2
//             pai->Cen->info2.palavra_portugues[0] = '\0';
//             pai->Cen->info2.ingles = NULL;
//             pai->Cen->Ninfos = 1; // Ajusta o número de informações de Cen
//             removeu = 1;
//         } else {
//             // Caso contrário, transfere palavra_portugues de raiz->info1 para Cen->info2
//             strcpy(pai->Cen->info2.palavra_portugues, raiz->info1.palavra_portugues);
//             pai->Cen->info2.ingles = raiz->info1.ingles; // Transferir ponteiro "ingles"
//             pai->Cen->Ninfos = 2; // Atualiza o número de informações do nó Cen
            
//             // Limpa pai->info2 e atualiza pai->Ninfos
//             pai->info2.palavra_portugues[0] = '\0';
//             pai->info2.ingles = NULL;
//             pai->Ninfos = 1;

//             // Libera a memória do nó raiz
//             free(raiz);
//             pai->Dir = NULL; // Aponta o nó pai->Dir para NULL
//             removeu = 1;
//         }
//     }

//     return removeu;
// }


Arv23 *obterMenorNo(Arv23 *raiz){
    Arv23 *aux = NULL;
    aux = raiz;
    if(raiz->Esq != NULL){
        aux = obterMenorNo(raiz->Esq);
    }
    return aux;
}

int numeroInfosArv(Arv23 *raiz) {
    int cont = 0;
    
    // Verifica se o nó não é NULL
    if (raiz != NULL) {
        // Conta o número de informações no nó atual
        cont += 1;  // Conta info1
        
        // Se houver info2, conta também
        if (raiz->info2.palavra_portugues[0] != '\0') {
            cont += 1;  // Conta info2
        }

        // Chama recursivamente os filhos (Esq, Cen, Dir) para contar as informações em cada subárvore
        cont += numeroInfosArv(raiz->Esq);
        cont += numeroInfosArv(raiz->Cen);
        cont += numeroInfosArv(raiz->Dir);
    }
    
    return cont;
}


Arv23 *obterMaiorNo(Arv23 *raiz){
    Arv23 *aux = NULL;
    aux = raiz;
    if(raiz->Dir != NULL){
        aux = obterMaiorNo(raiz->Dir);
    }else{
        if(raiz->Cen != NULL){
            aux = obterMaiorNo(raiz->Cen);
        }
    }
    return aux;
}

// int removeInfo2NaoFolha(Arv23 *raiz) {
//     int removeu = 0;
    
//     // Obtém o nó com a maior informação da subárvore central (Cen)
//     Arv23 *noMaiorInfoCen = obterMaiorNo(raiz->Cen);

//     // Verifica se o nó com a maior informação tem 2 informações
//     if (noMaiorInfoCen->Ninfos == 2) {
//         // Substitui a info2 do nó raiz pela info2 do nó com a maior informação da subárvore central
//         raiz->info2 = noMaiorInfoCen->info2;
//         // Remove a info2 do nó com a maior informação
//         removeu = remover(&(raiz->Cen), &raiz, noMaiorInfoCen->info2);
//     } else {
//         // Caso o nó tenha apenas uma informação, substitui a info2 do nó raiz pela info1 do nó com a maior informação
//         raiz->info2 = noMaiorInfoCen->info1;
//         // Remove a info1 do nó com a maior informação
//         removeu = remover(&(raiz->Cen), &raiz, noMaiorInfoCen->info1);
//     }

//     return removeu;
// }


// int removeInfo1Folha(Arv23 *raiz, Arv23 *pai) {
//     int removeu = 0;

//     // Caso o nó raiz tenha 2 informações, move info2 para info1
//     if (raiz->Ninfos == 2) {
//         raiz->info1 = raiz->info2;
//         raiz->info2 = (info23){0};  // Limpa a info2
//         raiz->Ninfos = 1;
//         removeu = 1;
//     }
//     // Caso o nó não tenha pai, significa que estamos no nó raiz da árvore
//     else if (pai == NULL) {
//         removeu = 3;  // Caso não seja possível remover sem um pai
//     } 
//     else {
//         // Caso o nó raiz seja o filho esquerdo do pai
//         if (pai->Esq == raiz) {
//             if (pai->Cen->Ninfos == 2) {
//                 // Redistribuição de informações: Move info1 de pai para raiz
//                 raiz->info1 = pai->info1;
//                 pai->info1 = pai->Cen->info1;
//                 pai->Cen->info1 = pai->Cen->info2;
//                 pai->Cen->info2 = (info23){0};  // Limpa a info2
//                 pai->Cen->Ninfos = 1;
//                 removeu = 1;
//             } 
//             else if (pai->Ninfos == 2) {
//                 // Caso o pai tenha 2 informações, promove a info1 de pai e funde
//                 raiz->info1 = pai->info1;
//                 raiz->info2 = pai->Cen->info1;
//                 raiz->Ninfos = 2;
//                 free(pai->Cen);
//                 pai->info1 = pai->info2;
//                 pai->info2 = (info23){0};  // Limpa a info2
//                 pai->Ninfos = 1;
//                 pai->Cen = pai->Dir;
//                 pai->Dir = NULL;
//                 removeu = 1;
//             } else {
//                 // Caso o pai não tenha 2 informações e a redistribuição não for possível
//                 removeu = 2;
//             }
//         }
//         // Caso o nó raiz seja o filho central do pai
//         else if (pai->Cen == raiz) {
//             if (pai->Esq->Ninfos == 2) {
//                 // Redistribui a info2 do nó esquerdo do pai para o nó raiz
//                 raiz->info1 = pai->info1;
//                 pai->info1 = pai->Esq->info2;
//                 pai->Esq->info2 = (info23){0};  // Limpa a info2
//                 pai->Esq->Ninfos = 1;
//                 removeu = 1;
//             }
//             else if (pai->Ninfos == 2) {
//                 if (pai->Dir->Ninfos == 2) {
//                     // Redistribui a info1 do nó direito do pai para o nó raiz
//                     raiz->info1 = pai->info2;
//                     pai->info2 = pai->Dir->info1;
//                     pai->Dir->info1 = pai->Dir->info2;
//                     pai->Dir->info2 = (info23){0};  // Limpa a info2
//                     pai->Dir->Ninfos = 1;
//                     removeu = 1;
//                 }
//                 else {
//                     // Caso o nó direito do pai tenha apenas uma informação, promove e funde
//                     raiz->info1 = pai->info2;
//                     raiz->info2 = pai->Dir->info1;
//                     raiz->Ninfos = 2;
//                     pai->info2 = (info23){0};  // Limpa a info2
//                     pai->Ninfos = 1;
//                     free(pai->Dir);
//                     pai->Dir = NULL;
//                     removeu = 1;
//                 }
//             } else {
//                 // Caso o pai tenha apenas uma informação, não há o que fazer
//                 removeu = 2;
//             }
//         }
//         // Caso o nó raiz seja o filho direito do pai
//         else {
//             if (pai->Cen->Ninfos == 2) {
//                 // Redistribui a info2 do nó central do pai para o nó raiz
//                 raiz->info1 = pai->info2;
//                 pai->info2 = pai->Cen->info2;
//                 pai->Cen->info2 = (info23){0};  // Limpa a info2
//                 pai->Cen->Ninfos = 1;
//                 removeu = 1;
//             } else {
//                 // Caso não seja possível redistribuir, promove e faz a fusão
//                 pai->Cen->info2 = pai->info2;
//                 pai->Cen->Ninfos = 2;
//                 pai->info2 = (info23){0};  // Limpa a info2
//                 pai->Ninfos = 1;
//                 free(pai->Dir);
//                 pai->Dir = NULL;
//                 removeu = 1;
//             }
//         }
//     }
//     return removeu;
// }



// int removeInfo1NaoFolha(Arv23 *raiz) {
//     int removeu = 0;
//     Arv23 *noMaiorInfoEsq = NULL;

//     // Obtém o nó com o maior valor na subárvore esquerda do nó raiz
//     noMaiorInfoEsq = obterMaiorNo(raiz->Esq);

//     // Caso o nó com maior valor na subárvore esquerda tenha 2 informações
//     if (noMaiorInfoEsq->Ninfos == 2) {
//         // Substitui a info1 do nó raiz pela info2 do nó maior da subárvore esquerda
//         raiz->info1 = noMaiorInfoEsq->info2;
//         // Remove a info2 do nó maior da subárvore esquerda
//         removeu = remover(&(raiz->Esq), &raiz, noMaiorInfoEsq->info2);
//     } else {
//         // Caso o nó com maior valor tenha apenas uma informação, usa a info1
//         raiz->info1 = noMaiorInfoEsq->info1;
//         // Remove a info1 do nó maior da subárvore esquerda
//         removeu = remover(&(raiz->Esq), &raiz, noMaiorInfoEsq->info1);
//     }

//     return removeu;
// }
