#include "Chess.h"
#include <string>
#include <iostream>
#include <queue>
using namespace std;
/* Constructor Comment Block
Function Prototype:
Chess();

Function Description:
This function is the constructor. Inside the header file we created to boardspace pointers, beginning and ending.
We made them private so that functions throughout the cpp file could call them. The constructor simply initializes
the beginning and ending pointers to NULL.

Example:
Chess *NewGame = new Chess();

Pre-condition: The only pre-conditions for this function are that the beginning and ending pointers be declared as
private variables in the header file. Without this, we would not be able to call them inside the functions in this cpp
file.

Post-condition: Once this function has run through, the beginning and ending boardSpace pointers will be set to NULL.
The pointers represent where we will be drawing the board from (beginning) and where we will be finishing the board (ending).
*/
Chess::Chess()
{
    //Initialize pointers!
    beginning = NULL;
    ending = NULL;
}


/* Destructor Comment Block
Function Prototype:
~Chess();

Function Description:
This function is the destructor. We did not need this function because we did not need the entire game to be deleted
at the end of the program.

Example:
Chess *NewGame = new ~Chess();

Pre-condition: No pre-conditions were required for the destructor because it was not used in this program.

Post-condition: No post-conditions were expected for the destructor because it was never called in the program.
*/
Chess::~Chess()
{
    //dtor
}

/* newSpace Comment Block
Function Prototype:
boardSpace* Chess::newSpace(std::string);

Function Description:
This function is written to initialize all attributes of the boardSpace struct. The function simply sets
everything to it's default values. For example, pointers are set to NULL and strings are set to "NULL".

Example:
Chess *NewGame = new Chess();
NewGame->Chess(spot);

Pre-condition: This function requires one precondition. In order to run, it must take in a string input which will
serve as the coordinates for that new board space. As with the rest of these functions, the constructor must be called
first so that the beginning and ending pointers are also initialized.

Post-condition: Once this function has run through, the board space will have all of it's attributes set to NULL.
This will make our lives easier as we try to call these attributes later in the program. It lessens our chances of
running into segmentation faults.
*/
boardSpace* Chess::newSpace(std::string placement)
{
    //Create the new boardSpace
    boardSpace* newSpot = new boardSpace;
    //Set the input coordinates (placement) to the new boardSpace's boardSpot.
    newSpot->boardSpot = placement;
    //Initialize all boardSpace attributes to NULL, or some form of NULL.
    newSpot->name = "_";
    newSpot->occupied = false;
    newSpot->team = "NULL";
    newSpot->up = NULL;
    newSpot->down = NULL;
    newSpot->left = NULL;
    newSpot->right = NULL;
    newSpot->upLeft = NULL;
    newSpot->upRight = NULL;
    newSpot->downLeft = NULL;
    newSpot->downRight = NULL;
    //Return the newly initialized boardSpace so that the entire board can be created.
    return newSpot;
}

/* createBoard function

Function Prototype:
void Chess::createBoard(std::string, std::string);

Function Description:
This method is written to illustrate all possible moves that a pawn can make. The function allows
pawns to move one space forward (at all times) and attack on diagonal moves.

Example:
string team1 = "Zach";
string team2 = "Blaine";
Chess *NewGame = new Chess();
NewGame->createBoard(team1, team2);

Pre-condition: This function requires two pre-conditions to be met. Both are the names of the teams that will
be playing. This will also be used to set each one of the chess pieces to one of the teams.
requires two additional pointers to be set: beginning and ending. These are set to NULL inside the constructor.

Post-condition: Once this function has run through, the pawn will either have moved forward one space or it will
attack an enemy piece in a diagonal move. Pointers and struct attributes will be updated after each successive
move.
*/
void Chess::createBoard(std::string Team1, std::string Team2)
{

    int index = 2;
    beginning = newSpace("0");
    ending = newSpace("65");
    boardSpace* temp = new boardSpace;
    temp = newSpace("a1");
    beginning->right = temp;
    temp->left = beginning;
    boardSpace* temp2 = new boardSpace;
    for(int j = 2; j < 65; j++)
    {
        if(2 <= index && index <= 8)
        {
            std::string b =std::to_string(j);
            temp2 = newSpace("a"+b);
        }
        if(9 <= index && index <= 16)
        {
            std::string b =std::to_string(j-8);
            temp2 = newSpace("b"+b);
        }
        if(17 <= index && index <= 24)
        {
            std::string b =std::to_string(j-16);
            temp2 = newSpace("c"+b);
        }
        if(25 <= index && index <= 32)
        {
            std::string b =std::to_string(j-24);
            temp2 = newSpace("d"+b);
        }
        if(33 <= index && index <= 40)
        {
            std::string b =std::to_string(j-32);
            temp2 = newSpace("e"+b);
        }
        if(41 <= index && index <= 48)
        {
            std::string b =std::to_string(j-40);
            temp2 = newSpace("f"+b);
        }
        if(49 <= index && index <= 56)
        {
            std::string b =std::to_string(j-48);
            temp2 = newSpace("g"+b);
        }
        if(57 <= index && index <= 64)
        {
            std::string b =std::to_string(j-56);
            temp2 = newSpace("h"+b);
        }
        index++;
        temp->right = temp2;
        temp2->left = temp;
        temp = temp2;
    }
    temp->right = ending;
    ending->left = temp;
    boardSpace* temp3 = beginning->right;
    boardSpace* DOWN = beginning->right;
    boardSpace* DOWNRIGHT = new boardSpace;
    boardSpace* DOWNLEFT = new boardSpace;

    //set up the down left, down right, and down spots;

    while(DOWN->boardSpot != "b1")
    {
        DOWN = DOWN->right;
    }
    DOWNLEFT = DOWN->left;
    DOWNRIGHT = DOWN->right;
    while(temp3->boardSpot != "h1")
    {
        //cout<<1<<endl;
        temp3->down = DOWN;
        if(temp3->boardSpot != "a8" && temp3->boardSpot != "b8" && temp3->boardSpot != "c8" && temp3->boardSpot != "d8" &&
           temp3->boardSpot != "e8" && temp3->boardSpot != "f8" && temp3->boardSpot != "g8")
        {
            temp3->downRight = DOWNRIGHT;
        }
        if(temp3->boardSpot != "a1" && temp3->boardSpot != "b1" && temp3->boardSpot != "c1" && temp3->boardSpot != "d1" &&
           temp3->boardSpot != "e1" && temp3->boardSpot != "f1" && temp3->boardSpot != "g1")
        {
            temp3->downLeft = DOWNLEFT;
        }
        temp3 = temp3->right;
        DOWN = DOWN->right;
        DOWNRIGHT= DOWNRIGHT->right;
        DOWNLEFT = DOWNLEFT->right;
    }

    //setup of up right, up left, and up

    temp3 = beginning->right;
    while(temp3->boardSpot != "b1")
    {
        temp3 = temp3->right;
    }
    boardSpace* UP = beginning->right;
    boardSpace* UPRIGHT = UP->right;
    boardSpace* UPLEFT = UP->left;

    while(temp3->boardSpot != "65")
    {
        temp3->up = UP;
        if(temp3->boardSpot != "h8" && temp3->boardSpot != "b8" && temp3->boardSpot != "c8" && temp3->boardSpot != "d8" &&
           temp3->boardSpot != "e8" && temp3->boardSpot != "f8" && temp3->boardSpot != "g8")
        {
            temp3->upRight = UPRIGHT;
        }
        if(temp3->boardSpot != "h1" && temp3->boardSpot != "b1" && temp3->boardSpot != "c1" && temp3->boardSpot != "d1" &&
           temp3->boardSpot != "e1" && temp3->boardSpot != "f1" && temp3->boardSpot != "g1")
        {
            temp3->upLeft = UPLEFT;
        }
        temp3 = temp3->right;
        UP = UP->right;
        UPRIGHT= UPRIGHT->right;
        UPLEFT = UPLEFT->right;
    }
    //set the horizontal boarders
    temp = beginning->right;
    temp = temp->down;
    while(temp != NULL)
    {
        temp->left = NULL;
        temp = temp->down;
    }
    temp = ending->left;
    temp = temp->up;
    while(temp != NULL)
    {
        temp->right = NULL;
        temp = temp->up;
    }

    //set Team 2 pieces
    temp = beginning->right;
    while(temp != NULL)
    {
        temp->team = Team2;
        temp->occupied = true;
        if(temp->boardSpot == "a1" || temp->boardSpot == "a8")
        {
            temp->name = "R";
        }
        if(temp->boardSpot == "a2" || temp->boardSpot == "a7")
        {
            temp->name = "N";
        }
        if(temp->boardSpot == "a3" || temp->boardSpot == "a6")
        {
            temp->name = "B";
            temp->team = Team2;
        }
        if(temp->boardSpot == "a4")
        {
            temp->name = "Q";
            temp->team = Team2;
        }
        if(temp->boardSpot == "a5")
        {
            temp->name = "K";
            temp->team = Team2;
        }
        temp = temp->right;
    }
    //set Team 2 pawns
    temp = beginning->right->down;
    while(temp != NULL)
    {
        temp->occupied = true;
        temp->team = Team2;
        temp->name = "P";
        temp = temp->right;
    }

    //set Team 1 pieces
    temp = ending->left;
    while(temp != NULL)
    {
        temp->occupied = true;
        temp->team = Team1;
        if(temp->boardSpot == "h1" || temp->boardSpot == "h8")
        {
            temp->name = "5";
        }
        if(temp->boardSpot == "h2" || temp->boardSpot == "h7")
        {
            temp->name = "6";
        }
        if(temp->boardSpot == "h3" || temp->boardSpot == "h6")
        {
            temp->name = "7";
        }
        if(temp->boardSpot == "h4")
        {
            temp->name = "8";
        }
        if(temp->boardSpot == "h5")
        {
            temp->name = "9";
        }
        temp = temp->left;
    }
    //set Team 1 pawns
    temp = ending->left->up;
    while(temp != NULL)
    {
        temp->occupied = true;
        temp->team = Team1;
        temp->name = "1";
        temp = temp->left;
    }



}
/* team1Board Comment Block
Function Prototype:
void Chess::team1Board();

Function Description:
This function is written to display the first team's board from their point of view. The function also informs
the players involved who's turn it is.

Example:
Chess *NewGame = new Chess();
NewGame->team1Board();

Pre-condition: This function does not take in any inputs so it has no pre-conditions. However, as with most of our
functions it requires that the beginning and ending pointers be set to NULL. This is done in the constructor.

Post-condition: Once this function has run through, the function will display the first team's board from their point
of view. It will also inform the player's whose turn it is and will later switch to team two's board once the first
player has completed their turn.
*/
void Chess::team1Board(std::string Team, std::string Team2)
{
    //Display the key telling the player's how their pieces are displayed on the board.
    cout<<endl<<"K & 9 = King, Q & 8 = Queen, B & 7 = Bishop"<<endl;
    cout<<"N & 6 = Knight, R & 5 = Rook, P & 1 = Pawn"<<endl<<endl;;

    std::queue<boardSpace*> T1;
    //Create the queue that will be used to mark the rows of the board (letters).
    std::queue<string> Letters;
    //Create the queue that will be used to mark the columns of the board (numbers).
    std::queue<int> Numbers;

    Letters.push("a");
    Letters.push("a");
    Letters.push("b");
    Letters.push("b");
    Letters.push("c");
    Letters.push("c");
    Letters.push("d");
    Letters.push("d");
    Letters.push("e");
    Letters.push("e");
    Letters.push("f");
    Letters.push("f");
    Letters.push("g");
    Letters.push("g");
    Letters.push("h");
    Letters.push("h");

    //Add the numbers that will be displayed to the queue.
    for(int h = 1; h < 9; h++)
    {
        Numbers.push(h);
    }

    //Add the numbers that will be displayed to the queue.
    for(int h = 1; h < 9; h++)
    {
        Numbers.push(h);
    }

    //Start from the top left corner of the board.
    boardSpace *temp = beginning->right;
    int j = 0;
    cout<<"            Team 2: "<<Team2<<endl;
    cout<<"        ";//A
    cout<<"    ";

    //Display numbers down the left hand side of the board.
    for(int i = 1; i < 9 ; i++)
    {
        cout<<Numbers.front()<<" ";
        Numbers.pop();
    }

    cout<<"        ";//A
    cout<<"    "<<endl;
    cout<<"        ";//A
    cout<<"  "<<"+-----------------+"<<" "<<endl;

    //Increment down the board while placing it in the queue.
    while(temp != NULL)
    {
        T1.push(temp);
        temp = temp->down;
    }

    //Read across the board from the queue.
    while(!T1.empty())
    {
        cout<<"        ";//A
        boardSpace *X = T1.front();
        //Display the letters at the bottom of the board.
        cout<<Letters.front()<<" |";
        Letters.pop();
        T1.pop();

        //Space indices appropriately.
        while(X != NULL && X != ending)
        {
            cout<<" "<<X->name;
            X = X->right;
        }

        cout<<" ";
        cout<<"| "<<Letters.front()<<endl;
        Letters.pop();
    }

    cout<<"        ";//A
    cout<<"  "<<"+-----------------+"<<" "<<endl;
    cout<<"    ";
    cout<<"        ";//A

    //Display numbers down the right hand side of the board.
    for(int i = 1; i < 9 ; i++)
    {
        cout<<Numbers.front()<<" ";
        Numbers.pop();
    }

    cout<<"    "<<endl;
    cout<<"            Team 1: "<<Team<<endl;
}

