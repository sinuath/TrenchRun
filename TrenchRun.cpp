//<<<<<<< HEAD
// TrenchRun.cpp : Defines the entry point for the console application.
// My Name is Chris Diel And I wrote this program in C++, for Gordon's CSC 180 class.
// I used some code From Professor Scott Gordon for the color coding, as well as the
// min max tic tac toe example presented to class.

//#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
using namespace std;

/* This is all Text Color Stuff */
#define RESET           0
#define BRIGHT          1
#define DIM             2
#define UNDERLINE       3
#define BLINK           4
#define REVERSE         7
#define HIDDEN          8
#define BLACK           0
#define RED             1
#define GREEN           2
#define YELLOW          3
#define BLUE            4
#define MAGENTA         5
#define CYAN            6
#define WHITE           7
#define MAXMOVES        80
#define COMPUTER        0 // False = Computer
#define HUMAN           1 // True = Human
void textcolor(int attr, int fg, int bg);

void computerMove();
void initGame();
void displayGameBoard();
void playerMove();
bool gameOver();
void debugPiecesArrays();
int charToCoordinate(char character);
char coordinateToXChar(int coordinate);
char coordinateToYChar(int coordinate); // Take a Num and converts it to a char for output of possible moves.
void check4LegalMoves(bool player); // Is it the player?
void updateBoardState();
void tieFighterLegalMoves(bool player, int gamePiece);
void xWingLegalMoves(bool player, int gamePiece);
void debugLegalMoves();
void makemove();
int min(int depth);
int max(int depth);
int evaluate();
void listPlayerMoves();
void listComputerMoves();
void displayHistoryTable();
int moveGamePiece(bool player, int move[]);// Return integer of killed piece
void unMoveGamePiece(bool player, int move[], int deadPiece);// Return integer of killed piece
int findPiece(bool player);
int checkCollision(bool player, int piecePos);

bool gameOverNow = false;
int movePiece[4]; // This is the array that holds the next move, I'm making it global because i'm lazy and Tired at 1300+ lines of code anyway.
char userMove[4];
char gameBoard[7][7];
//string gameBoard[7][7];
char playerPieces [4][11]; // Piece Type, X Coordinate, Y Coordinate, Dead ... For Each Row 11 pieces. If a piece is dead I'll change the coordinates to (x,x)
char computerPieces [4][11]; 
int playerLegalMoves[4][MAXMOVES]; // First two Int Represent where the piece is, the second two represent possible moves
int computerLegalMoves[4][MAXMOVES];
int historyTable[5][300]; // Tracks every move of the game; [0][move] = Player; 0 = computer; 1 = player
int historyIndex = 0;
int numComputerMoves=0;
int numPlayerMoves=0;
int maxDepth=3;
bool validInput = true;
string winner;

int main()
{
	initGame();


	cout << "\nWelcome To Trench Run, My Name is ";
	textcolor(BRIGHT,GREEN,BLACK);
	cout << "Orpheus";
	textcolor(BRIGHT,WHITE,BLACK);
	cout << " and I will be your opponent.\n";
	
	cout<<"\n Would you Like to Move First or Second? \n Please Respond with 1 or 2: "; // This works, leaving it out during testing
	int playerOrder;
	cin>>playerOrder;
	if(playerOrder==2){
		check4LegalMoves(COMPUTER);// false = computer
		computerMove();
	}
	

	while(!gameOver()){
		displayGameBoard();
		//check4LegalMoves(true);// true = player
		check4LegalMoves(HUMAN);// false = computer
		debugLegalMoves();
		//gameOverNow = true;
		
		playerMove(); // This should be uncommented out, it's important but leaving it out for debugging.
		if(!gameOver()){
			check4LegalMoves(COMPUTER);// false = computer
			computerMove();
		}
		
	}
	displayGameBoard();
	cout << endl <<"Game Over"<<" Winner is: ";
	if(winner == "Player"){	
		textcolor(BRIGHT,GREEN,BLACK);
	}else{
		textcolor(BRIGHT,RED,BLACK);
	
	}
	cout <<winner<<endl;
	textcolor(RESET,WHITE,BLACK);
	displayHistoryTable();
    return 0;
}

void playerMove(){
	string userInput="zzzz";// I want to keep the array from accessing invalid memmory
	do{
		if(!validInput){
			cout<<endl<<"Invalid Entry, Please Re-enter Command: ";
		}else{
			cout<<endl<< "Please make your Move: ";
		}

		cin >> userInput;
		cout <<endl<< "User Input: "<<userInput<<endl;

		validInput = false; // Keeps us in the loop if user enters bad data


		//Converts user input to the boards numerical array.
		cout <<endl<< "User Code Conversion: ";
		for(int i=0;i<4;i++){
			movePiece[i]=charToCoordinate(userInput[i]);
			cout<<movePiece[i];
		}
		
		// Check move against list of legal moves for playerMove
		for(int legalMove=0; legalMove < numPlayerMoves; legalMove++){
				if(movePiece[0]==playerLegalMoves[0][legalMove] &
					 movePiece[1]==playerLegalMoves[1][legalMove] &
					 movePiece[2]==playerLegalMoves[2][legalMove] &
					 movePiece[3]==playerLegalMoves[3][legalMove]){
							cout<<"\nPlayer move: ";
							cout<<coordinateToXChar(playerLegalMoves[0][legalMove]);
							cout<<coordinateToYChar(playerLegalMoves[1][legalMove]);
							cout<<coordinateToXChar(playerLegalMoves[2][legalMove]);
							cout<<coordinateToYChar(playerLegalMoves[3][legalMove]);
					validInput = true;
					
				}
		}
		
		if(validInput){
			moveGamePiece(HUMAN, movePiece); // Player Move
			historyTable[4][historyIndex] = 1; // 1 = player
			for(int i=0;i<4;i++){
				historyTable[i][historyIndex]=movePiece[i];

			}
			historyIndex++;
		}
		/*
		if(userInput[0] == 'q'){ // Right Now this is only Temporary for Testing
			gameOverNow = true;
		}
		*/
	}while(!validInput);
}

void displayHistoryTable(){
	cout<<endl<<"--- History Table ---";
	for(int i=0;i<historyIndex;i++){
		cout<<endl<<"Move: ";
		cout<<coordinateToXChar(historyTable[0][i]);
		cout<<coordinateToYChar(historyTable[1][i]);
		cout<<" -> ";
		cout<<coordinateToXChar(historyTable[2][i]);
		cout<<coordinateToYChar(historyTable[3][i]);
		
		if(historyTable[4][i] == 0){
			cout<<" Computer";
		}
		else
		{
			cout<<" Player";
		}
	}
	cout<<endl;
	
}

