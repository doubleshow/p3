#ifndef MAPGAME_H
#define MAPGAME_H

#include <iostream>

using namespace std;

class Map
{
private:
    const char UNEXPLORED = '-'; // marker for unexplored spaces
    const char EXPLORED = ' ';   // marker for explored spaces
    const char ROOM = 'R';       // marker for room locations
    const char NPC = 'N';        // marker for NPC locations
    const char PARTY = 'X';      // marker for party position
    const char EXIT = 'E';       // marker for dungeon exit

    static const int num_rows_ = 12; // number of rows in map
    static const int num_cols_ = 12; // number of columns in map
    static const int max_npcs_ = 5;  // max non-player characters
    static const int max_rooms_ = 5; // max number of rooms

    int player_position_[2];              // player position (row,col)
    int dungeon_exit_[2];                 // exit location of the dungeon
    int npc_positions_[max_npcs_][3];     // stores the (row,col) positions of NPCs present on map and if they have been found
    int room_positions_[max_rooms_][2];   // stores the (row,col) positions of rooms present on map
    char map_data_[num_rows_][num_cols_]; // stores the character that will be shown at a given (row,col)

    int npc_count_;  // stores number of misfortunes currently on map
    int room_count_; // stores number of sites currently on map
public:
    Map();

    void resetMap();

    // getters
    int getPlayerRow();
    int getPlayerCol();
    int getDungeonExitRow();
    int getDungeonExitCol();
    int getRoomCount();
    int getNPCCount();
    int getNumRows();
    int getNumCols();
    bool isOnMap(int row, int col);
    bool isNPCLocation(int row, int col);
    bool isRoomLocation(int row, int col);
    bool isExplored(int row, int col);
    bool isFreeSpace(int row, int col);
    bool isDungeonExit(int row, int col);

    // setters
    void setPlayerPosition(int row, int col);
    void setDungeonExit(int row, int col);

    // other
    void displayMap();
    bool move(char);
    bool addNPC(int row, int col);
    bool addRoom(int row, int col);
    bool removeNPC(int row, int col);
    bool removeRoom(int row, int col);
    void exploreSpace(int row, int col);

    void displayMapDebug();
};

#include "engine.h"

class  MapGame : public Engine, public Map
{    
    protected:

    string ICON_ROOM = "R_";
    string ICON_GOAL = "E_";
    string ICON_PLAYER = "P_";
    string ICON_UNEXPLORED = "--";
    string ICON_EXPLORED = "  ";

    void draw()
    {
        stroke(ICON_UNEXPLORED);
        fill(ICON_UNEXPLORED);
        rect(0,0,12,12);

        int ey = getDungeonExitRow();
        int ex = getDungeonExitCol();
        stroke(ICON_GOAL);
        point(ex, ey);

        for (int i = 0 ; i < getNumRows() ; i++)
        {
            for (int j = 0 ; j < getNumCols() ; j++)
            {
                if (isRoomLocation(i, j))
                {
                    stroke(ICON_ROOM);
                    point(j, i);
                }
                
                if (isExplored(i, j))
                {
                    stroke(ICON_EXPLORED);                    
                    point(j, i);
                }                   
            }
        }

        int y = getPlayerRow();
        int x = getPlayerCol();
        stroke(ICON_PLAYER);
        point(x, y);
    }

};

#endif