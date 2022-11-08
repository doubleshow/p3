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