#include<iostream>
#include<iomanip>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

#define INT_MAX 2147482647
#define MAX_TRIES 5
#define SIDE 3
#define ROW 4
#define COL 4
#define PLAYER1 1
#define PLAYER2 2
#define PLAYER1MOVE 'O'
#define PLAYER2MOVE 'X'

using namespace std;

void memoryGame() ;
void playTicTacToe(int );
int main(int argc, const char * argv[]) { 
    int option = 0;
    do {
		rand();
		cout << "1. Memory Game" <<endl;
		cout << "2. Tic-Tac-Toe" <<endl;
		cout << "3. Exit" <<endl;

	cin >> option;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	if(option == 1) {
	    memoryGame();
	}
	else if (option == 2) {
	    playTicTacToe(1);
	}
    } 
	while (option != 3);
    getchar();
    return 0;
}

struct RNG {
    int operator() (int n) {
	return rand() / (1.0 + RAND_MAX) * n;
    }
};


void shuffle(int cards[][COL]) {
    int start[16] = {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
    int index;
    srand((unsigned)time(NULL));

    for (index = 0; index < ROW * COL; index++) {
     int rIndex = rand() % 15 + 1;
     int temp = start[index];
     start[index] = start[rIndex];
     start[rIndex] = temp;
	 }

    index = 0;
    for(int row = 0; row < ROW; row++) {
	for (int col = 0; col < COL; col++) {
	    cards[row][col] = start[index];
	    index=index+1;
	}
    }
}

// to function displays the content of matrix

void cheat(int cards[][COL]) {
    cout << setw(3) << '|' << setw(4) << "1"<< setw(4) << "2" << setw(4) << "3" << setw(4) << "4" << endl;
    cout<<setfill('-')<<setw(20)<<"-"<<endl;
    cout<<setfill(' ');

    for (int row = 0; row < ROW; row++) {
	cout << row + 1 <<" |";
	for (int col = 0; col < COL; col++) {
	    cout << setw(4) << cards[row][col];
	}
	cout<<endl;
    }
    cout<<endl;
}

/*
cards 2D array cards
 displayed first time
 selR1 selects row 1
 selC1 selects col 1
 selR2 selects row 2
 selC2 selects row 2
 */

void displayBoard(int cards[][COL], bool cardstatus[][COL], bool firstTime, int selR1 = -1, int selC1 = -1, int selR2 = -1, int selC2 = -1) {
    cout << setw(3) << '|'<< setw(4) << "1" << setw(4) << "2" << setw(4) << "3" << setw(4) << "4" << endl;
    cout << setfill('-') << setw(20) << "-" << endl;
    cout << setfill(' ');

    for (int row = 0; row < ROW; row++) {
	cout << row +1<<" |";
	for (int col = 0; col < COL; col++) {
	    if(firstTime) {
		cout << setw(4) << "*";
		cardstatus[row][col] = false; 
	    }
	    else {
		if ((row == selR1) && (col == selC1)) {
		    cout << setw(4) << cards[row][col];
		}
		else if((row == selR2) && (col == selC2)) {
		    cout <<setw(4) << cards[row][col];
		}
		else if (cardstatus[row][col] == true) {
		    cout << setw(4) << cards[row][col];
		}
		else {
		    cout << setw(4) << "*";
		}
	    }
	}
	cout<<endl;
    }
}

//Function for memory game of 4*4 matrix

void memoryGame() {
    char comma;
    int selR1, selC1, selR2, selC2, cards[ROW][COL];
    bool cardstatus[ROW][COL];

    bool gameover = false;
    int moves;
	moves = 0;
	shuffle(cards);
	displayBoard(cards,cardstatus, true);
	cout<<endl;

	do {
	    bool check = false;
	    do {
		check = false;
		cout << "Please insert the first card row and column seperated by a comma." << endl;
		cin >> selR1 >> comma >> selC1;
		cin.clear();
		cin.ignore(INT_MAX,'\n');
		if( selR1 < 1 || selR1 > ROW){
		    cout << "Enter row within range." << endl;
		    check = true;

		} 
		else if( selC1 < 1 || selC1 > COL) {
		    cout << "Enter  column within range." << endl;
		    check = true;
		}
		else if(cardstatus[selR1 - 1][selC1 - 1] == true) //if the card is flipped.
		{
		    cout << "This card is already flipped! Select another card." << endl;
		    check = true;
		}

	    }
		while(check != false);
	    check = false;
	    do {
		cout << "Please insert the second card row and column separated by a comma.\n";
		cin >> selR2 >> comma >> selC2;
		cin.clear();
		cin.ignore(INT_MAX,'\n');
		check = false;

		if( selR2 < 1 || selR2 > ROW) {
		    cout << "Enter row within range." << endl;
		    check = true;
		}
		else if( selC2 < 1 || selC2 > COL) {
		    cout << "Enter  column within range." << endl;
		    check = true;
		}
		else if((selR1 == selR2) && (selC1 == selC2)) {
		    cout << "You can't select same card twice!" << endl;
		    check = true;
		}
		else if(cardstatus[selR2-1][selC2-1] == true) //if the card is flipped.
		{
		    cout << "This card is already flipped! Select another card." << endl;
		    check = true;
		}

	    }while(check != false);
	    selR1--;
	    selC1--;
	    selR2--;
	    selC2--;
	    displayBoard(cards,cardstatus, false,selR1,selC1,selR2,selC2);

	    if (cards[selR1][selC1]==cards[selR2][selC2]) // if cards match, keep them flipped.
	    {
		cout << "Cards Matched!" << endl;
		cardstatus[selR1][selC1] = true;
		cardstatus[selR2][selC2] = true;
	    }
	    else {
		cout <<" Cards did not match, please try again." << endl;
	    }
	    cin.get();
	    do {
		cout << "Press a key to continue...";
	    } while (cin.get() != '\n');
		
	    displayBoard(cards,cardstatus, false);

	    gameover = true;

	    for (int row = 0; row < ROW; row++) {
			for (int col = 0; col < COL; col++) {
				if(cardstatus[row][col]==false) {
					gameover = false;
					break;
		    }
		}
		if(gameover == false) {
		    break;
		}
	    }
	    moves++; // count moves here.
	    //repeat
	}
	while(gameover != true); 
	cout << "Congratulations, You won!!!" << endl;
	cout << "It Required " << moves << " moves to finish it." << endl;
    cin.get();
}

//tic tac toe
// A function to show the current board status

void showBoard(char board[][SIDE]) {
    cout<<endl<<endl;
    for(int r = 0; r < SIDE; r++) {
	cout<<"\t\t";
	for(int c = 0; c < SIDE; c++) {
	    if(c == SIDE-1)
		 cout << setw(2) << board[r][c];
	    else
		cout << setw(2) << board[r][c] << setw(2) << "|";
	}
	if(r == SIDE - 1)
	    cout << endl;
	else
	    cout << endl << "\t\t" << setfill('-') << setw(12) << "-" << setfill(' ') << endl;
    }
    return;
}

//To show the instructions
void showInstructions() {
    cout << "\t\t\t Tic-Tac-Toe\n\n";
    cout << "Choose a cell numbered from 1 to 9 as below and play\n\n";
    cout << "\t\t\t 1 | 2 | 3 \n";
    cout << "\t\t\t--------------\n";
    cout << "\t\t\t 4 | 5 | 6 \n";
    cout << "\t\t\t--------------\n";
    cout << "\t\t\t 7 | 8 | 9 \n\n";
    cout << "-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n";
    return;
}

//To initialise the game

void initialise(char board[][SIDE], int moves[]) {
    for (int i = 0; i < SIDE; i++) {
	for (int j = 0; j < SIDE; j++)
	    board[i][j] = ' ';
    }

    // Fill the moves with numbers
    for (int k = 0; k < SIDE * SIDE; k++)
	moves[k] = 0;
    return;
}

// To declare the winner of the game

void declareWinner(int whoseTurn) {
    if (whoseTurn == PLAYER1)
	cout << "PLAYER1 has won" << endl;
    else
	cout << "PLAYER2 has won" << endl;
    return;
}

//returns true if any of the row
//is crossed with the same player's move

bool rowCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
	if (board[i][0] == board[i][1] &&
	    board[i][1] == board[i][2] &&
	    board[i][0] != ' ')
	    return (true);
    }
    return(false);
}

