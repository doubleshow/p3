#include "engine.h"

class ChoreGame : public Engine
{    
    // (x, y) location of the player
    int x = 0;
    int y = 0;

    void setup()
    {
        createCanvas(10,10); 
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

        // draw a random number from 0 to 9
        int dice = rand() % 10;
        if (dice == 0)   
        {
            // 1 out of 10 chance
            cout << "You got pulled over by the police." << endl;
            pause();
        }
        else if (dice == 1 || dice == 2) 
        {
            // 2 out of 10 chance
            cout << "You ran over a pothole." << endl;
            pause();
        }
    }


    void draw()
    {
        clear();
        stroke("🚗");
        point(x, y);
    }

};

int main()
{
    ChoreGame game;
    game.play();
}