void unMoveGamePiece(bool player, int move[], int deadPiece){} // Code Stub :P

/***
 *
 *
 *      Move Game Piece that is currently saved in movePiece[4] <0,1> = current location; <2,3> = Destination
 *
 */
int moveGamePiece(bool player, int move[]){ // Need to add undo move ADD: location of pieces, & move. In undo function add an unkill piece move.
	//cout<<endl<<"Move Piece!";
	int piecePos;
	int deadPiece = 999;

	piecePos = findPiece(player);
	if(player){
		if(piecePos == 100){
			cout<<endl<<"No Piece in that location";
			validInput = false;
		}else{
			playerPieces[1][piecePos] ='0' + movePiece[2];
			playerPieces[2][piecePos] ='0' + movePiece[3];
			cout<<endl<<"Player Move: "<<coordinateToXChar(movePiece[0])<<", "<<coordinateToYChar(movePiece[1])<<" to: "<<coordinateToXChar(movePiece[2])<<", "<<coordinateToYChar(movePiece[3]);
			deadPiece = checkCollision(player, piecePos);
			if(deadPiece<15){
				cout << endl<<"Player Capture: "<<deadPiece;
			}
			

		}
	}else{ // Computer
		if(piecePos == 100){
			cout<<endl<<"No Piece in that location";
			validInput = false;
		}else{
			computerPieces[1][piecePos] ='0' + movePiece[2];
			computerPieces[2][piecePos] ='0' + movePiece[3];
			cout<<endl<<"Computer Move: "<<coordinateToXChar(movePiece[0])<<", "<<coordinateToYChar(movePiece[1])<<" to: "<<coordinateToXChar(movePiece[2])<<", "<<coordinateToYChar(movePiece[3]);
			deadPiece = checkCollision(player, piecePos);
			if(deadPiece<15){
				cout << endl<<"Computer Capture: "<<deadPiece;
			}

		}
	}

	return deadPiece;

}
/***
 *
 *
 *	Takes Piece Position and Kills any piece that current piece moves to.
 *
 */
int checkCollision(bool player, int piecePos){
	int collide = 999;
	if(player){
		for(int b=0;b<=10;b++){
			if((playerPieces[1][piecePos]==computerPieces[1][b])&&(playerPieces[2][piecePos]==computerPieces[2][b])){
				//	computerPieces[1][b] = 'x';
				//	computerPieces[2][b] = 'x';
					computerPieces[3][b] = 'x';
					collide = b;
			}
		}
	}else{
		for(int b=0;b<=10;b++){
			if((playerPieces[1][b]==computerPieces[1][piecePos])&&(playerPieces[2][b]==computerPieces[2][piecePos])){
				//	playerPieces[1][b] = 'x';
				//	playerPieces[2][b] = 'x';
					playerPieces[3][b] = 'x';
					collide = b;
			}
		}
	}
	//debugPiecesArrays();
	return collide;
}

/***
 *
 *
 *		Finds piece location in array.
 *		For some brilliant reason I used a char array so finding the index is a bit more involved.
 *
 **/
int findPiece(bool player){
	char tempXCoord, tempYCoord;
	int tempPlace = 100;
	tempXCoord = '0' + movePiece[0];
	tempYCoord = '0' + movePiece[1];

	if(player){
		for(int i=0;i<11;i++){
			if(((playerPieces[1][i]) == tempXCoord) && (playerPieces[2][i] == tempYCoord)){
				tempPlace = i;
			}
		}
	}else{
		for(int i=0;i<11;i++){
			if(((computerPieces[1][i]) == tempXCoord) && (computerPieces[2][i] == tempYCoord)){
				tempPlace = i;	
			}
		}

	
	}

	return tempPlace;
}


void computerMove(){
	cout<<endl<< "Computer Move";
	int computerMove=rand()%numComputerMoves; // MY AI
	movePiece[0] = computerLegalMoves[0][computerMove]; // Source X coordinate
	movePiece[1] = computerLegalMoves[1][computerMove]; // Source Y Coordinate
	movePiece[2] = computerLegalMoves[2][computerMove]; // Destination X Coordinate
	movePiece[3] = computerLegalMoves[3][computerMove]; // Destination Y Coordinate
	moveGamePiece(COMPUTER, movePiece); // false = computer; true = player // In retrospect this was stupid. Wish i had done things OO
	
	//History Table
	historyTable[4][historyIndex] = 0; // 0 = Computer
	for(int i=0;i<4;i++){
		historyTable[i][historyIndex]=movePiece[i];
	}
	historyIndex++;
	
}
	// The following is Tic Tac Toe Code Ripped for use as a Base for my Min Max Functions.
/*
void makemove()
{ 
	int best=-20000,depth=0,score,mi,mj;
	
	// Iterate through every possible current move on board
	
	for (int i=0; i<3; i++)
	{ 
		for (int j=0; j<3; j++)
		{ 
		
		
			if (b[i][j]==0) // tic tac toe for free space
			{ 
				b[i][j]=1; // make move on board
				score = min(depth+1); // have min take it's move and return score
				
				if (score > best) { mi=i; mj=j; best=score; } // if score better, save move
					b[i][j]=0; // undo move
			} } }
	cout << "my move is " << mi << " " << mj << endl;
	b[mi][mj]=1; // set actual move
}

int min(int depth)
{ 
	int best=20000,score;
	if (check4winner() != -1) return (check4winner());
	if (depth == maxdepth) return (evaluate());
	for (int i=0; i<3; i++){ 
		for (int j=0; j<3; j++){ 
			if (b[i][j]==0){ 
				b[i][j]=2; // make move on board
				score = max(depth+1);
			if (score < best) best=score;
			b[i][j]=0; // undo move
			} } }
	return(best);
}

int max(int depth)
{ 
	int best=-20000,score;
	if (check4winner() != -1) return (check4winner());
	if (depth == maxdepth) return (evaluate());
	for (int i=0; i<3; i++){ 
		for (int j=0; j<3; j++){ 
			if (b[i][j]==0){ 
				b[i][j]=1; // make move on board
				score = min(depth+1);
				if (score > best) best=score;
					b[i][j]=0; // undo move
				} } }
        return(best);
}
*/
int evaluate()
{ return 0; }  // stub

/**
 *	I realize there's a better way to do this but I was feeling lazy and didn't want to think about it.
 */
