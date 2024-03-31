#include <bits/stdc++.h>
using namespace std;

#define Computer 1
#define Human 2

#define Side 3

#define ComputerMove 'X'
#define HumanMove 'O'

void showBoard(char board[][Side])
{
  cout << "\n\t\t\t " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
  cout << "\t\t\t-----------\n";
  cout << "\t\t\t " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
  cout << "\t\t\t-----------\n";
  cout << "\t\t\t " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n\n";
}

void showInstructions()
{
  cout << "\nChoose a cell from 1 to 9 as below and play\n\n";

  cout << "\t\t 1 | 2 | 3 \n";
  cout << "\t\t-----------\n";
  cout << "\t\t 4 | 5 | 6 \n";
  cout << "\t\t-----------\n";
  cout << "\t\t 7 | 8 | 9 \n\n";
}

void initialise(char board[Side][Side])
{
  for (int i = 0; i < Side; i++)
  {
    for (int j = 0; j < Side; j++)
    {
      board[i][j] = '*';
    }
  }
}
void declareWinner(int whoseTurn)
{
  if (whoseTurn == Computer)
    printf("COMPUTER has won\n");
  else
    printf("HUMAN has won\n");
}

bool rowCrossed(char board[][Side])
{
  for (int i = 0; i < Side; i++)
  {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
      return true;
  }
  return false;
}

bool columnCrossed(char board[][Side])
{
  for (int i = 0; i < Side; i++)
  {
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '*')
      return true;
  }
  return false;
}

bool diagonalCrossed(char board[][Side])
{
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '*')
    return true;

  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '*')
    return true;

  return false;
}

bool gameOver(char board[][Side])
{
  return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

int miniMax(char board[Side][Side], int depth, bool isAI)
{
  int score = 0;
  int bestScore = 0;
  if (gameOver(board) == true)
  {
    if (isAI == true)
    {
      return -10;
    }
    if (isAI == false)
    {
      return +10;
    }
  }
  else
  {
    if (depth < 9)
    {
      if (isAI == true)
      {
        bestScore = -999;
        for (int i = 0; i < Side; i++)
        {
          for (int j = 0; j < Side; j++)
          {
            if (board[i][j] == '*')
            {
              board[i][j] = ComputerMove;
              score = miniMax(board, depth + 1, false);
              board[i][j] = '*';
              if (score > bestScore)
              {
                bestScore = score;
              }
            }
          }
        }
        return bestScore;
      }

      else
      {

        bestScore = 999;
        for (int i = 0; i < Side; i++)
        {
          for (int j = 0; j < Side; j++)
          {
            if (board[i][j] == '*')
            {
              board[i][j] = HumanMove;
              score = miniMax(board, depth + 1, true);
              board[i][j] = '*';
              if (score < bestScore)
              {
                bestScore = score;
              }
            }
          }
        }

        return bestScore;
      }
    }
    else
    {
      return 0;
    }
  }
}

int bestMove(char board[][Side], int moveIndex)
{
  int x = -1, y = -1;
  int score = 0, bestScore = -999;
  for (int i = 0; i < Side; i++)
  {
    for (int j = 0; j < Side; j++)
    {
      if (board[i][j] == '*')
      {
        board[i][j] = ComputerMove;
        score = miniMax(board, moveIndex + 1, false);
        board[i][j] = '*';
        if (score > bestScore)
        {
          bestScore = score;
          x = i;
          y = j;
        }
      }
    }
  }
  return x * 3 + y;
}

void playTicTacToe(int turn)
{
  char board[Side][Side];
  int moveIndex = 0, x = 0, y = 0;
  initialise(board);
  showInstructions();

  while (gameOver(board) == false && moveIndex != Side * Side)
  {
    int n;
    if (turn == Computer)
    {
      n = bestMove(board, moveIndex);
      x = n / Side;
      y = n % Side;
      board[x][y] = ComputerMove;
      cout << "Computer has put a X in cell " << n + 1 << endl;
      showBoard(board);
      moveIndex++;
      turn = Human;
    }

    else if (turn == Human)
    {
      cout << "You can insert in the following positions : [";
      for (int i = 0; i < Side; i++)
      {
        for (int j = 0; j < Side; j++)
        {
          if (board[i][j] == '*')
          {
            cout << " " << (i * 3 + j) + 1;
          }
        }
      }
      cout << " ]\n";
      cout << "Enter the position = ";
      cin >> n;
      n--;
      x = n / Side;
      y = n % Side;
      if (board[x][y] == '*' && n < 9 && n >= 0)
      {
        board[x][y] = HumanMove;
        cout << "Human has put a O in cell " << n + 1 << endl;
        showBoard(board);
        moveIndex++;
        turn = Computer;
      }

      else if (board[x][y] != '*' && n < 9 && n >= 0)
      {
        cout << "Position is occupied, select any one place from the available places.";
      }

      else if (n < 0 || n > 8)
      {
        cout << "Invalid Position.";
      }
    }
  }
  if (gameOver(board) == false && moveIndex == Side * Side)
  {
    cout << "It's a draw\n";
  }
  else
  {
    if (turn == Computer)
    {
      turn = Human;
    }
    else if (turn == Human)
    {
      turn = Computer;
    }
    declareWinner(turn);
  }
}

int main()
{
  cout << "\n-------------------------------\n";
  cout << "\tTic-Tac-Toe\n";
  cout << "\n-------------------------------\n";

  char cont = 'y';
  do
  {
    char choice;
    cout << "Do you want to start first?(y/n) :";
    cin >> choice;

    if (choice == 'n')
    {
      playTicTacToe(Computer);
    }
    else if (choice == 'y')
    {
      playTicTacToe(Human);
    }
    else
    {
      cout << "Invalid Choice\n";
    }

    cout << "\nDo you want to quit(y/n) : ";
    cin >> cont;
  } while (cont == 'n');

  return 0;
}
