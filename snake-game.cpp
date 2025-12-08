#include<iostream>
#include <conio.h>
#include <fstream>
using namespace std;

int gethighscore()
{
    ifstream fin("highscore.txt");
    int highscore=0;
    if(fin)
    {
        fin>>highscore;
        fin.close();
    }
    return highscore;
}
void savehighscore(int length)
{
    int currenthigh=gethighscore();
    if(length > currenthigh)
    {
        ofstream fout("highscore.txt");
        
        fout <<length;
         fout.close();

        cout<<"New High Score: "<<length <<"\n";
    }
}
void saveScoreHistory(int length)
 {
    ofstream fout("score_history.txt", ios::app); 
    if (!fout) 
    { 
        cout << "Error:Unable to open score_history.txt file!" << endl;
        return;
    }

    fout << "Score: " << length << endl;  
    fout.close(); 
}

int main()
{
    int grid_size = 20, max_len = 200, length = 1;
    char **grid = new char*[grid_size];
    int  food_x, food_y;
    int game_over = 0, grow = 0;

    for(int i = 0; i < grid_size; i++){
        grid[i] = new char[grid_size];
    }

    struct axes 
    {
        int x;
        int y;
    };

    axes *body = new axes[max_len];


    body[0].x = grid_size / 2;
    body[0].y = grid_size / 2;


    // random food generator ___________________________________________________________________________________________
    srand(time(NULL));
    do{
        food_x = rand() % grid_size;
        food_y = rand() % grid_size ;
    }while ((food_x == body[0].x && food_y == body[0].y));


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
        for(int i = 0; i < length; i++){
            grid[body[i].x][body[i].y] = (i==0) ? 'O' : 'o';
        }

        //printing stage _____________________________________________

    cout << "\nCONTROLS:    W     \n";
    cout << "         A   S   D \n";
    cout << "\nPress Q to quit\n";


        for(int i = 0; i < grid_size; i++){
            cout << "_";
        }
        cout << "\n";

        for(int i = 0; i < grid_size; i++){
            cout << "|";
            for(int j = 0; j < grid_size; j++){
                cout << grid[i][j];
            }
            cout << "|";
            cout << "\n";
        }

        for(int i = 0; i < grid_size; i++){
            cout << "_";
        }

        char input = _getch();

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
            cout << "\nGame Quitted\ndid you not like my game?\n:(";

            // free dynamic memory before exiting__________________________________________
            for(int i = 0; i < grid_size; i++){
               delete[] grid[i];
            }
                delete[] grid;
                delete[] body;
            exit(0);
        default:
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
        cout << "\nG A M E   O V E R !\n  y o u   l o s e\n";

        int highscore=gethighscore();
        cout<<"previous high score: "<<highscore<<endl;

        savehighscore(length-1);
        saveScoreHistory(length-1);
  }
    
   for(int i = 0; i < grid_size; i++){
        delete[] grid[i];
    }
        delete[] grid;
        delete[] body;

    return 0;
}