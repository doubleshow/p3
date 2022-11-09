#include "engine.h"

class RecursiveNumbers : public Engine
{
    void setup()
    {
        createCanvas(60,10);         
        redraw();
        noLoop();
    }

    void branch(int n, int x, int y)
    {     
        if (n > 2)
        {            
            text(to_string(n), x, y);

            // text(to_string(n/2), x + n/8, y + 1);
            // text(to_string(n/2), x - n/8, y + 1);

            branch(n/2, x + n/8, y + 1);
            branch(n/2, x - n/8, y + 1);
        }        
    }

    void draw()
    {                
        branch(128, 30, 0);
    }

};

class RecursiveTrees : public Engine
{
    void setup()
    {
        createCanvas(50, 20);
        redraw();
        noLoop();
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

class RecursiveBlocks : public Engine
{
    void setup()
    {
        createCanvas(50, 33);
        redraw();
        noLoop();
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

class Fibonacci : public Engine
{
    void setup()
    {
        createCanvas(35, 10);

        fv(6,20,0);
        redraw();
        noLoop();
    }

    int f(int n)
    {
        if (n == 1 || n == 0)
        {
            return n;
        }
        else
        {
            return f(n - 1) + f(n - 2);
        }
    }

    int fv(int n, int x, int y)
    {
        if (n == 1 || n == 0)
        {
            text("f(" + to_string(n) + ")=1", x, y);            
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
            
            return v;
        }
    }

};

int main()
{
    Menu menu;
    menu.add(new RecursiveNumbers(), "Numbers");       
    menu.add(new RecursiveTrees(), "Trees");
    menu.add(new RecursiveBlocks(), "Blocks");       
    menu.add(new Fibonacci(), "Fibonacci");       
    menu.play();
    return 0;
}