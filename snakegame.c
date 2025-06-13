#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#ifdef _WIN32
    #include<windows.h>
#else
   #include <unistd.h>
#endif       

//some constants__________________________
#define INITIAL_DELAY_MS 200
#define MIN_DELAY_MS    50
#define INCREMENTED_SPEED 20
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
    int initial_delay = INITIAL_DELAY_MS;
   
    #ifdef _WIN32
           HANDLE hconsole =GetStdHandle(STD_OUTPUT_HANDLE);
    #endif

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
        // clear system________________________________________
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

    //adding colors___________________________________________
        #ifdef _WIN32
              SetConsoleTextAttribute(hconsole , 1);
        #endif      
           printf("Score : %d\n", score);

        #ifdef _WIN32 
              SetConsoleTextAttribute(hconsole , 13);
        #endif
            printf("Level : %d\n",level);
         
        #ifdef _WIN32
               SetConsoleTextAttribute(hconsole , 7);
        #endif           


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
                char cell = grid[i][j];

                if(cell == '*')
                {
                    #ifdef _WIN32
                        SetConsoleTextAttribute(hconsole , 6);
                    #endif
                     printf("*");
                }     
                else if(cell == 'O')
                {  
                    #ifdef _WIN32
                        SetConsoleTextAttribute(hconsole , 11);
                     #endif        
                      printf("O");
                }      
                else if(cell == 'o')
                {
                     #ifdef _WIN32
                        SetConsoleTextAttribute(hconsole , 10);
                     #endif        
                      printf("o");
                }      
                else
                {
                    #ifdef _WIN32
                        SetConsoleTextAttribute(hconsole , 7);
                     #endif        
                      printf(" ");
                     
                }
            }
            #ifdef _WIN32
                SetConsoleTextAttribute(hconsole , 7);
                     #endif 
            printf("|");
            printf("\n");
        }

        for(int i = 0; i < grid_size; i++){
            printf("_");
        }

       
        char input = getchar();
        while ((getchar()) != '\n');

        axes pre_len = body[length-1];
        for(int i = length-1; i > 0; i--) {
            body[i] = body[i-1];
        }

        switch (input)
        {
        case 'w':
            body[0].x--;
            break;
        case 's':
            body[0].x++;
            break;
        case 'a':
            body[0].y--;
            break;
        case 'd':
            body[0].y++;
            break;
        case 'q':
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
                if(initial_delay > MIN_DELAY_MS)
                {
                   initial_delay -= INCREMENTED_SPEED;
                }
               printf("WOHOO! Level up !!Welcome to the level %d\n", level);

               #ifdef _WIN32
                  Sleep(1000);
               #else 
                  usleep(1000000);
               #endif   
            }

            // beep at eating food____________________________________
            #ifdef _WIN32
                Beep(230 , 30);
            #else
                printf("\a");
                fflush(stdout);
            #endif
    
        //generating food_____________________________________
            int valid;
            do{
                valid = 1;
                srand(time(NULL));
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

        //collision wilth walls_________________________________________
        if(body[0].x < 0 || body[0].y < 0 || body[0].x >= grid_size || body[0].y >= grid_size)
        {

            game_over = 1;
        }
    
        
        //collision with itself________________________________________
        for(int i = 1; i < length ; i++)
        {
            if(body[0].x == body[i].x && body[0].y == body[i].y)
            {
                game_over = 1;
            }        
        }
       
        //wait_______________________________
       #ifdef _WIN32
            Sleep(initial_delay);
       #else
            usleep(initial_delay * 1000);
       #endif      
    }

    if(game_over == 1)
    {
        #ifdef _WIN32
            SetConsoleTextAttribute(hconsole , 12);
        #endif    
        printf("G A M E  O V E R !\n  y o u  l o s e\n   Boooooo, noob!\n");
        
        #ifdef _WIN32
             SetConsoleTextAttribute(hconsole , 1);
        #endif     
        printf("Final score :%d\n",score);


        #ifdef _WIN32
              SetConsoleTextAttribute(hconsole ,13);
        #endif      
        printf("And the journey ends at level:%d Respect!\n",level);


        #ifdef _WIN32
              SetConsoleTextAttribute(hconsole , 7);
        #endif      
    }

    return 0;
}