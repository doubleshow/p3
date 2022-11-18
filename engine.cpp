#include <iostream>     // cout, cin, streambuf, hex, endl, sgetc, sbumpc
#include <iomanip>      // setw, setfill
#include <fstream>      // fstream

// These inclusions required to set terminal mode.
#include <termios.h>    // struct termios, tcgetattr(), tcsetattr()
#include <stdio.h>      // perror(), stderr, stdin, fileno()

using namespace std;

#ifdef OS_WIN
#include <conio.h>
#elif defined(OS_LINUX) || defined(OS_MAC)
#include <unistd.h>
#include <sys/socket.h>
#endif
bool stdinHasData()
{
#   if defined(OS_WIN)
    // this works by harnessing Windows' black magic:
    return _kbhit();
// #   elif defined(OS_LINUX) || defined(OS_MAC) 
#   else

    struct termios t;
    struct termios t_saved;

    // Set terminal to single character mode.
    tcgetattr(fileno(stdin), &t);
    t_saved = t;
    t.c_lflag &= (~ICANON & ~ECHO);
    t.c_cc[VTIME] = 0;
    t.c_cc[VMIN] = 1;
    if (tcsetattr(fileno(stdin), TCSANOW, &t) < 0) {
        perror("Unable to set terminal to single character mode");
        return -1;
    }


    // using a timeout of 0 so we aren't waiting:
    struct timespec timeout{ 0l, 0l };

    // create a file descriptor set
    fd_set fds{};

    // initialize the fd_set to 0
    FD_ZERO(&fds);
    // set the fd_set to target file descriptor 0 (STDIN)
    FD_SET(0, &fds);

    // pselect the number of file descriptors that are ready, since
    //  we're only passing in 1 file descriptor, it will return either
    //  a 0 if STDIN isn't ready, or a 1 if it is.

    

    bool s = pselect(0 + 1, &fds, nullptr, nullptr, &timeout, nullptr) == 1;

// Restore terminal mode.
    if (tcsetattr(fileno(stdin), TCSANOW, &t_saved) < 0) {
        perror("Unable to restore terminal mode");
        return -1;
    }
    return s;
// #   else
//     // throw a compiler error
//     static_assert(false, "Failed to detect a supported operating system!");
#   endif
}

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>


#include <vector>
#include "engine.h"

void Canvas::createCanvas(int w, int h)
{
    _width = w;
    _height = h;
    clear();
}

void Canvas::stroke(const string symbol)
{
    _strokeSymbol = symbol;
}

void Canvas:: clear()
{
    for (int i = 0; i < _height; i++)
    {
        for (int j = 0; j < _width; j++)
        {
            // buffer[i][j][0] = 0;
            // buffer[i][j][1] = 0;
            // buffer[i][j][2] = 0;
            // buffer[i][j][3] = 0;
            buffer[i][j] = "";
        }                
    }
}

void Canvas::point(int x, int y)
{
    // if (x >= 0 && x <  _width && y < _height && y >= 0)
    // {                            
        point(x, y, _strokeSymbol);
    // }
}

void Canvas::point(int x_, int y_, string symbol)
{
    int x = _xo + x_;
    int y = _yo + y_;

    if (x >= 0 && x <  _width && y < _height && y >= 0)
    {
        // for (int i = 0; i < symbol.size(); i++)
        // {
        //     buffer[y][x][i] = symbol[i];
        // }             
        buffer[y][x] = symbol;
    }
}

void Canvas:: text(string word, int x_, int y_)
{
    int x = _xo + x_;
    int y = _yo + y_;

    int j = 0;
    for (int i = 0; i < word.size(); i = i + 2)
    {
        j = x + (i / 2);
        if (y >= 0 && j >= 0 && y < MAX_HEIGHT && j < MAX_WIDTH)
        {
            buffer[y][j] = word.substr(i, 2);
        }
        // buffer[y][j][0] = word[i];
        // buffer[y][j][1] = word[i+1];   
        // buffer[y][j][2] = 0;
    }
    if (word.size() % 2 == 0)
    {
        // buffer[y][j][2] = 0;
    }
    else 
    {
        if (y >= 0 && j >= 0 && y < MAX_HEIGHT && j < MAX_WIDTH)
        {
            buffer[y][j] = word.substr(word.size()-1,1) + " ";
        }
        // buffer[y][j][0] = word[word.size()-1];
        // buffer[y][j][1] = ' ';
        // buffer[y][j][2] = 0;
    }
}

void Canvas:: vertical_line(int x, int y1, int y2)
{
    for (int y = y1; y <= y2; y++)
    {
        point(x, y);
    }
}

void  Canvas::horizontal_line(int y, int x1, int x2)
{
    for (int x = x1; x <= x2; x++)
    {
        point(x, y);
    }
}        

