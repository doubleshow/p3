#include "MapGame.h"

using namespace std;

Map::Map()
{
    resetMap();
}

/*
 * Algorithm: Resets positions of player, NPCs, and rooms and clears map_data_
 * Set Player position coordinates to 0
 * Set npc_count_ to false
 * Set room_count_ to 0
 * loop i from 0 to max_npcs_
 *      Set row and col of location to -1
 * loop i from 0 to max_rooms
 *      Set row and col of room location to -1
 * loop i from 0 to num_rows_
 *      loop j from 0 to num_cols_
 *          Set (i,j) location on map_data_ to '-'
 * Parameters: none
 * Return: nothing (void)
 */
void Map::resetMap()
{
    // resets player position, count values, and initializes values in position arrays to -1
    player_position_[0] = 0;
    player_position_[1] = 0;

    // set dungeon exit
    dungeon_exit_[0] = num_rows_ - 1;
    dungeon_exit_[1] = num_cols_ / 2;

    for (int i = 0; i < max_npcs_; i++)
    {
        npc_positions_[i][0] = -1;
        npc_positions_[i][1] = -1;
    }
    npc_count_ = 0;

    for (int i = 0; i < max_rooms_; i++)
    {
        room_positions_[i][0] = -1;
        room_positions_[i][1] = -1;
    }
    room_count_ = 0;

    for (int i = 0; i < num_rows_; i++)
    {
        for (int j = 0; j < num_cols_; j++)
        {
            map_data_[i][j] = UNEXPLORED;
        }
    }
    map_data_[dungeon_exit_[0]][dungeon_exit_[1]] = EXIT;
}

// return player's row position
int Map::getPlayerRow()
{
    return player_position_[0];
}

// return player's column position
int Map::getPlayerCol()
{
    return player_position_[1];
}

// return current room count
int Map::getRoomCount()
{
    return room_count_;
}

// return dungeon exit row
int Map::getDungeonExitRow()
{
    return dungeon_exit_[0];
}

// return dungeon exit col
int Map::getDungeonExitCol()
{
    return dungeon_exit_[1];
}

// set player position, if in range
void Map::setPlayerPosition(int row, int col)
{
    if (isOnMap(row, col))
    {
        player_position_[0] = row;
        player_position_[1] = col;
    }
}

// set dungeon exit position, if in range
void Map::setDungeonExit(int row, int col)
{
    if (isOnMap(row, col))
    {
        dungeon_exit_[0] = row;
        dungeon_exit_[1] = col;
    }
}

// returns member variable num_rows_
int Map::getNumRows()
{
    return num_rows_;
}

// returns member variable num_cols_
int Map::getNumCols()
{
    return num_cols_;
}

/*
 * @brief Checks if the given (row, col) position is on the map
 *
 * Algorithm:
 *  if 0 <= row < num_rows_ and 0 <= col < num_cols_:
 *      return true
 *  else:
 *      return false
 *
 * Parameters: row (int), col (int)
 * Returns: bool
 */
bool Map::isOnMap(int row, int col)
{
    if (0 <= row && row < num_rows_ && 0 <= col && col < num_cols_)
    {
        return true;
    }
    return false;
}

/*
 * Algorithm: Checks if the location is an NPC location
 * if (row, col) is not within the map boundaries
 *      return false
 * loop i from 0 to npc_count_
 *      if (row,col) is a npc location
 *          return true
 * return true
 * Parameters: row (int), col (int)
 * return false
 * Parameters: none
 * Return: boolean (bool)
 */
bool Map::isNPCLocation(int row, int col)
{
    if (!isOnMap(row, col))
    {
        return false;
    }
    for (int i = 0; i < npc_count_; i++)
    {
        if (row == npc_positions_[i][0] && col == npc_positions_[i][1])
        {
            return true;
        }
    }
    return false;
}

/*
 * Algorithm: Checks if the location is an room location
 * if (row, col) is not within the map boundaries
 *      return false
 * loop i from 0 to room_count_
 *      if (row,col) is a room location
 *          return true
 * return true
 * Parameters: row (int), col (int)
 * return false
 * Parameters: none
 * Return: boolean (bool)
 */
bool Map::isRoomLocation(int row, int col)
{
    if (!isOnMap(row, col))
    {
        return false;
    }
    for (int i = 0; i < room_count_; i++)
    {
        if (row == room_positions_[i][0] && col == room_positions_[i][1])
        {
            return true;
        }
    }
    return false;
}

/*
 * Algorithm: Checks if the given row and column is an explored space
 * if (row, col) is not on the map:
 *     return false
 * if map_data_[row][col] is ' ':
 *     return true
 * if (row, col) is npc location and has been found:
 *     return true
 * else:
 *     return false
 */
