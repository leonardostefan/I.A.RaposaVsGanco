#ifndef __MINIMAX__
#define __MINIMAX__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE !FALSE
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b
#define absoluto(a) a > 0 ? a : -a
#define MAXMOVESTR 256
#define K_ganco 2
char mySide;

typedef struct Node
{
    char board[9][9];
    int childrenSize;
    char move[MAXMOVESTR];
    struct Node **children;

} Node;

char setSide(char s);

//minimax com poda alfa-beta
int alphabeta(Node *node, int depth, int alpha, int beta, int maximizingPlayer);


//verifica se é estado final
int endGame(Node* node);

//encontra e atribui todos os possiveis movimentos a node->nodeChildren
void getNodeChildren(Node *node, char foxMove);
void searchFoxMove(int l, int c, char board[9][9], Node *node, int attackChainIndex);
void recursiveFoxAttack(int l, int c, char board[9][9], Node *node, int attackNumber, char *attackChain);
int searchGeeseMoves(Node *node);

//copia em nova area de memoria
void boardCopy(char oldBoard[9][9], char board[9][9]);

//calcula heuristica para o nodo
int h(Node *node);
//Distancia de manhattan entre 2 ponto
int distancia(int x1, int y1, int x2, int y2);
//Verifixação se o ganço esta seguro
int gansoSeguro(int x, int y, char field[9][9]);

#endif