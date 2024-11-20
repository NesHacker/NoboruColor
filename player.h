/**
 * Player types and functions.
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include <stdint.h>
#include "timer.h"

/**
 * Denotes that the player is standing still.
 */
#define PLAYER_STANDING 0

/**
 * Denotes that the player is walking. Primarily used to determine the sprite
 * graphics to display when the player is in motion.
 */
#define PLAYER_WALKING  1

/**
 * Denotes that the player is moving fast enough to be considered "running".
 * Primarily used to determine the sprite graphics to display.
 */
#define PLAYER_RUNNING  2

/**
 * Denotes that the player is jumping. Used for sprite graphics selection.
 */
#define PLAYER_JUMPING  3

/**
 * Denotes that the player if pivoting (accelerating opposite of the current
 * horizontal velocity while not airbore). Primairily used for sprite selection.
 */
#define PLAYER_PIVOTING 4

/**
 * Denotes that the player is facing right. Note this is not the same thing as
 * the direction the player is moving.
 */
#define HEADING_RIGHT   0

/**
 * Denotes that the player is facing left.
 */
#define HEADING_LEFT    1

/**
 * Maximum walking speed in 8.8 fixed point.
 */
#define MAX_WALK_SPEED        0x180

/**
 * Maximum running speed in 8.8 fixed point.
 */
#define MAX_RUN_SPEED         0x280

/**
 * Initial jump speed in 8.8 fixed point.
 */
#define INITIAL_JUMP_SPEED    0x280

/**
 * How fast "gravity" affects a jump when the player is "slow falling". Slow
 * falls occur for up to 24 frames while the player is holding the A button
 * after a jump. Denoted in 8.8 fixed point.
 */
#define FALL_SLOW_ACCEL       0x10

/**
 * How fast "gravity" is when the player is "fast falling". Denoted in 8.8
 * fixed point.
 */
#define FALL_FAST_ACCEL       0x50

/**
 * Maximum fall speed for the player in 8.8 fixed point.
 */
#define MAX_FALL_SPEED        0x400

/**
 * Maximum number of frames to apply "slow fall" acceleration.
 */
#define MAX_FALL_SLOW_FRAMES  24

/**
 * Y position for the player when grounded in 8.8 fixed point.
 */
#define GROUND_Y              (96 << 8)

/**
 * Starting horizontal position for the player in 8.8 fixed point.
 */
#define PLAYER_X_START        (90 << 8)

/**
 * Player structure. Organizes various values related to the player's state.
 */
typedef struct Player {
  /**
   * Player's x position in 8.8 fixed point.
   */
  uint16_t x;

  /**
   * Player's x velocity in 8.8 fixed point.
   */
  int16_t dx;

  /**
   * Player's y position in 8.8 fixed point.
   */
  uint16_t y;

  /**
   * Player's y velocity in 8.8 fixed point.
   */
  int16_t dy;

  /**
   * Player's graphical state.
   * @see PLAYER_STANDING, PLAYER_WALKING, PLAYER_RUNNING, PLAYER_JUMPING,
   *      PLAYER_PIVOTING
   */
  uint8_t state;

  /**
   * The direction the player is facing.
   * @see HEADING_LEFT, HEADING_RIGHT
   */
  uint8_t heading;

  /**
   * Current walk animation frame. Can be either 0 or 1.
   */
  uint8_t walk_frame;

  /**
   * Whether or not the player is considered "airborne".
   */
  uint8_t airborne;

  /**
   * Whether or not the player is "slow falling".
   */
  uint8_t slow_fall;
} Player;

/**
 * The main player state object.
 */
extern Player player;

void init_player(void);
void update_player(void);

#endif
