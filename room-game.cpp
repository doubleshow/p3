#include "engine.h"
#include <fstream>

class  RoomGame : public Engine
{
    protected:

    int player_x;
    int player_y;

    int num_treasures_found;

    string ICON_PLAYER = "🧍";    
    string ICON_EXIT = "  ";    
    string ICON_WALL = "▓▓";
    string ICON_DOOR = "🚪";
    string ICON_TREASURE = "💰";
    string ICON_MONSTER = "🦁";

    const int MAP_HEIGHT = 16;
    const int MAP_WIDTH = 48; 

    const int SCREEN_HEIGHT = 12;
    const int SCREEN_WIDTH = 12;

    // a vector of strings to store the map data
    // map_data[i][j]  gives us access to
    //   i'th row, j'th column 
    //   or coordinate (j, i)   i.e., x = column, y = row
    vector<string> map_data;

    void setup()
    {
        
        // read the map data from file
        string line;
        ifstream file("room-data.txt");
        if (file.is_open())
        {            
            while (getline(file,line))
            {                       
                map_data.push_back(line);                
            }
            file.close();
        }
        
        // find the player's starting position
        for (int i = 0; i < MAP_HEIGHT; i++)
        {
            for (int j = 0; j < MAP_WIDTH; j++)
            {
                char c = map_data[i][j];
                switch (c)
                {
                    case 'S':
                        player_x = j;
                        player_y = i;
                }
            }
        }

        // initalize the number of treasures found
        num_treasures_found = 0;

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
            player_y = y1;
        }

    } 

    void draw()
    {
        clear();

        // translate by half the screen dimensions with respect to the
        // player's location in order to center the screen on the player
        translate(SCREEN_WIDTH/2-player_x, SCREEN_HEIGHT/2-player_y);

        for (int i = 0 ; i < MAP_HEIGHT; i++)
        {            
            for (int j = 0 ; j < MAP_WIDTH ; j++)
            {
                char d = map_data[i][j];
                switch (d)
                {
                    case 'W':
                        stroke(ICON_WALL);
                        point(j, i);
                        break;

                    case 'D':
                        stroke(ICON_DOOR);
                        point(j, i);
                        break;

                    case 'T':
                        stroke(ICON_TREASURE);
                        point(j, i);
                        break;

                    case 'M':
                        stroke(ICON_MONSTER);
                        point(j, i);
                        break;                        

                    case 'E':
                        stroke(ICON_EXIT);
                        point(j, i);
                        break;
                }
            }
        }

        stroke(ICON_PLAYER);
        point(player_x, player_y);        
    }

    void console()
    {
        cout << "Number of treasures found: " << num_treasures_found << endl;

        char d = map_data[player_y][player_x];
        if (d == 'E')
        {
            cout << "You left this room." << endl;
            quit();            
        }
        else if (d == 'T')
        {
            cout << "You found a treasure!" << endl;

            // increment the number of treasures found by one
            num_treasures_found++;

            // remove the treasure by setting the map data
            // at this location to blank
            map_data[player_y][player_x] = ' ';
            pause();
        }
        else if (d == 'M')
        {
            cout << "You got killed by a monster!" << endl;
            cout << "Game Over" << endl;
            quit();
        }
    }
};


int main()
{
    RoomGame game;
    game.play();
}