char coordinateToXChar(int coordinate){
	char tempChar;
	switch (coordinate){
		case 0:
			tempChar = 'A';
			break;
		case 1:
			tempChar = 'B';
			break;
		case 2:
			tempChar = 'C';
			break;
		case 3:
			tempChar = 'D';
			break;
		case 4:
			tempChar = 'E';
			break;
		case 5:
			tempChar = 'F';
			break;
		case 6:
			tempChar = 'G';
			break;
		default:
			tempChar = 'Z';
	}
	return tempChar;
}

char coordinateToYChar(int coordinate){
	char tempChar;
	switch (coordinate){
		case 0:
			tempChar = '7';
			break;
		case 1:
			tempChar = '6';
			break;
		case 2:
			tempChar = '5';
			break;
		case 3:
			tempChar = '4';
			break;
		case 4:
			tempChar = '3';
			break;
		case 5:
			tempChar = '2';
			break;
		case 6:
			tempChar = '1';
			break;
		default:
			tempChar = 'Z';
	}
	return tempChar;
}


int charToCoordinate(char character){
	int tempInt;
	switch (character){
		case 'A':
			tempInt = 0;
			break;
		case 'B':
			tempInt = 1;
			break;
		case 'C':
			tempInt = 2;
			break;
		case 'D':
			tempInt = 3;
			break;
		case 'E':
			tempInt = 4;
			break;
		case 'F':
			tempInt = 5;
			break;
		case 'G':
			tempInt = 6;
			break;
		case 'a':
			tempInt = 0;
			break;
		case 'b':
			tempInt = 1;
			break;
		case 'c':
			tempInt = 2;
			break;
		case 'd':
			tempInt = 3;
			break;
		case 'e':
			tempInt = 4;
			break;
		case 'f':
			tempInt = 5;
			break;
		case 'g':
			tempInt = 6;
			break;
		case '7':
			tempInt = 0;
			break;
		case '6':
			tempInt = 1;
			break;
		case '5':
			tempInt = 2;
			break;
		case '4':
			tempInt = 3;
			break;
		case '3':
			tempInt = 4;
			break;
		case '2':
			tempInt = 5;
			break;
		case '1':
			tempInt = 6;
			break;
		default:
			tempInt = -1;
	}
	return tempInt;
}

bool gameOver(){
	if(playerPieces[3][5]=='x'){
		gameOverNow=true;
		winner = "Orpheus";
	}else if(computerPieces[3][5]=='x'){
		gameOverNow=true;
		winner = "Player";
		
	}
	return gameOverNow;
}

void check4LegalMoves(bool player){
	updateBoardState();
	if(player){
		numPlayerMoves = 0;
	
		//playerPieces [3][11];
		//playerLegalMoves[4][MAXMOVES];
		//
		//numComputerMoves=0;
		//numPlayerMoves=0;

		for(int i=0;i<11;i++){ 
			if((playerPieces[0][i]=='t')&&(playerPieces[3][i]!='x')){ // (x,x) Coordinates for a piece indicates it's dead now.
				tieFighterLegalMoves(player, i);
			}else if((playerPieces[0][i]== 'x')&&(playerPieces[3][i]!='x')){
				xWingLegalMoves(player, i);
			}
		}
	
	}else{
		numComputerMoves=0;
		for(int i=0;i<11;i++){ 
			if((computerPieces[0][i]=='T')&&(computerPieces[3][i]!='x')){ // (x,x) Coordinates for a piece indicates it's dead now.
				tieFighterLegalMoves(player, i);
			}else if((computerPieces[0][i]== 'X')&&(computerPieces[3][i]!='x')){
				xWingLegalMoves(player, i);
			}
		}
	
	}
}