bool Map::isExplored(int row, int col)
{
    if (!isOnMap(row, col))
    {
        return false;
    }
    if (map_data_[row][col] == EXPLORED)
    {
        return true;
    }
    for (int i = 0; i < npc_count_; i++)
    {
        if (npc_positions_[i][0] == row && npc_positions_[i][1] == col)
        {
            if (npc_positions_[i][2] == true)
            {
                return true;
            }
            break;
        }
    }
    return false;
}

/*
 * Algorithm: checks if (row, col) is dungeon_exit_
 *
 */
bool Map::isDungeonExit(int row, int col)
{
    if (row == dungeon_exit_[0] && col == dungeon_exit_[1])
    {
        return true;
    }
    return false;
}

/*
 * Algorithm: Checks if the given row and column on map is a free space
 * if row and column is not within the map boundaries
 *      return false
 * if row and column is a npc location
 *      return false
 * if row and column is a room location
 *      return false
 * if row and column is the dungeon exit
 *      return false
 * return true
 *
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
bool Map::isFreeSpace(int row, int col)
{
    if (!isOnMap(row, col))
    {
        return false;
    }
    if (isNPCLocation(row, col))
    {
        return false;
    }
    if (isRoomLocation(row, col))
    {
        return false;
    }
    if (isDungeonExit(row, col))
    {
        return false;
    }
    return true;
}

/*
 * Algorithm: Create an NPC on the map
 * if npc is present on map
 *      return false
 * if (row,col) is not a free space
 *      return false
 * store row and col values in npcPosition array
 * mark NPC as hidden
 * set (row,col) value in map_data_ to 'N'
 * increment npc_count_
 * return true
 *
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
bool Map::addNPC(int row, int col)
{
    if (npc_count_ >= max_npcs_)
    {
        return false;
    }
    if (!isFreeSpace(row, col))
    {
        return false;
    }

    npc_positions_[npc_count_][0] = row;
    npc_positions_[npc_count_][1] = col;
    npc_positions_[npc_count_][2] = false;
    map_data_[row][col] = NPC;
    npc_count_++;
    return true;
}

/*
 * Algorithm: Create a room on the map
 * if room_count_ is more than or equal to number of rooms
 *      return false
 * if (row,col) is not a free space
 *      return false
 * if next row in room_positions_ matrix is -1 -1
 *      store row, col and type values in the current row of room_positions_ matrix
 *      increment room_count_
 *      Set (row,col) value in map_data_ to 'R'
 *      return true
 *
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
bool Map::addRoom(int row, int col)
{

    if (room_count_ >= max_rooms_)
    {
        return false;
    }

    // location must be blank to spawn
    if (!isFreeSpace(row, col))
    {
        return false;
    }

    room_positions_[room_count_][0] = row;
    room_positions_[room_count_][1] = col;
    room_count_++;
    map_data_[row][col] = ROOM;
    return true;
}

/*
 * Algorithm: Removes the NPC at (row, col) from the map
 * loop i from 0 to npc_count_
 *      if npc_position[i] is (row, col)
 *          swap npc_position[npc_count_-1] with npc_position[i]
 *          reset npc_position[npc_count_-1][0] and npc_position[npc_count_-1][1] to -1
 *          reset npc_position[npc_count_-1][2] to 0
 *          decrement npc_count_
 *          set map data at (row, col) to explored
 *          return true
 * return false
 *
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
bool Map::removeNPC(int row, int col)
{
    for (int i = 0; i < npc_count_; i++)
    {
        if (npc_positions_[i][0] == row && npc_positions_[i][1] == col)
        {
            // swap i'th npc with last npc
            npc_positions_[i][0] = npc_positions_[npc_count_ - 1][0];
            npc_positions_[i][1] = npc_positions_[npc_count_ - 1][1];
            npc_positions_[i][2] = npc_positions_[npc_count_ - 1][2];
            // reset last npc
            npc_positions_[npc_count_ - 1][0] = -1;
            npc_positions_[npc_count_ - 1][1] = -1;
            npc_positions_[npc_count_ - 1][2] = false;
            // decrement npc_count_
            npc_count_--;
            // set map data to explored
            map_data_[row][col] = EXPLORED;
            return true;
        }
    }
    return false;
}

/*
 * Algorithm: Removes the room at (row, col) from the map
 * loop i from 0 to room_count_
 *      if room_position[i] is (row, col)
 *          swap room_position[room_count_-1] with room_position[i]
 *          reset room_position[room_count_-1][0] and room_position[room_count_-1][1] to -1
 *          decrement room_count_
 *          set map data at (row, col) to explored
 *          return true
 * return false
 *
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
bool Map::removeRoom(int row, int col)
{
    for (int i = 0; i < room_count_; i++)
    {
        if (room_positions_[i][0] == row && room_positions_[i][1] == col)
        {
            // swap i'th room with last room
            room_positions_[i][0] = room_positions_[room_count_ - 1][0];
            room_positions_[i][1] = room_positions_[room_count_ - 1][1];
            // reset last room
            room_positions_[room_count_ - 1][0] = -1;
            room_positions_[room_count_ - 1][1] = -1;
            // decrement room_count_
            room_count_--;
            // set map data to explored
            map_data_[row][col] = EXPLORED;
            return true;
        }
    }
    return false;
}

/*
 * Algorithm: Mark (row, col) as explored, either revealing NPC or empty space
 * if (row, col) is NPC location
 *      mark npc at player_position_ as found
 * else if (row, col) is a free space
 *      mark space as explored in map data
 *
 * Parameters: row (int), col (int)
 * Return: boolean (bool)
 */
