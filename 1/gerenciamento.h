// 1) (3,5 pontos) Cada unidade em um livro-texto em inglês contém um vocabulário Inglês-Português de
// palavras que são usadas pela primeira vez em uma unidade em particular. Desejamos converter um conjunto
// de tais vocabulários armazenados em um arquivo Inglês em um conjunto de vocabulários Português-Inglês.
// Para isso considere que:
// (a) Os nomes das unidades são precedidos por um símbolo de porcentagem.
// (b) Há somente uma entrada por linha.
// (c) Uma palavra em Inglês é separada por dois pontos de sua(s) equivalente(s) portuguesa(s); se há mais de
// uma equivalente, elas são separadas por vírgula.
// Exemplo:
//  % Unidade 1
//  Bus: ônibus, barramento;
//  Bug: inseto, problema;
//  Bike: bicicleta;
//  Coller: ventilador;
//  Network: rede de computadores;
//  System: sistema;
//  % Unidade 2
//  Bug: inseto;
//  Bicycle: bicicleta;
//  Fan: ventilador;
//  Network: rede de relacionamento;

// Para produzir as palavras em ordem alfabética, crie uma árvore 2-3 contendo todas as palavras em português
// de todas as unidades e uma árvore binária de busca com as equivalentes inglesas e em cada nó da lista
// contenha também a unidade que pertence aquela palavra em inglês. Assegure-se de que exista apenas um nó
// para cada palavra portuguesa na árvore.
// Além disso, permita ao usuário:
// (i) informar uma unidade e então imprima todas as palavras da unidade em português seguida das
// equivalentes em inglês;
// (ii)informar uma palavra em português e então imprima todas as palavras em inglês equivalente a palavra em
// português dada, independente da unidade;
// (iii)informar uma palavra em inglês e e a unidade a qual a mesma pertence remove-la das árvores binárias
// das quais ela pertence. Caso ela seja a única palavra em uma das árvores binárias, remover também da
// árvore 2-3;
// (iv)informar uma palavra em português e a unidade a qual a mesma pertence e então remove-la, para isto
// deve remover a palavra em inglês da árvore binária correspondente a palavra em português da mesma
// unidade. Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da
// árvore 2-3.
// Faça um experimento que busque por 30 palavras em português para, mostre o caminho percorrido na
// árvore para encontrar o item e o tempo gasto. Depois faça uma análise dos resultados obtidos. 

typedef struct no{
    char palavra_ingles[50];
    int unidade;
    struct no *esq;
    struct no *dir;
}No;

typedef struct info23{
    char palavra_portugues[50];
    No *Abb;
}info23;

struct Arv23{//Estrutura da arvore 2-3
    info23 info1, info2;
    int Ninfos;
    struct Arv23 *Esq, *Cen, *Dir;
};
typedef struct Arv23 Arv23;



//prototipos das funcoes
Arv23 *criaNo(info23 info1, Arv23 *filho_esq, Arv23 *filho_cen, Arv23 *filho_dir);
int ehFolha(Arv23 *raiz);
Arv23 *adicionaChave(Arv23 *raiz, info23 novaInfo, Arv23 *ptr);
Arv23 *quebraNo(Arv23 *raiz, info23 novaInfo, info23 *promove, Arv23 *ptr);
Arv23 *insere(Arv23 **raiz, info23 novaInfo, info23 *promove, Arv23 **pai);
void imprimir(Arv23 *raiz);
int remover(Arv23 **raiz, Arv23 **pai, info23 valor);
int balancear(Arv23 **raiz, Arv23 **pai, int removeu);
int removeInfo2Folha(Arv23 *raiz);
int removeInfo2ComDirFolha(Arv23 *raiz, Arv23*pai);
Arv23 *obterMenorNo(Arv23 *raiz);
int numeroInfosArv(Arv23 *raiz);
Arv23 *obterMaiorNo(Arv23 *raiz);
int removeInfo2NaoFolha(Arv23 *raiz);
int removeInfo1Folha(Arv23 *raiz, Arv23 *pai);
int removeInfo1NaoFolha(Arv23 *raiz);


No* criarARVORE();                           // Cria uma árvore binária vazia
int inserir(No **raiz, char *palavra_ingles, int unidade);  // Insere uma palavra na árvore binária
int tamanho(No *raiz);                        // Retorna o tamanho da árvore binária
int busca(No *raiz, char *palavra_ingles);    // Busca por uma palavra na árvore binária
void imprimir_pre_ordem(No *raiz);            // Imprime a árvore binária em pré-ordem
void imprimir_em_ordem(No *raiz);             // Imprime a árvore binária em ordem
void imprimir_pos_ordem(No *raiz);            // Imprime a árvore binária em pós-ordem
No* remover_abb(No *raiz, char *palavra_ingles);  // Remove uma palavra da árvore binária
No* buscar_no(No *raiz, char *palavra_ingles); // Busca um nó com a palavra na árvore binária
int altura(No *raiz);                         // Calcula a altura da árvore binária
int altura_no(No *raiz, char *palavra_ingles); // Calcula a altura de um nó específico na árvore binária
No* libera_arvore(No *raiz);                  // Libera a memória da árvore binária


void menu_principal();
void ler_dados(Arv23 **raiz2_3);
void adicionar_palavra_ingles(Arv23 **raiz2_3, char *palavra_portugues1, char *palavra_portugues2, char *palavra_ingles, int unidade);
void imprimir_arvore_23(Arv23 *raiz);
void imprimir_arvore_abb(No *raiz);

//item 1
void imprimir_portugues_ingles(Arv23 *raiz2_3, int unidade);
void imprimir_abb_p_unidade(No *raiz, int unidade, char *palavra_portugues);

//item 2
void mostrar_tudo_ingles(Arv23 *raiz2_3, char *palavra_portugues);