#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#include "continuity.h"
//#include <conio.h>

// constants _______________________________________________________________________
#define up 1
#define down 2
#define left 3
#define right 4

int main(){
    int grid_size = 20, max_len = grid_size * grid_size, length = 1;
    char grid[grid_size][grid_size];
    int  food_x, food_y;
    int game_over = 0, grow = 0;
    int direction = up;

    typedef struct 
    {
        int x;
        int y;
    }axes;

    printf("press any key to start");
    fflush(stdout);
    enable_continuous_mode();

    axes body[max_len];
    body[0].x = grid_size / 2;
    body[0].y = grid_size / 2;


    // random food generator ___________________________________________________________________________________________
    srand(time(NULL));
    do{
        food_x = rand() % grid_size;
        food_y = rand() % grid_size ;
    }while ((food_x == body[0].x && food_y == body[0].y));


    // basic control input _______________________________________________________________________________________________
     while (!get_key_nonblocking()) {
        game_sleep(50);
    }

    while(!game_over){
       
        int key = get_key_nonblocking();
        if (key) {
            switch (key) {
                case 'w':
                case 'W':
                    if (direction != down) direction = up;
                    break;
                case 's':
                case 'S':
                    if (direction != up) direction = down;
                    break;
                case 'a':
                case 'A':
                    if (direction != right) direction = left;
                    break;
                case 'd':
                case 'D':
                    if (direction != left) direction = right;
                    break;
                case 'q':
                case 'Q':
                    printf("Game Quitted\ndid you not like my game?\n:(");
                    game_over = 1;
                    break;
            }
        }

        axes pre_len = body[length-1];
        for(int i = length-1; i > 0; i--) {
            body[i] = body[i-1];
        }

        switch (direction)
        {
        case up:
            body[0].x--;
            break;
        case down:
            body[0].x++;
            break;
        case left:
            body[0].y--;
            break;
        case right:
            body[0].y++;
            break;
        }

        // "eating" food ___________________________________________________________
        if(body[0].x == food_x && body[0].y == food_y){
            grow = 1;
            int valid;
            do{
                valid = 1;
                srand(time(NULL));
                food_x = rand() % grid_size;
                food_y = rand() % grid_size;

                for(int i = 0; i < length; i++){
                    if((food_x == body[i].x && food_y == body[i].y) || grid[food_x][food_y] != ' '){
                        valid = 0;
                    }
                }
            } while (!valid);

            grid[food_x][food_y] = '*';
        }

        if(grow){
            if(length < max_len){
                body[length] = pre_len;
                length++;
            }
            grow = 0;
        }
        // collison check _______________________________________________________________________
        if(body[0].x < 0 || body[0].y < 0 || body[0].x >= grid_size || body[0].y >= grid_size){
            game_over = 1;
        }
        for (int i = 1; i < length; i++) {
            if (body[0].x == body[i].x && body[0].y == body[i].y) {
                game_over = 1;
            }
        }

        clear_screen();

        // cisuals_______________________________________
        fflush(stdout);
        for(int i = 0; i < grid_size; i++){
            for(int j = 0; j < grid_size; j++){
                grid[i][j] = ' ';
            }
        }
    
        grid[food_x][food_y] = '*';
        for(int i = 0; i < length; i++){
            grid[body[i].x][body[i].y] = (i==0) ? 'O' : 'o';
        }

        for(int i = 0; i < grid_size; i++){
            printf("_");
        }
        printf("\n");

        for(int i = 0; i < grid_size; i++){
            printf("|");
            for(int j = 0; j < grid_size; j++){
                printf("%c", grid[i][j]);
            }
            printf("|");
            printf("\n");
        }

        for(int i = 0; i < grid_size; i++){
            printf("_");
        }
        printf("\n");

        game_sleep(200);
    }

    disable_continuous_mode();

    if(game_over == 1){
        printf("\nG A M E   O V E R !\n  y o u   l o s e\n   Boooooo, noob!");
    }
    
    return 0;
}