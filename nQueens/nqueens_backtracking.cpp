/*
* N queens problem using backtracking 
* @authored: Fernando A. Lovera
* @date: Tue 31 March 2015
* @email: flovera1@gmail.com
*/
#define N 7 // here N is the size of the dashboard

#include <stdio.h>
/* 
* @param board: board is the board where the queens live
* @return void: This is just an utility function to print 
*               the solution 
*/
void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf(" %d ", board[i][j]);
        }
        printf("\n");
    }
}
/**
* @param board: this represents the queens'board 
* @param row: which represents the row in where you want to put the queen
* @param col: which means column and it represents the column where you want to put the queen,
              it also represents the number of queens already placed
* @description:
*   A utility function to check if a queen can be placed on board[row][col] position: [row][col]
*   Note that this function is called when "col" queens are already placed in columns from 0 to col -1.
*   So we need to check only left side for attacking queens 
* @return bool: 
*  true if you can put the queen in the position, false otherwise
*/
bool isSafe(int board[N][N], int row, int col){
    int i, j;
    /* Check this row on left side */
    for (i = 0; i < col; i++){
        if (board[row][i]){
            return false;
        }
    }
    /* Check upper diagonal on left side */
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--){
        if (board[i][j])
            return false;
    }
    /* Check lower diagonal on left side */
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
    {
        if (board[i][j])
            return false;
    }
    return true;
}
/*
* @param board: the queens'board
* @param col: the number of queens 
* @return boolean:
*    true in case that all queens are placed false otherwise
* @description: A function to solve N Queen problem */
bool util(int board[N][N], int col){
    // base case: If all queens are placed then return true 
    if (col >= N){
        return true;
    }
    /** Consider this column (col) and try placing this queen in all rows
     *  one by one 
     */
    for (int i = 0; i < N; i++){
        // Check if queen can be placed on board[i][col] 
        if (isSafe(board, i, col)){
            // Place this queen in board[i][col] 
            board[i][col] = 1;
            // recur to place rest of the queens
            if (util(board, col + 1) == true){
                return true;
            }
            /* If placing queen in board[i][col] doesn't lead to a solution
            *   then remove queen from board[i][col] 
            */
            board[i][col] = 0; //IMPORTANT! Backtracking
        }
    }
     /* If queen can not be place in any row in this colum col
      *  then return false 
      */
    return false;
}
/**
* @param none
* @return true if the board has a solution.
          false otherwise.
* @description:  
* This function solves the N Queen problem using Backtracking.  It mainly uses
* util() to solve the problem. It returns false if queens cannot be placed,
* otherwise return true and prints placement of queens in the form of 1s. Please
* note that there may be more than one solutions, this function prints one of the
* feasible solutions.*/
bool solve(){
    int i, j;
    int board[N][N];
    for (i = 0; i < N; i++){
      for (j = 0; j < N; j++){
         board[i][j] = 0;
      }
   }
    if (util(board, 0) == false){
      printf("Solution does not exist");
      return false;
    }
    printSolution(board);
    return true;
}
 
// driver program to test above function
int main()
{
    solve();
    return 0;
}
