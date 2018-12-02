#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "tabuleiro.h"
#include "minimax.h"

#define MAXSTR 512
#define DEPTH 4

void getBoard(char *str, char board[9][9]);

void printBoard(char board[][9]);

int main(int argc, char **argv)
{

    tabuleiro_conecta(argc, argv);
    char buf[MAXSTR];
    char *linha;
    Node *root;

    root = calloc(1, sizeof(Node));
    setSide(argv[1][0]);

    while (1)
    {
        tabuleiro_recebe(buf);
        getBoard(buf, root->board);
        //printBoard(root->board);

        int choiceIndex = 0, choiceH = -__INT_MAX__;
        {
            getNodeChildren(root, mySide);

            for (int i = 1; i < root->childrenSize; i++)
            {
                int r = alphabeta(root->children[i], DEPTH, -__INT_MAX__, +__INT_MAX__, FALSE);
                if (r > choiceH)
                {
                    choiceH = r;
                    choiceIndex = i;
                }
            }
        }
        linha = root->children[choiceIndex]->move;
        // linha = readline(NULL);
        if (linha[0] == '0')
            break;
        printf( "%s\n", linha);

        //sprintf(buf, "%s\n", linha);
        // free(linha);
        tabuleiro_envia(buf);
        liberdade(root);
    }
}

void getBoard(char *str, char newBoard[9][9])
{

    char *pch;
    char board[9][10];
    // printf("%s", str);
    pch = strtok(str, "\n");
    for (int i = -2; pch != NULL; i++)
    {
        if (i >= 0)
            strcpy(board[i], pch);
        pch = strtok(NULL, "\n");
    }

    // newBoard = calloc(9, sizeof(char *));
    for (int i = 0; i < 9; i++)
    {
        // newBoard[i] = calloc(9, sizeof(char));
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = '#';
                newBoard[i][j] = '#';
            }else{
                newBoard[i][j]= board[i][j];
            }
        }
    }
}

void printBoard(char board[][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            printf("%c", board[i][j]);
        printf ("\n");
    }
}