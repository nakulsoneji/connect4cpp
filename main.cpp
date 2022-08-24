#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#define DEFAULT 7

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
char turn = '1';
char winner = ' ';

struct index2D
{
    int a;
    int b;
};

index2D i1 = {-1, -1};
index2D i2 = {-1, -1};
index2D i3 = {-1, -1};
index2D i4 = {-1, -1};
index2D winValues[] = {i1, i2, i3, i4};

void printBoard(std::vector<std::vector<char>> board)
{
    const std::string EDGE_ROW_TOP = "  1  |  2  |  3  |  4  |  5  |  6  |  7  ";
    const std::string EDGE_ROW_BOTTOM = "     |     |     |     |     |     |     ";
    const std::string MIDDLE_ROW = "-----|-----|-----|-----|-----|-----|-----";

    for (int i = 0; i < board.size(); i++)
    {
        if (i == 0)
        {
            SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            std::cout << EDGE_ROW_TOP << std::endl;
            SetConsoleTextAttribute(console, DEFAULT);
        }
        else
        {
            SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            std::cout << MIDDLE_ROW << std::endl; 
            SetConsoleTextAttribute(console, DEFAULT);
        }
        for (int j = 0; j < board[i].size(); j++)
        {
            char marker = ' ';

            if (board[i][j] == '1')
            {
                SetConsoleTextAttribute(console, FOREGROUND_RED);
                marker = 'O';
                if (winValues[0].a != -1)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        if (i == winValues[k].a && j == winValues[k].b)
                        {
                            marker = 'X';
                            break;
                        }
                    }
                }
            }
            else if (board[i][j] == '2')
            {
                marker = 'O';
                SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN);
                if (winValues[0].a != -1)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        if (i == winValues[k].a && j == winValues[k].b)
                        {
                            marker = 'X';
                            break;
                        }
                    }
                } 
            }
            if (j == 0)
            {
                std::cout << "  " << marker << "\033[34m  |  \033[0m";
            }
            else if (j == board[0].size() - 1)
            {
                std::cout << marker << "  \n";
            }
            else
            {
                std::cout << marker << "\033[34m  |  \033[0m";
            }
        }
        SetConsoleTextAttribute(console, DEFAULT);
        if (i == board.size() - 1)
        {
            SetConsoleTextAttribute(console, FOREGROUND_BLUE);
            std::cout << EDGE_ROW_BOTTOM << std::endl;
            SetConsoleTextAttribute(console, DEFAULT);
        }
    }
    SetConsoleTextAttribute(console, DEFAULT);
}

void getInput(std::vector<std::vector<char>> &board)
{
    int column;

    do
    {
        if (turn == '1')
        {
            SetConsoleTextAttribute(console, FOREGROUND_RED);
        }
        else if (turn == '2')
        {
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN);
        }

        std::cout << "\nplayer " << turn;
        SetConsoleTextAttribute(console, DEFAULT);
        std::cout << " column: ";
        std::cin >> column;
        std::cout << std::endl;

    } while (board[0][column - 1] != ' ');
    
    for (int i = board.size() - 1; i >= 0; i--)
    {
        if (board[i][column - 1] == ' ')
        {
            board[i][column - 1] = turn;
            break;
        }
    }
    
    switch(turn)
    {
        case '1':
            turn = '2';
            break;
        case '2':
            turn = '1';
            break;
    }
}

void onWin(std::vector<std::vector<char>> board, int i, int j)
{
    winner = board[i][j];
    std::string color = (winner == '1') ? "red" : "yellow";
    printBoard(board);

    if (color == "red")
    {
        SetConsoleTextAttribute(console, FOREGROUND_RED);
    }
    else if (color == "yellow")
    {
        SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN);
    }

   
    std::cout << std::endl << color;
    SetConsoleTextAttribute(console, DEFAULT);
    std::cout << " wins!\n\n";
}

bool check(std::vector<std::vector<char>> board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (j + 4 <= board[i].size() && board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == board[i][j + 3] && board[i][j] != ' ')
            {
                winValues[0] = {i, j};
                winValues[1] = {i, j + 1};
                winValues[2] = {i, j + 2};
                winValues[3] = {i, j + 3};
                onWin(board, i, j);
                return true;
            }
            else if (i + 4 <= board.size() && board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == board[i + 3][j] && board[i][j] != ' ')
            {
                winValues[0] = {i, j};
                winValues[1] = {i + 1, j};
                winValues[2] = {i + 2, j};
                winValues[3] = {i + 3, j};
                onWin(board, i, j);
                return true;
            }
            else if (i + 4 <= board.size() && j + 4 <= board[i].size() && board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == board[i + 3][j + 3] && board[i][j] != ' ')
            {
                winValues[0] = {i, j};
                winValues[1] = {i + 1, j + 1};
                winValues[2] = {i + 2, j + 2};
                winValues[3] = {i + 3, j + 3};
                onWin(board, i, j);
                return true;
            }
            else if (i - 3 >= 0 && j + 4 <= board[i].size() && board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 2][j + 2] == board[i - 3][j + 3] && board[i][j] != ' ')
            {
                winValues[0] = {i, j};
                winValues[1] = {i - 1, j + 1};
                winValues[2] = {i - 2, j + 2};
                winValues[3] = {i - 3, j + 3};
                onWin(board, i, j);
                return true;
            }
        }
    }
    return false;
}

int main()
{
    std::vector<std::vector<char>> board = 
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };  

    while(check(board) == false)
    {
        printBoard(board);
        getInput(board);  
    }
}