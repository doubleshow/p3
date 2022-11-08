#include "engine.h"

class ChoreGame : public Engine
{
    private:
        int x = 0;
        int y = 0;
        bool _schoolMissionCompleted = false;
        bool _bankMissionCompleted = false;
    
    public:

        void setup() override;
        void keyPressed(int keyCode) override;
        void draw() override;
        void console() override;
};

void ChoreGame::setup()
{
    createCanvas(20,10); 
}

void ChoreGame::keyPressed(int keyCode)
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


void ChoreGame::draw()
{
    clear();

    stroke("🏫");
    point(2, 2);

    stroke("🏦");
    point(4, 4);

    stroke("🚗");
    point(x, y);
}

void ChoreGame::console()
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
        quit();
    }
}

int main()
{
    ChoreGame game;
    game.play();
}