// returns true if any of the column
// is crossed with the same player's move

bool columnCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
	if (board[0][i] == board[1][i] &&
	    board[1][i] == board[2][i] &&
	    board[0][i] != ' ')
	    return (true);
    }
    return(false);
}

// returns true if any of the diagonal
// is crossed with the same player's move

bool diagonalCrossed(char board[][SIDE]) {
    if (board[0][0] == board[1][1] &&
	board[1][1] == board[2][2] &&
	board[0][0] != ' ')
	return(true);

    if (board[0][2] == board[1][1] &&
	board[1][1] == board[2][0] &&
	board[0][2] != ' ')
	return(true);
    return(false);
}

// returns true if the game is over
// else it returns a false

bool gameOver(char board[][SIDE]) {
    return(rowCrossed(board) || columnCrossed(board)
	   || diagonalCrossed(board) );
}

// play Tic-Tac-Toe
void playTicTacToe(int whoseTurn) {
    // A 3*3 Tic-Tac-Toe board for playing
    char board[SIDE][SIDE];
    int moves[SIDE*SIDE];

    initialise(board, moves);
    showInstructions();

    int moveIndex = 0, x, y;
    bool check = false;
    // play till the game is over or it is a draw
    while (gameOver(board) == false &&
	   moveIndex != SIDE * SIDE) {
	check = false;

	int selectedPos = 0;
	do {
	    if (whoseTurn == PLAYER1)
		cout << "PLAYER1, enter cell number... ";
	    else
		cout << "PLAYER2, enter cell number... ";

	    cin>>selectedPos;
	    cin.clear();
	    cin.ignore(INT_MAX,'\n');
	    if(selectedPos > 0 && selectedPos <= SIDE*SIDE) {
			 if(moves[selectedPos - 1] == 0){
				x = (selectedPos - 1) / SIDE;
				y = (selectedPos - 1) % SIDE;
		if (whoseTurn == PLAYER1) {
		    board[x][y] = PLAYER1MOVE;
		    whoseTurn = PLAYER2;
		} else {
		   board[x][y] = PLAYER2MOVE;
		    whoseTurn = PLAYER1;
		}

		showBoard(board);
		moveIndex ++;

		check = true;
		moves[selectedPos-1] = 1;
	    }
	    else {
		cout << "Cell already selected. Select another..." << endl;
	    }

	    }
	    else {
		cout << "Enter a valid number..." << endl;
	    }

	}
	while(check != true);
    }

    // If the game is drawn
    if (gameOver(board) == false && moveIndex == SIDE * SIDE)
	cout<<"It's a draw\n";
    else {
	if (whoseTurn == PLAYER1)
	    whoseTurn = PLAYER2;
	else if (whoseTurn == PLAYER2)
	    whoseTurn = PLAYER1;

	declareWinner(whoseTurn);
    }
    cin.get();
    return;
}

// return 0 if not found, -1 if already found else count of times found
 