void tieFighterLegalMoves(bool player, int gamePiece){
	/*
	 *
	 *
	int playerLegalMoves[4][MAXMOVES]; // First two Int Represent where the piece is, the second two represent possible moves
	int computerLegalMoves[4][MAXMOVES];
	int numComputerMoves=0;
	int numPlayerMoves=0;
	 *
	 * */
	int xCoordinate, yCoordinate;
	if(player){

		/****
		 *
		 *
		 *		PLAYER MOVE GENERATOR!
		 *
		 *
		 */
		xCoordinate=('0' - playerPieces[1][gamePiece])*-1;
		yCoordinate=('0' - playerPieces[2][gamePiece])*-1;
		//cout<<endl<<"Tie Fighter: X: "<<xCoordinate<<" Y: "<<yCoordinate;
		


		// Forward Y- Coordinate Tie Fighter Code
		bool canGoForward=true;
		int maxVertical=yCoordinate;

		// Possible Forward Moves for Tie Fighter
		for(int i=yCoordinate-1;i>=-1;i--){
			if(gameBoard[xCoordinate][i]!='-'){
				if(canGoForward){
					canGoForward=false;
					if((gameBoard[xCoordinate][i]=='X') || (gameBoard[xCoordinate][i]=='T')){
						maxVertical=i;
					}else{
						maxVertical= i + 1;
					}
				}
			}else if((i==-1) && (canGoForward)){
				maxVertical= i+1;
			}
		}
		if(maxVertical != yCoordinate){
			//cout<<endl<<"Possible Vertical Movements: X: "<<xCoordinate<<" Y: "<<maxVertical;
			for(int i=maxVertical;i<yCoordinate;i++){
				//cout<<endl<<"Coordinates in between: X: "<<xCoordinate<<" Y: "<<i;

				playerLegalMoves[0][numPlayerMoves] = xCoordinate;
				playerLegalMoves[1][numPlayerMoves] = yCoordinate;
				playerLegalMoves[2][numPlayerMoves] = xCoordinate;
				playerLegalMoves[3][numPlayerMoves] = i;
				numPlayerMoves++;
			}
		}

		// Possible Left Moves for Tie Fighter
		bool canGoLeft=true;
		int maxLeft=xCoordinate;
		for(int i=xCoordinate-1;i>=-1;i--){
			if(gameBoard[i][yCoordinate]!='-'){
				if(canGoLeft){
					canGoLeft=false;
					if((gameBoard[i][yCoordinate]=='X') || (gameBoard[i][yCoordinate]=='T')){
						maxLeft=i;
					}else{
						maxLeft= i + 1;
					}
				}
			}else if((i==-1)&& (canGoLeft)){
				maxLeft= i+1;
			}
		}
		if(maxLeft != xCoordinate){
			for(int i=maxLeft;i<xCoordinate;i++){
				//cout<<endl<<"Coordinates in between: X: "<<i<<" Y: "<<yCoordinate;

				playerLegalMoves[0][numPlayerMoves] = xCoordinate;
				playerLegalMoves[1][numPlayerMoves] = yCoordinate;
				playerLegalMoves[2][numPlayerMoves] = i;
				playerLegalMoves[3][numPlayerMoves] = yCoordinate;
				numPlayerMoves++;
			}
		}

		// Possible Right Moves For Tie Fighter.
		bool canGoRight=true;
		int maxRight=xCoordinate;
		
		for(int i=xCoordinate+1;i<=7;i++){
			if(gameBoard[i][yCoordinate]!='-'){
				if(canGoRight){
					//cout<<endl<<"Tie Fighter: "<<xCoordinate<<", "<<yCoordinate;
					//cout<<endl<<"x: "<<i;
					canGoRight=false;
					if((gameBoard[i][yCoordinate]=='X') || (gameBoard[i][yCoordinate]=='T')){
						maxRight=i;
					}else{
						//cout<<endl<<"i: "<<i;
						maxRight= i - 1;
					}
				}
			}else if((i==7)&&(canGoRight)){
				maxRight= 6;
			}
		}

		if(maxRight != xCoordinate){
			//cout<<endl<<"Possible Vertical Movements: X: "<<xCoordinate<<" Y: "<<maxVertical;
			for(int i=maxRight;i>xCoordinate;i--){

				playerLegalMoves[0][numPlayerMoves] = xCoordinate;
				playerLegalMoves[1][numPlayerMoves] = yCoordinate;
				playerLegalMoves[2][numPlayerMoves] = i;
				playerLegalMoves[3][numPlayerMoves] = yCoordinate;
				numPlayerMoves++;
			}
		}



		// Backward Y- Coordinate Tie Fighter Code
		bool canGoBackward=true;
		int maxBackward=yCoordinate;

		// Possible Forward Moves for Tie Fighter
		for(int i=yCoordinate+1;i<=6;i++){
			if(gameBoard[xCoordinate][i]!='-'){
				if(canGoBackward){
					canGoBackward=false;
					if((gameBoard[xCoordinate][i]=='X') || (gameBoard[xCoordinate][i]=='T') || (gameBoard[xCoordinate][i]=='*')){
						maxBackward=i;
						playerLegalMoves[0][numPlayerMoves] = xCoordinate;
						playerLegalMoves[1][numPlayerMoves] = yCoordinate;
						playerLegalMoves[2][numPlayerMoves] = xCoordinate;
						playerLegalMoves[3][numPlayerMoves] = i;
						numPlayerMoves++;
					}
				}
			}
		}
		/*
		}
		*/
		

	}else{

		/***
		 *
		 *	COMPUTER MOVE GENERATOR!!!!!!
		 *
		 *
		 */
		xCoordinate=('0' - computerPieces[1][gamePiece])*-1;
		yCoordinate=('0' - computerPieces[2][gamePiece])*-1;
		//cout<<endl<<"Tie Fighter: X: "<<xCoordinate<<" Y: "<<yCoordinate;


		// Forward Y- Coordinate Tie Fighter Code
		bool canGoForward=true;
		int maxVertical=yCoordinate;

		// Possible Forward Moves for Tie Fighter
		for(int i=yCoordinate+1;i<=7;i++){
			if(gameBoard[xCoordinate][i]!='-'){
				if(canGoForward){
					canGoForward=false;
					if((gameBoard[xCoordinate][i]=='x') || (gameBoard[xCoordinate][i]=='t')){
						maxVertical=i;
					}else{
						maxVertical= i - 1;
					}
				}
			}else if((i==7) && (canGoForward)){
				maxVertical= i-1;
			}
		}
		if(maxVertical != yCoordinate){
			//cout<<endl<<"Possible Vertical Movements: X: "<<xCoordinate<<" Y: "<<maxVertical;
			for(int i=maxVertical;i>yCoordinate;i--){
				//cout<<endl<<"Coordinates in between: X: "<<xCoordinate<<" Y: "<<i;

				computerLegalMoves[0][numComputerMoves] = xCoordinate;
				computerLegalMoves[1][numComputerMoves] = yCoordinate;
				computerLegalMoves[2][numComputerMoves] = xCoordinate;
				computerLegalMoves[3][numComputerMoves] = i;
				numComputerMoves++;
			}
		}

		// Possible Left Moves for Tie Fighter
		bool canGoLeft=true;
		int maxLeft=xCoordinate;
		for(int i=xCoordinate-1;i>=-1;i--){
			if(gameBoard[i][yCoordinate]!='-'){
				if(canGoLeft){
					canGoLeft=false;
					if((gameBoard[i][yCoordinate]=='x') || (gameBoard[i][yCoordinate]=='t')){
						maxLeft=i;
					}else{
						maxLeft= i + 1;
					}
				}
			}else if((i==-1)&& (canGoLeft)){
				maxLeft= i+1;
			}
		}
		if(maxLeft != xCoordinate){
			for(int i=maxLeft;i<xCoordinate;i++){
				//cout<<endl<<"Coordinates in between: X: "<<i<<" Y: "<<yCoordinate;

				computerLegalMoves[0][numComputerMoves] = xCoordinate;
				computerLegalMoves[1][numComputerMoves] = yCoordinate;
				computerLegalMoves[2][numComputerMoves] = i;
				computerLegalMoves[3][numComputerMoves] = yCoordinate;
				numComputerMoves++;
			}
		}

		// Possible Right Moves For Tie Fighter.
		bool canGoRight=true;
		int maxRight=xCoordinate;
		
		for(int i=xCoordinate+1;i<=7;i++){
			if(gameBoard[i][yCoordinate]!='-'){
				if(canGoRight){
					//cout<<endl<<"Tie Fighter: "<<xCoordinate<<", "<<yCoordinate;
					//cout<<endl<<"x: "<<i;
					canGoRight=false;
					if((gameBoard[i][yCoordinate]=='x') || (gameBoard[i][yCoordinate]=='t')){
						//cout<<endl<<"Collision i: "<<i;
						maxRight=i;
					}else{
						//cout<<endl<<"i: "<<i;
						maxRight= i - 1;
					}
				}
			}else if((i==7)&&(canGoRight)){
				maxRight= 6;
			}
		}

		if(maxRight != xCoordinate){
			//cout<<endl<<"Possible Vertical Movements: X: "<<xCoordinate<<" Y: "<<maxVertical;
			for(int i=maxRight;i>xCoordinate;i--){
				//cout<<endl<<"Coordinates in between: X: "<<i<<" Y: "<<yCoordinate;

				computerLegalMoves[0][numComputerMoves] = xCoordinate;
				computerLegalMoves[1][numComputerMoves] = yCoordinate;
				computerLegalMoves[2][numComputerMoves] = i;
				computerLegalMoves[3][numComputerMoves] = yCoordinate;
				numComputerMoves++;
			}
		}



		// Backward Y- Coordinate Tie Fighter Code
		bool canGoBackward=true;
		int maxBackward=yCoordinate;

		// Possible Forward Moves for Tie Fighter
		for(int i=yCoordinate-1;i>=0;i--){
			if(gameBoard[xCoordinate][i]!='-'){
				if(canGoBackward){
					canGoBackward=false;
					if((gameBoard[xCoordinate][i]=='x') || (gameBoard[xCoordinate][i]=='t') || (gameBoard[xCoordinate][i]=='@')){
						maxBackward=i;
						computerLegalMoves[0][numComputerMoves] = xCoordinate;
						computerLegalMoves[1][numComputerMoves] = yCoordinate;
						computerLegalMoves[2][numComputerMoves] = xCoordinate;
						computerLegalMoves[3][numComputerMoves] = i;
						numComputerMoves++;
					}
				}
			}
		}
		
	}
}

