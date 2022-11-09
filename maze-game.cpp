#include "engine.h"
#include <fstream>

class  MazeGame : public Engine
{
    protected:
    int player_x;
    int player_y;
    int goal_x;
    int goal_y;

    string ICON_PLAYER = "🧍";    
    string ICON_GOAL = "🏁";   
    string ICON_BREADCRUMB = "░░";   
    string ICON_WALL = "🌲";   

    const int MAZE_HEIGHT = 11;
    const int MAZE_WIDTH = 27; 

    // a vector of strings to store the map data
    // maze_data[i][j]  gives us access to
    //   i'th row, j'th column 
    //   or coordinate (j, i)   i.e., x = column, y = row
    vector<string> maze_data;

    void setup()
    {
        // read the map data from file
        string line;
        ifstream maze_file("maze-data.txt");
        if (maze_file.is_open())
        {            
            while (getline(maze_file,line))
            {                       
                maze_data.push_back(line);                
            }
            maze_file.close();
        }

        // find the player's starting position
        // and the position of the goal
        for (int i = 0; i < MAZE_HEIGHT; i++)
        {
            for (int j = 0; j < MAZE_WIDTH; j++)
            {
                char c = maze_data[i][j];
                switch (c)
                {
                    case 'g':
                        goal_x = j;
                        goal_y = i;
                        break;

                    case 's':
                        player_x = j;
                        player_y = i;
                }
            }
        }

        createCanvas(MAZE_WIDTH, MAZE_HEIGHT);
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
        if (x1 < MAZE_WIDTH && y1 < MAZE_HEIGHT && x1 > 0 && y1 >= 0 && maze_data[y1][x1] != 'w')
        {
            player_x = x1;
            player_y = y1;

            // mark this location as 'visited'
            maze_data[y1][x1] = 'v';
        }
  
    } 

    void draw()
    {
        clear();
        for (int i = 0 ; i < MAZE_HEIGHT; i++)
        {            
            for (int j = 0 ; j < MAZE_WIDTH ; j++)
            {
                char d = maze_data[i][j];
                switch (d)
                {
                    case 'w':
                        stroke(ICON_WALL);
                        point(j, i);
                        break;
                    case 'v':
                        stroke(ICON_BREADCRUMB);
                        point(j, i);
                        break;
                }
            }
        }
        stroke(ICON_GOAL);
        point(goal_x, goal_y);

        stroke(ICON_PLAYER);
        point(player_x, player_y);
        stroke(BLOCK);

    }

    void console()
    {
        if (player_x == goal_x && player_y == goal_y)
        {
            cout << "You won!!" << endl;
            quit();            
        }
    }
};

class MazeGameSolver : public MazeGame
{
    bool isGoalReached = false;

    void setup()
    {
        // call the parent's setup() to read the map data
        MazeGame::setup();

        // explore the map
        explore(player_x, player_y);
        noLoop();
    }
    
    // explore the map until the goal is reached using a recursive
    // depth-first-search algorithm
    void explore(int x, int y)
    {         
        if (isGoalReached)
        {
        // BASE CONDITION: if the goal is already reached.
            return;
        }
        else if (x >= MAZE_WIDTH || y >= MAZE_HEIGHT || x < 0 || y < 0)
        // BASE CONDITION: if it is out of bound.
        {            
            return;
        }
        else if (maze_data[y][x] == 'w' || maze_data[y][x] == 'v')
        {
        // BASE CONDITION: if the location is a wall or is already visited.
            return;
        } 
        else if (maze_data[y][x] == 'g')
        {
        // BASE CONDITION: if the location is the goal.
            string s;
            cout <<"GOAL!" << endl;
            isGoalReached = true;
            return;
        }
        else if (!isGoalReached)
        {
            // mark this cell as visited
            maze_data[y][x] = 'v';
            // update the location of the player
            player_x = x; 
            player_y = y;

            // redraw the canvas immedidately
            redraw();
            // sleep a bit so that the animation does not move too fast
            sleep(100);
            
            // recursively explore the four adjacent directions
            explore(x, y+1);
            explore(x, y-1);
            explore(x+1, y);
            explore(x-1, y);
        }        
    }    
};

int main()
{
    Menu menu;
    menu.add(new MazeGame(), "MazeGame");
    menu.add(new MazeGameSolver(), "MazeGameSolver");
    menu.play();
}