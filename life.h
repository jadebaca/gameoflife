/**
* @file life.h
*
* @brief Declaration of functions
*
* @author Jade Baca
*
* @date 2016-12-6
*
 **/
#ifndef LIFE_H_
#define LIFE_H_
enum mode {T = 1,K,H};
unsigned char **init_matrix(int rows, int cols);
void read_file(char *file_name, unsigned char **matrix,int row, int col, int optx, int opty, int shape);
void read_oldfile(char *file_name, unsigned char **matrix, int row, int col, int optx, int opty, int shape);
void print_matrix(unsigned char **matrix,int row, int col);
int hedge_call(unsigned char **matrix,int row, int col,int x, int y,int i, int j);
int torus_call(unsigned char **matrix,int row, int col,int x, int y,int i, int j);
int klein_call(unsigned char **matrix,int row, int col,int x, int y,int i, int j);
int internal_addition(unsigned char **matrix, int row, int col, int x, int y, int shape);
void internal_case(unsigned char **matrix_a, unsigned char **matrix_b,int row, int col, int shape);
#endif
