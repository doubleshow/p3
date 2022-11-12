#define ENGINE_VERSION "1.1"
#define AUTHOR Tom Yeh <tom.yeh@colorado.edu>

#include <iostream>     // cout, cin, streambuf, hex, endl, sgetc, sbumpc
#include <string>
#include <vector>

#define BLOCK  "██"
#pragma once

using namespace std;
class Canvas
{
    public:        
        void createCanvas(int w, int h);

        void resizeCanvas(int w, int h) 
        {
            createCanvas(w, h);
        }
        
        string _strokeSymbol = BLOCK;
        
        void stroke(const string icon);
        
        void clear();
        
        void point(int x, int y);
        void point(int x, int y, string symbol);

        void text(string word, int x, int y);
        
        void vertical_line(int x, int y1, int y2);
        
        void horizontal_line(int y, int x1, int x2);
        
        void render();



    bool _isLooping = true;
    void noLoop()
    {
        _isLooping = false;
    }

    bool _isFill = false;
    string _fillSymbol = BLOCK;

    void fill(string fillSymbol)
    {
        _fillSymbol = fillSymbol;
        _isFill = true;
    }

    void noFill()
    {
        _isFill = false;
    }

    void background(string symbol)
    {        
        for (int i = 0; i < getHeight(); i++)
        {
            for (int j = 0 ; j < getWidth(); j++)
            {                
                point(j, i, symbol);
            }
        }
    }

    void rect(int x, int y, int width, int height)
    {
            horizontal_line(y, x, x + width - 1);       
            horizontal_line(y+height-1, x, x + width - 1);      
            vertical_line(x, y, y + height - 1);      
            vertical_line(x+width-1, y, y + height - 1);     
        if (_isFill)
        {     
            string saved = _strokeSymbol;  
            for (int i = 1; i < height -1; i++)
            {
                stroke(_fillSymbol);
                horizontal_line(y+i, x+1, x+width-2);
            }
            stroke(saved);
        }
    }

    string _description;
    void describe(string text)
    {
        _description = text;
    }

    int _xo = 0;
    int _yo = 0;
    void translate(int x, int y)
    {
        _xo += x;
        _yo += y;
    }
         
    private:

        static const int MAX_WIDTH = 100;
        static const int MAX_HEIGHT = 50;
        // wchar_t buffer[MAX_HEIGHT][MAX_WIDTH][8];
        string buffer[MAX_HEIGHT][MAX_WIDTH];

        int _width;
        int _height;

    public:
    int getWidth()
    {
        return _width;
    }

    int getHeight()
    {
        return _height;
    }

     

};


class Engine :  public Canvas
{
    bool  _pausedUntilSpaceIsPressed = false;
    bool _quit = false;

    public:
    Engine()
    {
        createCanvas(10, 10);
    }

    protected:

    void quit();
    void pause();

    virtual void draw() {};
    virtual void console() {};
    virtual void keyPressed(int keyCode) {};
    virtual void setup() {};

    void redraw()
    {
        draw();
        render();
    }

    public:
    
    void play();

    void sleep(int milliseconds);   


};

//  returns a random number from 0 up to (but not including) the number.
int random(int n);

// returns a random number from the first argument up to 
// (but not including) the second argument.
int random(int a, int b);

string random(vector<string> choices);


class Menu : public Engine
{
    vector<Engine*> games;
    vector<string> game_names;

    public:

    void add(Engine* game, string name)
    {
        games.push_back(game);
        game_names.push_back(name);
    }

    void setup()
    {
        for (int i = 0 ; i < games.size() ; i++)
        {
            cout << (i+1) << ". " << game_names[i] << endl;
        }

        string c;
        cout << "Choose a game:";
        cin >> c;
        int i = stoi(c);
        if (i >= 1 && i <= games.size())
        {
            games.at(i-1)->play();
        }
        else
        {
            cout << "Not a valid choice." << endl;
        }
        quit();
    }

};