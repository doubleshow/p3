#include "MapGame.h"

// roll a n-face dice
int roll_dice(int n)
{    
    return (rand() % n) + 1;
}

class Computer
{
    public:
    Computer()
    {
        _level = 0;
    }

    // return the level
    int getLevel()
    {
        return _level;
    }

    // set the level
    void setLevel(int level)
    {
        _level = level;
    }

    private:    
    int _level; // the level of this computer, the higher the more powerful
};

class Player
{
    public:

    // default constructor
    Player()
    {
        _name = "";
        _coins = 0;
    }

    // parameterized constructor to create a player object
    Player(string name, int coins)
    {
        _name = name;
        _coins = coins;
    }

    // return the name of the player
    string getName()
    {
        return _name;
    }

    // set the name of the player
    void setName(string name)
    {
        _name = name;
    }

    // return coins
    int getCoins()
    {
        return _coins;
    }

    // set the number of coins held by the player
    void setCoins(int coins)
    {
        _coins = coins;
    }

    // add a computer to this player's possession
    void addComputer(Computer c)
    {
        _computers.push_back(c);
    }

    // return the number of computers
    int getNumComputers()
    {
        return _computers.size();
    }

    private:
    string _name;   // player's name
    int _coins;     // players' coins
    vector<Computer> _computers;    // player's computers
    
};

// The HackerQuest class inherits the functions and data of the 
// MapGame class, which in turn inherits the function and data of both
// the Map class and the Engine class.
class HackerQuest : public MapGame
{
    // Player object to represent the player
    Player _player;

    // boolean flag to keep track of whether the menu is open or not
    bool _isMenuOpen = false;

    // number of unsafe passwords discovered so far
    int _numPasswords = 0;

    void setup()
    {
        createCanvas(12, 12);     

        // 
        // Add rooms and NPCs to the map
        //
        // @TODO: andomize their locations
        // @TODO: increase the number to five each

        // add two server rooms
        addRoom(2, 2);
        addRoom(7, 9);

        // add two NPCs
        addNPC(3, 3);
        addNPC(2, 8);

        // customize icons
        // @TODO: replace them with icons that suit your game

        ICON_ROOM = "R_";
        ICON_GOAL = "🏁";
        ICON_PLAYER = "🧍";
        ICON_UNEXPLORED = "▒▒";
        ICON_EXPLORED = "  ";

        //
        // Start Screen
        //

        // display the title of the game
        // @TODO: customize the title
        cout << "===========================" << endl;
        cout << "        Hacker Quest       " << endl;
        cout << "===========================" << endl;
        
        // prompt the player to enter their name
        cout << "What is your name? ";
        string buffer;
        cin >> buffer;

        // @TODO: add more prompts
        
        // initialize the player with the given name and with 100 coins
        // @TODO: extend this as more properties are added to the player class
        _player = Player(buffer, 100);

        // greet the player by their name
        cout << "Welcome " << _player.getName() << endl;
        pause();
    }

    void keyPressed(int keyCode)
    {
        // get the player's current location on the map
        int i = getPlayerRow();
        int j = getPlayerCol();    
        bool isMoved = false;    
        switch (keyCode)
        {
            case 'd':
            case 'D':
                j = j + 1;
                isMoved = true;
                break;

            case 'a':
            case 'A':
                j = j - 1;
                isMoved = true;
                break;

            case 'w':
            case 'W':
                i = i - 1;
                isMoved = true;
                break;

            case 's':
            case 'S':
                i = i + 1;
                isMoved = true;
                break;
            case 'q':
            case 'Q':
                quit();
                break;
            case 'M':
            case 'm':
                // open the menu
                _isMenuOpen = true;
                break;
        }

        // if the player is moved
        if (isMoved)
        {       
            // set the new player position on the map
            setPlayerPosition(i, j);

            // roll a dice to get a number between 1 and 10
            int dice = roll_dice(10); 
            // @TODO: add more random events
            // @TODO: implement the logic of each random event
            // @TODO: adjust the chance values

            if (dice == 1)  // 1 out of 10 chance
            {                        
                cout << "A Random Event Happened!" << endl;
                cout << "You were blacklisted by a sys admin." << endl;
                // lost 5 coins
                _player.setCoins(_player.getCoins() - 5);
                pause();
            }        
            else if (dice == 2 || dice == 3) // 2 out of 10
            {
                cout << "A Random Event Happened!" << endl;
                cout << "You discovered an unsafe password!" << endl;
                // got one more unsafe passwords
                _numPasswords++;
                pause();
            }

        }
    }    
    

    void console()
    {
        // print the status
        // @TODO: customize the status display
        cout << "Name: " << _player.getName() << endl;
        cout << "Coins: " << _player.getCoins() << endl;
        cout << "Passwords: " << _numPasswords << endl;
        cout << "Computers: " << _player.getNumComputers() << endl;

        if (!_isMenuOpen)
        {
            // if the menu's status is not open, display
            // the prompt to let the player know how 
            // to open the menu
            cout << "Press [M] to Open Menu" << endl;
        }
        else
        {
            // get the location of the player on the map
            int i = getPlayerRow();
            int j = getPlayerCol();    

            // depending on where the player is, present
            // the appropriate menu

            if (isRoomLocation(i ,j))
            {
                // if the player is in a server room, present
                // the menu sepcific to the server room location.

                // @TODO: customize the menu
                cout << "---------------------" << endl;
                cout << "SERVER ROOM" << endl;
                cout << "(1) Hack" << endl;
                cout << "(2) Repair" << endl;
                cout << "---------------------" << endl;
                cout << "(q) Quit" << endl;
                cout << "Choose one:";
                string option;
                cin >> option;                    

                // @TODO: customize how each menu option is handled
                if (option == "1")
                {
                    cout << "You hacked the server." << endl;               

                    // @TODO: check if the player have at least one password
                    
                    // one password is used
                    _numPasswords--;

                    // remove the room from the map
                    removeRoom(i, j);

                }
                else if (option == "2")
                {
                    cout << "You repaired the server." << endl;
                    // @TODO: update the game data
                }
                else if (option == "q")
                {
                    cout << "You quitted the game." << endl;
                    quit();
                }
                // @TODO: add more menu option
            }
            // else if (@TODO: handle the NPC location's menu)
            // {

            // }
            else
            {
                // if the player is in neither a server room or with
                // an NPC, present the "NORMAL" menu

                cout << "---------------------" << endl;
                cout << "NORMAL" << endl;
                cout << "(1) Rest" << endl;                
                cout << "(2) Build a Computer " << endl;
                cout << "---------------------" << endl;
                cout << "(q) Quit" << endl;
                cout << "Choose one:";
                string option;
                cin >> option;
                if (option == "1" )
                {
                    cout << "You rested." << endl;
                    // @TODO: update the game data
                }
                else if (option == "2")
                {
                    cout << "You built a computer." << endl;
                    // @TODO: update the game data
                    Computer c;
                    _player.addComputer(c);
                }
                else if (option == "q")
                {
                    quit();
                }                
            }
            pause();

            // hide the menu
            _isMenuOpen = false;
        }
    }

};

int main()
{
    HackerQuest game;
    game.play();
    return 0;
}