void debugLegalMoves(){
	//cout<<endl<<"Debugging Moves"<<endl;
	/*
	cout<<endl<<"Player Moves: "<<numPlayerMoves;
	for(int i=0;i<numPlayerMoves;i++){
		cout<<endl<<"move "<<i<<": "<<playerLegalMoves[0][i]<<playerLegalMoves[1][i]<<playerLegalMoves[2][i]<<playerLegalMoves[3][i];
	}
	
	cout<<endl<<"Computer Moves: "<<numComputerMoves;
	for(int i=0;i<numComputerMoves;i++){
		cout<<endl<<"move "<<i<<": "<<computerLegalMoves[0][i]<<computerLegalMoves[1][i]<<computerLegalMoves[2][i]<<computerLegalMoves[3][i];
	}
	*/
	listPlayerMoves();
	//listComputerMoves();
}

void listComputerMoves(){
	cout<<endl<<"Legal Computer Moves: ";
	cout<<endl<<"moves: ";
	for(int i=0;i<numComputerMoves;i++){
		cout<<coordinateToXChar(computerLegalMoves[0][i]);
		cout<<coordinateToYChar(computerLegalMoves[1][i]);
		cout<<coordinateToXChar(computerLegalMoves[2][i]);
		cout<<coordinateToYChar(computerLegalMoves[3][i]);
		cout<<"  ";
	}
}

void listPlayerMoves(){
	cout<<endl<<"Legal Player Moves: ";
	cout<<endl<<"moves: "; 
	for(int i=0;i<numPlayerMoves;i++){
		cout<<coordinateToXChar(playerLegalMoves[0][i]);
		cout<<coordinateToYChar(playerLegalMoves[1][i]);
		cout<<coordinateToXChar(playerLegalMoves[2][i]);
		cout<<coordinateToYChar(playerLegalMoves[3][i]);
		cout<<"  ";
	}
}

