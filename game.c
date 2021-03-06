#include <stdlib.h>
#include "game.h"

#include "player.h"
#include "ship.h"

#define DEFAULT_GRID_WIDTH   (10)
#define DEFAULT_GRID_HEIGHT  (10)
#define DEFAULT_SHIP_COUNT   (5)

/** Global declarations of ship names */
const char* str_destroyer  = "Destroyer";
const char* str_submarine  = "Submarine";
const char* str_cruiser    = "Cruiser";
const char* str_battleship = "Battleship";
const char* str_carrier    = "Carrier";


void make_default_game(game_t* game) {
    // Initialise game properties
    uint8_t width  = DEFAULT_GRID_WIDTH;
    uint8_t height = DEFAULT_GRID_WIDTH;

    uint8_t ship_count = 5;
    ship_t ships[DEFAULT_SHIP_COUNT] = {
        {.name = str_destroyer,  .ref = 1, .length = 2, SHIP_DEFAULTS},
        {.name = str_submarine,  .ref = 2, .length = 3, SHIP_DEFAULTS},
        {.name = str_cruiser,    .ref = 3, .length = 3, SHIP_DEFAULTS},
        {.name = str_battleship, .ref = 4, .length = 4, SHIP_DEFAULTS},
        {.name = str_carrier,    .ref = 5, .length = 5, SHIP_DEFAULTS},
    };

    // Initialise game
    game->turn = PLAYER_ONE;
    game->shots = 0;
    game->player_one = malloc(sizeof(player_t));
    game->player_two = malloc(sizeof(player_t));

    make_player(game->player_one, width, height, ships, ship_count);    
    make_player(game->player_two, width, height, ships, ship_count);
}


void free_game(game_t* game) {
    free_player(game->player_one);
    free(game->player_one);

    free_player(game->player_two);
    free(game->player_two);
}


uint8_t get_player_idx(game_t* game, player_t* player) {
    if (game->player_one == player) {
        return PLAYER_ONE;
    }
    if (game->player_two == player) {
        return PLAYER_TWO;
    }
    return -1;
}


uint8_t next_player_idx(game_t* game) {
    switch (game->turn) {
    case (PLAYER_ONE):
        return PLAYER_TWO;
    case (PLAYER_TWO):
        return PLAYER_ONE;
    default:
        return -1;
    }
}


player_t* get_player(game_t* game, uint8_t player_idx) {
    switch (player_idx) {
    case (PLAYER_ONE):
        return game->player_one;
    case (PLAYER_TWO):
        return game->player_two;
    default:
        return NULL;
    }
}


player_t* get_current_player(game_t* game) {
    return get_player(game, game->turn);
}


player_t* get_next_player(game_t* game) {
    return get_player(game, next_player_idx(game));
}
