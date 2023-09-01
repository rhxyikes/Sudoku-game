#include <bits/stdc++.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void printBoard(vector<vector<int>>& board) {
    for(int i=0;i<9;i++){
        if(i%3==0)cout<<" ----------------------------"<<endl;
        for(int j=0;j<9;j++){
            if(j==0) cout<<" | ";
            cout<<board[i][j]<<" ";
            if (j%3==2) cout<<" | ";
        		}
        cout<<endl;
        if(i==8) cout<<" ----------------------------"<<endl;
    		}
	}

bool isSafe(vector<vector<int>>& board, int row, int col, int n) {
    	for(int j=0;j<9;j++) if(n==board[row][j]) return false;
	for(int i=0;i<9;i++) if(n==board[i][col]) return false;
	int left=col-col%3;
	int right=left+2;
	int top=row-row%3;
	int bottom=top+2;
	for(int i=top;i<=bottom;i++){
		for(int j=left;j<=right;j++){
			if(board[i][j]==n) return false;
			}
		}
	return true;
	}

bool findEmptyCell(vector<vector<int>>& board, int* row, int* col) {
    for(int r=0;r<9;r++){
		for(int c=0;c<9;c++){
			if(board[r][c]==0){
				*row=r;
				*col=c;
				return true;
				}
			}
		}
	return false;
	}
bool isSolved(vector<vector<int>>& board){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(board[i][j]==0) return false;
			}
		}
	return true;
	}	
bool solveSudoku(vector<vector<int>>& board, vector<vector<int>>& solvedBoard){
    int row,col;
    srand(time(0));
    if (!findEmptyCell(board,&row,&col)) return true;
    int randomize=(rand()%5)+2;
    while(randomize==1) randomize=(rand()%5)+2;
    for(int num=randomize;num<=9;num+=randomize%(num+1)){
	if (isSafe(board,row,col,num)){
            board[row][col]=num;
            solvedBoard[row][col]=num;
            if (solveSudoku(board,solvedBoard)) return true;
            board[row][col]=0;
            solvedBoard[row][col]=0;
            		}
    		}	
    for (int num=1;num<=9;num++){
        if (isSafe(board,row,col,num)){
            board[row][col]=num;
            solvedBoard[row][col]=num;
            if (solveSudoku(board,solvedBoard)) return true;
            board[row][col]=0;
            solvedBoard[row][col]=0;
            		}
    		}
    return false;
	}

void generateSudoku(vector<vector<int>>& board,vector<vector<int>>& solvedBoard,int level) {
    srand(time(0));
    solveSudoku(board,solvedBoard);
    int cellsToRemove = 0;
    if(level==1) cellsToRemove=30;
    if(level==2) cellsToRemove=35;
    if(level==3) cellsToRemove=50;
   while(cellsToRemove!=0){
		int row=rand()%9;
		int col=rand()%9;
		if(board[row][col]!=0){
			board[row][col]=0;
			cellsToRemove-=1;
			}
		}
	}

void play(vector<vector<int>>& board,vector<vector<int>>&solvedBoard) {
    int row,col,num;
    while(true){
    	if (isSolved(board)) break;
    	cout<<endl<<endl<<endl;
        printBoard(board);
      	cout<<endl<<endl<<endl<<"   ENTER ROW,COLUMN AND NUMBER AS -1 TO QUIT AND SEE THE SOLVED SUDOKU :)"<<endl<<endl;
		cout<<"   ENTER ROW (1-9): "; cin>>row;
		cout<<"   ENTER COLUMN (1-9): "; cin>>col;
		cout<<"   ENTER NUMBER (1-9): ";cin>>num;

        if(row==-1 || col==-1 || num==-1){
        		cout<<endl<<endl<<"   THE SOLVED SUDOKU IS: "<<endl<<endl<<endl;
			printBoard(solvedBoard);
			cout<<endl<<endl<<"   GAME OVER, BETTER LUCK NEXT TIME :)"<<endl<<endl<<endl;
			return;
			}
        row = row-1;
        col = col-1;
        if(num!=solvedBoard[row][col]){
			cout<<endl<<endl<<endl<<"   WRONG ENTRY, TRY AGAIN :)";
			continue;
			}
	cout<<endl<<endl<<endl<<"   GOOD GOING! YOU CAN DO IT :)";
	board[row][col]=num;
	}
        cout<<endl<<endl<<endl<<"   YOU HAVE SOLVED THE PUZZLE!!"<<endl<<endl<<endl;
	printBoard(board);
	cout<<endl<<endl<<endl<<"   CONGRATULATIONS! WELL PLAYED :)"<<endl<<endl<<endl;
	return;
	}	

int main() {
    	vector<vector<int>> board(9,vector<int>(9,0));
	vector<vector<int>> solvedBoard(9,vector<int>(9,0));
	cout<<"\t\t\t\t\t<=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=>\n"<<endl;
	cout<<"\t\t\t\t\t|                              SUDOKU GAME                              |\n"<<endl;
	cout<<"\t\t\t\t\t|            Fill in the missing numbers (0) to win the game!           |\n"<<endl;
	cout<<"\t\t\t\t\t<=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=>\n"<<endl;

    while(true){
        int level;
	cout<<"   (1)EASY\n";
	cout<<"   (2)INTERMEDIATE\n";
	cout<<"   (3)HARD\n\n";
	cout<<"   CHOOSE DIFFICULTY LEVEL: ";cin>>level;
	generateSudoku(board,solvedBoard,level);
	cout<<endl<<endl<<endl;
	printBoard(board);
	cout<<endl<<endl<<endl;
	cout<<"   (1) SOLVE THE SUDOKU\n";
	cout<<"   (2) UNABLE TO SOLVE,GET SOLVED SUDOKU :(\n";
	cout<<"   (3) BORED! WANT TO EXIT!\n\n";
	cout<<"   ENTER YOUR CHOICE: ";
	int choice;cin>>choice;
        if(choice==1){
            play(board,solvedBoard);
            break;
            }
        else if(choice==2) {
        	cout<<endl<<endl<<"   THE SOLVED SUDOKU IS: "<<endl<<endl<<endl;
				for(int i=0;i<9;i++){
					if(i%3==0) cout<<" ----------------------------"<<endl;
					for(int j=0;j<9;j++){
						if(j==0)cout<<" | ";
						cout<<solvedBoard[i][j]<<" ";
						if(j%3==2) cout<<" | ";
						}
					cout<<endl;
					if(i==8) cout<<" ----------------------------"<<endl;
					}
				cout<<endl<<endl<<"   GAME OVER, BETTER LUCK NEXT TIME :)"<<endl<<endl<<endl;
			break;
			}
		else if(choice==3){
			string ex;
			cout<<"   ARE YOU SURE YOU WANT TO EXIT? (yes/no)"<<endl; cout<<"   ";cin>>ex;
			if(ex=="yes") exit(0);
			else{
				cout<<endl<<endl<<endl;
				cout<<"\t\t\t\t\t<=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=>\n"<<endl;
				cout<<"\t\t\t\t\t|                              SUDOKU GAME                              |\n"<<endl;
				cout<<"\t\t\t\t\t|            Fill in the missing numbers (0) to win the game!           |\n"<<endl;
				cout<<"\t\t\t\t\t<=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=>\n"<<endl;
				}
			}
		else{
			cout<<endl<<endl<<endl<<"   INVALID CHOICE\n"<<endl;
			break;
			}
		}
    	return 0;
	}