void xWingLegalMoves(bool player, int gamePiece){
	int xCoordinate, yCoordinate;
	if(player){
		xCoordinate=('0' - playerPieces[1][gamePiece])*-1;
		yCoordinate=('0' - playerPieces[2][gamePiece])*-1;
		/***
		 *
		 *        Max Left
		 */
		bool canGoForwardLeft=true;
		int maxForwardLeft=yCoordinate;
		int maxLeft=xCoordinate;
		//cout<<endl<<"Starting Points: ("<<xCoordinate<<", "<<yCoordinate<<") ";
		
		int tempX=xCoordinate;
		for(int i=yCoordinate-1;i>=-1;i--){
			tempX--;
			//cout<<endl<<"("<<tempX<<","<<i<<")";
			if(((i<0)||(tempX<0)) && (canGoForwardLeft)){
				maxForwardLeft= i+1;
				maxLeft=tempX+1;
				canGoForwardLeft=false;
				//cout<<endl<<"Off Board";
				//cout<<endl<<"X: "<<maxLeft<<", y: "<<maxForwardLeft;
			}else if(gameBoard[tempX][i]!='-'){
				if(canGoForwardLeft){
					canGoForwardLeft=false;
					if((gameBoard[tempX][i]=='X') || (gameBoard[tempX][i]=='T')){
						maxForwardLeft=i;
						maxLeft=tempX;
						//cout<<endl<<"Hit X or T";
						//cout<<endl<<"X: "<<tempX<<", y: "<<i;
					}else{
						maxForwardLeft= i + 1;
						maxLeft=tempX+1;
						//cout<<endl<<"Hit an indesctuctible";
						//cout<<endl<<"X: "<<maxLeft<<", y: "<<maxForwardLeft;
					}
				}
			}
		}


		if(maxForwardLeft != yCoordinate){
			//cout<<endl<<"Possible Vertical Movements: X: "<<xCoordinate<<" Y: "<<maxVertical;
			tempX = maxLeft;
			for(int i=maxForwardLeft;i<yCoordinate;i++){
				//cout<<endl<<"Coordinates in between: X: "<<xCoordinate<<" Y: "<<i;
				playerLegalMoves[0][numPlayerMoves] = xCoordinate;
				playerLegalMoves[1][numPlayerMoves] = yCoordinate;
				playerLegalMoves[2][numPlayerMoves] = tempX;
				playerLegalMoves[3][numPlayerMoves] = i;
				numPlayerMoves++;
				tempX++;
			}
		}
		
		/***
		 *
		 *        Max Forward Right
		 */
		bool canGoForwardRight=true;
		int maxForwardRight=yCoordinate;
		int maxRight=xCoordinate;
		//cout<<endl<<"Starting Points: ("<<xCoordinate<<", "<<yCoordinate<<") ";
		
		tempX=xCoordinate;
		for(int i=yCoordinate-1;i>=-1;i--){
			tempX++;
			//cout<<endl<<"("<<tempX<<","<<i<<")";
			if(((i<0)||(tempX>6)) && (canGoForwardRight)){
				maxForwardRight= i+1;
				maxRight=tempX-1;
				canGoForwardRight=false;
				//cout<<endl<<"Off Board";
				//cout<<endl<<"X: "<<maxRight<<", y: "<<maxForwardRight;
			}else if(gameBoard[tempX][i]!='-'){
				if(canGoForwardRight){
					canGoForwardRight=false;
					if((gameBoard[tempX][i]=='X') || (gameBoard[tempX][i]=='T')){
						maxForwardRight=i;
						maxRight=tempX;
						//cout<<endl<<"Hit X or T";
						//cout<<endl<<"X: "<<tempX<<", y: "<<i;
					}else{
						maxForwardRight= i + 1;
						maxRight=tempX-1;
						//cout<<endl<<"Hit an indesctuctible";
						//cout<<endl<<"X: "<<maxRight<<", y: "<<maxForwardRight;
					}
				}
			}
		}
		if(maxForwardRight != yCoordinate){
			//cout<<endl<<"Possible Vertical Movements: X: "<<xCoordinate<<" Y: "<<maxVertical;
			tempX = maxRight;
			for(int i=maxForwardRight;i<yCoordinate;i++){
				//cout<<endl<<"Coordinates in between: X: "<<xCoordinate<<" Y: "<<i;
				playerLegalMoves[0][numPlayerMoves] = xCoordinate;
				playerLegalMoves[1][numPlayerMoves] = yCoordinate;
				playerLegalMoves[2][numPlayerMoves] = tempX;
				playerLegalMoves[3][numPlayerMoves] = i;
				numPlayerMoves++;
				tempX--;
			}
		}

		/***
		 *
		 *
		 *      Max Backward Left
		 *
		 */
		// Backward Y- Coordinate Tie Fighter Code
		bool canGoBackward=true;
		int maxBackwardLeftY=yCoordinate;
		int maxBackwardLeftX=xCoordinate;

			//cout<<"Backward checking";
		// Possible Forward Moves for Tie Fighter
		for(int i=yCoordinate+1;i<=6;i++){
			maxBackwardLeftX--;
			//cout<<endl<<"( "<<maxBackwardLeftX<<", "<<i<<" )";
			
			if((gameBoard[maxBackwardLeftX][i]!='-')&&(maxBackwardLeftX <= 6)){
				if(canGoBackward){
					canGoBackward=false;
					if((gameBoard[maxBackwardLeftX][i]=='X') || (gameBoard[maxBackwardLeftX][i]=='T') || (gameBoard[maxBackwardLeftX][i]=='*')){
						maxBackwardLeftY=i;
						playerLegalMoves[0][numPlayerMoves] = xCoordinate;
						playerLegalMoves[1][numPlayerMoves] = yCoordinate;
						playerLegalMoves[2][numPlayerMoves] = maxBackwardLeftX;
						playerLegalMoves[3][numPlayerMoves] = i;
						numPlayerMoves++;
					}
				}
			}
		}


		/***
		 *
		 *
		 *      Max Backward Right
		 *
		 */
		// Backward Y- Coordinate Tie Fighter Code
		canGoBackward=true;
		int maxBackwardRightY=yCoordinate;
		int maxBackwardRightX=xCoordinate;


			//cout<<"Backward checking";
		// Possible Forward Moves for Tie Fighter
		for(int i=yCoordinate+1;i<=6;i++){
			maxBackwardRightX++;
			//cout<<endl<<"( "<<maxBackwardRightX<<", "<<i<<" )";
			
			if((gameBoard[maxBackwardRightX][i]!='-')&&(maxBackwardRightX <= 6)){
				if(canGoBackward){
					canGoBackward=false;
					if((gameBoard[maxBackwardRightX][i]=='X') || (gameBoard[maxBackwardRightX][i]=='T') || (gameBoard[maxBackwardRightX][i]=='*')){
						maxBackwardRightY=i;
						playerLegalMoves[0][numPlayerMoves] = xCoordinate;
						playerLegalMoves[1][numPlayerMoves] = yCoordinate;
						playerLegalMoves[2][numPlayerMoves] = maxBackwardRightX;
						playerLegalMoves[3][numPlayerMoves] = i;
						numPlayerMoves++;
					}
				}
			}
		}


	}else{
		/**
		 *
		 *
		 *	COMPUTER XWING LOGIC
		 *
		 */
		xCoordinate=('0' - computerPieces[1][gamePiece])*-1;
		yCoordinate=('0' - computerPieces[2][gamePiece])*-1;
		/***
		 *
		 *        Max Left
		 */
		bool canGoForwardLeft=true;
		int maxForwardLeft=yCoordinate;
		int maxLeft=xCoordinate;
		//cout<<endl<<"Starting Points: ("<<xCoordinate<<", "<<yCoordinate<<") ";
		
		int tempX=xCoordinate;
		for(int i=yCoordinate+1;i<=7;i++){ // THIS IS WHERE YOU ARE IN FIXING STUFF
			tempX++;
			//cout<<endl<<"("<<tempX<<","<<i<<")";
			if(((i>6)||(tempX>6)) && (canGoForwardLeft)){
				maxForwardLeft= i-1;
				maxLeft=tempX-1;
				canGoForwardLeft=false;
				//cout<<endl<<"Off Board"; // DEBUGGING
				//cout<<endl<<"X: "<<maxLeft<<", y: "<<maxForwardLeft; // DEBUGGING
			}else if(gameBoard[tempX][i]!='-'){
				if(canGoForwardLeft){
					canGoForwardLeft=false;
					if((gameBoard[tempX][i]=='x') || (gameBoard[tempX][i]=='t')){
						maxForwardLeft=i;
						maxLeft=tempX;
						//cout<<endl<<"Hit X or T";
						//cout<<endl<<"X: "<<tempX<<", y: "<<i;
					}else{
						maxForwardLeft= i - 1;
						maxLeft=tempX-1;
						//cout<<endl<<"Hit an indesctuctible";
						//cout<<endl<<"X: "<<maxLeft<<", y: "<<maxForwardLeft;
					}
				}
			}
		}
		if(maxForwardLeft != yCoordinate){
			//cout<<endl<<"Possible Vertical Movements: X: "<<xCoordinate<<" Y: "<<maxVertical;
			tempX = maxLeft;
			for(int i=maxForwardLeft;i>yCoordinate;i--){
				//cout<<endl<<"Coordinates in between: X: "<<xCoordinate<<" Y: "<<i;
				computerLegalMoves[0][numComputerMoves] = xCoordinate;
				computerLegalMoves[1][numComputerMoves] = yCoordinate;
				computerLegalMoves[2][numComputerMoves] = tempX;
				computerLegalMoves[3][numComputerMoves] = i;
				numComputerMoves++;
				tempX--;
			}
		}

		/***
		 *
		 *        Max Forward Right
		 */
		bool canGoForwardRight=true;
		int maxForwardRight=yCoordinate;
		int maxRight=xCoordinate;
		//cout<<endl<<"Starting Points: ("<<xCoordinate<<", "<<yCoordinate<<") "; //DEBUG
		
		tempX=xCoordinate;
		for(int i=yCoordinate+1;i<=7;i++){
			tempX--;
			//cout<<endl<<"("<<tempX<<","<<i<<")"; // DEBUG
			if(((i>6)||(tempX<0)) && (canGoForwardRight)){
				maxForwardRight= i-1;
				maxRight=tempX+1;
				canGoForwardRight=false;
				//cout<<endl<<"Off Board"; // DEBUG
				//cout<<endl<<"X: "<<maxRight<<", y: "<<maxForwardRight; //DEBUG
			}else if(gameBoard[tempX][i]!='-'){
				if(canGoForwardRight){
					canGoForwardRight=false;
					if((gameBoard[tempX][i]=='x') || (gameBoard[tempX][i]=='t')){
						maxForwardRight=i;
						maxRight=tempX;
						//cout<<endl<<"Hit X or T"; //Debug
						//cout<<endl<<"X: "<<tempX<<", y: "<<i; //Debug
					}else{
						maxForwardRight= i - 1;
						maxRight=tempX+1;
						//cout<<endl<<"Hit an indesctuctible"; //Debug
						//cout<<endl<<"X: "<<maxRight<<", y: "<<maxForwardRight; //Debug
					}
				}
			}
		}
		if(maxForwardRight != yCoordinate){
			//cout<<endl<<"Possible Vertical Movements: X: "<<xCoordinate<<" Y: "<<maxVertical;
			tempX = maxRight;
			for(int i=maxForwardRight;i>yCoordinate;i--){
				//cout<<endl<<"Coordinates in between: X: "<<xCoordinate<<" Y: "<<i;

				//cout<<endl<<"Move Entry:  ("<<xCoordinate<<", "<<yCoordinate<<") X: "<<tempX<<", y: "<<i; //Debug
				computerLegalMoves[0][numComputerMoves] = xCoordinate;
				computerLegalMoves[1][numComputerMoves] = yCoordinate;
				computerLegalMoves[2][numComputerMoves] = tempX;
				computerLegalMoves[3][numComputerMoves] = i;
				numComputerMoves++;
				tempX++;
			}
		}

		/***
		 *
		 *
		 *      Max Backward Right
		 *
		 */
		// Backward Y- Coordinate Tie Fighter Code
		bool canGoBackward=true;
		int maxBackwardRightY=yCoordinate;
		int maxBackwardRightX=xCoordinate;


			//cout<<"Backward checking";
		// Possible Forward Moves for Tie Fighter
		for(int i=yCoordinate-1;i>=0;i--){
			maxBackwardRightX--;
			//cout<<endl<<"( "<<maxBackwardRightX<<", "<<i<<" )";
			
			if((gameBoard[maxBackwardRightX][i]!='-')&&(maxBackwardRightX >= 0)){
				if(canGoBackward){
					canGoBackward=false;
					if((gameBoard[maxBackwardRightX][i]=='x') || (gameBoard[maxBackwardRightX][i]=='t') || (gameBoard[maxBackwardRightX][i]=='@')){
						maxBackwardRightY=i;
						computerLegalMoves[0][numComputerMoves] = xCoordinate;
						computerLegalMoves[1][numComputerMoves] = yCoordinate;
						computerLegalMoves[2][numComputerMoves] = maxBackwardRightX;
						computerLegalMoves[3][numComputerMoves] = i;
						numComputerMoves++;
					}
				}
			}
		}

		/***
		 *
		 *
		 *      Max Backward Left 
		 *
		 */
		// Backward Y- Coordinate Tie Fighter Code
		canGoBackward=true;
		int maxBackwardLeftY=yCoordinate;
		int maxBackwardLeftX=xCoordinate;


		// Possible Forward Moves for Tie Fighter
		for(int i=yCoordinate-1;i>=0;i--){
			maxBackwardLeftX++;
			
			if((gameBoard[maxBackwardLeftX][i]!='-')&&(maxBackwardLeftX <= 6)){
				if(canGoBackward){
					canGoBackward=false;
					if((gameBoard[maxBackwardLeftX][i]=='x') || (gameBoard[maxBackwardLeftX][i]=='t') || (gameBoard[maxBackwardLeftX][i]=='@')){
						maxBackwardLeftY=i;
						computerLegalMoves[0][numComputerMoves] = xCoordinate;
						computerLegalMoves[1][numComputerMoves] = yCoordinate;
						computerLegalMoves[2][numComputerMoves] = maxBackwardLeftX;
						computerLegalMoves[3][numComputerMoves] = i;
						numComputerMoves++;
					}
				}
			}
		}


	}
}


