#include "minimax.h"

char setSide(char s)
{
    if (s == 'g')
        mySide = s;
    else
        mySide = 'r';
    return mySide;
}
int alphabeta(Node *node, int depth, int alpha, int beta, int maximizingPlayer)
//minimax com poda alfa-beta
{
    char nextMove;
    if ((mySide == 'r' && maximizingPlayer == TRUE) || (mySide == 'g' && maximizingPlayer == FALSE))
        nextMove = 'r';
    else
        nextMove = 'g';

    int isTerminal = 0;
    isTerminal = endGame(node);
    int value = 0;
    if (!depth || isTerminal)
    {
        if (isTerminal)
            return isTerminal;
        else
            return h(node);
    }
    getNodeChildren(node, nextMove);
    if (maximizingPlayer)
    {
        value = -__INT_MAX__;
        for (int i = 0; i < node->childrenSize; i++)
        {
            value = max(value, alphabeta(node->children[i], depth - 1, alpha, beta, FALSE));
            alpha = max(alpha, value);
            // if (alpha <= beta)
            // {
            //     break;
            // }
        }
        return value;
    }
    else
    {

        value = __INT_MAX__;
        for (int i = 0; i < node->childrenSize; i++)
        {
            value = min(value, alphabeta(node->children[i], depth - 1, alpha, beta, TRUE));
            beta = min(beta, value);
            // if (alpha <= beta)
            // {
            //     break;
            // }
        }
        return value;
    }
}

