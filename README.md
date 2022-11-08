# p3 - A simple game engine for the "Project 3"

Author:

Tom Yeh\
Associate Professor\
Department of Computer Science

## Supported Environments
VSCode on coding.csel.io

(other platforms have not been tested yet)

## Quick Start
Compile and run examples:
```bash
$ g++ engine.cpp examples.cpp
$ ./a.out
```

## Hello World
```c++
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

```
p3 Engine 1.0
    0 1 2 3 4 5 6 7 8 9
  ┌────────────────────┐
 0│Hello World         │
 1│                    │
  └────────────────────┘
```

## Point
```c++
class PointExampleReadme : public Engine
{
    void setup()
    {
        createCanvas(10,10);
    }

    void draw()
    {
        point(1, 1);

        stroke("->");
        point(3, 3);

        stroke("🌲");
        point(5, 5);
    }
};
```

```
p3 Engine 1.0
    0 1 2 3 4 5 6 7 8 9
  ┌────────────────────┐
 0│                    │
 1│  ██                │
 2│                    │
 3│      ->            │
 4│                    │
 5│          🌲        │
 6│                    │
 7│                    │
 8│                    │
 9│                    │
  └────────────────────┘
```

## Animation

```c++
class Game : public Engine
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
    }
};

int main()
{
    Game game;
    game.play();
}
```

![animation-example.gif](animation-example.gif)