void Map::exploreSpace(int row, int col)
{
    for (int i = 0; i < npc_count_; i++)
    {
        if (row == npc_positions_[i][0] && col == npc_positions_[i][1])
        {
            // mark NPC as found
            npc_positions_[i][2] = 1;
            return;
        }
    }
    if (isFreeSpace(row, col))
    {
        map_data_[player_position_[0]][player_position_[1]] = EXPLORED;
    }
}

/*
 * Algorithm: Make the player move based on the given command
 * if user inputs w and if its not the top row of the map
 *      Move the player up by one row
 * if user inputs s and if its not the bottom row of the map
 *      Move the player down by one row
 * if user inputs a and if its not the leftmost column
 *      Move the player left by one column
 * if user inputs d and if its not the rightmost column
 *      Move the player right by one column
 * if player moved
 *      if new location is an NPC location
 *          mark new location as explored
 *      return true
 * else
 *      return false
 *
 * Parameters: direction (char)
 * Return: boolean (bool)
 */
bool Map::move(char direction)
{
    // check input char and move accordingly
    switch (tolower(direction))
    {
    case 'w': // if user inputs w, move up if it is an allowed move
        if (player_position_[0] > 0)
        {
            player_position_[0] -= 1;
        }
        else
        {
            return false;
        }
        break;
    case 's': // if user inputs s, move down if it is an allowed move
        if (player_position_[0] < num_rows_ - 1)
        {
            player_position_[0] += 1;
        }
        else
        {
            return false;
        }
        break;
    case 'a': // if user inputs a, move left if it is an allowed move
        if (player_position_[1] > 0)
        {
            player_position_[1] -= 1;
        }
        else
        {
            return false;
        }
        break;
    case 'd': // if user inputs d, move right if it is an allowed move
        if (player_position_[1] < num_cols_ - 1)
        {
            player_position_[1] += 1;
        }
        else
        {
            return false;
        }
        break;
    default:
        return false;
    }
    // if new location is an NPC location, mark as explored
    if (isNPCLocation(player_position_[0], player_position_[1]))
    {
        exploreSpace(player_position_[0], player_position_[1]);
    }
    return true;
}

/*
 * Algorithm: This function prints a 2D map in the terminal.
 * Loop i from 0 to number of rows
 *      Loop j from 0 to number of columns
 *          if player position is at (i,j)
 *              print 'X'
 *          else if npc is at (i,j)
 *              if npc has been found:
 *                  print 'N'
 *              else
 *                  print '-'
 *          else
 *              print the value of (i,j) in map_data_
 *
 * Parameters: none
 * Return: nothing (void)
 */
void Map::displayMap()
{
    for (int i = 0; i < num_rows_; i++)
    {
        for (int j = 0; j < num_cols_; j++)
        {
            if (player_position_[0] == i && player_position_[1] == j)
            {
                cout << PARTY;
            }
            else if (map_data_[i][j] == 'N')
            { // NPC location, have to check if they were found yet
                for (int k = 0; k < npc_count_; k++)
                {
                    if (npc_positions_[k][0] == i && npc_positions_[k][1] == j)
                    {
                        if (npc_positions_[k][2] == true)
                        {
                            cout << NPC;
                        }
                        else
                        {
                            cout << UNEXPLORED;
                        }
                    }
                }
            }
            else
            {
                cout << map_data_[i][j];
            }
        }
        cout << endl;
    }
}

#include <iomanip>
void Map::displayMapDebug()
{    
    cout << " ";
    for (int i = 0; i < num_rows_; i++)
    {
        cout << setw(5) << i;
    }
    cout << endl;

    for (int i = 0; i < num_rows_; i++)
    {
        cout << setw(2) << i << ": ";

        for (int j = 0; j < num_cols_; j++)
        {
            if (player_position_[0] == i && player_position_[1] == j)
            {
                cout << PARTY;
            }
            else if (map_data_[i][j] == 'N')
            { // NPC location, have to check if they were found yet
                for (int k = 0; k < npc_count_; k++)
                {
                    if (npc_positions_[k][0] == i && npc_positions_[k][1] == j)
                    {
                        if (npc_positions_[k][2] == true)
                        {
                            cout << NPC;
                        }
                        else
                        {
                            cout << UNEXPLORED;
                        }
                    }
                }
            }
            else
            {
                cout << map_data_[i][j];
            }
            

            cout << "[" << map_data_[i][j] << "] ";
        }
        cout << endl;
    }
}