/* team2Board Comment Block
Function Prototype:
void Chess::team2Board();

Function Description:
This function is written to display the second team's board from their point of view. The function also informs
the players involved who's turn it is.

Example:
Chess *NewGame = new Chess();
NewGame->team2Board();

Pre-condition: This function does not take in any inputs so it has no pre-conditions. However, as with most of our
functions it requires that the beginning and ending pointers be set to NULL. This is done in the constructor.

Post-condition: Once this function has run through, the function will display the second team's board from their point
of view. It will also inform the player's whose turn it is and will later switch back to team one's board once the second
player has completed their turn.
*/
void Chess::team2Board(std::string Team,std::string Team2)
{
    //Display the key telling the player's how their pieces are displayed on the board.
    cout<<endl<<"K & 9 = King, Q & 8 = Queen, B & 7 = Bishop"<<endl;
    cout<<"N & 6 = Knight, R & 5 = Rook, P & 1 = Pawn"<<endl<<endl;;

    std::queue<boardSpace*> T1;
    //Create the queue that will be used to mark the rows of the board (letters).
    std::queue<string> Letters;
    //Create the queue that will be used to mark the columns of the board (numbers).
    std::queue<int> Numbers;

    Letters.push("h");
    Letters.push("h");
    Letters.push("g");
    Letters.push("g");
    Letters.push("f");
    Letters.push("f");
    Letters.push("e");
    Letters.push("e");
    Letters.push("d");
    Letters.push("d");
    Letters.push("c");
    Letters.push("c");
    Letters.push("b");
    Letters.push("b");
    Letters.push("a");
    Letters.push("a");

    //Add the numbers that will be displayed to the queue.
    for(int h = 8; h > 0; h--)
    {
        Numbers.push(h);
    }

    //Add the numbers that will be displayed to the queue.
    for(int h = 8; h > 0; h--)
    {
        Numbers.push(h);
    }

    //Start from ending since the board has flipped.
    boardSpace *temp = ending->left;
    int j = 0;
    cout<<"            Team 1: "<<Team<<endl;
    cout<<"        ";//A
    cout<<"    ";

    //Display numbers down the left hand side of the board.
    for(int i = 1; i < 9 ; i++)
    {
        cout<<Numbers.front()<<" ";
        Numbers.pop();
    }

    cout<<"        ";//A
    cout<<"    "<<endl;
    cout<<"        ";//A
    cout<<"  "<<"+-----------------+"<<" "<<endl;

    //Increment up the board while placing it in the queue.
    while(temp != NULL)
    {
        T1.push(temp);
        temp = temp->up;
    }

    //Read across the board from the queue.
    while(!T1.empty())
    {
        cout<<"        ";//A
        boardSpace *X = T1.front();
        //Display the letters at the bottom of the board.
        cout<<Letters.front()<<" |";
        Letters.pop();
        T1.pop();

        //Space indices appropriately.
        while(X != NULL && X != beginning)
        {
            cout<<" "<<X->name;
            X = X->left;
        }

        cout<<" ";
        cout<<"| "<<Letters.front()<<endl;
        Letters.pop();
    }

    cout<<"        ";//A
    cout<<"  "<<"+-----------------+"<<" "<<endl;
    cout<<"    ";
    cout<<"        ";//A

    //Display numbers down the right hand side of the board.
    for(int i = 1; i < 9 ; i++)
    {
        cout<<Numbers.front()<<" ";
        Numbers.pop();
    }

    cout<<"    "<<endl;
    cout<<"            Team 2: "<<Team2<<endl;
}

/* createBoard function

Function Prototype:
void Chess::createBoard(std::string, std::string);

Function Description:
This method is written to illustrate all possible moves that a pawn can make. The function allows
pawns to move one space forward (at all times) and attack on diagonal moves.

Example:
string team1 = "Zach";
string team2 = "Blaine";
Chess *NewGame = new Chess();
NewGame->createBoard(team1, team2);

Pre-condition: This function requires two pre-conditions to be met. Both are the names of the teams that will
be playing. This will also be used to set each one of the chess pieces to one of the teams.
requires two additional pointers to be set: beginning and ending. These are set to NULL inside the constructor.

Post-condition: Once this function has run through, the pawn will either have moved forward one space or it will
attack an enemy piece in a diagonal move. Pointers and struct attributes will be updated after each successive
move.
*/