/**
 * Initializes Game Board and ComputerPieces/playerPieces arrays. This feels a bit redundant,
 * but keeping track of things from a seperate array should make coding later easier.
 * I have no idea why I didn't just use Classes for this.
 *
 * */
void initGame() {
	
//playerPieces [3][11];
//computerPieces [3][11];
//
	winner = "Game Not Over Yet";
	// In Retrospect I have no idea why I didn't make these classes.
	// Of course the fringe benefit is i'm not wasting resouces on class creation.
	// Although I am using a lot of functions which will eat up a little more space then writing all of 
	// this procedurally, but I'm afraid that would turn into a much larger headache If i wrote this program that way.
	//
	// Computer Tie Fighters
	computerPieces [0][0] = 'T';
	computerPieces [1][0] = '1'; // X
	computerPieces [2][0] = '0'; // Y
	computerPieces [3][0] = ' ';

	computerPieces [0][1] = 'T';
	computerPieces [1][1] = '2'; // X
	computerPieces [2][1] = '0'; // Y
	computerPieces [3][1] = ' ';

	computerPieces [0][2] = 'T';
	computerPieces [1][2] = '4'; // X
	computerPieces [2][2] = '0'; // Y
	computerPieces [3][2] = ' ';

	computerPieces [0][3] = 'T';
	computerPieces [1][3] = '5'; // X
	computerPieces [2][3] = '0'; // Y
	computerPieces [3][3] = ' ';

	// Computer Wall
	computerPieces [0][4] = '~';
	computerPieces [1][4] = '2'; // X
	computerPieces [2][4] = '1'; // Y
	computerPieces [3][4] = ' ';
	
	// Computer Death Star
	computerPieces [0][5] = '*';
	computerPieces [1][5] = '3'; // X
	computerPieces [2][5] = '1'; // Y
	computerPieces [3][5] = ' ';

	// Computer Wall
	computerPieces [0][6] = '~';
	computerPieces [1][6] = '4'; // X
	computerPieces [2][6] = '1'; // Y
	computerPieces [3][6] = ' ';

	// Computer X Wing
	computerPieces [0][7] = 'X';
	computerPieces [1][7] = '0'; // X
	computerPieces [2][7] = '2'; // Y
	computerPieces [3][7] = ' ';

	computerPieces [0][8] = 'X';
	computerPieces [1][8] = '1'; // X
	computerPieces [2][8] = '2'; // Y
	computerPieces [3][8] = ' ';

	computerPieces [0][9] = 'X';
	computerPieces [1][9] = '5'; // X
	computerPieces [2][9] = '2'; // Y
	computerPieces [3][9] = ' ';

	computerPieces [0][10] = 'X';
	computerPieces [1][10] = '6'; // X
	computerPieces [2][10] = '2'; // Y
	computerPieces [3][10] = ' ';

	// Player X-Wing
	playerPieces [0][0] = 'x';
	playerPieces [1][0] = '0'; // X
	playerPieces [2][0] = '4'; // Y
	playerPieces [3][0] = ' ';

	playerPieces [0][1] = 'x';
	playerPieces [1][1] = '1'; // X
	playerPieces [2][1] = '4'; // Y
	playerPieces [3][1] = ' ';

	playerPieces [0][2] = 'x';
	playerPieces [1][2] = '5'; // X
	playerPieces [2][2] = '4'; // Y
	playerPieces [3][2] = ' ';

	playerPieces [0][3] = 'x';
	playerPieces [1][3] = '6'; // X
	playerPieces [2][3] = '4'; // Y
	playerPieces [3][3] = ' ';

	// Player Wall
	playerPieces [0][4] = '+';
	playerPieces [1][4] = '2'; // X
	playerPieces [2][4] = '5'; // Y
	playerPieces [3][4] = ' ';

	// Player Death Star
	playerPieces [0][5] = '@';
	playerPieces [1][5] = '3'; // X
	playerPieces [2][5] = '5'; // Y
	playerPieces [3][5] = ' ';
	

	// Player Wall
	playerPieces [0][6] = '+';
	playerPieces [1][6] = '4'; // X
	playerPieces [2][6] = '5'; // Y
	playerPieces [3][6] = ' ';


	// Player Tie Fighters 
	playerPieces [0][7] = 't';
	playerPieces [1][7] = '1'; // X
	playerPieces [2][7] = '6'; // Y
	playerPieces [3][7] = ' ';

	playerPieces [0][8] = 't';
	playerPieces [1][8] = '2'; // X
	playerPieces [2][8] = '6'; // Y
	playerPieces [3][8] = ' ';

	playerPieces [0][9] = 't';
	playerPieces [1][9] = '4'; // X
	playerPieces [2][9] = '6'; // Y
	playerPieces [3][9] = ' ';

	playerPieces [0][10] = 't';
	playerPieces [1][10] = '5'; // X
	playerPieces [2][10] = '6'; // Y
	playerPieces [3][10] = ' ';
	

	//debugPiecesArrays();
	//cout <<endl<< "Actual Board";
}


