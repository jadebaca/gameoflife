/**
* @file life.c
*
* @brief Functions for gl.c
*
* @details Includes memory allocation, read-in for file, middle behavior, and hedge, torus, and klein
*
* @author Jade Baca
*
* @date 2017-5-3
*
* @todo none
*
* @bug none that I know of
*
* @remark x and y are sprite width amd sprite height, respectively
*
*
*
 **/
#include "life.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/** Allocates memory for two matrices (a and b)
 * @param rows number of rows needed for matrix
 * @param cols number of columns needed for matrix
 * @return matrix created
 **/
unsigned char **init_matrix(int rows, int cols)
{
        int i;
        int j;
        unsigned char **matrix;
        /* allocate rows */
        matrix = calloc(rows, sizeof(unsigned char *));
        if(!matrix)
                return NULL;
        for(i = 0; i < rows; i++){
                /* allocate cols for each row */
                matrix[i] = calloc(cols, sizeof(unsigned char));
                if (!matrix[i]) {
                        for (j = 0; j < i; j++)
                        free(matrix[j]);
                        free(matrix);
                        return NULL;
                }
        }
        return matrix;
}
/** Reads info from the file and places them on the matrix
 * @param *file_name the name of the file
 * @param **matrix the matrix that we will place the sprites on
 * @param row the number of rows in the matrix
 * @param col the number of columns in the matrix
 * @param optx original x
 * @param opty original y
 * @param shape determines the edge behavior and will code according to that
 **/
void read_file(char *file_name, unsigned char **matrix, int row, int col, int optx, int opty, int shape)
{
        char buf[1024];
        int x;
        int y;
        FILE *file = fopen(file_name,"r");
        if(file == NULL) { /* case is there is no file/wrong file */
                printf("error: Invalid file for read in/ file not used\n");
        }

                while(fgets(buf, 1024, file) != NULL){
                        if (sscanf(buf, "%d %d\n", &x, &y) == 2){
                                /* grabs coordinate and assigns it to x, y */
                                x = x + optx;
                                y = y + opty;

                                if(shape == H){
                                        /* Hedge case for coordinate */
                                        if (x >= 0 && x < row && y >= 0 && y < col){
                                                matrix[x][y] = 1;
                                        }
                                }else if (shape == T){
                                        /* torus case for coordinate */
                                        if ((x) >= row){
                                                x = x % row;
                                        }else if ((x) < 0){
                                                x = (x % row)+ row;
                                        }
                                        if ((y) >= col){
                                                y =  (y % (col));
                                        } else if((y) < 0){
                                                y = (y % col)+ col;
                                        }
                                        matrix[x][y] = 1;
                                }else if (shape == K){
                                        /* klein case for coordinate */
                                        if ((y) >= col){
                                                y = (y % (col));
                                        } else if((y) < 0){
                                                y =  ((y % col)+ col);
                                        }
                                        if ((x) >= row){
                                                x = x % row;
                                                y = col -1 -y;
                                        }else if ((x) < 0){
                                                x = (x % row)+ row;
                                                y = col -1 -y;
                                        }

                                        matrix[x][y] = 1;
                                }
                        }
                }
        }
}

/** Prints the matrix
 * @param **matrix the matrix with the sprites
 * @param row the number of rows in the matrix
 * @param col the number of columns in the matrix
 **/
void print_matrix(unsigned char **matrix, int row, int col)
{
        int i;
        int j;
        /*goes through each row and col and prints 0 or 1 */
        for(i = 0; i < row; i++){
                for(j = 0; j < col;j++){
                        printf(" %d ", matrix[i][j]);
                }
                printf("\n");
        }
}
/**Implements edge behavior
 * @param **matrix the matrix with the sprites
 * @param row the number of rows in the matrix
 * @param col the number of columns in the matrix
 * @param x coordinates of the sprites
 * @param y coordinates of the sprites
 * @param shape determines the edge behavior and will code according to that
 **/