void Chess::PlayerTurn(std::string Team1, std::string Team2)
{
    /*
        ZACH
    */
    int teamCounter = 1;
    std::string Winner;
    std::string answer;
    while(teamCounter != 3)
    {
        if(teamCounter == 1)
        {
            bool turnIsOver = false;
            while(turnIsOver == false)
            {
            team1Board(Team1,Team2);
            cout<<endl<<"It is "<<Team1<<"'s turn."<<endl;
            cout<<"What piece do you want to move: ";
            cin >> ws;
            getline(cin, answer);
            //cout<<SearchSpot(answer)->team<<endl;
            boardSpace* temp = SearchSpot(answer);

            //cout<<temp->name<<" "<<temp->team<<" "<<temp->occupied<<endl;
            if(temp != NULL && temp->occupied != false && temp->team  == Team1)
            {
                if(temp->name == "1")
                {
                    //cout<<"Pawn"<<endl;

                    turnIsOver = Pawn(Team1, temp, 1);
                    if(checkForKing("K"))
                    {
                        teamCounter = 2;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else if(temp->name == "5")
                {
                    //cout<<"Rook"<<endl;

                    turnIsOver = Rook(Team1, temp, 1);
                    if(checkForKing("K"))
                    {
                        teamCounter = 2;
                    }
                    else
                    {
                        teamCounter = 3;
                    }

                }
                else if(temp->name == "6")
                {
                    turnIsOver = Knight(Team1, temp, 1);
                    if(checkForKing("K"))
                    {
                        teamCounter = 2;
                    }
                    else
                    {
                        teamCounter = 3;
                    }

                }
                else if(temp->name == "7")
                {
                    turnIsOver = Bishop(Team1, temp, 1);
                    if(checkForKing("K"))
                    {
                        teamCounter = 2;
                    }
                    else
                    {
                        teamCounter = 3;
                    }

                }
                else if(temp->name == "8")
                {
                    turnIsOver = Queen(Team1, temp, 1);
                    if(checkForKing("K"))
                    {
                        teamCounter = 2;
                    }
                    else
                    {
                        teamCounter = 3;
                    }

                }
                else if(temp->name == "9")
                {
                    turnIsOver = King(Team1, temp, 1);
                    if(checkForKing("K"))
                    {
                        teamCounter = 2;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else
                {
                    cout<<"Not a valid choice!"<<endl<<"What piece do you want to move: ";
                }

            }
            }

        }
        if(teamCounter == 3)
        {
            Winner = Team1;
            break;
        }
        if(teamCounter == 2)
        {
            bool turnIsOver = false;
            while(turnIsOver == false)
            {
            team2Board(Team1,Team2);
            cout<<endl<<"It is "<<Team2<<"'s turn."<<endl;
            cout<<"What piece do you want to move: ";
            cin >> ws;
            getline(cin, answer);
            boardSpace* temp = SearchSpot(answer);
            if(temp != NULL && temp->occupied != false && temp->team  == Team2)
            {
                if(temp->name == "P")
                {
                    turnIsOver =Pawn(Team2, temp, 2);

                    if(checkForKing("9"))
                    {
                        teamCounter = 1;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else if(temp->name == "R")
                {
                    turnIsOver = Rook(Team2, temp, 2);
                    if(checkForKing("9"))
                    {
                        teamCounter = 1;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else if(temp->name == "N")
                {
                    turnIsOver = Knight(Team2, temp, 2);
                    if(checkForKing("9"))
                    {
                        teamCounter = 1;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else if(temp->name == "B")
                {
                    turnIsOver = Bishop(Team2, temp, 2);
                    if(checkForKing("9"))
                    {
                        teamCounter = 1;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else if(temp->name == "Q")
                {
                    turnIsOver = Queen(Team2, temp, 2);
                    if(checkForKing("9"))
                    {
                        teamCounter = 1;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else if(temp->name == "K")
                {
                    turnIsOver = King(Team2, temp, 2);
                    if(checkForKing("9"))
                    {
                        teamCounter = 1;
                    }
                    else
                    {
                        teamCounter = 3;
                    }
                }
                else
                {
                    cout<<"Not a valid choice!"<<endl<<"What piece do you want to move: ";
                }
            }
            }

        }
        if(teamCounter == 3)
        {
            Winner = Team2;
            break;
        }

    }
    cout<<"The Winner is "<<Winner<<"!";
}

/* SearchSpot Comment Block
Function Prototype:
boardSpace* Chess::SearchSpot(std::string SPOT);

Function Description:
This function is written to search through the board and find the piece that the player wants to move. It will pass this board space
into the appropriate piece function.

Example:
Chess *NewGame = new Chess();
NewGame->SearchSpot(b1);

Pre-condition: This function requires one pre-condition. It will take in the string of the spot where the player piece resides.However,
as with most of our functions it requires that the beginning and ending pointers be set to NULL. This is done in the constructor.

Post-condition: Once this function has run through, the function will return the boardSpace of the spot where the player piece resides.
It will pass this boardSpace into the piece function of the player's choosing and proceed with the appropriate moves.
*/
boardSpace* Chess::SearchSpot(std::string SPOT)
{
    //Initialize checkers.
    std::string tempWord;
    bool theEnd = false;

    boardSpace* temp = beginning->right;

    //Start the search process
    while(temp != NULL)
    {
        tempWord = temp->boardSpot;

        //Check the first character of the input.
        if(SPOT[0] == tempWord[0])
        {
            while(temp != NULL)
            {
                //If you have found the spot, return it.
                if(temp->boardSpot == SPOT)
                {
                    return temp;
                }
                //Otherwise keep moving right.
                else
                {
                    temp = temp->right;
                }
            }
            //Set the bool if it was not found.
            if(temp == NULL)
            {
                theEnd = true;
            }
        }

        //Jump out of the while loop and tell the user that the space was not found.
        if(theEnd == true)
        {
            break;
        }
        else
        {
            temp = temp->down;
        }
    }
    cout<<"Invalid Space"<<endl;
    //Return the space. To be used later.
    return temp;
}

/* checkForKing Comment Block
Function Prototype:
bool Chess::checkForKing(std::string KING);

Function Description:
This function is written to search through the board and see if there is a king still on the board who belong's to the opposite team. If there
is a king on the board, then the game will proceed. However, if a king is not found on the board, then the game will end and declare the
appropriate winner. This is essentially the check mate function.

Example:
Chess *NewGame = new Chess();
NewGame->checkForKing(K);

Pre-condition: This function requires one pre-condition. It will take in the string, which will be the first character of the piece that the
player chooses to move. As with most of our functions, it requires that the beginning and ending pointers be set to NULL. This is done
in the constructor.

Post-condition: Once this function has run through, the function will return a bool that says whether or not the opposite team's king is on
the board. It will pass this bool into the player turn function which will determine if the game should end on that player's turn or not.
*/
bool Chess::checkForKing(std::string KING)
{
    //Set initializers.
    bool found = false;
    boardSpace*temp = beginning->right;
    queue<boardSpace*> A;

    //Search down the board while pushing onto the queue.
    while(temp != NULL)
    {
        A.push(temp);
        temp = temp->down;
    }

    //Search inside the queue to see if the King is found. If not, keep searching.
    while(!A.empty())
    {
        boardSpace *X = A.front();
        A.pop();

        while(X != NULL && X != ending)
        {
            if(X->name == KING)
            {
                found = true;
                break;
            }
            else
            {
                X = X->right;
            }
        }

        if(found == true)
        {
            break;
        }
    }

    //Return the resulting bool.
    return found;
}
/* Pawn Comment Block
Function Prototype:
bool Chess::Pawn(string, boardSpace*, int);

Function Description:
This function is written to illustrate all possible moves that a pawn can make. The function allows
pawns to move one space forward (at all times) and attack on diagonal moves.

Example:
Chess *NewGame = new Chess();
NewGame->Pawn(Team1, inSpot, 1);

Pre-condition: This function requires three pre-conditions to be met. The first, the input string name is
the name of the team that is playing in that turn. The second, the input boardSpace pointer is the space
on the board where the chess piece resides. This will also be used to check all possible moves for
this piece. The third, the input integer is the counter telling us which team is in play. Each chess piece function
requires two additional pointers to be set: beginning and ending. These are set to NULL inside the constructor.

Post-condition: Once this function has run through, the pawn will either have moved forward one space or it will
attack an enemy piece in a diagonal move. Pointers and struct attributes will be updated after each successive
move.
*/
bool Chess::Pawn(std::string Team, boardSpace* currentSpace , int teamCount)
{
    //Set initial bool checks to false. These will be used to check if a space is clear or not.
    bool upClear = false;
    bool upRightClear = false;
    bool upLeftClear = false;

    //Bool to tell program whether or not to switch player turn.
    bool turnComplete = true;

    //If team one is in play, do the following:
    if(teamCount == 1)
    {
        //Check if up is clear. If so, set bool to true.
        if(currentSpace->up != NULL)
        {
            if(currentSpace->up->name == "_"|| (currentSpace->up->team != Team && currentSpace->up->occupied == true))
            {
                upClear = true;
            }
        }
        //Check if up and to the left is clear. If so, set bool to true.
        if(currentSpace->upLeft != NULL)
        {
            if(currentSpace->upLeft->team != Team && currentSpace->upLeft->occupied == true)
            {
                upLeftClear = true;
            }
        }
        //Check if up and to the right is clear. If so, set bool to true.
        if(currentSpace->upRight != NULL)
        {
            if(currentSpace->upRight->team != Team && currentSpace->upRight->occupied == true)
            {
                upRightClear = true;
            }
        }
        //If all available spots are not open, inform user.
        if(upRightClear == false && upLeftClear == false && currentSpace->up->name != "_")
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }

        string Input;
        cout<<"Where would you like to move your pawn?"<<endl;

        //Options to tell the user where they are able to move. Indicated by arrows.
        cout<<"You may move";
        if(upLeftClear == true && currentSpace->upLeft->occupied == true)
        {
            cout<<" ⇖,";
        }
        if(upClear == true && currentSpace->up->occupied == false)
        {
            cout<<" ⇑,";
        }
        if(upRightClear == true && currentSpace->upRight->occupied == true)
        {
            cout<<" or ⇗.";
        }

        //Take in the user move input using number pad directions.
        cout<<endl<<"Press";
        if(upLeftClear == true && currentSpace->upLeft->occupied == true)
        {
            cout<<" 7 for ⇖,";
        }
        if(upClear == true && currentSpace->up->occupied == false)
        {
            cout<<" 8 for ⇑,";
        }
        if(upRightClear == true && currentSpace->upRight->occupied == true)
        {
            cout<<" 9 for ⇗.";
        }

        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);

        //If user wants to move up and to the left, do the following:
        if(input == 7 && upLeftClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->upLeft->name = currentSpace->name;
            currentSpace->upLeft->occupied = true;
            currentSpace->upLeft->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            PawnSwitchOut(currentSpace->upLeft,Team,1);
            //End turn.
            return turnComplete;
        }
        //If the user wants to move up, do the following:
        else if(input == 8 && upClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->up->name = currentSpace->name;
            currentSpace->up->occupied = true;
            currentSpace->up->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            PawnSwitchOut(currentSpace->up,Team,1);
            //End turn.
            return turnComplete;
        }
        //If the user wants to move up and to the right, do the following:
        else if(input == 9 && upRightClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->upRight->name = currentSpace->name;
            currentSpace->upRight->occupied = true;
            currentSpace->upRight->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            PawnSwitchOut(currentSpace->upRight,Team,1);
            //End turn.
            return turnComplete;
        }
        //If the input is not correct, inform user.
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }

    //If team two is in play, do the following:
    if(teamCount == 2)
    {
        //Board has flipped so directions are now opposite.
        //Check if down is clear. If so, set upClear to true.
        if(currentSpace->down != NULL)
        {
            if(currentSpace->down->name == "_"|| (currentSpace->down->team != Team && currentSpace->down->occupied == true))
            {
                upClear = true;
            }
        }
        //Check if down and to the right is clear. If so, set upLeft to true.
        if(currentSpace->downRight != NULL)
        {
            if(currentSpace->downRight->team != Team && currentSpace->downRight->occupied == true)
            {
                upLeftClear = true;
            }
        }
        //Check if down and to the left is clear. If so, set upRight to true.
        if(currentSpace->downLeft != NULL)
        {
            if(currentSpace->downLeft->team != Team && currentSpace->downLeft->occupied == true)
            {
                upRightClear = true;
            }
        }
        //If all available spots are not clear, inform user.
        if(upRightClear == false && upLeftClear == false && currentSpace->down->name != "_")
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }

        string Input;
        cout<<"Where would you like to move your pawn?"<<endl;

        //Options to tell the user where they are able to move. Indicated by arrows.
        cout<<"You may move";
        if(upLeftClear == true && currentSpace->downRight->occupied == true)
        {
            cout<<" ⇖,";
        }
        if(upClear == true && currentSpace->down->occupied == false)
        {
            cout<<" ⇑,";
        }
        if(upRightClear == true && currentSpace->downLeft->occupied == true)
        {
            cout<<" or ⇗.";
        }

        //Take in the user move input using number pad directions.
        cout<<endl<<"Press";
        if(upLeftClear == true && currentSpace->downRight->occupied == true)
        {
            cout<<" 7 for ⇖,";
        }
        if(upClear == true && currentSpace->down->occupied == false)
        {
            cout<<" 8 for ⇑,";
        }
        if(upRightClear == true && currentSpace->downLeft->occupied == true)
        {
            cout<<" 9 for ⇗.";
        }
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);

        //If user wants to move up and to the left, do the following:
        if(input == 7 && upLeftClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->downRight->name = currentSpace->name;
            currentSpace->downRight->occupied = true;
            currentSpace->downRight->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            PawnSwitchOut(currentSpace->downRight,Team,2);
            //End turn.
            return turnComplete;
        }
        //If user wants to move up, do the following:
        else if(input == 8 && upClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->down->name = currentSpace->name;
            currentSpace->down->occupied = true;
            currentSpace->down->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            PawnSwitchOut(currentSpace->down,Team,2);
            //End turn.
            return turnComplete;
        }
        //If user wants to move up and to the right, do the following:
        else if(input == 9 && upRightClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->downLeft->name = currentSpace->name;
            currentSpace->downLeft->occupied = true;
            currentSpace->downLeft->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            PawnSwitchOut(currentSpace->downLeft,Team,2);
            //End turn.
            return turnComplete;
        }
        //If the input is not correct, inform user.
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }
}
/* Rook Piece function

Function Prototype:
void Chess::createBoard(std::string Team, boardSpace* currentSpace , int teamCount);

Function Description:
This function prompts the user for the available spots the Rook can move. The function checks the preset pointers
of left, right, up, and down for surrounding open spots or enemy pieces. Based on the output of the check, it will
prompt the user for the allowed moves. It will ask for how many spaces the piece should move, and if the there is
an object in the way the user will be brought back to choose a piece.

Example:

NewGame->Rook(team1, (b2)spot, 1);

Pre-condition:
The Pre-conditions for this function are the name of the team whose turn it is, the pointer to the spot that the
piece resides, and the number assigned to the team during the createboard function.

Post-condition: This function will return a boolean whether or not the move was completed or not.
*/
bool Chess::Rook(std::string Team, boardSpace* currentSpace , int teamCount)
{
    bool upClear = false;
    bool rightClear = false;
    bool leftClear = false;
    bool downClear = false;

    bool turnComplete = true;
    //for team 1 check the available spots
    if(teamCount == 1)
    {
        if(currentSpace->up != NULL)
        {
            if(currentSpace->up->name == "_" || (currentSpace->up->team != Team && currentSpace->up->occupied == true))
            {
                upClear = true;
            }
        }
        if(currentSpace->left != NULL && currentSpace->left != beginning)
        {
            if(currentSpace->left->name == "_" || (currentSpace->left->team != Team && currentSpace->left->occupied == true))
            {
                leftClear = true;
            }
        }
        if(currentSpace->right != NULL && currentSpace->right != ending)
        {
            if(currentSpace->right->name == "_" || (currentSpace->right->team != Team && currentSpace->right->occupied == true))
            {
                rightClear = true;
            }
        }
        if(currentSpace->down != NULL)
        {
            if(currentSpace->down->name == "_" || (currentSpace->down->team != Team && currentSpace->down->occupied == true))
            {
                downClear = true;
            }
        }
        if(upClear == false && downClear == false && rightClear == false && leftClear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }


        string Input;
        cout<<"Where would you like to move your Rook?"<<endl;

        cout<<"You may move";
        //cout available moves
        if(leftClear == true && currentSpace->left != beginning)
        {
            cout<<" ⇐,";
        }
        if(upClear == true)
        {
            cout<<" ⇑,";
        }
        if(rightClear == true && currentSpace->right != ending)
        {
            cout<<" ⇒,";
        }
        if(downClear == true)
        {
            cout<<" or ⇓.";
        }
        cout<<endl<<"Press";
        if(leftClear == true && currentSpace->left != beginning)
        {
            cout<<" 4 for ⇐,";
        }
        if(upClear == true)
        {
            cout<<" 8 for ⇑,";
        }
        if(rightClear == true && currentSpace->right != ending)
        {
            cout<<" 6 for ⇒,";
        }
        if(downClear == true)
        {
            cout<<" or 2 for ⇓.";
        }
        //takes in direction
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);
        cout<<"How many spaces do you what to move? : ";
        //takes in number of spaces
        string Input2;
        cin>>ws;
        getline(cin, Input2);
        int input2 = stoi(Input2);
        boardSpace* MoveTo = new boardSpace;
        MoveTo = currentSpace;
        bool inWay = false;
        if(input == 8 && upClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->up;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->up;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 4 && leftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->left;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->left;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && rightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->right;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->right;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->down;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->down;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }

    if(teamCount == 2)
    {
        if(currentSpace->up != NULL)
        {
            if(currentSpace->up->name == "_" || (currentSpace->up->team != Team && currentSpace->up->occupied == true))
            {
                downClear = true;
            }
        }
        if(currentSpace->left != NULL && currentSpace->left != beginning)
        {
            if(currentSpace->left->name == "_" || (currentSpace->left->team != Team && currentSpace->left->occupied == true))
            {
                rightClear = true;
            }
        }
        if(currentSpace->right != NULL && currentSpace->right != ending)
        {
            if(currentSpace->right->name == "_" || (currentSpace->right->team != Team && currentSpace->right->occupied == true))
            {
                leftClear = true;
            }
        }
        if(currentSpace->down != NULL)
        {
            if(currentSpace->down->name == "_" || (currentSpace->down->team != Team && currentSpace->down->occupied == true))
            {
                upClear = true;
            }
        }
        if(upClear == false && downClear == false && rightClear == false && leftClear == false )
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }

        string Input;
        cout<<"Where would you like to move your Rook?"<<endl;

        cout<<"You may move";
        if(leftClear == true && currentSpace->right != beginning)
        {
            cout<<" ⇐,";
        }
        if(upClear == true)
        {
            cout<<" ⇑,";
        }
        if(rightClear == true && currentSpace->left != ending)
        {
            cout<<" ⇒,";
        }
        if(downClear == true)
        {
            cout<<" or ⇓.";
        }
        cout<<endl<<"Press";
        if(leftClear == true && currentSpace->right != beginning)
        {
            cout<<" 4 for ⇐,";
        }
        if(upClear == true)
        {
            cout<<" 8 for ⇑,";
        }
        if(rightClear == true && currentSpace->left != ending)
        {
            cout<<" 6 for ⇒,";
        }
        if(downClear == true)
        {
            cout<<" or 2 for ⇓.";
        }
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);
        cout<<"How many spaces do you what to move? : ";
        string Input2;
        cin>>ws;
        getline(cin, Input2);
        int input2 = stoi(Input2);
        boardSpace* MoveTo = new boardSpace;
        MoveTo = currentSpace;
        bool inWay = false;
        if(input == 8 && upClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->down;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->down;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 4 && leftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->right;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->right;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && rightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->left;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->left;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->up;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->up;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }
}
/* Knight Comment Block
Function Prototype:
bool Chess::Knight(string, boardSpace*, int);

Function Description:
This function is written to illustrate all possible moves that a knight can make. The function allows
knights to move in the eight L-shaped moves. It also allows the knight to attack if an enemy piece is within
range.

Example:
Chess *NewGame = new Chess();
NewGame->Knight(Team1, inSpot, 1);

Pre-condition: This function requires three pre-conditions to be met. The first, the input string name is
the name of the team that is playing in that turn. The second, the input boardSpace pointer is the space
on the board where the chess piece resides. This will also be used to check all possible moves for
this piece. The third, the input integer is the counter telling us which team is in play. Each chess piece function
requires two additional pointers to be set: beginning and ending. These are set to NULL inside the constructor.

Post-condition: Once this function has run through, the knight will either have moved in one of the 8 L-shaped moves or
it will attack an enemy piece if it is within range. Pointers and struct attributes will be updated after each
successive move.
*/
bool Chess::Knight(std::string Team, boardSpace* currentSpace , int teamCount)
{
    //Set initial bool checks to false and initialize strings for spot indicators.
    //These will be used to check if a space is clear or not and will hold on to this spot if need be.
    bool b1Clear = false;
    string b1Spot;
    bool b2Clear = false;
    string b2Spot;
    bool b3Clear = false;
    string b3Spot;
    bool b4Clear = false;
    string b4Spot;
    bool b5Clear = false;
    string b5Spot;
    bool b6Clear = false;
    string b6Spot;
    bool b7Clear = false;
    string b7Spot;
    bool b8Clear = false;
    string b8Spot;

    //Bool to tell program whether or not to switch player turn.
    bool turnComplete = true;
    //Initialize a boardSpace that we will use to increment through the possible checks.
    boardSpace *LookSpot = new boardSpace;

    //If team one is in play, do the following:
    if(teamCount == 1)
    {
        //Check if side left L is clear. If so, set bool to true and hold spot.
        LookSpot = currentSpace->up;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->left;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->left;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b1Clear = true;
                        b1Spot = LookSpot->boardSpot;
                    }
                }

            }
        }
        //Check if tall left L is clear. If so, set bool to true and hold spot.
        LookSpot = currentSpace->up;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->up;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->left;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b2Clear = true;
                        b2Spot = LookSpot->boardSpot;
                    }
                }
            }
        }
        //Check if tall right L is clear. If so, set bool to true and hold spot.
        LookSpot = currentSpace->up;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->up;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->right;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b3Clear = true;
                        b3Spot = LookSpot->boardSpot;
                    }
                }
            }
        }
        //Check if side right L is clear. If so, set bool to true and hold spot.
        LookSpot = currentSpace->up;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->right;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->right;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b4Clear = true;
                        b4Spot = LookSpot->boardSpot;
                    }
                }
            }
        }

        //Check if down side right L is clear. If so, set bool to true and hold spot.
        LookSpot = currentSpace->down;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->right;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->right;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b5Clear = true;
                        b5Spot = LookSpot->boardSpot;
                    }
                }
            }
        }
        //Check if down tall right L is clear. If so, set bool to true and hold spot.
        LookSpot = currentSpace->down;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->down;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->right;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b6Clear = true;
                        b6Spot = LookSpot->boardSpot;
                    }
                }
            }
        }
        //Check if down tall left L is clear. If so, set bool to true and hold spot.
        LookSpot = currentSpace->down;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->down;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->left;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b7Clear = true;
                        b7Spot = LookSpot->boardSpot;
                    }
                }
            }
        }
        //Check if down side left L is clear. If so, set bool to true and hold spot.
        LookSpot = currentSpace->down;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->left;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->left;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b8Clear = true;
                        b8Spot = LookSpot->boardSpot;
                    }
                }
            }
        }

        //If all available spots are not clear, inform user.
        if(b1Clear == false && b2Clear == false && b3Clear == false && b4Clear == false && b5Clear == false && b6Clear == false && b7Clear == false && b8Clear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }

        string Input;
        cout<<"Where would you like to move your Knight?"<<endl;

        //Options to tell the user where they are able to move. Indicated by board coordinates. EX: b4, c7, etc.
        cout<<"You may move to one of these available spots: ";
        if(b1Clear == true)
        {
            cout<<b1Spot<< " ";
        }
        if(b2Clear == true)
        {
            cout<<b2Spot<< " ";
        }
        if(b3Clear == true)
        {
            cout<<b3Spot<< " ";
        }
        if(b4Clear == true)
        {
            cout<<b4Spot<< " ";
        }
        if(b5Clear == true)
        {
            cout<<b5Spot<< " ";
        }
        if(b6Clear == true)
        {
            cout<<b6Spot<< " ";
        }
        if(b7Clear == true)
        {
            cout<<b7Spot<< " ";
        }
        if(b8Clear == true)
        {
            cout<<b8Spot<< " ";
        }

        //Take in the user move input using input board coordinate.
        cout<<endl<<"Please select an available spot.";
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        string input = Input;
        //Initialize a boardSpace that mimics the appropriate move.
        boardSpace *moveTo = new boardSpace;

        //If the user wants to move side left L, do the following:
        if(input == b1Spot && b1Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->up;
            moveTo = moveTo->left;
            moveTo = moveTo->left;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn
            return turnComplete;
        }
        //If the user wants to move tall left L, do the following:
        else if(input == b2Spot && b2Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->up;
            moveTo = moveTo->up;
            moveTo = moveTo->left;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move tall right L, do the following:
        else if(input == b3Spot && b3Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->up;
            moveTo = moveTo->up;
            moveTo = moveTo->right;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move side right L, do the following:
        else if(input == b4Spot && b4Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->up;
            moveTo = moveTo->right;
            moveTo = moveTo->right;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down side right L, do the following:
        else if(input == b5Spot && b5Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->down;
            moveTo = moveTo->right;
            moveTo = moveTo->right;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down tall right L, do the following:
        else if(input == b6Spot && b6Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->down;
            moveTo = moveTo->down;
            moveTo = moveTo->right;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down tall left L, do the following:
        else if(input == b7Spot && b7Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->down;
            moveTo = moveTo->down;
            moveTo = moveTo->left;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down side left L, do the following:
        else if(input == b8Spot && b8Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->down;
            moveTo = moveTo->left;
            moveTo = moveTo->left;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the input is not correct, inform user.
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }

    //If team two is in play, do the following:
    if(teamCount == 2)
    {
        //Board has flipped so directions are now opposite.
        //Check if side left L is clear. If so, set b5Clear to true and hold spot.
        LookSpot = currentSpace->up;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->left;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->left;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b5Clear = true;
                        b5Spot = LookSpot->boardSpot;
                    }
                }
            }
        }
        //Check if tall left L is clear. If so, set b6Clear to true and hold spot.
        LookSpot = currentSpace->up;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->up;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->left;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b6Clear = true;
                        b6Spot = LookSpot->boardSpot;
                    }
                }
            }
        }
        //Check if tall right L is clear. If so, set b7Clear to true and hold spot.
        LookSpot = currentSpace->up;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->up;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->right;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b7Clear = true;
                        b7Spot = LookSpot->boardSpot;
                    }
                }
            }
        }
        //Check if side right L is clear. If so, set b8Clear to true and hold spot.
        LookSpot = currentSpace->up;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->right;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->right;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b8Clear = true;
                        b8Spot = LookSpot->boardSpot;
                    }
                }
            }
        }

        //Check if down side right L is clear. If so, set b1Clear to true and hold spot.
        LookSpot = currentSpace->down;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->right;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->right;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b1Clear = true;
                        b1Spot = LookSpot->boardSpot;
                    }
                }
            }
        }
        //Check if down tall right L is clear. If so, set b2Clear to true and hold spot.
        LookSpot = currentSpace->down;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->down;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->right;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b2Clear = true;
                        b2Spot = LookSpot->boardSpot;
                    }
                }
            }
        }
        //Check if down tall left L is clear. If so, set b3Clear to true and hold spot.
        LookSpot = currentSpace->down;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->down;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->left;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b3Clear = true;
                        b3Spot = LookSpot->boardSpot;
                    }
                }
            }
        }
        //Check if down side left L is clear. If so, set b4Clear to true and hold spot.
        LookSpot = currentSpace->down;
        if(LookSpot != NULL)
        {
            LookSpot = LookSpot->left;
            if(LookSpot != NULL)
            {
                LookSpot = LookSpot->left;
                if(LookSpot != NULL)
                {
                    if(LookSpot->name == "_" ||(LookSpot->occupied == true && LookSpot->team != Team))
                    {
                        b4Clear = true;
                        b4Spot = LookSpot->boardSpot;
                    }
                }
            }
        }

        //If all available spots are not clear, inform user.
        if(b1Clear == false && b2Clear == false && b3Clear == false && b4Clear == false && b5Clear == false && b6Clear == false && b7Clear == false && b8Clear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }

        string Input;
        cout<<"Where would you like to move your Knight?"<<endl;

        //Options to tell the user where they are able to move. Indicated by board coordinates. EX: b4, c7, etc.
        cout<<"You may move to one of these available spots: ";
        if(b5Clear == true)
        {
            cout<<b5Spot<<" ";
        }
        if(b6Clear == true)
        {
            cout<<b6Spot<<" ";
        }
        if(b7Clear == true)
        {
            cout<<b7Spot<<" ";
        }
        if(b8Clear == true)
        {
            cout<<b8Spot<<" ";
        }
        if(b1Clear == true)
        {
            cout<<b1Spot<<" ";
        }
        if(b2Clear == true)
        {
            cout<<b2Spot<<" ";
        }
        if(b3Clear == true)
        {
            cout<<b3Spot<<" ";
        }
        if(b4Clear == true)
        {
            cout<<b4Spot<<" ";
        }

        //Take in the user move input using input board coordinate.
        cout<<endl<<"Please select an available spot.";
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        string input = Input;
        //Initialize a boardSpace that mimics the appropriate move.
        boardSpace *moveTo = new boardSpace;

        //If the user wants to move side left L, do the following:
        if(input == b1Spot && b1Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->down;
            moveTo = moveTo->right;
            moveTo = moveTo->right;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move tall left L, do the following:
        else if(input == b2Spot && b2Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->down;
            moveTo = moveTo->down;
            moveTo = moveTo->right;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move tall right L, do the following:
        else if(input == b3Spot && b3Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->down;
            moveTo = moveTo->down;
            moveTo = moveTo->left;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move side right L, do the following:
        else if(input == b4Spot && b4Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->down;
            moveTo = moveTo->left;
            moveTo = moveTo->left;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down side right L, do the following:
        else if(input == b5Spot && b5Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->up;
            moveTo = moveTo->left;
            moveTo = moveTo->left;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down tall right L, do the following:
        else if(input == b6Spot && b6Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->up;
            moveTo = moveTo->up;
            moveTo = moveTo->left;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down tall left L, do the following:
        else if(input == b7Spot && b7Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->up;
            moveTo = moveTo->up;
            moveTo = moveTo->right;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down side left L, do the following:
        else if(input == b8Spot && b8Clear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            moveTo = currentSpace->up;
            moveTo = moveTo->right;
            moveTo = moveTo->right;
            moveTo->name = currentSpace->name;
            moveTo->occupied = true;
            moveTo->team = currentSpace->team;
            //Set old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the input is not correct, inform user.
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }
}
/* Bishop Piece function

Function Prototype:
void Chess::Bishop(std::string Team, boardSpace* currentSpace , int teamCount);

Function Description:
This function prompts the user for the available spots the Bishop can move. The function checks the preset pointers
of upleft, upright, downright, and downleft for surrounding open spots or enemy pieces. Based on the output of the check, it will
prompt the user for the allowed moves. It will ask for how many spaces the piece should move, and if the there is
an object in the way the user will be brought back to choose a piece.

Example:

NewGame->Bishop(team1, (b2)spot, 1);

Pre-condition:
The Pre-conditions for this function are the name of the team whose turn it is, the pointer to the spot that the
piece resides, and the number assigned to the team during the createboard function.

Post-condition: This function will return a boolean whether or not the move was completed or not.
*/
bool Chess::Bishop(std::string Team, boardSpace* currentSpace , int teamCount)
{
    bool upRightClear = false;
    bool upLeftClear = false;
    bool downRightClear = false;
    bool downLeftClear = false;

    bool turnComplete = true;

    if(teamCount == 1)
    {
        if(currentSpace->upLeft != NULL)
        {
            if(currentSpace->upLeft->name == "_" || (currentSpace->upLeft->team != Team && currentSpace->upLeft->occupied == true))
            {
                upLeftClear = true;
            }
        }
        if(currentSpace->upRight != NULL)
        {
            if(currentSpace->upRight->name == "_" || (currentSpace->upRight->team != Team && currentSpace->upRight->occupied == true))
            {
                upRightClear = true;
            }
        }
        if(currentSpace->downRight != NULL)
        {
            if(currentSpace->downRight->name == "_" || (currentSpace->downRight->team != Team && currentSpace->downRight->occupied == true))
            {
                downRightClear = true;
            }
        }
        if(currentSpace->downLeft != NULL)
        {
            if(currentSpace->downLeft->name == "_" || (currentSpace->downLeft->team != Team && currentSpace->downLeft->occupied == true))
            {
                downLeftClear = true;
            }
        }
        if(upRightClear == false && upLeftClear == false && downRightClear == false && downLeftClear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }


        string Input;
        cout<<"Where would you like to move your Bishop?"<<endl;

        cout<<"You may move";
        if(upLeftClear == true)
        {
            cout<<" ⇖,";
        }
        if(upRightClear == true)
        {
            cout<<" ⇗,";
        }
        if(downRightClear == true)
        {
            cout<<" ⇘,";
        }
        if(downLeftClear == true)
        {
            cout<<" or ⇙.";
        }
        cout<<endl<<"Press";
        if(upLeftClear == true)
        {
            cout<<" 7 for ⇖,";
        }
        if(upRightClear == true)
        {
            cout<<" 9 for ⇗,";
        }
        if(downRightClear == true)
        {
            cout<<" 3 for ⇘,";
        }
        if(downLeftClear == true)
        {
            cout<<" or 1 for ⇙.";
        }
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);
        cout<<"How many spaces do you what to move? : ";
        string Input2;
        cin>>ws;
        getline(cin, Input2);
        int input2 = stoi(Input2);
        boardSpace* MoveTo = new boardSpace;
        MoveTo = currentSpace;
        bool inWay = false;
        if(input == 7 && upLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upLeft;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 9 && upRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upRight;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && downLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downLeft;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downRight;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }

    if(teamCount == 2)
    {
        if(currentSpace->upLeft != NULL)
        {
            if(currentSpace->upLeft->name == "_" || (currentSpace->upLeft->team != Team && currentSpace->upLeft->occupied == true))
            {
                downRightClear = true;
            }
        }
        if(currentSpace->upRight != NULL)
        {
            if(currentSpace->upRight->name == "_" || (currentSpace->upRight->team != Team && currentSpace->upRight->occupied == true))
            {
                downLeftClear = true;
            }
        }
        if(currentSpace->downRight != NULL)
        {
            if(currentSpace->downRight->name == "_" || (currentSpace->downRight->team != Team && currentSpace->downRight->occupied == true))
            {
                upLeftClear = true;
            }
        }
        if(currentSpace->downLeft != NULL)
        {
            if(currentSpace->downLeft->name == "_" || (currentSpace->downLeft->team != Team && currentSpace->downLeft->occupied == true))
            {
                upRightClear = true;
            }
        }
        if(upRightClear == false && upLeftClear == false && downRightClear == false && downLeftClear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }


        string Input;
        cout<<"Where would you like to move your Rook?"<<endl;

        cout<<"You may move";
        if(upLeftClear == true)
        {
            cout<<" ⇖,";
        }
        if(upRightClear == true)
        {
            cout<<" ⇗,";
        }
        if(downRightClear == true)
        {
            cout<<" ⇘,";
        }
        if(downLeftClear == true)
        {
            cout<<" or ⇙.";
        }
        cout<<endl<<"Press";
        if(upLeftClear == true)
        {
            cout<<" 7 for ⇖,";
        }
        if(upRightClear == true)
        {
            cout<<" 9 for ⇗,";
        }
        if(downRightClear == true)
        {
            cout<<" 3 for ⇘,";
        }
        if(downLeftClear == true)
        {
            cout<<" or 1 for ⇙.";
        }
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);
        cout<<"How many spaces do you what to move? : ";
        string Input2;
        cin>>ws;
        getline(cin, Input2);
        int input2 = stoi(Input2);
        boardSpace* MoveTo = new boardSpace;
        MoveTo = currentSpace;
        bool inWay = false;
        if(input == 7 && upLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downRight;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 9 && upRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downLeft;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && downLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upRight;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upLeft;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }

}
/* Queen Piece function

Function Prototype:
void Chess::Queen(std::string Team, boardSpace* currentSpace , int teamCount);

Function Description:
This function prompts the user for the available spots the Queen can move. The function checks the preset pointers
of left, upleft, up, upright,right, downright, down, and downleft for surrounding open spots or enemy pieces. Based on the output of the check, it will
prompt the user for the allowed moves. It will ask for how many spaces the piece should move, and if the there is
an object in the way the user will be brought back to choose a piece.

Example:

NewGame->Queen(team1, (b2)spot, 1);

Pre-condition:
The Pre-conditions for this function are the name of the team whose turn it is, the pointer to the spot that the
piece resides, and the number assigned to the team during the createboard function.

Post-condition: This function will return a boolean whether or not the move was completed or not.
*/
bool Chess::Queen(std::string Team, boardSpace* currentSpace , int teamCount)
{
    bool upRightClear = false;
    bool upLeftClear = false;
    bool downRightClear = false;
    bool downLeftClear = false;
    bool upClear = false;
    bool rightClear = false;
    bool leftClear = false;
    bool downClear = false;

    bool turnComplete = true;

    if(teamCount == 1)
    {
        if(currentSpace->up != NULL)
        {
            if(currentSpace->up->name == "_" || (currentSpace->up->team != Team && currentSpace->up->occupied == true))
            {
                upClear = true;
            }
        }
        if(currentSpace->left != NULL)
        {
            if(currentSpace->left->name == "_" || (currentSpace->left->team != Team && currentSpace->left->occupied == true))
            {
                leftClear = true;
            }
        }
        if(currentSpace->right != NULL)
        {
            if(currentSpace->right->name == "_" || (currentSpace->right->team != Team && currentSpace->right->occupied == true))
            {
                rightClear = true;
            }
        }
        if(currentSpace->down != NULL)
        {
            if(currentSpace->down->name == "_" || (currentSpace->down->team != Team && currentSpace->down->occupied == true))
            {
                downClear = true;
            }
        }
        if(currentSpace->upLeft != NULL)
        {
            if(currentSpace->upLeft->name == "_" || (currentSpace->upLeft->team != Team && currentSpace->upLeft->occupied == true))
            {
                upLeftClear = true;
            }
        }
        if(currentSpace->upRight != NULL)
        {
            if(currentSpace->upRight->name == "_" || (currentSpace->upRight->team != Team && currentSpace->upRight->occupied == true))
            {
                upRightClear = true;
            }
        }
        if(currentSpace->downRight != NULL)
        {
            if(currentSpace->downRight->name == "_" || (currentSpace->downRight->team != Team && currentSpace->downRight->occupied == true))
            {
                downRightClear = true;
            }
        }
        if(currentSpace->downLeft != NULL)
        {
            if(currentSpace->downLeft->name == "_" || (currentSpace->downLeft->team != Team && currentSpace->downLeft->occupied == true))
            {
                downLeftClear = true;
            }
        }
        if(upRightClear == false && upLeftClear == false && downRightClear == false && downLeftClear == false
           && upClear == false && downClear == false && rightClear == false && leftClear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }


        string Input;
        cout<<"Where would you like to move your Queen?"<<endl;

        cout<<"You may move";
        if(leftClear == true && currentSpace->left != beginning)
        {
            cout<<" ⇐,";
        }
        if(upLeftClear == true)
        {
            cout<<" ⇖,";
        }
        if(upClear == true)
        {
            cout<<" ⇑,";
        }
        if(upRightClear == true)
        {
            cout<<" ⇗,";
        }
        if(rightClear == true && currentSpace->left != ending)
        {
            cout<<" ⇒,";
        }
        if(downRightClear == true)
        {
            cout<<" ⇘,";
        }
        if(downClear == true)
        {
            cout<<" ⇓,";
        }
        if(downLeftClear == true)
        {
            cout<<" or ⇙.";
        }

        cout<<endl<<"Press";

        if(leftClear == true && currentSpace->left != beginning)
        {
            cout<<" 4 for ⇐,";
        }
        if(upLeftClear == true)
        {
            cout<<" 7 for ⇖,";
        }
        if(upClear == true)
        {
            cout<<" 8 for ⇑,";
        }
        if(upRightClear == true)
        {
            cout<<" 9 for ⇗,";
        }
        if(rightClear == true && currentSpace->left != ending)
        {
            cout<<" 6 for ⇒,";
        }
        if(downRightClear == true)
        {
            cout<<" 3 for ⇘,";
        }
        if(downClear == true)
        {
            cout<<" 2 for ⇓,";
        }
        if(downLeftClear == true)
        {
            cout<<" or 1 for ⇙.";
        }
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);
        cout<<"How many spaces do you what to move? : ";
        string Input2;
        cin>>ws;
        getline(cin, Input2);
        int input2 = stoi(Input2);
        boardSpace* MoveTo = new boardSpace;
        MoveTo = currentSpace;
        bool inWay = false;
        if(input == 8 && upClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->up;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->up;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 4 && leftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->left;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->left;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && rightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->right;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->right;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->down;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->down;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        if(input == 7 && upLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upLeft;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 9 && upRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upRight;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && downLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downLeft;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downRight;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }

    if(teamCount == 2)
    {
        if(currentSpace->up != NULL)
        {
            if(currentSpace->up->name == "_" || (currentSpace->up->team != Team && currentSpace->up->occupied == true))
            {
                downClear = true;
            }
        }
        if(currentSpace->left != NULL)
        {
            if(currentSpace->left->name == "_" || (currentSpace->left->team != Team && currentSpace->left->occupied == true))
            {
                rightClear = true;
            }
        }
        if(currentSpace->right != NULL)
        {
            if(currentSpace->right->name == "_" || (currentSpace->right->team != Team && currentSpace->right->occupied == true))
            {
                leftClear = true;
            }
        }
        if(currentSpace->down != NULL)
        {
            if(currentSpace->down->name == "_" || (currentSpace->down->team != Team && currentSpace->down->occupied == true))
            {
                upClear = true;
            }
        }
        if(currentSpace->upLeft != NULL)
        {
            if(currentSpace->upLeft->name == "_" || (currentSpace->upLeft->team != Team && currentSpace->upLeft->occupied == true))
            {
                downRightClear = true;
            }
        }
        if(currentSpace->upRight != NULL)
        {
            if(currentSpace->upRight->name == "_" || (currentSpace->upRight->team != Team && currentSpace->upRight->occupied == true))
            {
                downLeftClear = true;
            }
        }
        if(currentSpace->downRight != NULL)
        {
            if(currentSpace->downRight->name == "_" || (currentSpace->downRight->team != Team && currentSpace->downRight->occupied == true))
            {
                upLeftClear = true;
            }
        }
        if(currentSpace->downLeft != NULL)
        {
            if(currentSpace->downLeft->name == "_" || (currentSpace->downLeft->team != Team && currentSpace->downLeft->occupied == true))
            {
                upRightClear = true;
            }
        }
        if(upRightClear == false && upLeftClear == false && downRightClear == false && downLeftClear == false
           && upClear == false && downClear == false && rightClear == false && leftClear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }


        string Input;
        cout<<"Where would you like to move your Rook?"<<endl;

        cout<<"You may move";
        if(leftClear == true && currentSpace->right != beginning)
        {
            cout<<" ⇐,";
        }
        if(upLeftClear == true)
        {
            cout<<" ⇖,";
        }
        if(upClear == true)
        {
            cout<<" ⇑,";
        }
        if(upRightClear == true)
        {
            cout<<" ⇗,";
        }
        if(rightClear == true&& currentSpace->right != ending)
        {
            cout<<" ⇒,";
        }
        if(downRightClear == true)
        {
            cout<<" ⇘,";
        }
        if(downClear == true)
        {
            cout<<" ⇓,";
        }
        if(downLeftClear == true)
        {
            cout<<" or ⇙.";
        }

        cout<<endl<<"Press";

        if(leftClear == true && currentSpace->right != beginning)
        {
            cout<<" 4 for ⇐,";
        }
        if(upLeftClear == true)
        {
            cout<<" 7 for ⇖,";
        }
        if(upClear == true)
        {
            cout<<" 8 for ⇑,";
        }
        if(upRightClear == true)
        {
            cout<<" 9 for ⇗,";
        }
        if(rightClear == true && currentSpace->right != ending)
        {
            cout<<" 6 for ⇒,";
        }
        if(downRightClear == true)
        {
            cout<<" 3 for ⇘,";
        }
        if(downClear == true)
        {
            cout<<" 2 for ⇓,";
        }
        if(downLeftClear == true)
        {
            cout<<" or 1 for ⇙.";
        }
        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);
        cout<<"How many spaces do you what to move? : ";
        string Input2;
        cin>>ws;
        getline(cin, Input2);
        int input2 = stoi(Input2);
        boardSpace* MoveTo = new boardSpace;
        MoveTo = currentSpace;
        bool inWay = false;
        if(input == 8 && upClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->down;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->down;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 4 && leftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->right;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->right;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && rightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->left;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->left;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->up;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->up;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        if(input == 7 && upLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downRight;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 9 && upRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->downLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->downLeft;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 6 && downLeftClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upRight;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upRight;
            }

            if(inWay == false)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else if(input == 2 && downRightClear == 1)
        {
            for(int i = 0; i < input2-1; i++)
            {
                MoveTo = MoveTo->upLeft;
                if(MoveTo->occupied == true || MoveTo == NULL)
                {
                    inWay= true;
                    break;
                }
            }
            if(MoveTo != NULL)
            {
                MoveTo = MoveTo->upLeft;
            }

            if(inWay == false && MoveTo->team != Team)
            {
                MoveTo->name = currentSpace->name;
                MoveTo->occupied = true;
                MoveTo->team = currentSpace->team;
                currentSpace->name = "_";
                currentSpace->occupied = false;
                currentSpace->team = "NULL";
                return turnComplete;
            }
            else
            {
                cout<<"Not a valid move."<<endl;
                turnComplete = false;
                return turnComplete;
            }
        }
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }
}
/* King Comment Block
Function Prototype:
bool Chess::King(string, boardSpace*, int);

Function Description:
This function is written to illustrate all possible moves that a king can make. The function allows
pawns to move one space forward, backward, left, right, and diagonal (in all directions). It also allows
the king to attack if an enemy piece is within range.

Example:
Chess *NewGame = new Chess();
NewGame->King(Team1, inSpot, 1);

Pre-condition: This function requires three pre-conditions to be met. The first, the input string name is
the name of the team that is playing in that turn. The second, the input boardSpace pointer is the space
on the board where the chess piece resides. This will also be used to check all possible moves for
this piece. The third, the input integer is the counter telling us which team is in play. Each chess piece function
requires two additional pointers to be set: beginning and ending. These are set to NULL inside the constructor.

Post-condition: Once this function has run through, the king will either have moved one space in all directions or it
will attack an enemy piece if it is within range. Pointers and struct attributes will be updated after each successive
move.
*/
bool Chess::King(std::string Team, boardSpace* currentSpace , int teamCount)
{
    //Set initial bool checks to false. These will be used to check if a space is clear or not.
    bool upClear = false;
    bool upRightClear = false;
    bool upLeftClear = false;

    bool leftClear = false;
    bool rightClear = false;

    bool downClear = false;
    bool downRightClear = false;
    bool downLeftClear = false;

    //Bool to tell program whether or not to switch player turn.
    bool turnComplete = true;

    //If team one is in play, do the following:
    if(teamCount == 1)
    {
        //Check if up is clear. If so, set bool to true.
        if(currentSpace->up != NULL)
        {
            if(currentSpace->upLeft->name == "_"|| (currentSpace->up->team != Team && currentSpace->up->occupied == true))
            {
                upClear = true;
            }
        }
        //Check if down is clear. If so, set bool to true.
        if(currentSpace->down != NULL)
        {
            if(currentSpace->down->name == "_"|| (currentSpace->down->team != Team && currentSpace->down->occupied == true))
            {
                downClear = true;
            }
        }
        //Check if up and to the left is clear. If so, set bool to true.
        if(currentSpace->upLeft != NULL)
        {
            if(currentSpace->upLeft->name == "_" || (currentSpace->upLeft->team != Team && currentSpace->upLeft->occupied == true))
            {
                upLeftClear = true;
            }
        }
        //Check if up and to the right is clear. If so, set bool to true.
        if(currentSpace->upRight != NULL)
        {
            if(currentSpace->upRight->name == "_" || (currentSpace->upRight->team != Team && currentSpace->upRight->occupied == true))
            {
                upRightClear = true;
            }
        }
        //Check if right is clear. If so, set bool to true.
        if(currentSpace->right != NULL)
        {
            if(currentSpace->right->name == "_" || (currentSpace->right->team != Team && currentSpace->right->occupied == true))
            {
                rightClear = true;
            }
        }
        //Check if left is clear. If so, set bool to true.
        if(currentSpace->left != NULL)
        {
            if(currentSpace->left->name == "_" || (currentSpace->left->team != Team && currentSpace->left->occupied == true))
            {
                leftClear = true;
            }
        }
        //Check if down and to the left is clear. If so, set bool to true.
        if(currentSpace->downLeft != NULL)
        {
            if(currentSpace->downLeft->name == "_" || (currentSpace->downLeft->team != Team && currentSpace->downLeft->occupied == true))
            {
                downLeftClear = true;
            }
        }
        //Check if down and to the right is clear. If so, set bool to true.
        if(currentSpace->downRight != NULL)
        {
            if(currentSpace->downRight->name == "_" || (currentSpace->downRight->team != Team && currentSpace->downRight->occupied == true))
            {
                downRightClear = true;
            }
        }
        //If all spots are not clear, inform user.
        if(leftClear == false && upLeftClear == false && upClear == false && upRightClear == false && rightClear == false && downRightClear == false && downClear == false && downLeftClear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }

        string Input;
        cout<<"Where would you like to move your King?"<<endl;

        //Options to tell the user where they are able to move. Indicated by arrows.
        cout<<"You may move";
        if(leftClear == true)
        {
            cout<<" ⇐,";
        }
        if(upLeftClear == true)
        {
            cout<<" ⇖,";
        }
        if(upClear == true)
        {
            cout<<" ⇑,";
        }
        if(upRightClear == true)
        {
            cout<<" ⇗,";
        }
        if(rightClear == true)
        {
            cout<<" ⇒,";
        }
        if(downRightClear == true)
        {
            cout<<" ⇘,";
        }
        if(downClear == true)
        {
            cout<<" ⇓,";
        }
        if(downLeftClear == true)
        {
            cout<<" or ⇙.";
        }

        //Take in the user move input using number pad directions.
        cout<<endl<<"Press";
        if(leftClear == true)
        {
            cout<<" 4 for ⇐,";
        }
        if(upLeftClear == true)
        {
            cout<<" 7 for ⇖,";
        }
        if(upClear == true)
        {
            cout<<" 8 for ⇑,";
        }
        if(upRightClear == true)
        {
            cout<<" 9 for ⇗,";
        }
        if(rightClear == true)
        {
            cout<<" 6 for ⇒,";
        }
        if(downRightClear == true)
        {
            cout<<" 3 for ⇘,";
        }
        if(downClear == true)
        {
            cout<<" 2 for ⇓,";
        }
        if(downLeftClear == true)
        {
            cout<<" 1 for ⇙.";
        }

        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);

        //If the user wants to move to the left, do the following:
        if(input == 4 && leftClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->left->name = currentSpace->name;
            currentSpace->left->occupied = true;
            currentSpace->left->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move up and to the left, do the following:
        else if(input == 7 && upLeftClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->upLeft->name = currentSpace->name;
            currentSpace->upLeft->occupied = true;
            currentSpace->upLeft->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move up, do the following:
        else if(input == 8 && upClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->up->name = currentSpace->name;
            currentSpace->up->occupied = true;
            currentSpace->up->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move up and to the right, do the following:
        else if(input == 9 && upRightClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->upRight->name = currentSpace->name;
            currentSpace->upRight->occupied = true;
            currentSpace->upRight->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move to the right, do the following:
        else if(input == 6 && rightClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->right->name = currentSpace->name;
            currentSpace->right->occupied = true;
            currentSpace->right->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down and to the right, do the following:
        else if(input == 3 && downRightClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->downRight->name = currentSpace->name;
            currentSpace->downRight->occupied = true;
            currentSpace->downRight->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down, do the following:
        else if(input == 2 && downClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->down->name = currentSpace->name;
            currentSpace->down->occupied = true;
            currentSpace->down->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down and to the left, do the following:
        else if(input == 1 && downLeftClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->downLeft->name = currentSpace->name;
            currentSpace->downLeft->occupied = true;
            currentSpace->downLeft->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the input is not correct, inform user.
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }

    //If team two is in play, do the following:
    if(teamCount == 2)
    {
        //Board has flipped, so directions are now opposite.
        //Check if up is clear. If so, set down to true.
        if(currentSpace->up != NULL)
        {
            if(currentSpace->upLeft->name == "_"|| (currentSpace->up->team != Team && currentSpace->up->occupied == true))
            {
                downClear = true;
            }
        }
        //Check if down is clear. If so, set up to true.
        if(currentSpace->down != NULL)
        {
            if(currentSpace->down->name == "_"|| (currentSpace->down->team != Team && currentSpace->down->occupied == true))
            {
                upClear = true;
            }
        }
        //Check if up and to the left is clear. If so, set down and to the right to true.
        if(currentSpace->upLeft != NULL)
        {
            if(currentSpace->upLeft->name == "_" || (currentSpace->upLeft->team != Team && currentSpace->upLeft->occupied == true))
            {
                downRightClear = true;
            }
        }
        //Check if up and to the right is clear. If so, set down and to the left to true.
        if(currentSpace->upRight != NULL)
        {
            if(currentSpace->upRight->name == "_" || (currentSpace->upRight->team != Team && currentSpace->upRight->occupied == true))
            {
                downLeftClear = true;
            }
        }
        //Check if right is clear. If so, set left to true.
        if(currentSpace->right != NULL)
        {
            if(currentSpace->right->name == "_" || (currentSpace->right->team != Team && currentSpace->right->occupied == true))
            {
                leftClear = true;
            }
        }
        //Check if left is clear. If so, set right to true.
        if(currentSpace->left != NULL)
        {
            if(currentSpace->left->name == "_" || (currentSpace->left->team != Team && currentSpace->left->occupied == true))
            {
                rightClear = true;
            }
        }
        //Check if down and to the left is clear. If so, set up and to the right to true.
        if(currentSpace->downLeft != NULL)
        {
            if(currentSpace->downLeft->name == "_" || (currentSpace->downLeft->team != Team && currentSpace->downLeft->occupied == true))
            {
                upRightClear = true;
            }
        }
        //Check if down and to the right is clear. If so, set up and to the left to true.
        if(currentSpace->downRight != NULL)
        {
            if(currentSpace->downRight->name == "_" || (currentSpace->downRight->team != Team && currentSpace->downRight->occupied == true))
            {
                upLeftClear = true;
            }
        }
        //If all spots are not clear, inform user.
        if(leftClear == false && upLeftClear == false && upClear == false && upRightClear == false && rightClear == false && downRightClear == false && downClear == false && downLeftClear == false)
        {
            cout<<"Piece has nowhere to move."<<endl;
            turnComplete = false;
            return turnComplete;
        }

        string Input;
        cout<<"Where would you like to move your King?"<<endl;

        //Options to tell the user where they are able to move. Indicated by arrows.
        cout<<"You may move";
        if(leftClear == true)
        {
            cout<<" ⇐,";
        }
        if(upLeftClear == true)
        {
            cout<<" ⇖,";
        }
        if(upClear == true)
        {
            cout<<" ⇑,";
        }
        if(upRightClear == true)
        {
            cout<<" ⇗,";
        }
        if(rightClear == true)
        {
            cout<<" ⇒,";
        }
        if(downRightClear == true)
        {
            cout<<" ⇘,";
        }
        if(downClear == true)
        {
            cout<<" ⇓,";
        }
        if(downLeftClear == true)
        {
            cout<<" or ⇙.";
        }

        //Take in the user move input using number pad directions.
        cout<<endl<<"Press";
        if(leftClear == true)
        {
            cout<<" 4 for ⇐,";
        }
        if(upLeftClear == true)
        {
            cout<<" 7 for ⇖,";
        }
        if(upClear == true)
        {
            cout<<" 8 for ⇑,";
        }
        if(upRightClear == true)
        {
            cout<<" 9 for ⇗,";
        }
        if(rightClear == true)
        {
            cout<<" 6 for ⇒,";
        }
        if(downRightClear == true)
        {
            cout<<" 3 for ⇘,";
        }
        if(downClear == true)
        {
            cout<<" 2 for ⇓,";
        }
        if(downLeftClear == true)
        {
            cout<<" 1 for ⇙.";
        }

        cout<<endl;
        cin>>ws;
        getline(cin, Input);
        int input = stoi(Input);

        //If the user wants to move to the left, do the following:
        if(input == 4 && leftClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->right->name = currentSpace->name;
            currentSpace->right->occupied = true;
            currentSpace->right->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move up and to the left, do the following:
        else if(input == 7 && upLeftClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->downRight->name = currentSpace->name;
            currentSpace->downRight->occupied = true;
            currentSpace->downRight->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move up, do the following:
        else if(input == 8 && upClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->down->name = currentSpace->name;
            currentSpace->down->occupied = true;
            currentSpace->down->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move up and to the right, do the following:
        else if(input == 9 && upRightClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->downLeft->name = currentSpace->name;
            currentSpace->downLeft->occupied = true;
            currentSpace->downLeft->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move to the right, do the following:
        else if(input == 6 && rightClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->left->name = currentSpace->name;
            currentSpace->left->occupied = true;
            currentSpace->left->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down and to the right, do the following:
        else if(input == 3 && downRightClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->upLeft->name = currentSpace->name;
            currentSpace->upLeft->occupied = true;
            currentSpace->upLeft->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down, do the following:
        else if(input == 2 && downClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->up->name = currentSpace->name;
            currentSpace->up->occupied = true;
            currentSpace->up->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the user wants to move down and to the left, do the following:
        else if(input == 1 && downLeftClear == 1)
        {
            //Move the piece to the new spot and set the appropriate attributes.
            currentSpace->upRight->name = currentSpace->name;
            currentSpace->upRight->occupied = true;
            currentSpace->upRight->team = currentSpace->team;
            //Set the old space to NULL.
            currentSpace->name = "_";
            currentSpace->occupied = false;
            currentSpace->team = "NULL";
            //End turn.
            return turnComplete;
        }
        //If the input is not correct, inform user.
        else
        {
            cout<<"Not a valid move."<<endl;
            turnComplete = false;
            return turnComplete;
        }
    }
}

/* Pawn Switch Out function

Function Prototype:
void Chess::PawnSwitchOut(std::string Team, boardSpace* currentSpace , int teamCount);

Function Description:
This function is activated when a pawn of team A reaches the end of tean B's side. This allows team A to change their
pawn to a Queen, Bishop, Rook, or Knight.

Example:

NewGame->PawnSwitchOut(team1, (a5)spot, 1);

Pre-condition:
We need to know the pawns team name, the spot that it has reached, and the team number.

Post-condition: The piece will become the chosen piece
*/
void Chess::PawnSwitchOut(boardSpace* pawnSpot,std::string Team1, int teamCount)
{
    //ZACH
    char X = pawnSpot->boardSpot[0];
    //if it has reached the a row or the h row.
    if((X == 'a' && teamCount == 1) || (X == 'h' && teamCount == 2))
    {
        cout<<endl<<"You made a pawn to the other end!"<<endl;
        cout<<"What do you want to change your pawn too?"<<endl;
        bool changed = false;
        while(changed == false)
        {
            cout<<"Press 1 for Queen, 2 for Bishop, 3 for Knight, 4 for Rook"<<endl;
            string input;
            cin>>ws;
            getline(cin, input);
            int Input = stoi(input);
            if(teamCount == 1)
            {
                if(Input == 1)
                {
                    pawnSpot->name = "8";
                    changed = true;
                }
                if(Input == 2)
                {
                    pawnSpot->name = "7";
                    changed = true;
                }
                if(Input == 3)
                {
                    pawnSpot->name = "6";
                    changed = true;
                }
                if(Input == 4)
                {
                    pawnSpot->name = "5";
                    changed = true;
                }
                if(changed != true)
                {
                    cout<<"Not a valid option."<<endl;
                }
            }
            else if(teamCount == 2)
            {
                if(Input == 1)
                {
                    pawnSpot->name = "Q";
                    changed = true;
                }
                if(Input == 2)
                {
                    pawnSpot->name = "B";
                    changed = true;
                }
                if(Input == 3)
                {
                    pawnSpot->name = "N";
                    changed = true;
                }
                if(Input == 4)
                {
                    pawnSpot->name = "R";
                    changed = true;
                }
                if(changed != true)
                {
                    cout<<"Not a valid option."<<endl;
                }
            }


        }
    }
}

/*
    string integerCheck(string userInput);
    Method checks if user input is an integer
    ex. integerCheck("up")
    Pre-conditions: function takes user input in as a string
    Post-condition: user input has been validated and can be cast as an integer using stoi without core dumping
*/
std::string Chess::integerCheck(std::string userInput)
{
    while (userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4" && userInput != "5"
           && userInput != "6" && userInput != "7" && userInput != "8" && userInput != "9")
    {
        std::cout << "Please enter an integer between 1 and 9." << std::endl;
        getline(cin, userInput);
    }
    return userInput;
}


/*
    bool goBeyondEdgeOfBoard(boardSpace* currentSpace, int numberOfMoves, string direction);
    Method returns true if the desired move will take the piece off the edge of the board
    ex. goBeyondEdgeOfBoard(h2, 3, "upLeft")
    Pre-conditions: takes in current space on the board, the number of moves and direction desired
    Post-conditions: determines whether the piece will go off the board in the number of moves and direction desired
*/
bool Chess::goBeyondEdgeOfBoard(boardSpace* currentSpace, int numberOfMoves, std::string direction)
{
    boardSpace *tempSpacePointer = currentSpace;
    int counter = 1;
    while (tempSpacePointer != NULL)
    {
        counter++;
        if (direction == "up"){
            tempSpacePointer = tempSpacePointer->up;
        }
        else if (direction == "upLeft"){
            tempSpacePointer = tempSpacePointer->upLeft;
        }
        else if (direction == "upRight"){
            tempSpacePointer = tempSpacePointer->upRight;
        }
        else if (direction == "right"){
            tempSpacePointer = tempSpacePointer->right;
        }
        else if (direction == "downRight"){
            tempSpacePointer = tempSpacePointer->downRight;
        }
        else if (direction == "down"){
            tempSpacePointer = tempSpacePointer->down;
        }
        else if (direction == "downLeft"){
            tempSpacePointer = tempSpacePointer->downLeft;
        }
        else{
            tempSpacePointer = tempSpacePointer->left;
        }
    }
    if (numberOfMoves > counter)
    {
        return true;
    }
    return false;
}
