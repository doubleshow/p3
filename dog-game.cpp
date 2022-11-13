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
                x = x - 1;
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

    // player's (x,y) location
    int x;
    int y;
    // goal's (x,y) location 
    int goal_x;
    int goal_y;
    // a vector of dog objects
    vector<Dog> dogs;

    string ICON_PLAYER = "🧍";
    string ICON_DOG = "🐕";
    string ICON_GOAL = "🏁";

    void setup()
    {
        // prompt the user to enter how many dogs to
        // put in the game?
        cout << "How many dogs? ";
        int n;
        cin >> n; 
        
        // create n instances of dogs
        for (int i = 0; i < n; i ++)
        {
            int x = random(12);
            int y = random(12);

            // initialize them 
            Dog dog(x,y);
            dogs.push_back(dog);
        }
          
        createCanvas(12, 12);
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

        // draw the dog
        stroke(ICON_GOAL);
        point(goal_x, goal_y);

        // draw the player
        stroke(ICON_PLAYER);
        point(x, y);

        // draw all the dogs
        for (Dog dog : dogs)
        {
            dog.update();
            stroke(ICON_DOG);
            point(dog.x, dog.y);
        }
    }

    void console()
    {
        // for each dog in the vector of dog objects
        for (Dog dog : dogs)
        {
            // if the player's position overlaps with this dog
            if (y == dog.y && x == dog.x)
            {
                cout << "You are bitten by a dog. GAME OVER!! " << endl;
                quit();         
                return;
            }
        } 

        // if the player's position is at the goal's position
        if (x == goal_x && y == goal_y)
        {
            cout << "You survived!!" << endl;
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