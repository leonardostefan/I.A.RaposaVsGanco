#define FALSE 0
#define TRUE !FALSE
#define max(a, b) a > b ? a : b
#define max(a, b) a < b ? a : b
#define absoluto(a) a > 0 ? a : -a
int alphabeta(Node *node, int depth, int alpha, int beta, int maximizingPlayer)
//minimax com poda alfa-beta
{

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
    int childrenSize = 0;
    childrenSize = getNodeChildren(node, );
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
            return value;
        }
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
            return value;
        }
    }
}

typedef struct Node
{
    char **board;
    Node **children;
    int childrenSize;
    char *move;

} Node;

//encontra e atribui todos os possiveis movimentos a node->nodeChildren
int getNodeChildren(Node *node, int foxMove)
{
    char **board = boardCopy(node->board);

    Node **children = calloc(1, sizeof(Node *));
    children[0] = calloc(1, sizeof(Node));
    children[0]->board = board;
    children[0]->children = calloc(40, sizeof(Node *)); //chutei o 40 pode dar erro se a raposa tiver MUITAS possibilidas de atacar
    children[0]->childrenSize = 0;
    children[0]->move = "r n"; // calloc(10, sizeof(char*)); FIX-IT

    //se for movivmento da raposa
    if (foxMove)
    {
        int l, c;

        for (int i = 3; i < 6; i++)
        {
            for (int j = 1; j < 8; j++)
            {
                if (board[i][j] == 'r')
                {
                    l = i;
                    c = j;
                }
            }
        }
        //TODO: encontrar todos os nodos resultantes pra raposa;
        searchFoxMove(l, c, board, children, FALSE);

        ;
    }
    else
    {
        //TODO: encontrar todos os nodos resultantes pra ganço;
        char **board;
        for (int i = 3; i < 6; i++)
        {
            for (int j = 1; j < 8; j++)
            {
            }
        }
    }
}
int h(Node *node)
//calcula heuristica para o nodo
{
    ;
}
int *searchFoxMove(int l, int c, char **board, Node *node, int attackChain)
{
    //se não estiver em uma cadeia de ataque
    if (attackChain == FALSE)
    {
        //Movimentos
        if (board[l + 1][c] == "-")
        {
            Node *newNode = calloc(1, sizeof(Node));
            newNode->board = boardCopy(board);
            newNode->board[l][c] = "-";
            newNode->board[l + 1][c] = "r";
            newNode->move = "r m %d %d %d %d", l, c, (l + 1), c; //FIX-IT   : <jogador> m <l_ini> <c_ini> <l_fin> <c_fin>

            node->childrenSize++;
            node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
            node->children[node->childrenSize - 1] = newNode;
        }

        if (board[l - 1][c] == "-")
        {
            Node *newNode = calloc(1, sizeof(Node));
            newNode->board = boardCopy(board);
            newNode->board[l][c] = "-";
            newNode->board[l - 1][c] = "r";
            newNode->move = "r m %d %d %d %d", l, c, (l - 1), c; //FIX-IT   : <jogador> m <l_ini> <c_ini> <l_fin> <c_fin>

            node->childrenSize++;
            node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
            node->children[node->childrenSize - 1] = newNode;
        }

        if (board[l][c + 1] == "-")
        {
            Node *newNode = calloc(1, sizeof(Node));
            newNode->board = boardCopy(board);
            newNode->board[l][c] = "-";
            newNode->board[l][c + 1] = "r";
            newNode->move = "r m %d %d %d %d", l, c, l, (c + 1); //FIX-IT   : <jogador> m <l_ini> <c_ini> <l_fin> <c_fin>

            node->childrenSize++;
            node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
            node->children[node->childrenSize - 1] = newNode;
        }
        if (board[l][c - 1] == "-")
        {
            Node *newNode = calloc(1, sizeof(Node));
            newNode->board = boardCopy(board);
            newNode->board[l][c] = "-";
            newNode->board[l][c - 1] = "r";
            newNode->move = "r m %d %d %d %d", l, c, l, (c - 1); //FIX-IT   : <jogador> m <l_ini> <c_ini> <l_fin> <c_fin>

            node->childrenSize++;
            node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
            node->children[node->childrenSize - 1] = newNode;
        }
        ////Ataques
        if (board[l + 1][c] == "g")
        {
            Node *newNode = calloc(1, sizeof(Node));
            newNode->board = boardCopy(board);
            newNode->board[l][c] = "-";
            newNode->board[l + 1][c] = "r";
            newNode->move = "r s %d %d %d %d", l, c, (l + 1), c; //FIX-IT   : <jogador> m <l_ini> <c_ini> <l_fin> <c_fin>

            node->childrenSize++;
            node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
            node->children[node->childrenSize - 1] = newNode;
        }

        if (board[l - 1][c] == "g")
        {
            Node *newNode = calloc(1, sizeof(Node));
            newNode->board = boardCopy(board);
            newNode->board[l][c] = "-";
            newNode->board[l - 1][c] = "r";
            newNode->move = "r s %d %d %d %d", l, c, (l - 1), c; //FIX-IT   : <jogador> m <l_ini> <c_ini> <l_fin> <c_fin>

            node->childrenSize++;
            node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
            node->children[node->childrenSize - 1] = newNode;
        }

        if (board[l][c + 1] == "g")
        {
            Node *newNode = calloc(1, sizeof(Node));
            newNode->board = boardCopy(board);
            newNode->board[l][c] = "-";
            newNode->board[l][c + 1] = "r";
            newNode->move = "r s %d %d %d %d", l, c, l, (c + 1); //FIX-IT   : <jogador> m <l_ini> <c_ini> <l_fin> <c_fin>

            node->childrenSize++;
            node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
            node->children[node->childrenSize - 1] = newNode;
        }
        if (board[l][c - 1] == "g")
        {
            Node *newNode = calloc(1, sizeof(Node));
            newNode->board = boardCopy(board);
            newNode->board[l][c] = "-";
            newNode->board[l][c - 1] = "r";
            newNode->move = "r s %d %d %d %d", l, c, l, (c - 1); //FIX-IT   : <jogador> m <l_ini> <c_ini> <l_fin> <c_fin>

            node->childrenSize++;
            node->children = realloc(node->children, node->childrenSize * sizeof(Node *));
            node->children[node->childrenSize - 1] = newNode;
        }
    }
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

//Verifixação se o ganço esta seguro
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
