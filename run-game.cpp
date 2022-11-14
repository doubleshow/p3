#include "engine.h"
#include <fstream>

class  RunGame : public Engine
{
    protected:

    int player_x;
    int player_y;

    int player_money;
    int player_health;

    string ICON_PLAYER = "🧍";    
    string ICON_WALL = "▓▓";
    string ICON_TREASURE = "💰";

    const int MAP_HEIGHT = 100;
    const int MAP_WIDTH = 3; 

    const int SCREEN_HEIGHT = 15;
    const int SCREEN_WIDTH = 3;

    // a vector of strings to store the map data
    // map_data[i][j]  gives us access to
    //   i'th row, j'th column 
    //   or coordinate (j, i)   i.e., x = column, y = row
    vector<string> map_data;

    // a counter to keep track how many loops so that
    // we control how fast we want to move the player down
    // the map
    int loop_count = 0;

    void setup()
    {
        // Create a random map that looks like below
        // where X denotes an obstacle and T denotes
        // a treasure. Each line is a string of 3 characters
        //
        // OOO
        // OOO
        // OOX
        // TOO
        // OOO
        // OOO
        //
        //
        for (int i = 0 ; i < MAP_HEIGHT ; i++)
        {
            string line = "OOO";

            // 1 of 5 chance there is an obstacle
            int p1 = random(5);
            if (p1 == 0)
            {
                int j = random(3);
                line[j] = 'X';
            }

            // 1 of 10 chance there is a treasure
            int p2 = random(10);
            if (p2 == 0)
            {
                int j = random(3);
                line[j] = '$';
            }
            map_data.push_back(line);
        }
        

        // initalize player stats
        player_health = 3;
        player_money = 0;

        createCanvas(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    
    void keyPressed(int keyCode)
    {            
        int x1 = player_x;
        int y1 = player_y;
        switch (keyCode)
        {
            case 'd':        
                x1 = player_x + 1;
                break;

            case 'a':
                x1 = player_x - 1;
                break;

            case 'w':
                y1 = player_y - 1;
                break;

            case 's':
                y1 = player_y + 1;
                break;
        }   

        // check if this move is not within the bound and also not a wall 
        if (x1 < MAP_WIDTH && y1 < MAP_HEIGHT && x1 >= 0 && y1 >= 0 && map_data[y1][x1] != 'W')
        {
            player_x = x1;
        }

    } 

    void draw()
    {
        clear();

        // translate to place player at the center of the top line
        translate(0, -player_y);

        for (int y = 0 ; y < MAP_HEIGHT; y++)
        {            
            for (int x = 0 ; x < MAP_WIDTH ; x++)
            {
                char d = map_data[y][x];
                switch (d)
                {
                    case 'X':
                        stroke(ICON_WALL);                        
                        point(x, y);
                        break;    

                    case '$':
                        stroke(ICON_TREASURE);
                        point(x, y);
                        break;
                }
            }
        }

        stroke(ICON_PLAYER);
        point(player_x, player_y);     

        // every three loops, we move the player down by one
        if (loop_count % 3 == 0)
        {
            player_y++;
        }        
        loop_count++;
    }

    void console()
    {        
        cout << "Health: " << player_health << ", Money: " << player_money << endl;

        char d = map_data[player_y][player_x];
        if (d == 'X')
        {
            // the player hits an obstacle, health goes down by one
            player_health--;

            // remove the obstacle from the map
            map_data[player_y][player_x] = ' ';

            if (player_health == 0)
            {
                // the player's health reached zero and died
                // the game is over
                cout << "You died. Game over!" << endl;
                quit();
            }
        }
        else if (d == '$')
        {
            // the player hits a treasure, money goes up by one   
            player_money++;            

            // remove the treasure from the map
            map_data[player_y][player_x] = ' ';
        }
        else if (player_y == MAP_HEIGHT - 1)
        {
            // the player reaches the end of the map
            cout << "Finished!" << endl;            
            quit();
        }
    }
};


int main()
{
    RunGame game;
    game.play();
}