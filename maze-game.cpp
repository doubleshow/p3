#include "engine.h"
#include <fstream>

class  MazeGame : public Engine
{

    int x;
    int y;
    int goal_x;
    int goal_y;
    int window_w;
    int window_h;

    string ICON_PLAYER = "🧍";    
    string ICON_GOAL = "🏁";    

    vector<string> maze_data;

    void setup()
    {
        x = 1;
        y = 0;
        
        goal_x = 25;
        goal_y = 10;

        window_w = 5;
        window_h = 5;


        string line;
        ifstream maze_file("maze.txt");
        if (maze_file.is_open())
        {            
            while (getline(maze_file,line))
            {                      
                maze_data.push_back(line);                
            }
            maze_file.close();
        }             

        createCanvas(27, 11);        
    }
    
    void keyPressed(int keyCode)
    {            
        int x1 = x;
        int y1 = y;
        switch (keyCode)
        {
            case 'd':        
                x1 = x + 1;
                break;

            case 'a':
                x1 = x - 1;
                break;

            case 'w':
                y1 = y - 1;
                break;

            case 's':
                y1 = y + 1;
                break;
        }   
             
        // if (x1 < 27 && y1 < 11 && x1 > 0 && y1 >= 0 && maze_data[y1][x1] != 'w')
        // {
            x = x1;
            y = y1;
        // }
    }    

    void draw()
    {
        clear();
        for (int i = 0 ; i < 11; i++)
        {
            string line = maze_data[i];
            for (int j = 0 ; j < 27 ; j++)
            if (line[j] == 'w')
            {
                stroke("🌲");
                point(j, i);
            }                
        }
        stroke(ICON_GOAL);
        point(goal_x, goal_y);

        stroke(ICON_PLAYER);
        point(x, y);
        stroke(BLOCK);

    }

    void draw_window()
    {
        clear();
        int xo = x - 2;
        int yo = y - 2; 
        for (int i = 0 ; i < 5; i++)
        {
            int y1 = yo + i;            
            if (y1 >= 0) {
                string line = maze_data[y1];
                for (int j = 0 ; j <  5 ; j++)            
                {
                    int x1 = xo + j;
                    if (x1 >= 0 && line[x1] == 'w')
                    {
                        point(j, i);
                    }
                }
            }
        }
        stroke(ICON_GOAL);
        point(goal_x, goal_y);

        stroke(ICON_PLAYER);
        point(2, 2);
        stroke(BLOCK);

    }

    void console()
    {
        if (x == goal_x && y == goal_y)
        {
            cout << "You won!!" << endl;
            quit();            
        }
    }
};

// class  MazeGame : public Engine
// {

//     int x;
//     int y;
//     int goal_x;
//     int goal_y;

//     string ICON_PLAYER = "🧍";    
//     string ICON_GOAL = "🏁";    

//     vector<string> maze_data;

//     void setup()
//     {
//         x = 1;
//         y = 0;
//         goal_x = 25;
//         goal_y = 10;

//         string line;
//         ifstream maze_file("maze.txt");
//         if (maze_file.is_open())
//         {            
//             while (getline(maze_file,line))
//             {                      
//                 maze_data.push_back(line);                
//             }
//             maze_file.close();
//         }             

//         createCanvas(27, 11);
//     }
    
//     void keyPressed(int keyCode)
//     {            
//         int x1 = x;
//         int y1 = y;
//         switch (keyCode)
//         {
//             case 'd':        
//                 x1 = x + 1;
//                 break;

//             case 'a':
//                 x1 = x - 1;
//                 break;

//             case 'w':
//                 y1 = y - 1;
//                 break;

//             case 's':
//                 y1 = y + 1;
//                 break;
//         }        
//         if (x1 < 27 && y1 < 11 && x1 > 0 && y1 >= 0 && maze_data[y1][x1] != 'w')
//         {
//             x = x1;
//             y = y1;
//         }
//     }    


//     void draw()
//     {
//         clear();

//         for (int i = 0 ; i < maze_data.size(); i++)
//         {
//             string line = maze_data[i];
//             for (int j = 0 ; j <  line.size() ; j++)            
//             {
//                 if (line[j] == 'w')
//                 {
//                     point(j, i);
//                 }
//             }
//         }
//         stroke(ICON_GOAL);
//         point(goal_x, goal_y);

//         stroke(ICON_PLAYER);
//         point(x, y);
//         stroke(BLOCK);

//     }

//     void console()
//     {
//         if (x == goal_x && y == goal_y)
//         {
//             cout << "You won!!" << endl;
//             quit();            
//         }
//     }
// };

int main()
{
    MazeGame game;
    game.play();
}