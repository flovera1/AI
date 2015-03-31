/*
* N queens problem using backtracking
* @authored: Fernando A. Lovera
* @date: Tue 31 March 2015
* @email: flovera1@gmail.com
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

char board[10][10];
int size;
/*
* @return: void(just print the matrix)
* @param:  no parameters needed  
*/
void printmatrix(){
	int i,j;
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			printf("%c\t", board[i][j]);
		}
		printf("\n");
	}
}
/*
* @returns: returns the column of a particular row in which
*           there is a queen Q
* @param:   row which represents a row in the board.
*/
int getColumn(int row){
	int i;
	for(i = 0; i < size; i++){
		if(board[row][i] == 'Q'){
			return i;
			break;
		}
	}
	return -1;
}
/*
* @returns: Basically it tells if you can move to the 
*           [row][column] position.
* @param:   position(row and column) 
*/
int feasible(int row, int column){
	int i, tcol = 0;
	for(int i = 0; i < size; i++){
		tcol  = getColumn(i);
		if(column == tcol || abs(row - i) == abs(column - tcol)){
			return 0; // returns 0 when is not feasible
		}
	}
	return 1;
}
/*
* nqueen procedure
* @return: void(check if a particular row has a queen with the 
*           feasible method. Put all the queens first and then
*           the '.' iterative recursive).
* @param: row the particular row.
*/
void nqueen(){
	int i = 0;
	int j = 0;
	if(i < size){
		for(i = 0; i < size; i++){
			for(j = 0; j < size; j++){
				if(feasible(j, i) == 1){
					board[i][j] = 'Q';//insert all the Q in one row 
				}
				else{
					board[i][j] = '.';
				}
			}
		}
	}
	//else{
		printf("\n one solution is: \n");
		printmatrix();
	//}
}
int main() {
   int i, j;
   printf("\nEnter the number of queens:- ");
   scanf("%d", &size);
   for (i = 0; i < size; i++){
      for (j = 0; j < size; j++){
         board[i][j] = '.';
      }
   }
   nqueen();
   return (0);
}