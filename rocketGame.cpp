// Author : abdelrhman
#include <bits/stdc++.h>
#include <windows.h> // to color compilare
using namespace std;
// **player number one ==> place of it will be in the left of board and
//  must be reach to right(all rockets) to win

// **player number two ==> place of it will be in the top of board and 
// must be reach to bottom(all rockets) to win
class rockGamePlayerWithPlayer
{
protected:
    int sizeBoard;
    bool player = true;
    char p1;
    char p2;
    int counter = 0;
    int p1NumRow = -1;    // the number row of this Rocket ==> player 1
    int p1NumColumn = -1; // the number column of this Rocket ==> player 1
    int p2NumRow = -1;    // the number row of this Rocket ==> player 2
    int p2NumColumn = -1; // the number Column of this Rocket ==> player 2
    vector<vector<char>> board{' '};
    vector<char> nameRockPOne;
    vector<char> nameRockPTwo;
    map<char, int> mNameRockPOne;
    map<char, int> mNameRockPTwo;

public:
    rockGamePlayerWithPlayer(){}
    rockGamePlayerWithPlayer(int sizeBo);
    int getSize();
    void setSize();
    void createBoard();
    void updateBoard();
    void playerOne();
    void playerTwo();
    void placeOfRock(char rockFP);
    void move(char rockF);
    bool possibilityOfMovement();
    void Run();
    int checkWinner();
    void setTextColor(int n);
};
rockGamePlayerWithPlayer::rockGamePlayerWithPlayer(int sizeBo)
{
    this->sizeBoard = sizeBo;
    createBoard();

}
void rockGamePlayerWithPlayer::createBoard(){
     char k = 65;
    // char j = 97;
    for (int i = 0; i < sizeBoard - 2; i++)
    {
        nameRockPOne.push_back(k);
        mNameRockPOne.insert({k, 1});
        k++;
    }
    for (int i = 0; i < sizeBoard - 2; i++)
    {
        nameRockPTwo.push_back(k);
        mNameRockPTwo.insert({k, 2});
        k++;
    }
    int indexP1 = 0, indexP2 = 0; // 5 ==> 1 3 1
    for (int i = 0; i < sizeBoard; i++)
    {
        for (size_t j = 0; j < sizeBoard; j++)
        {
            if (i >= 1 && i < sizeBoard - 1 && j == 0)
            {
                board[i].push_back(nameRockPOne[indexP1++]);
            }
            else if (j >= 1 && j < sizeBoard - 1 && i == 0)
            {
                board[i].push_back(nameRockPTwo[indexP2++]);
            }
            else
            {
                board[i].push_back(' ');
            }
        }
    }
    updateBoard();

}
int rockGamePlayerWithPlayer::getSize(){
    return sizeBoard;
}
void rockGamePlayerWithPlayer::setSize(){
    int size;
    cout << "Please, Enter the size of game board : \n>>>";
    cin >> size;
    sizeBoard = size;
}
void rockGamePlayerWithPlayer::updateBoard()
{

    for (int i = 0; i < sizeBoard; i++)
    {
        // cout << "\n\t\t\t*-------------------*\n";
        cout << "\n\t\t\t\n";
        for (size_t j = 0; j < sizeBoard; j++)
        {
            int flag = true;
            if (j == 0)
                cout << "\t\t\t| ";
            if(board[i][j] != ' ' && board[i][j] != '#'){
                for (size_t k = 0; k < nameRockPOne.size(); k++)
                {
                    if(board[i][j] == nameRockPOne[k]){
                        setTextColor(2);
                        flag = true;
                        cout << board[i][j];
                        setTextColor(7);
                        break;
                    }else{
                        flag = false;
                    }
                }
                if(flag == false){
                    setTextColor(3);
                    cout << board[i][j];
                    setTextColor(7);
                }
                cout << " | ";

            }
            if(board[i][j] == ' '){
                cout << board[i][j] << " | ";
            }
        }
    }
    // cout << "\n\t\t\t*-------------------*\n";
    cout << "\n\t\t\t\n";
}
void rockGamePlayerWithPlayer::playerOne()
{
    // int c = 1;
    string c;
    cout << "\n<<<Player One, Choose from this rockets (";
    for (int i = 0; i < nameRockPOne.size(); i++)
    {
        if (i == nameRockPOne.size() - 1)
            cout << nameRockPOne[i];
        else
            cout << nameRockPOne[i] << " Or ";
    }
    cout << ") : \n>>>";
    cin >> c;
    if(c.size() == 1) p1 = (char)toupper(c[0]);
    if (mNameRockPOne[p1] != 1 || c.size() > 1)
    {
        //  for (auto k : mNameRockPOne)
        // {
        //     cout << k.first << " " << k.second << endl;
        // }
        cout << "\n\t\t\tPlayer One, This message for you";
        cout << "\n\t\t***** This rocket does not belong to you! *****\n\n";
        mNameRockPOne.erase(p1);
        playerOne();
    }
}
void rockGamePlayerWithPlayer::playerTwo()
{
    // int c = 1;
    string c;
    cout << "\n<<<Player Two, Choose from this rockets (";
    for (int i = 0; i < nameRockPTwo.size(); i++)
    {
        if (i == nameRockPTwo.size() - 1)
            cout << nameRockPTwo[i];
        else
            cout << nameRockPTwo[i] << " Or ";
    }
    cout << ") : \n>>>";
    cin >> c;
    if(c.size() == 1)p2 = (char)toupper(c[0]);
    if (mNameRockPTwo[p2] != 2 || c.size() > 1)
    {
        // for (auto k : mNameRockPTwo)
        // {
        //     cout << k.first << " " << k.second << endl;
        // }
        cout << "\n\t\t\t Player Two, This message for you";
        cout << "\n\t\t***** This rocket does not belong to you! *****\n\n";
        mNameRockPTwo.erase(p2);
        playerTwo();
    }
}
void rockGamePlayerWithPlayer::placeOfRock(char rockF)
{
    // first player ===> true
    //   -- row of any rocket --> no change
    //   -- column of any rocket --> change
    // second player ===> false
    //   -- row of any rocket --> change
    //   -- column of any rocket --> no change
    for (auto k : nameRockPOne)
    {
        if (k == rockF)
        {
            player = true;
            break;
        }
        else
        {
            player = false;
        }
    }
    // player one
    if (player == true)
    {
        for (size_t i = 0; i < nameRockPOne.size(); i++)
        {
            if (nameRockPOne[i] == rockF)
            {
                p1NumRow = i + 1;
                break;
            }
        }
        for (size_t i = 0; i < sizeBoard; i++)
        {
            if (board[p1NumRow][i] == rockF)
            {
                p1NumColumn = i;
                break;
            }
        }
        // player = true;
    }
    else
    {
        for (size_t i = 0; i < nameRockPTwo.size(); i++)
        {
            if (nameRockPTwo[i] == rockF)
            {
                p2NumColumn = i + 1;
                break;
            }
        }
        for (size_t i = 0; i < sizeBoard; i++)
        {
            if (board[i][p2NumColumn] == rockF)
            {
                p2NumRow = i;
                break;
            }
        }
        // player = false;
    }
}
bool rockGamePlayerWithPlayer::possibilityOfMovement()
{
    if (player == true)
    {
        counter = 0;
        for (size_t i = p1NumColumn + 1; i < sizeBoard; i++)
        {
            if (board[p1NumRow][i] == ' ' && board[p1NumRow][i] != '#')
            {
                return true;
                break;
            }
            else if (board[p1NumRow][i] != ' '&& board[p1NumRow][i] != '#')
                counter++;
        }
        if (counter == 1)
            return true;
        else
            return false;
    }
    else
    {
        counter = 0;
        for (size_t i = p2NumRow + 1; i < sizeBoard; i++)
        {
            if (board[i][p2NumColumn] == ' ')
            {
                return true;
                break;
            }
            else if (board[i][p2NumColumn] != ' ' && board[i][p2NumColumn] != '#')
                counter++;
        }
        if (counter == 1)
            return true;
        else
            return false;
    }
}
void rockGamePlayerWithPlayer::move(char rockF)
{
    placeOfRock(rockF);
    //cout << "player : " << player << endl;
    if (possibilityOfMovement() == true)
    {
        if (player == true) // player one
        {
            if (counter == 0)
            {
                swap(board[p1NumRow][p1NumColumn], board[p1NumRow][p1NumColumn + 1]);
            }
            else if (counter == 1)
            {
                swap(board[p1NumRow][p1NumColumn], board[p1NumRow][p1NumColumn + 2]);
            }
            // player = false;
        }
        else if (player == false)
        {
            if (counter == 0)
            {
                swap(board[p2NumRow][p2NumColumn], board[p2NumRow + 1][p2NumColumn]);
            }
            else if (counter == 1)
            {
                swap(board[p2NumRow][p2NumColumn], board[p2NumRow + 2][p2NumColumn]);
            }
            // player = true;
        }
    }
}
int rockGamePlayerWithPlayer::checkWinner()
{
    int countFilledCell = 0; // to count filled destination cells for player one or two
    if (player == true)
    {
        for (size_t i = 0; i < sizeBoard; i++)
        {
            if (board[i][sizeBoard - 1] != ' ')
                countFilledCell++;
        }
    }
    else
    {
        for (size_t i = 0; i < sizeBoard; i++)
        {
            if (board[sizeBoard - 1][i] != ' ')
                countFilledCell++;
        }
    }
    //cout << "player w : " << player << endl;
    if (countFilledCell == sizeBoard - 2 && player == true)
    {
        return 1;
    }
    else if (countFilledCell == sizeBoard - 2 && player == false)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
void rockGamePlayerWithPlayer::Run()
{
    while (true)
    {
        int reWinner = -1;
        playerOne();
        move(p1);
        updateBoard();
        reWinner = checkWinner();
        if (reWinner == 1)
        {
            cout << "\t\t\t*** Player One is winner!!! *** " << endl;
            break;
        }
        Sleep(4000);
        system("cls");
        updateBoard();
        playerTwo();
        move(p2);
        updateBoard();
        reWinner = checkWinner();
        if (reWinner == 0)
        {
            cout << "\t\t\t*** Player Two is winner!!! ***" << endl;
            break;
        }
        Sleep(4000);
        system("cls");
        updateBoard();
    }
}
void rockGamePlayerWithPlayer::setTextColor(int n)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, n);
}
int main()
{
    system("cls");
     cout << "\n\n                                    <<-------WELCOME USER IN THIS GAME------->>\n" << endl;
    cout << "\n                                           ***** Rocket Game *****\n" << endl;
    int size;
    cout << "Please, Enter the size of game board : \n>>>";
    cin >> size;
    rockGamePlayerWithPlayer game(size);
    game.Run();
}