//encontra e atribui todos os possiveis movimentos a node->nodeChildren
void getNodeChildren(Node *node, char foxMove)
{
    char **board = boardCopy(node->board);

    Node **children = calloc(1, sizeof(Node *));
    children[0] = calloc(1, sizeof(Node));
    children[0]->board = board;
    children[0]->children = 0;
    children[0]->childrenSize = 0;
    sprintf(children[0]->move, "r n"); //movimento invalido
    node->children = children;

    //se for movivmento da raposa
    if (foxMove == 'r')
    {
        int l, c;

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] == 'r')
                {
                    l = i;
                    c = j;
                }
            }
        }
        //TODO: encontrar todos os nodos resultantes pra raposa;
        searchFoxMove(l, c, board, node, FALSE);

        ;
    }
    else
    {
        //TODO: encontrar todos os nodos resultantes pra ganço;
        searchGeeseMoves(node);
    }
}
//calcula heuristica para o nodo
int h(Node *node)
{
    char **board = node->board;
    int result = 0;
    int rL, rC;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == 'r')
            {
                rL = i;
                rC = j;
            }
        }
    }
    int hDist = 0;
    int hSeg = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == 'g')
            {
                int d = distancia(rL, rC, i, j);

                hDist += 80 - (d * d);                        // Distancia maxima² - distancia²  para "aproximar os ganços da raposa
                hSeg += (K_ganco + gansoSeguro(i, j, board)); // K_ganco(valor não muito alto nem muito baixo para afetar no peso) + fator de segurança do ganço
            }
        }
    }
    result = hDist * hSeg;

    if (mySide == 'g')
    {
        return result;
    }
    else
    {
        return (-result);
    }
}
void searchFoxMove(int l, int c, char **board, Node *node, int attackChainIndex)
{
    //se não estiver em uma cadeia de ataque
    if (attackChainIndex == FALSE)
    {
        //Movimentos
        {
            if (board[l + 1][c] == '-')
            {
                Node *newNode = calloc(1, sizeof(Node));
                newNode->board = boardCopy(board);
                newNode->board[l][c] = '-';
                newNode->board[l + 1][c] = 'r';
                sprintf(newNode->move, "r m %d %d %d %d", l, c, (l + 1), c);

                node->childrenSize++;
                node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
                node->children[node->childrenSize - 1] = newNode;
            }

            if (board[l - 1][c] == '-')
            {
                Node *newNode = calloc(1, sizeof(Node));
                newNode->board = boardCopy(board);
                newNode->board[l][c] = '-';
                newNode->board[l - 1][c] = 'r';
                sprintf(newNode->move, "r m %d %d %d %d", l, c, (l - 1), c);

                node->childrenSize++;
                node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
                node->children[node->childrenSize - 1] = newNode;
            }

            if (board[l][c + 1] == '-')
            {
                Node *newNode = calloc(1, sizeof(Node));
                newNode->board = boardCopy(board);
                newNode->board[l][c] = '-';
                newNode->board[l][c + 1] = 'r';
                sprintf(newNode->move, "r m %d %d %d %d", l, c, l, (c + 1));

                node->childrenSize++;
                node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
                node->children[node->childrenSize - 1] = newNode;
            }
            if (board[l][c - 1] == '-')
            {
                Node *newNode = calloc(1, sizeof(Node));
                newNode->board = boardCopy(board);
                newNode->board[l][c] = '-';
                newNode->board[l][c - 1] = 'r';
                sprintf(newNode->move, "r m %d %d %d %d", l, c, l, (c - 1));

                node->childrenSize++;
                node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
                node->children[node->childrenSize - 1] = newNode;
            }
        }
        ////Primeiros Ataques
        {
            if ((board[l + 1][c] == 'g') && (board[l + 2][c] == '-'))
            {
                Node *newNode = calloc(1, sizeof(Node));
                newNode->board = boardCopy(board);
                newNode->board[l][c] = '-';
                newNode->board[l + 1][c] = '-';
                newNode->board[l + 2][c] = 'r';
                sprintf(newNode->move, "r s 1 %d %d %d %d", l, c, (l + 2), c);

                node->childrenSize++;
                node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
                node->children[node->childrenSize - 1] = newNode;

                char chain[250];
                sprintf(chain, "%d %d %d %d", l, c, (l + 2), c);
                recursiveFoxAttack(l + 2, c, newNode->board, node, 1, chain);
            }

            if ((board[l - 1][c] == 'g') && (board[l - 2][c] == '-'))
            {
                Node *newNode = calloc(1, sizeof(Node));
                newNode->board = boardCopy(board);
                newNode->board[l][c] = '-';
                newNode->board[l - 1][c] = '-';
                newNode->board[l - 2][c] = 'r';
                sprintf(newNode->move, "r s 1 %d %d %d %d", l, c, (l - 2), c);

                node->childrenSize++;
                node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
                node->children[node->childrenSize - 1] = newNode;

                char chain[250];
                sprintf(chain, "%d %d %d %d", l, c, (l - 2), c);
                recursiveFoxAttack(l - 2, c, newNode->board, node, 1, chain);
            }

            if ((board[l][c + 1] == 'g') && (board[l][c + 2] == '-'))
            {
                Node *newNode = calloc(1, sizeof(Node));
                newNode->board = boardCopy(board);
                newNode->board[l][c] = '-';
                newNode->board[l][c + 1] = '-';
                newNode->board[l][c + 2] = 'r';
                sprintf(newNode->move, "r s 1 %d %d %d %d", l, c, l, (c + 2));

                node->childrenSize++;
                node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
                node->children[node->childrenSize - 1] = newNode;

                char chain[250];
                sprintf(chain, "%d %d %d %d", l, c, l, c + 2);
                recursiveFoxAttack(l, c + 2, newNode->board, node, 1, chain);
            }
            if ((board[l][c - 1] == 'g') && (board[l][c - 2] == '-'))
            {
                Node *newNode = calloc(1, sizeof(Node));
                newNode->board = boardCopy(board);
                newNode->board[l][c] = '-';
                newNode->board[l][c - 1] = '-';
                newNode->board[l][c - 2] = 'r';
                sprintf(newNode->move, "r s 1 %d %d %d %d", l, c, l, (c - 2));

                node->childrenSize++;
                node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
                node->children[node->childrenSize - 1] = newNode;

                char chain[250];
                sprintf(chain, "%d %d %d %d", l, c, l, c - 2);
                recursiveFoxAttack(l - 2, c, newNode->board, node, 1, chain);
            }
        }
    }
}
void recursiveFoxAttack(int l, int c, char **board, Node *node, int attackNumber, char *attackChain)
{

    {
        if ((board[l + 1][c] == 'g') && (board[l + 2][c] == '-'))
        {
            Node *newNode = calloc(1, sizeof(Node));
            newNode->board = boardCopy(board);
            newNode->board[l][c] = '-';
            newNode->board[l + 1][c] = '-';
            newNode->board[l + 2][c] = 'r';
            sprintf(newNode->move, "r s %d %s %d %d", attackNumber + 1, attackChain, (l + 2), c);

            node->childrenSize++;
            node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
            node->children[node->childrenSize - 1] = newNode;

            char chain[250];
            sprintf(chain, " %d %d", (l + 2), c);
            strcat(attackChain, chain);
            recursiveFoxAttack(l + 2, c, newNode->board, node, attackNumber + 1, chain);
        }

        if ((board[l - 1][c] == 'g') && (board[l - 2][c] == '-'))
        {
            Node *newNode = calloc(1, sizeof(Node));
            newNode->board = boardCopy(board);
            newNode->board[l][c] = '-';
            newNode->board[l - 1][c] = '-';
            newNode->board[l - 2][c] = 'r';
            sprintf(newNode->move, "r s %d %s %d %d", attackNumber + 1, attackChain, (l - 2), c);

            node->childrenSize++;
            node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
            node->children[node->childrenSize - 1] = newNode;

            char chain[250];
            sprintf(chain, " %d %d", (l - 2), c);
            recursiveFoxAttack(l - 2, c, newNode->board, node, attackNumber + 1, chain);
        }

        if ((board[l][c + 1] == 'g') && (board[l][c + 2] == '-'))
        {
            Node *newNode = calloc(1, sizeof(Node));
            newNode->board = boardCopy(board);
            newNode->board[l][c] = '-';
            newNode->board[l][c + 1] = '-';
            newNode->board[l][c + 2] = 'r';
            sprintf(newNode->move, "r s %d %s %d %d", attackNumber + 1, attackChain, l, (c + 2));

            node->childrenSize++;
            node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
            node->children[node->childrenSize - 1] = newNode;

            char chain[250];
            sprintf(chain, " %d %d", l, c + 2);
            recursiveFoxAttack(l, c + 2, newNode->board, node, attackNumber + 1, chain);
        }
        if ((board[l][c - 1] == 'g') && (board[l][c - 2] == '-'))
        {
            Node *newNode = calloc(1, sizeof(Node));
            newNode->board = boardCopy(board);
            newNode->board[l][c] = '-';
            newNode->board[l][c - 1] = '-';
            newNode->board[l][c - 2] = 'r';
            sprintf(newNode->move, "r s %d %s %d %d", attackNumber + 1, attackChain, l, (c - 2));

            node->childrenSize++;
            node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
            node->children[node->childrenSize - 1] = newNode;

            char chain[250];
            sprintf(chain, " %d %d", l, c - 2);
            recursiveFoxAttack(l - 2, c, newNode->board, node, attackNumber + 1, chain);
        }
    }
}
int *searchGeeseMoves(Node *node)
{
    char **board = boardCopy(node->board);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == 'g')
            {
                //Movimentos
                if (board[i + 1][j] == '-')
                {
                    Node *newNode = calloc(1, sizeof(Node));
                    newNode->board = boardCopy(board);
                    newNode->board[i][j] = '-';
                    newNode->board[i + 1][j] = 'g';
                    sprintf(newNode->move, "g m %d %d %d %d", i, j, (i + 1), j);

                    node->childrenSize++;
                    node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
                    node->children[node->childrenSize - 1] = newNode;
                }

                if (board[i - 1][j] == '-')
                {
                    Node *newNode = calloc(1, sizeof(Node));
                    newNode->board = boardCopy(board);
                    newNode->board[i][j] = '-';
                    newNode->board[i - 1][j] = 'g';
                    sprintf(newNode->move, "g m %d %d %d %d", i, j, (i - 1), j);

                    node->childrenSize++;
                    node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
                    node->children[node->childrenSize - 1] = newNode;
                }

                if (board[i][j + 1] == '-')
                {
                    Node *newNode = calloc(1, sizeof(Node));
                    newNode->board = boardCopy(board);
                    newNode->board[i][j] = '-';
                    newNode->board[i][j + 1] = 'g';
                    sprintf(newNode->move, "g m %d %d %d %d", i, j, i, (j + 1));

                    node->childrenSize++;
                    node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
                    node->children[node->childrenSize - 1] = newNode;
                }
                if (board[i][j - 1] == '-')
                {
                    Node *newNode = calloc(1, sizeof(Node));
                    newNode->board = boardCopy(board);
                    newNode->board[i][j] = '-';
                    newNode->board[i][j - 1] = 'g';
                    sprintf(newNode->move, "g m %d %d %d %d", i, j, i, (j - 1));

                    node->childrenSize++;
                    node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
                    node->children[node->childrenSize - 1] = newNode;
                }
            }
        }
    }
    return (node->childrenSize);
}