// adapated from
// ref: https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/
// fixed off by one bug by modifying how x1 and y1 increment / decrement
void plotPixel(int x1, int y1, int x2, int y2, int dx,
               int dy, int decide, Canvas *canvas)
{
    // pk is initial decision making parameter
    // Note:x1&y1,x2&y2, dx&dy values are interchanged
    // and passed in plotPixel function so
    // it can handle both cases when m>1 & m<1
    int pk = 2 * dy - dx;
    for (int i = 0; i <= dx; i++) {
        // cout << x1 << "," << y1 << endl;         
        // 
        // checking either to decrement or increment the
        // value if we have to plot from (0,100) to (100,0) 

        if (pk < 0) {
            
            // decision value will decide to plot
            // either  x1 or y1 in x's position
            if (decide == 0) {
                // putpixel(x1, y1, RED);
                // canvas->stroke("11");
                canvas->point(x1, y1);                
                pk = pk + 2 * dy;
            }
            else {
                //(y1,x1) is passed in xt
                // putpixel(y1, x1, YELLOW);
                // canvas->stroke("22");
                canvas->point(y1, x1);    
                pk = pk + 2 * dy;
            }
        }
        else {
            // y1 < y2 ? y1++ : y1--;
            if (decide == 0) {
 
                // putpixel(x1, y1, RED);
                // canvas->stroke("33");
                canvas->point(x1, y1);    
            }
            else {
                //  putpixel(y1, x1, YELLOW);
                // canvas->stroke("44");
                // canvas->stroke(to_string(y1));
                canvas->point(y1, x1);    
            }
            pk = pk + 2 * dy - 2 * dx;
            // pk = pk - 2 * dx;

            if (y1 < y2)
            {
                y1++;
            }
            else if (y1 > y2)
            {
                y1--;
            }
        }

        if (x1 < x2)
        {
            x1++;
        }
        else if (x1 > x2)
        {
            x1--;
        }        

    }
}

void  Canvas::line(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
 
    // If slope is less than one
    if (dx > dy) {
 
        // passing argument as 0 to plot(x,y)
        plotPixel(x1, y1, x2, y2, dx, dy, 0, this);
    }
    // if slope is greater than or equal to 1
    else {
 
        // passing argument as 1 to plot (y,x)
        plotPixel(y1, x1, y2, x2, dy, dx, 1, this);
    }
}    

void Canvas::render()
{
    cout << "\033[2J\033[1;1H";
    cout << "p3 Engine " << ENGINE_VERSION << endl ;
    cout << "  ";    
    for (int i = 0; i < _width; i++)
    {   
        cout << setw(2) << i % 10;
    }    
    cout << endl;
    cout << "  ┌";
    for (int i = 0; i < _width; i++)
    {   
        cout << "──";
    }
    cout << "┐";
    cout << endl;
    for (int i = 0; i < _height; i++)
    {
        cout << setw(2) << i << "│";
        for (int j = 0; j < _width; j++)
        {                    
            if (buffer[i][j].size() > 0)
            {
                cout << buffer[i][j];
            } 
            else
            {
                cout << "  ";
            }
        }
        cout << "│";
        cout << endl;                
    }
    cout << "  └";
    for (int i = 0; i < _width; i++)
    {   
        cout << "──";
    }
    cout << "┘";
    cout << endl;
}

void Engine::quit()
{
    _quit = true;
}

void Engine::pause()
{
    cout <<  "Press [SPACE] to continue." << endl;
    _pausedUntilSpaceIsPressed = true;
}

void Engine::play()
{
    setup();
    if (!_isLooping)
    {
        return;
    }

    int keyCode{ 0 };
    while (!_quit)
    {        
        if (_pausedUntilSpaceIsPressed)            
        {
            if (stdinHasData())
            { 
                keyCode = std::cin.get();
                if (keyCode == ' ')
                {
                    _pausedUntilSpaceIsPressed = false;
                }
                
            }
        }
        else 
        {

            
        
            if (stdinHasData()) 
            {            
                keyCode = std::cin.get();
                cout << endl;
                keyPressed(keyCode);       
                if (_pausedUntilSpaceIsPressed)
                {
                    continue;
                }         
            }
            
            // reset translation
            _xo = 0;
            _yo = 0;
            _strokeSymbol = BLOCK;       
            _isFill = false;     
            draw();
            render();
            if (_description.size())
            {
                cout << "SCREEN READER: " << _description << endl;
            }            
            console();
            cout.flush();

        }
                
        sleep(100);
    }
}

void Engine::sleep(int milliseconds)
{
     this_thread::sleep_for(chrono::milliseconds(milliseconds));
}


//  returns a random number from 0 up to (but not including) the number.
int random(int n)
{    
    return (rand() % n);
}

// returns a random number from the first argument up to 
// (but not including) the second argument.
int random(int a, int b)
{
    return (rand() % (b - a)) + a;
}

string random(vector<string> choices)
{
    int i = random(choices.size());
    return choices[i];
}