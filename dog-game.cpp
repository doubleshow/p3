#include "engine.h"

class Dog
{
    public:
    Dog(int x_, int y_)
    {
        x = x_;
        y = y_;
    }

    int x;
    int y;

    void update()
    {
        int chance = random(10);
        if (chance >= 5)
        {
            string random_move = random({"up","down","left","right"});
            if (random_move == "up")
            {
                y = y - 1;
            }
            else if (random_move == "down")
            {
                y = y + 1;
            }
            else if (random_move == "left")
            {
                // x = x - 1;
            }
            else if (random_move == "right")
            {
                x = x + 1;
            }
        }
    }
};

class  DogGame : public Engine
{

    int x;
    int y;
    int goal_x;
    int goal_y;
    vector<Dog> dogs;

    string ICON_PLAYER = "🧍";
    string ICON_DOG = "🐕";
    string ICON_GOAL = "🏁";

    void setup()
    {
        cout << "How many dogs? ";
        int n;
        cin >> n; 
        for (int i = 0; i < n; i ++)
        {
            int x = random(24);
            int y = random(24);
            Dog dog(x,y);
            dogs.push_back(dog);
        }
          
        createCanvas(24, 24);
        goal_x = 11;
        goal_y = 5;
    }
    
    void keyPressed(int keyCode)
    {            
        switch (keyCode)
        {
            case 'd':        
                x = x + 1;
                break;

            case 'a':
                x = x - 1;
                break;

            case 'w':
                y = y - 1;
                break;

            case 's':
                y = y + 1;
                break;
        }        
    }    


    void draw()
    {
        clear();

        stroke(ICON_GOAL);
        point(goal_x, goal_y);

        stroke(ICON_PLAYER);
        point(x, y);

        for (Dog dog : dogs)
        {
            dog.update();
            stroke(ICON_DOG);
            point(dog.x, dog.y);
        }
    }

    void console()
    {
        for (Dog dog : dogs)
        {
            if (y == dog.y && x == dog.x)
            {
                cout << "You are bitten by a dog. GAME OVER!! " << endl;
                quit();         
                return;
            }
        } 

        if (x == goal_x && y == goal_y)
        {
            cout << "You won!!" << endl;
            quit();
            return;
        }
    }
};

int main()
{
    DogGame game;
    game.play();
}