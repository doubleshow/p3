#include "engine.h"
#include <vector>


class ShootGame : public Engine
{    
    int x = 0;
    int y = 0;
    int dx = 1;
    int dy = 0;
    
    void setup()
    {
        createCanvas(30,10); 
    }

    void keyPressed(int keyCode)
    {
        switch (keyCode)
        {
            case 'd':        
                dx = 1;
                dy = 0;
                break;

            case 'a':
                dx = -1;
                dy = 0;
                break;

            case 'w':
                dx = 0;
                dy = -1;
                break;

            case 's':
                dx = 0;
                dy = 1;
                break;
        }
    }

    void draw()
    {
        clear();
        stroke("$$");
        point(29, 5);

        stroke("->");
        point(x, y);
    }

    void console()
    {
        cout << "Try to control the arraw to shoot the target" << endl;          
        if (x == 29 && y == 5)
        {
            cout << "You hit the target!" << endl;            
            quit();
        }

        x = x + dx;
        y = y + dy;
    }

};


class ExploreGame : public Engine
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
        stroke("_?");
        point(5, 5);       

        stroke("_?");
        point(3, 6);

        stroke("👮");
        point(x, y); 

        describe("A police man. Two question marks.");
    }

    void console()
    {
        if (x == 5 && y == 5)
        {
            cout << "You found a criminal." << endl;
            x = 6;             
            pause();
        }
        else if (x == 3 && y == 6)
        {
            cout << "You found a lost child." << endl;
            x = 4;
            pause();
        }
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

class PaintGame : public Engine
{    
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
    }

    void draw()
    {                
        point(x, y);
    }

    void console()
    {
        cout << "(" << x << "," << y << ")" << endl;
    }

};





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

class PointExample : public Engine
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

class LineExample : public Engine
{
    void setup()
    {
        createCanvas(10,10);
    }

    void draw()
    {
        vertical_line(1, 2, 5);
        vertical_line(3, 2, 5);
        vertical_line(5, 2, 5);

        horizontal_line(3, 0, 5);
        horizontal_line(5, 0, 5);
        horizontal_line(7, 0, 5);

        describe("Three vertical lines and three horizontal lines.");
    }
};

class RectExample1 : public Engine
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

class RectExample2 : public Engine
{
    void setup()
    {
        createCanvas(20,10);
    }

    void draw()
    {
        fill("**");
        rect(0, 0, 4, 4);

        rect(7, 3, 4, 4);
        
        rect(15, 2, 5, 5);

        describe("Three rectangules filled with *.");
    }
};

class RectExample3 : public Engine
{
    void setup()
    {
        createCanvas(20,10);
    }

    void draw()
    {
        stroke("🌻");
        fill("🌲");
        rect(0, 0, 6, 8);

        stroke("🌹");
        rect(7, 3, 7, 4);

        noFill();
        rect(15, 2, 5, 5);

        describe("Two rectangular areas of trees surrounded by sunflowers. One rectangular empty area surrounded by flowers.");
    }
};

class MoveExample1 : public Engine
{
    int x;

    void setup()
    {
        x = 0;        
        createCanvas(30, 10);
    }

    void draw()
    {
        clear();
        point(x, 0);
        x = x + 1;        

        describe("A point moves horizontally to the right.");
    }
};

class MoveExample2 : public Engine
{
    int x1;
    int x2;

    void setup()
    {
        x1 = 0;
        x2 = 0;
        createCanvas(30, 5);        
    }

    void draw()
    {
        clear();
        point(x1, 0);
        x1 += 1;
        point(x2, 2);     
        x2 += 2;

        describe("Two points move horizontally at different speeds.");
    }
};

class KeyPressedExample1 : public Engine
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

        describe(string("A point is at (") + to_string(x) + "," + to_string(y) + ")");
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

class KeyPressedExample2 : public Engine
{
    void setup()
    {
        createCanvas(10, 10);
    }

    void draw()
    {
        clear();
        text("Press (Q) to Quit.",0,0);
    }

    void keyPressed(int keyCode)
    {
        switch (keyCode)
        {
            case 'q':
            case 'Q':        
                quit();
                break;
        }
    }
};

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
        horizontal_line(6, 2, 8);
    }
};

class ConsoleInputExample : public Engine
{
    int numTrees = 0;
    int numFlowers = 0;

    void setup()
    {
        createCanvas(10, 10);
    }

    void draw()
    {
        clear();
        stroke("🌲");
        horizontal_line(2, 0, numTrees);

        stroke("🌻");
        horizontal_line(4, 0, numFlowers);

        describe("A line of trees and a line of sun flowers");
    }

    void console()
    {
        string s;
        cout << "How many trees? ";
        cin >> s;
        numTrees = stoi(s);        
        cout << "How many flowers? ";
        cin >> s;        
        numFlowers = stoi(s);
    }
};

class ResizeCanvasExample : public Engine
{
    int size;        
    void setup()
    {
        createCanvas(10, 10);
    }

    void draw()
    {
        clear();
        
    }

