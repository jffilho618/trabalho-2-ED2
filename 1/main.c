#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciamento.h"

int main() {
    int op;
    Arv23 *raiz2_3 = NULL;
    char *palavra_portugues;
    int unidade;
    do
    {
        menu_principal();
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            ler_dados(&raiz2_3);
            break;

        case 2:
            imprimir_arvore_23(raiz2_3);
            break;
        
        case 3:
            printf("Digite a unidade para qual deseja ver as palavras em inglês: ");
            scanf("%d", &unidade);
            imprimir_portugues_ingles(raiz2_3, unidade); 
            break;
        
        case 4:
            printf("Digite a palavra em português para qual deseja ver as traduções em inglês: ");
            scanf("%s", palavra_portugues);
            mostrar_tudo_ingles(raiz2_3, palavra_portugues);
            break;
        
        default:
            break;
        }
    } while (op != 0);
    
}