/***
 * UpdateBoardState Clears the board then applies pieces arrays directly to the board.
 * I was planning on using a for loop on gameboard and just checking for equivalence on the player pieces and computer pieces.
 * In the end I came up with the following which i feel was more clever and won't waste as many computer cycles.
 * They say generally you don't want to come up with too clever of code 'kis' for debugging reasons, But I believe this class
 * is the specific time that optimization trumps simplicity.
 *
 */
void updateBoardState(){
	int xCoordinate, yCoordinate;
	// Clear Board
	for (int b = 0; b < 7; b++) {
		for (int a = 0; a < 7; a++) {
			gameBoard[a][b] = '-';
		}
	}
	for (int b = 0; b < 11; b++) {
		if(playerPieces[3][b]!='x'){ // if 3 = 'x' then the piece is dead
			xCoordinate=('0' - playerPieces[1][b])*-1;
			yCoordinate=('0' - playerPieces[2][b])*-1;
			gameBoard[xCoordinate][yCoordinate] = playerPieces[0][b]; // Piece
		}
	}
	
	for (int b = 0; b < 11; b++) {
		if(computerPieces[3][b]!='x'){ // if 3 = 'x' then the piece is dead
			xCoordinate=('0' - computerPieces[1][b])*-1;
			yCoordinate=('0' - computerPieces[2][b])*-1;
			gameBoard[xCoordinate][yCoordinate] = computerPieces[0][b]; // Piece
		}
	}

}

void debugPiecesArrays(){
	for(int r=0;r<2;r++){
			if(r==0){
				cout<<endl<<"Computer Pieces: ";
			}else{
				cout<<endl<<"Player Pieces: ";		
			}
	
		for(int i =0;i<11;i++){
			cout<<endl;
			for(int y=0;y<3;y++){
				if(r==0){
					cout<<computerPieces[y][i];
				}else{
					cout<<playerPieces[y][i];
				}
				if(y==0){
					cout<<": ";
				}else if(y<2){
					cout<<", ";
				}
			}
		}
	}

}

//void displayGameBoard(char gameBoard[][7]) {
void displayGameBoard() {
	
	updateBoardState(); // Places pieces on board.
	//debugPiecesArrays();
	int leftAxis = 7;
	cout << endl << "\n\t-- Board --"<<endl;
	for (int b = 0; b < 7; b++) {
		cout << endl;
		printf("%2d | ", leftAxis);
		for (int a = 0; a < 7; a++) {
			
			if((gameBoard[a][b] == 'X') || (gameBoard[a][b] == 'T') || (gameBoard[a][b] == '*')){
				textcolor(BRIGHT,RED,BLACK);
				printf("%-3c", gameBoard[a][b]);
			}else if((gameBoard[a][b] == 'x') || (gameBoard[a][b] == 't') || (gameBoard[a][b] == '@')){
				textcolor(BRIGHT,BLUE,BLACK);
				printf("%-3c", gameBoard[a][b]);
			}else if((gameBoard[a][b] == '~') || (gameBoard[a][b] == '+') ){
				textcolor(BRIGHT,YELLOW,BLACK);
				printf("%-3c", gameBoard[a][b]);
			}else{
				textcolor(BRIGHT,WHITE,BLACK);
				printf("%-3c", gameBoard[a][b]);
			}
			
			//cout<<"X: "<<a<<", Y: "<<b<<endl;
				textcolor(BRIGHT,WHITE,BLACK);
		}
		leftAxis--;
	}
	//printf("\n %9s", );
	//cout << endl << "      A  B  C  D  E  F  G";
	cout << endl << "   ";
	for (int b = 0; b < 21; b++) {
		cout << "-";
	}
	cout << endl << "     A  B  C  D  E  F  G";

	cout << endl;
}

void textcolor(int attr, int fg, int bg)
{ char command[13];
	  sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	    printf("%s", command);
}

//>>>>>>> b539753fc393124fd90590718dd3338ad72d516d
