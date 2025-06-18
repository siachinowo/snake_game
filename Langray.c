#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <conio.h>
       

//constants__________________________
#define SCORE_PER_FOOD  10
#define SCORE_PER_LEVEL 50



int main()
{
    int grid_size = 20, max_len = 200, length = 1;
    char grid[grid_size][grid_size];
    int  food_x, food_y;
    int game_over = 0, grow = 0;
    int score = 0, high_score = 0;
    int level=1;
    int padding = 10;

    typedef struct 
    {
        int x;
        int y;
    }axes;

    axes body[max_len];
    body[0].x = grid_size / 2;
    body[0].y = grid_size / 2;


    // random food generator ___________________________________________________________________________________________
    srand(time(NULL));
    do{
        food_x = rand() % grid_size;
        food_y = rand() % grid_size;
    }while ((food_x == body[0].x && food_y == body[0].y));


    // basic control input _______________________________________________________________________________________________
    while(!game_over){
        // clear system______________________________________________
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        //"processing" stage_________________________________________
        for(int i = 0; i < grid_size; i++){
            for(int j = 0; j < grid_size; j++){
                grid[i][j] = ' ';
            }
        }
    
        grid[food_x][food_y] = '*';
        for(int i = 0; i < length; i++){
            grid[body[i].x][body[i].y] = (i==0) ? 'O' : 'o';
        }

        //printing stage _____________________________________________
        printf("\n");
        printf("CONTROLS:    W                      SCORE: %d\n", score);
        printf("         A   S   D                  LEVEL: %d\n", level);
        printf("\nPress Q to quit\n");

        for(int i = 0; i < padding; i++){printf(" ");}
        for(int i = 0; i <= grid_size; i++){
            printf("_");
        }
        printf("\n");

        for(int i = 0; i < grid_size; i++){
            for(int i = 0; i < padding; i++){printf(" ");}
            printf("|");
            for(int j = 0; j < grid_size; j++){
                printf("%c", grid[i][j]);
            }
            printf("|");
            printf("\n");
        }

        for(int i = 0; i < padding; i++){printf(" ");}
        for(int i = 0; i <= grid_size; i++){
            printf("_");
        }
        printf("\n\n");
        printf("press 'enter' after every input, as game is made by langry <3\n");

        //taking input ________________________________________
        char input = getchar();
        while ((getchar()) != '\n');

        axes pre_len = body[length-1];
        for(int i = length-1; i > 0; i--) {
            body[i] = body[i-1];
        }

        switch (input)
        {
        case 'w':
        case 'W':
            body[0].x--;
            break;
        case 's':
        case 'S':
            body[0].x++;
            break;
        case 'a':
        case 'A':
            body[0].y--;
            break;
        case 'd':
        case 'D':
            body[0].y++;
            break;
        case 'q':
        case 'Q':
            printf("Game Quitted\ndid you not like my game?\n:(");
            exit(0);
        default:
            break;
        }

        // "eating" food ___________________________________________________
        if(body[0].x == food_x && body[0].y == food_y)
        {
            grow = 1;

            //scoring system________________________________________________
            score += SCORE_PER_FOOD;
            if (score % SCORE_PER_LEVEL == 0) 
            {
                level++;
            }
    
            //generating food_____________________________________
            int valid;
            do{
                valid = 1;
                food_x = rand() % grid_size;
                food_y = rand() % grid_size;

                for(int i = 0; i < length; i++){
                    if((food_x == body[i].x && food_y == body[i].y) || grid[food_x][food_y] != ' ')
                    {
                        valid = 0;
                    }
                }
            } while (!valid);
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
    }

    if(game_over == 1){
        if(level < 4){
            printf("\nG A M E  O V E R !\n  y o u  l o s e\n  Final score: %d\n\n   Boooo, noob!\n",score); 
        }
        else{
            printf("\nG A M E  O V E R !\n  y o u  l o s e\n  Final score: %d\n\n   dang-! got nothing better to do?",score);
        }     
    }

    return 0;
}