#include <stdio.h>
#include <stdlib.h>
#include<time.h>
//#include <conio.h>

int main(){
    int grid_size = 20;
    char grid[grid_size][grid_size];
    int head_x = grid_size / 2, head_y = grid_size / 2, food_x, food_y;
    int game_over = 0;


    // random food generator ___________________________________________________________________________________________
    srand(time(NULL));
    do{
        food_x = rand() % grid_size;
        food_y = rand() % grid_size ;
    }while (grid[food_x][food_y] != grid[head_x][head_y]);


    // basic control input _______________________________________________________________________________________________
    

    while(!game_over){
        // clear system________________________________________
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        for(int i = 0; i < grid_size; i++){
            for(int j = 0; j < grid_size; j++){
                grid[i][j] = ' ';
            }
        }
    
        grid[food_x][food_y] = '*';
        grid[head_x][head_y] = 'o';

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

        char input = getchar();
        while ((getchar()) != '\n');

        switch (input)
        {
        case 'w':
            head_x--;
            break;
        case 's':
            head_x++;
            break;
        case 'a':
            head_y--;
            break;
        case 'd':
            head_y++;
            break;
        case 'q':
            printf("Game Quitted\ndid you not like my game?\n:(");
            exit(0);
        default:
            break;
        }

        // "eating" food ___________________________________________________________
        if(head_x == food_x && head_y == food_y){
            do{
                srand(time(NULL));
                food_x = rand() % grid_size;
                food_y = rand() % grid_size;
            } while (grid[food_x][food_y] != grid[head_x][head_y] || grid[food_x][food_y] != ' ');

            grid[food_x][food_y] = '*';
        }

        if(head_x < 0 || head_y < 0 || head_x >= grid_size || head_y >= grid_size){
            game_over = 1;
        }
    }

    
   
    if(game_over == 1){
        printf("G A M E   O V E R !\n  y o u   l o s e\n   Boooooo, noob!");
    }
    
    return 0;
}