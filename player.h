#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdbool.h>

#include "grid.h"
#include "ship.h"

/**
 * Enumeration of possible results from attempting a shot.
 */
typedef enum {
    Invalid,
    Miss,
    Hit,
    HitAndDestroyed,
} shot_res_t;

/**
 * Structure holding state information for a player.
 */
typedef struct {
    grid_t* grid; // Grid with ships placed and enemy shots
    int8_t last_x;
    int8_t last_y;
    ship_t* ships;
    uint8_t ship_count;
    bool cpu;
} player_t;


/**
 * Generate a new player using a new grid and a copy of the provided ship list.
 *
 * @param  player     Pointer to player to update 
 * @param  width      Width of grid to generate
 * @param  height     Height of grid to generate
 * @param  ships      List of ships to copy to player
 * @param  ship_count Number of ships to place
 */
void make_player(player_t* player, uint8_t width, uint8_t height, ship_t ships[], uint8_t ship_count);

/**
 * Free all memory used by player, this will stop the player being usable.
 *
 * @param player Player for which to free
 */
void free_player(player_t* player);

/**
 * Check if all player's ships are destroyed.
 * 
 * @param  player Player to check
 * @return        Whether all ships are destroyed
 */
bool is_player_destroyed(player_t* player);

/**
 * Shoot at a player grid using the given x, y coordinates. The players ship
 * states will be updated in line with the grid.
 * 
 * @param  target Player to target with shot
 * @param  x      x coordinate to target
 * @param  y      y coordinate
 * @return        Return code reflecting result of shot
 */
shot_res_t shoot_pos(player_t* target, int8_t x, int8_t y);

#endif // PLAYER_H