# p3 - A simple game engine for the "Project 3"

Author:

Tom Yeh\
Associate Professor\
Department of Computer Science

## Supported Environments
VSCode on [coding.csel.io](https://coding.csel.io/)

(other platforms have not been tested yet)

## Quick Start
Compile and run examples:
```bash
$ g++ engine.cpp examples.cpp
$ ./a.out
```

## Hello World

![helloworld](images/helloworld.png)

```c++
#include "engine.h"
class HelloWorld : public Engine
{
    void setup()
    {
        createCanvas(10,2);
    }

    void draw()
    {
        text("Hello World", 0, 0);
    }
};

int main()
{
    HelloWorld game;
    game.play();
    return 0;
}
```



# Basic Examples

## Point

![4 points](images/4points.png)

```c++
class Points : public Engine
{
    void setup()
    {
        createCanvas(10,10);
    }

    void draw()
    {
        point(1, 1);
        point(3, 3);
        point(5, 5);
        point(7, 7);        

        describe("Four points.");
    }
};
```


## Vertical/Horizontal Lines
![grid](images/grid.png)

```c++
class VerticalHorizontalLines : public Engine
{
    void setup()
    {
        createCanvas(10,10);
    }

    void draw()
    {
        vertical_line(1, 2, 9);
        vertical_line(3, 2, 9);
        vertical_line(5, 2, 9);

        horizontal_line(3, 0, 7);
        horizontal_line(5, 0, 7);
        horizontal_line(7, 0, 7);

        describe("Three vertical lines and three horizontal lines.");
    }
};
```

## Line

![diagonals](images/diagonals.png)
```c++
class Diagonals : public Engine
{
    void setup()
    {
        createCanvas(10,10);
    }

    void draw()
    {
        line(0,0,9,9);
        line(9,0,0,9);
    }
};
```

![rays](images/rays.png)

```c++
class Rays : public Engine
{
    void setup()
    {
        createCanvas(31,31);
    }

    void draw()
    {
        for (int i = 0 ; i <= 30; i = i + 5)
        {
            stroke("<<");
            line(0, i, 15, 15);            
            stroke(">>");
            line(30, i, 15, 15);
            stroke("MM");
            line(i, 0, 15, 15);
            stroke("WW");
            line(i, 30, 15, 15);
        }
        stroke("OO");
        point(15,15);
    }
};
```

## Rect

![rects](images/rects.png)

```c++
class RectExample : public Engine
{
    void setup()
    {
        createCanvas(20,10);
    }

    void draw()
    {
        rect(0, 0, 4, 4);

        rect(7, 3, 4, 4);
        
        rect(15, 2, 5, 5);

        describe("Three rectangules.");
    }
};

```
## Stroke

![stroke example](images/stroke.png)

* A stroke symbol is a two character string, such as `"->"`.
* A stroke symbol can be a unicode graphical symbol. Some are already two character wide, such as `"🌲"`. You can use a search engine like the [Unicode Table](https://unicode-table.com/en/) to find a symbol you want and copy/paste it into your code. Some are single character and you need to include two, such as `"★★"`.

```c++
class StrokeExample : public Engine
{
    void setup()
    {
        createCanvas(10, 10);
    }

    void draw()
    {
        clear();

        stroke("->");
        point(1, 1);         
        horizontal_line(5, 2, 8);

        stroke("🌲");
        point(1, 2); 
        horizontal_line(6, 2, 8);

        stroke("★★");
        point(1, 3); 
        horizontal_line(7, 2, 8);        
    }
};
```

## Background

![background](images/background.png)

```c++
class BackgroundExample : public Engine
{
    void draw()
    {
        background("xx");        
        point(3, 3);
        point(5, 5);
        describe("Two points against a background filled by x's.");
    }
};

```
# Animation Examples

## Example: Changing Location

![move example](images/move-example.gif)

```c++
class PointAnimation : public Engine
{
    int x = 0;    
    void setup()
    {
        createCanvas(10,10);
    }

    void draw()
    {
        clear();
        point(x, 0);        
        if (x == 10)
        {
            x = 0;
        }
        else
        {
            x++;
        }

        describe("A point moving horizontally across the canvas.")
    }
};
```

## Example: Changing Size

![box exmaple](images/animation-box.gif)

```c++
class RectAnimation : public Engine
{
    int s;
    int ds;
    
    void setup()
    {
        s = 0;    
        ds = 1;
        createCanvas(10, 10);        
    }

    void draw()
    {
        clear();
        rect(0,0,s,s);
        // if the size reaches the max
        if (s == 10)
        {
            // decrease
            ds = -1;
        }
        // else if the size reaches the min
        else if (s == 0)
        {
            // increase
            ds = 1;
        }
        // update the rectangle's size
        s = s + ds;

        describe("A box is expanding and then shrinking in size.");
    }
};
```

## Example: Scrolling Text

![scroll text](images/scroll-text.gif)

```c++
class ScrollingTextExample : public Engine
{
    string message = "This is a really long message to display.";

    // offset in the x direction to implement the scrolling effect
    int offset = 0;

    void setup()
    {
        createCanvas(10, 2);
    }

    void draw()
    {
        // join two copies of the same message so that we can
        // have the tail of the message followed immeidately by
        // the head of the same message.
        string message2 = message + " " + message;

        // extract a substring that can fit inside the canvas        
        // because each x,y can display 2 characters, the 
        // toal number of characters we can fit is
        // 2 x getWidth();
        string fit = message2.substr(offset, 2 * getWidth());
        
        clear();
        text(fit, 0, 0);
        offset++;

        // wrap around if offset exceeds the size of the message
        // which can be achieved by taking the modulo of n where
        // n is the size of the message
        int n = message.size();
        offset = offset % message.size();
    }

};
```

## Example: Random Fill

![random fill](images/random-fill.gif)

```c++
class RandomFill : public Engine
{
    // 2d array to keep track of whether a location is filled
    // 0: unfilled, 1: filled
    int filled[8][8] = {0};
    void setup()
    {
        createCanvas(8, 8);        
    }

    void draw()
    {
        int x;
        int y;

        // randomly draw a location (x,y) that has not
        // already been filled
        do
        {
            x = random(8);
            y = random(8);
        } while (filled[y][x] == 1);
        
        // draw a point at an unfilled location
        point(x,y);

        // mark the location as filled
        filled[y][x] = 1;
        
        describe("The screen is gradually filled up.");
    }
};
```

## Example: Scanning Line

![scan line](images/scanline.gif)


```c++
class ScanningLine : public Engine
{

    int y = 0;
    int dy = 1;
    void setup()
    {
        createCanvas(20,20);     
    }

    void draw()
    {
        clear();
        line(0,0,20,y);
        if (y == 20)
        {
            dy = -1;
        }
        else if (y == 0)
        {
            dy = 1;
        }
        y = y + dy;
    }
};
```

# User Input

## Keyboard

This example demonstrates how to handle keyboard events (i.e., when a user pressed a key) and updates the location of a point on the canvas.

```c++
class KeyPressedExample : public Engine
{
    int x;    
    int y;
    void setup()
    {
        x = 0;     
        y = 0; 
        createCanvas(10, 10);
    }

    void draw()
    {
        clear();
        point(x, y);        
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
};
```

## Menu

This example demonstrates how to enable the user to press a key to open up a simple menu.

![menu exmaple](images/menu-example.gif)

```c++
class MenuExample : public Engine
{
    bool isMenuOpen = false;

    void setup()
    {
        createCanvas(10,1);
    }

    void keyPressed(int keyCode)
    {
        switch (keyCode)
        {
            case 'x':
            case 'X':
                isMenuOpen = true;
                break;
        }
    }

    void console()
    {
        if (!isMenuOpen)
        {
            cout << "Press [X] to open the menu" << endl;
        }
        else
        {
            cout << "MENU" << endl;
            cout << "1. Open" << endl;
            cout << "2. Save" << endl;
            cout << "3. Quit" << endl;
            cout << "Choose one:";
            string choice;
            cin >> choice;
            if (choice == "1")
            {
                cout << "Opening the file" << endl;
                pause();
            }
            else if (choice == "2")
            {
                cout << "Saving the file" << endl;
                pause();
            }
            else if (choice == "3")
            {
                cout << "Quitting" << endl;
                cout << "Bye!" << endl;
                quit();
            }
            else
            {
                cout << "The option is invalid" << endl;
                pause();
            }
            isMenuOpen = false;
        }
    }

};
```

# Game Examples

## Chore Game
In this game, the player needs to visit two locations, a school and a bank, in order to complete two chores. Once both chores are completed, the player won the game. This example demonstrates how to check if the player arrives at a location, how to use `cin` and `cout` to implement an interactive dialog for the player to do the chore at that location, and how to use  use `boolean` variables as flags to keep track of the player's progress (i.e., whether or not the player has completed each mission).

![chore game](images/chore-game.gif)

Source code: [chore-game.cpp](chore-game.cpp)

Compile and run:
```
$ g++ engine.cpp chore-game.cpp
$ ./a.out
```

## Dog Game
In this game, the player is first prompted to choose the number of dogs to place on a map. Then, the player moves around the map toward the goal, trying not to run into any of the dogs roaming around. This example demonstrates how tp represent each dog as an object instance of the `Dog` class, how to handle collisons (i.e., the player is in the same location as one of the dogs) and how to trigger events (i.e., the player was bitten by a dog and lost).

![dog game](images/dog-game.gif)

Source code: [dog-game.cpp](dog-game.cpp)

Compile and run:
```bash
$ g++ engine.cpp dog-game.cpp 
$ ./a.out
```

## Chance Game
In this game, the player moves a vehicle around the map.
Each time the vehicle moves, there is a 1 in 10 chance the player
got pulled over by the police, and a 2 in 10 chance the player
ran over a pothole. This example demonstrates how you can 
trigger chance events in a game.

![chance game](images/chance-example.gif)

Source code: [chance-game.cpp](chance-game.cpp)

Complie and run:
```
$ g++ engine.cpp chance-game.cpp
$ ./a.out
```
## Maze Game
In this game, the player moves aroud in a maze to reach the goal. This game demonstrates how to read map data from a file and populate an internal 2D data structure, and draw individual map tiles (e.g., player, wall, empty space, goal, breadcrumb).

![maze game](images/maze-game.gif)

Souce code: [maze-game.cpp](maze-game.cpp)

Compile and run
```
$ g++ engine.cpp maze-game.cpp
$ ./a.out
```

## Room Game
In this game, the player explores different rooms to collect treasures and avoid monsters. This game demonstrates how to scroll a map that's larger than the screen, while centering on the player. It also demonstrates how to load a game map and draw individual tiles.


![room game](images/room-game.gif)

Souce code: [room-game.cpp](room-game.cpp)

Compile and run
```
$ g++ engine.cpp room-game.cpp
$ ./a.out
```

## Run Game
In this game, the player is running on a course  with obstacles and treasures. This game demonstrates how to generate a random game map filled with obstacles and treasures, and how to use `translate` to achieve the effect of scrolling the map vertically.

![run game](images/run-game.gif)

Souce code: [run-game.cpp](run-game.cpp)

Compile and run
```
$ g++ engine.cpp run-game.cpp
$ ./a.out
```



# Advanced Examples

## Recursive Tree

![recursive tree](images/recursive-tree.gif)

```c++
class RecursiveTrees : public Engine
{
    void setup()
    {
        createCanvas(50, 20);
        branch(25, 0, 30);
    }

    void branch(int x, int y, int size)
    {     
        if (size > 2)
        {            
            int x1 = x - size * 0.4;
            int x2 = x + size * 0.4;
            horizontal_line(y, x1, x2);
            vertical_line(x1, y+1, y+3);            
            vertical_line(x2, y+1, y+3);        

            redraw();
            sleep(300);    

            branch(x1, y+4, size/2);
            branch(x2, y+4, size/2);
        }        
    }
};
```

## Fibonacci
![Fibonacci](images/fibonacci.gif)
```c++
class Fibonacci : public Engine
{
    void setup()
    {
        createCanvas(35, 10);
        fv(6,20,0);
    }

    int fv(int n, int x, int y)
    {
        if (n == 1 || n == 0)
        {
            text("f(" + to_string(n) + ")=1", x, y);
            redraw();
            sleep(300);                        
            return n;
        }
        else
        {
            stroke("──");
            horizontal_line(y+1, x - 4, x + 4);
            stroke("─┴");
            point(x, y+1);

            int v =  fv(n - 1, x - 4, y + 1) + fv(n - 2, x + 4, y + 1);
            
            text("f(" + to_string(n) + ")=" + to_string(v), x, y);
            redraw();
            sleep(300);
            return v;
        }
    }

};
```