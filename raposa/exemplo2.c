#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "tabuleiro.h"

#define MAXSTR 512
void getBoard(char *str, char board[][10]);

void printBoard(char board[][10]);

int main(int argc, char **argv)
{
  int movLeft = __INT_MAX__;
  char buf[MAXSTR];
  char *linha;
  char board[9][10];

  tabuleiro_conecta(argc, argv);
  while (1)
  {
    tabuleiro_recebe(buf);
    getBoard(buf, board);
    printBoard(board);
    // printf("%s", buf);
    linha = readline(NULL);
    if (linha[0] == '0')
      break;
    sprintf(buf, "%s\n", linha);
    free(linha);
    tabuleiro_envia(buf);
  }
}

void getBoard(char *str, char board[][10])
{

  char *pch;
  char *aux;
  // printf("%s", str);
  pch = strtok(str, "\n");
  for (int i = -2; pch != NULL; i++)
  {
    if (i >= 0)
      strcpy(board[i], pch);
    pch = strtok(NULL, "\n");
  }
  for (int i=0 ;i<9;i++){
    for(int j=0 ;j<9;j++){
      if (board[i][j]==' '){
        board[i][j]='#';
      }
    }
  }


}

void printBoard(char board[][10])
{
  for (int i = 0; i < 9; i++)
  {
    printf("%s\n", board[i]);
  }
}