    void keyPressed(int keyCode)
    {
        switch (keyCode)
        {
            case '1':        
                resizeCanvas(10, 10);        
                break;

            case '2':
                resizeCanvas(15, 15);        
                break;

            case '3':
                resizeCanvas(20, 20);
                break;
        }
    }
};



class RandomExample1 : public Engine
{
    void setup()
    {
        createCanvas(30, 5);
    }

    void draw()
    {
        clear();
        for (int i = 0; i < 5; i++) {
            int r = random(15);            
            horizontal_line(i, 0, r);
        }
        describe("Five lines with constantly changing lengths, aligned to the left.");
    }
};

class RandomExample2 : public Engine
{
    vector<string> choices{"rock", "paper", "scissor"};

    void setup()
    {
        createCanvas(30, 5);
    }

    void draw()
    {
        clear();        
        string c = random(choices);
        text(c, 0, 0);
        describe(c);
    }
};

class RandomExample3 : public Engine
{
    void setup()
    {
        createCanvas(30, 5);
    }

    void draw()
    {
        clear();
        for (int i = 0; i < 5; i++) {
            int r = random(-5, 5);
            horizontal_line(i, 10 + r, 10 + r + 10);
        }
        describe("Five lines with constantly changing lengths.");
    }
};

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

class TranslateExample1 : public Engine
{
    void setup()
    {
        createCanvas(15, 15);
    }

    void draw_box()
    {
        rect(0, 0, 3, 3);
        text("Hi", 1, 1);
    }

    void draw()
    {
        draw_box(); // Draw a box at original 0,0
        
        translate(5, 5);
        draw_box(); // Draw a box at new 0,0
        
        // Translations are cumulative. For example,
        // calling translate(2,2)  and translate(3,3)
        // is equivalent to calling translate(5,5)        
        translate(2, 2);
        translate(3, 3);
        draw_box(); // Draw a box at new 0,0        
    }
};

class TranslateExample2 : public Engine
{
    int x = 0;

    void setup()
    {
        createCanvas(15, 15);
    }

    void draw_box()
    {
        rect(0, 0, 3, 3);
        text("Hi", 1, 1);
    }

    void draw()
    {        
        // the transformation is reset when the loop begins again.

        clear();
        translate(x, 0);
        draw_box();
        x = x + 1;

        describe("A box is moving horizontally.");
    }
};


class RecursionExample1 : public Engine
{
    void setup()
    {
        createCanvas(50, 20);
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

            branch(x1, y+4, size/2);
            branch(x2, y+4, size/2);
        }        
    }

    void draw()
    {        
        branch(25, 0, 30);
    }

};

class RecursionExample2 : public Engine
{
    void setup()
    {
        createCanvas(50, 33);
    }

    void branch(int x, int y, int size, int levels)
    {     
        if (levels <4)
        {            
            rect(x, y, size, size);
            
            int x1 = x + 1;
            int x2 = x + size/2;
            int y1 = y + 1;
            int y2 = y + size/2;
            int s = size/2-1;
            stroke("🌻");
            branch(x1, y1, s, levels+1);
            stroke("🌲");
            branch(x2, y1, s, levels+1);
            stroke("🌹");
            branch(x1, y2, s, levels+1);
            stroke("🌴");
            branch(x2, y2, s, levels+1);            
        }        
    }

    void draw()
    {        
        stroke("🏠");
        branch(0, 0, 32, 0);
    }

};

class MenuExample : public Engine
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

// class PointExampleReadme : public Engine
// {
//     int x = 0;    
//     void setup()
//     {
//         createCanvas(10,10);
//     }

//     void draw()
//     {
//         clear();
//         point(x, 0);        
//         if (x == 10)
//         {
//             x = 0;
//         }
//         else
//         {
//             x++;
//         }
//     }
// };

int main()
{
    MenuExample game;        
    
    // Games
    game.add(new PaintGame(), "PaintGame");
    game.add(new ExploreGame(), "ExploreGame");
    game.add(new ShootGame(), "ShootGame");

    // Basic Examples
    game.add(new HelloWorld(), "HelloWorld");
    game.add(new LineExample(), "LineExample");
    game.add(new PointExample(), "PointExample");
    game.add(new StrokeExample(), "StrokeExample");
    game.add(new RectExample1(), "RectExample1");
    game.add(new RectExample2(), "RectExample2");
    game.add(new RectExample3(), "RectExample3");    
    game.add(new MoveExample1(), "MoveExample1");
    game.add(new MoveExample2(), "MoveExample2");        
    game.add(new KeyPressedExample1(), "KeyPressedExample1");
    game.add(new KeyPressedExample2(), "KeyPressedExample2");
    game.add(new StrokeExample(), "StrokeExample");
    game.add(new RandomExample1(), "RandomExample1");
    game.add(new RandomExample2(), "RandomExample2");
    game.add(new RandomExample3(), "RandomExample3");    
    game.add(new ResizeCanvasExample(), "ResizeCanvasExample"); 
    game.add(new BackgroundExample(), "BackgroundExample");
    game.add(new TranslateExample1(), "TranslateExample1");
    game.add(new TranslateExample2(), "TranslateExample2");
    game.play();

    return 0;
}