int internal_addition(unsigned char **matrix, int row, int col,int x, int y, int shape)
{
        int i;
        int j;
        int count;

        count = -matrix[x][y];
        for(i = -1;i <= 1;i++){
                for(j = -1;j <= 1;j++){
                        switch(shape){
                                /* if shape is called it will call the function and count */
                                case 1:
                                        count = count +  torus_call(matrix, row, col, x, y, i, j);
                                        break;
                                case 2:
                                        count = count + klein_call(matrix, row, col, x, y, i, j);
                                        break;
                                case 3:
                                        count= count + hedge_call(matrix, row, col, x, y, i, j);
                                        break;
                        }
                }
        }
        return count;
}

/**Implements hedge behavior
 * @param **matrix the matrix with the sprites
 * @param row the number of rows in the matrix
 * @param col the number of columns in the matrix
 * @param x coordinates of the sprites
 * @param y coordinates of the sprites
 * @param i used to count through rows
 * @param j used to count through columns
 * @return returns the edges of the matrix
 **/
int hedge_call(unsigned char **matrix, int row, int col, int x, int y, int i, int j)
{
        /* turns all of the edges to 0 */
        if(((x + i) >= row) || (( x+ i) < 0) || (( y + j) >= col) || (( y + j) < 0)){
                return 0;
        }
        return matrix[x + i][y + j];
}

/**Implements torus behavior
 * @param **matrix the matrix with the sprites
 * @param row the number of rows in the matrix
 * @param col the number of columns in the matrix
 * @param x coordinates of the sprites
 * @param y coordinates of the sprites
 * @param i used to count through rows
 * @param j used to count through columns
 * @return returns the edges of the matrix
 **/
int torus_call(unsigned char **matrix,int row, int col,int x, int y, int i, int j)
{
        int xnew = x + i;
        int ynew = y + j;
        /* coordinate 'wraps around' to other side */
        if((x + i)> row-1){
                xnew = (x + i) % row;
        }
        if((x + i)< 0){
                xnew = row +(x + i);
        }
        if((y + j)> col - 1){
                ynew = (y + j) % col;
        }
         if((y + j) < 0){
                ynew = col + y + j;

        }
        return matrix[xnew][ynew];
}

/**Implements klein bottle behavior
 * @param **matrix the matrix with the sprites
 * @param row the number of rows in the matrix
 * @param col the number of columns in the matrix
 * @param x coordinates of the sprites
 * @param y coordinates of the sprites
 * @param i used to count through rows
 * @param j used to count through columns
 * @return returns the edges of the matrix
 **/
int klein_call(unsigned char **matrix, int row, int col,int x, int y,int i, int j)
{
        int xnew = x + i;
        int ynew = y + j;
        /* i and j are created to reverse coordinate */
        if((y + j) > col - 1){
                ynew = (y + j) % col;
        }
         if((y + j) < 0){
                ynew = col + y + j;
        }
        if((x + i) > row - 1){
                xnew = (x + i) % row;
                ynew = col - 1 - ynew;
        }
        if((x + i) < 0){
                xnew = row + (x + i);
                ynew = col - 1 - ynew;
        }

        return matrix[xnew][ynew];
}

/**the rules for game of life are implemented here
 * @param **matrix_a matrix before rules applied
 * @param **matrix_b matrix after rules applied
 * @param row the number of rows in the matrix
 * @param col the number of columns in the matrix
 * @param shape determines the edge behavior and will code according to that
 **/
void internal_case(unsigned char **matrix_a, unsigned char **matrix_b, int row, int col, int shape)
{
        int i;
        int j;
        int count;

        for (i = 0; i < row; i++){
                for(j = 0; j < col; j++){

                        count = internal_addition(matrix_a, row, col, i, j, shape); /* calls internal_addition for edge behavior */
                        if(matrix_a[i][j] == 0 && count == 3)
                                matrix_b[i][j] = 1;
                        else if(matrix_a[i][j] == 1 && (count == 2 || count == 3))
                                matrix_b[i][j] = 1;
                        else
                                matrix_b[i][j] = 0;
                }
        }
}
