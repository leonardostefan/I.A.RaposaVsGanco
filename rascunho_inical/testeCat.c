#include <stdio.h>
#include <string.h>
void getBoard(char *str, char **board);

void printBoard(char **board);
int main()
{
    char str[] = "r n \n#########\n#  ggg  #\n#  ggg  #\n#-gggggg#\n#g------#\n#---r---#\n#  ---  #\n#  ---  #\n#########\n";
    char *pch;
    printf("Splitting string \"%s\" into tokens:\n", str);
    pch = strtok(str, " ,.-");
    while (pch != NULL)
    {
        printf("%s\n", pch);
        pch = strtok(NULL, "\n");
    }
    return 0;
}

void getBoard(char *str, char **board)
{

    // board = calloc(9, sizeof(char *));
    // for (int i = 0; i < 9; i++)
    // {
    //   board[i] = calloc(10, sizeof(char));
    // }

    char *pch;
    printf("%s", str);
    pch = strtok(str, "\n");
    for (int i = -1; pch != NULL; i++)
    {
        if (i >= 0)
        {
            for (int j = 0; j < 9; j++)
            {
            }
            // sprintf(board[i], "%s", pch);
            // printf( "%d :%s",i, pch);
        }
        pch = strtok(NULL, "\n");
    }
}

void printBoard(char **board)
{
    for (int i = 0; i < 9; i++)
    {
        printf("%s", board[i]);
    }
}

