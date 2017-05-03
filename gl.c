/**
* @file gl.c
*
* @brief Game of life implemented into SDL
*
* @details Includes flags for compilation, function calls, and renders into SDL
*
* @author Jade Baca
*
* @date 2017-5-3
*
* @todo none
*
* @bug none that I know of
*
* @remark matrix_a and matrix_b are swapped back and forth on SDL
* @remark my favorite run through has been this: ./life -P ../gol/conway/windmill_106.lif -p 300,300.
*  The flags allow you to choose specific details of the overall function.
 **/
#include <stdlib.h>
#include<stdio.h>
#include "SDL2/SDL.h"
#include "sdl.h"
#include "life.h"
#include <string.h>
#include <unistd.h> /*this is for getopt */

int main(int argc, char *argv[])
{
        int width = 800;
        int height = 600;
        int sprite_size = 16; /* either 2, 4, 8, or 16 */
        int row = width / sprite_size;
        int col = height / sprite_size;
        char cd;
        int shape = T; /* default structure is torus */
        int gen_count = 0;
        int x = -1;
        int y = -1;
        int px = -1;
        int py = -1;
        int qx = -1;
        int qy = -1;
        int verflag = 0;
        /* colors are RGB model valid values [0, 255]. Default is a purple color */
        unsigned char red = 140;
	unsigned char green = 145;
	unsigned char blue = 250;
        struct sdl_info_t sdl_info; /* this is needed to graphically display the game */

        unsigned char **matrix_a;
        unsigned char **matrix_b;
        char *filename = ("../gol/conway/glider_106.lif"); /*default file is glider */

        char *filename2 = (NULL); /* you can add 2 more shapes (thru flags only) */
        char *filename3 = (NULL);

        while((cd = getopt(argc, argv, "w:h:r:g:b:s:f:fver5:P:p:Q:q:o:e:H")) != -1){
                switch(cd) {
                        case 'w':
                                width = atoi(optarg);
                                break;
                        case 'h':
                                height = atoi(optarg);
                                break;
                        case 'r':
                                red = atoi(optarg);
                                if (red > 250){
                                        red = 140;
                                        printf("Invalid rgb integer. Default value for red used\n");
                                        break;
                                }
                                break;
                        case 'g':
                                green = atoi(optarg);
                                if (green > 250){
                                        green = 145;
                                        printf("Invalid rgb integer. Default value for green used\n");
                                        break;
                                }
                                break;
                        case 'b':
                                blue = atoi(optarg);
                                if (blue > 250){
                                        blue = 250;
                                        printf("Invalid rgb integer. Default value for blue used\n");
                                        break;
                                }
                                break;
                        case 's':
                                sprite_size = atoi(optarg);
                                if(sprite_size != 2 || sprite_size != 4 || sprite_size != 8 || sprite_size != 16){
                                        sprite_size = 16;
                                        printf("Invalid sprite size. Must be 2, 4, 8, or 16. Default size used\n");
                                        break;
                                }
                                break;
                        case 'f':
                                filename = strdup(optarg);
                                break;
                        case 'fver5':
                                verflag = 1; /* sets 1.05 flag */
                                filename = strdup(optarg);
                                break;
                        case 'P':
                                filename2 = strdup(optarg);
                                break;
                        case 'p':
                                sscanf(optarg,"%d,%d",&px, &py);
                                break;
                        case 'Q':
                                filename3 = strdup(optarg);
                                break;
                        case 'q':
                                sscanf(optarg,"%d, %d", &qx, &qy);
                                break;
                        case 'e':{
                                if (strcmp(optarg, ("torus")) == 0)
                                        shape = T;
                                else if (strcmp(optarg,("klein")) == 0)
                                        shape = K;
                                else if (strcmp(optarg,("hedge")) == 0)
                                        shape = H;
                                else {
                                        shape = H;
                                        printf("Invalid edge pattern. Default Torus used \n");
                                }
                                break;
                        }
                        case 'o':{
                                sscanf(optarg,"%d,%d",&x, &y);
                                break;
                        }
                        case 'H':{
                                printf("Flags that can be used: -w -h -r -g -b -s -f -fver5 -e -o -H\n\n");
                                printf("-w \n\t width of screen, integer\n");
                                printf("-h \n\t height of screen, integer\n");
                                printf("-r, -g, -b \n\t rgb value of color of sprite, integer. Each flag is red, green, blue\n");
                                printf("-s \n\t sprite size, integer. Can only be 2, 4, 8, or 16\n");
                                printf("-f \n\t filename in file format 1.06. Must use correct relative pathname\n");
                                printf("-fver5 \n\t filename in the file format 1.05. Must use correct relative pathname\n");
                                printf("-o \n\t determines the starting coordinates of shape f, x,y integer\n");
                                printf("-P \n\t filename in file format 1.06. Must use correct relative pathname\n");
                                printf("-p \n\t determines the starting coordinates of shape P, x,y integer\n");
                                printf("-Q \n\t filename in file format 1.06. Must use correct relative pathname\n");
                                printf("-q \n\t determines the starting coordinates of shape Q, x,y integer\n");
                                printf("-e \n\t Determines edge pattern, character string. Options are hedge, torus, \n\t klein\n");
                                printf("-H \n\t Prints this help menu\n");
                                break;
                        }
                        default:
                                printf("Error: %c is not a valid flag, ignored\n", optopt);
                                printf("Use -H for help\n");
                                break;

                }
        }
        row = width / sprite_size;
        col = height  / sprite_size;

        if (x == -1 || y == -1){
                x = row / 2;
                y = col / 2;
                }
        row = width / sprite_size;
        col = height  / sprite_size;

        if (px == -1 || py == -1){
                px = row / 2;
                py = col / 2;
                }
        row = width / sprite_size;
        col = height  / sprite_size;

        if (qx == -1 || qy == -1){
                qx = row / 2;
                qy = col / 2;
                }

        // printf ("row: %d, col: %d", row, col);
        matrix_a = init_matrix(row, col);
        matrix_b = init_matrix(row, col);
        if (verflag = 1){
                read_oldfile(filename, matrix_a, row, col, x, y, shape);
        } else {
                read_file(filename, matrix_a, row, col, x, y, shape);
        }
        read_file(filename2, matrix_a, row, col, px, py, shape);
        read_file(filename3, matrix_a, row, col, qx, qy, shape);
        /* set up SDL -- works with SDL2 */
        init_sdl_info(&sdl_info, width, height, sprite_size, red, green, blue);

        while (1)
        {


                /* change the  modulus value to slow the rendering */
                if (SDL_GetTicks() % 30 == 0) {
                        if(gen_count % 2 == 0){
                                sdl_render_life(&sdl_info, matrix_a);
                                internal_case(matrix_a, matrix_b, row, col, shape);
                        } else {
                                sdl_render_life(&sdl_info, matrix_b);
                                internal_case(matrix_b, matrix_a, row, col, shape);
                        }
                        gen_count++;
                }

                /* Poll for events, and handle the ones we care about.
                * You can click the X button to close the window
                */
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {

                        switch (event.type)
                        {
                                case SDL_KEYDOWN:
                                break;
                                case SDL_KEYUP:

                                /* If escape is pressed, return (and thus, quit) */
                                if (event.key.keysym.sym == SDLK_ESCAPE){
                                        for (col = 0; col < row; col++){
                                                free(matrix_b[col]);
                                                free(matrix_b);
                                        }
                                        free(matrix_a[row]);
                                        free(matrix_a);

                                        return 0;
                                }
                                break;
                                case SDL_QUIT:
                                for (col = 0; col < row; col++){
                                        free(matrix_b[col]);
                                        free(matrix_b);
                                        }
                                free(matrix_a[row]);
                                free(matrix_a);
                                break;
                                return 0;
                        }
                }

        }
        return 0;
}
