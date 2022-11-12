#include "engine.h"

class ChoreGame : public Engine
{    
    // (x, y) location of the player
    int x = 0;
    int y = 0;

    // boolean flags to keep track of whether each mission has been completed
    bool _schoolMissionCompleted = false;
    bool _bankMissionCompleted = false;

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
    }


    void draw()
    {
        clear();

        stroke("🏫");
        point(2, 2);

        stroke("🏦");
        point(4, 4);

        stroke("🚗");
        point(x, y);
    }

    void console()
    {        
        if (y == 4 && x == 4 && !_bankMissionCompleted)
        {
            cout << "You have arrived at the bank." << endl;
            cout << "How much do you want to withdraw? " ;
            string c;
            cin >> c;         
            cout << "You have withdrawn " << c << " dollars." << endl;
            _bankMissionCompleted = true;
            pause();
        }
        else if (y == 2 && x == 2 && !_schoolMissionCompleted)
        {
            cout << "You arrived at the school." << endl;
            cout << "You dropped off your children." << endl;
            _schoolMissionCompleted = true;
            pause();
        }
        else if (_bankMissionCompleted && _schoolMissionCompleted)
        {
            cout << "You completed all the missions!" << endl;
            cout << endl << endl;
            quit();
        }
    }
};

int main()
{
    ChoreGame game;
    game.play();
}