//copia em nova area de memoria
char **boardCopy(char **oldBoard)
{
    char **board = calloc(9, sizeof(char *));
    for (int i = 0; i < 9; i++)
    {
        board[i] = calloc(9, sizeof(char));
        for (int j = 0; j < 9; j++)
        {
            board[i][j] = oldBoard[i][j];
        }
    }
    return board;
}
//Distancia de manhattan entre 2 ponto
int distancia(int x1, int y1, int x2, int y2)
{
    return absoluto(x1 - x2) + absoluto(y1 - y2);
}

//Verificação se o ganço esta seguro
int gansoSeguro(int x, int y, char **field)
{ //pode morrer na horizontal
    if (field[x + 1][y] == '-' && field[x - 1][y] == '-')
    {
        return 0;
    }
    //pode morrer na vertical
    if (field[x][y - 1] == '-' && field[x][y + 1] == '-')
    {
        return 0;
    }
    //ganço completamente seguro
    if ((field[x][y - 1] == '#' || field[x][y + 1] == '#') && (field[x + 1][y] == '#' || field[x - 1][y] == '#'))
    {
        return 2;
    }
    //se não caiu nos outros casos, apenas seguro
    return 1;
}

int endGame(Node *node)
{
    char **board = node->board;
    int l, c;
    int numG = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == 'r')
            {
                l = i;
                c = j;
            }
            if (board[i][j] == 'g')
            {
                numG++;
            }
        }
    }

    if (numG < 4)
    {
        if (mySide == 'g')
            return (-__INT_MAX__);

        else
            return (__INT_MAX__);
    }
    //Verifica se a raposa esta presa
    {
        int isTraped = TRUE;

        if (((board[l + 1][c] == 'g') && (board[l + 2][c] == '-')) || (board[l + 1][c] == '-') ||
            ((board[l - 1][c] == 'g') && (board[l - 2][c] == '-')) || (board[l - 1][c] == '-') ||
            ((board[l][c + 1] == 'g') && (board[l][c + 2] == '-')) || (board[l][c + 1] == '-') ||
            ((board[l][c - 1] == 'g') && (board[l][c - 2] == '-')) || (board[l][c - 1] == '-'))
        {
            isTraped = FALSE;
        }

        if (isTraped)
        {
            if (mySide == 'r')
                return (-__INT_MAX__);

            else
                return (__INT_MAX__);
        }
    }
    return FALSE;
}
