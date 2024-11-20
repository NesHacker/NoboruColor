#include <gb/gb.h>

#include "joypad.h"
#include "player.h"

Player player;

/**
 * Timer used to control the walking animation.
 */
Timer walk_timer;

/**
 * Timer used to controll the falling speed when airborne.
 */
Timer slow_fall_timer;

/**
 * Updates the sprite graphics for the player based on the current state.
 */
void update_player_sprites (void) {
  // Determine sprite tiles based on heading
  uint8_t frame_tile_base;
  switch (player.state) {
  case PLAYER_WALKING:
    frame_tile_base = player.walk_frame ? 0x24 : 0x20;
    break;
  case PLAYER_RUNNING:
    frame_tile_base = player.walk_frame ? 0x2C : 0x30;
    break;
  case PLAYER_JUMPING:
    frame_tile_base = 0x28;
    break;
  case PLAYER_PIVOTING:
    frame_tile_base = 0x38;
    break;
  case PLAYER_STANDING:
  default:
    frame_tile_base = 0x20;
    break;
  }

  // Set sprite props & sprite x-coordinates based on heading
  uint8_t props = 0;
  uint8_t x = (player.x >> 8);
  uint8_t y = (player.y >> 8);
  uint8_t x0 = x;
  uint8_t x1 = x + 8;

  if (player.heading == HEADING_LEFT) {
    props |= 0b00100000;
    x0 = x + 8;
    x1 = x;
  }

  // Update the shadow OAM
  set_sprite_tile(0, frame_tile_base);
  set_sprite_prop(0, props);
  move_sprite(0, x0, y);
  set_sprite_tile(1, frame_tile_base + 2);
  set_sprite_prop(1, props);
  move_sprite(1, x1, y);
}

/**
 * Handles the game loop logic for the player. Determines the player's state,
 * heading, velocity, etc. based on joypad input.
 */
void update_player (void) {
  // Determine the direction the player is pressing on the D-PAD
  int8_t dpad_heading = 0;
  if (joypad_down & J_LEFT) {
    dpad_heading = -1;
    player.heading = HEADING_LEFT;
  } else if (joypad_down & J_RIGHT) {
    dpad_heading = 1;
    player.heading = HEADING_RIGHT;
  }

  // Update the player's vertical velocity
  if (player.airborne) {
    int16_t accel_y = FALL_FAST_ACCEL;

    if (player.slow_fall) {
      if (update_timer(slow_fall_timer) || !a_down()) {
        player.slow_fall = 0;
      } else {
        accel_y = FALL_SLOW_ACCEL;
      }
    }

    player.dy += accel_y;
    if (player.dy > MAX_FALL_SPEED) {
      player.dy = MAX_FALL_SPEED;
    }
  }

  // Check to see if they pressed "A" to jump
  if (a_pressed() && !player.airborne) {
    player.dy = -INITIAL_JUMP_SPEED;
    player.airborne = 1;
    player.slow_fall = 1;
    reset_timer(slow_fall_timer);
  }

  // Determine the target velocity via the player & joypad state
  int16_t target_dx = 0;
  if (dpad_heading < 0)
    target_dx = b_down() ? -MAX_RUN_SPEED : -MAX_WALK_SPEED;
  else if (dpad_heading > 0)
    target_dx = b_down() ? MAX_RUN_SPEED : MAX_WALK_SPEED;

  if (player.airborne) {
    if (
      dpad_heading == 0 ||
      (dpad_heading > 0 && player.dx < 0) ||
      (dpad_heading < 0 && player.dx > 0)
    ) {
      target_dx = 0;
    } else {
      target_dx = player.dx;
    }
  }

  // Accelerate the player
  if (player.dx < target_dx) {
    player.dx += 0x10;
  } else if (player.dx > target_dx) {
    player.dx -= 0x10;
  }

  // Determine the player's visual state based on the current velocity
  if (player.airborne) {
    player.state = PLAYER_JUMPING;
  } else if (player.dx == 0) {
    player.state = PLAYER_STANDING;
  } else if (
    (player.dx > 0 && dpad_heading < 0) ||
    (player.dx < 0 && dpad_heading > 0)
  ) {
    player.state = PLAYER_PIVOTING;
  } else if (player.dx > MAX_WALK_SPEED || player.dx < -MAX_WALK_SPEED) {
    player.state = PLAYER_RUNNING;
  } else {
    player.state = PLAYER_WALKING;
  }

  // Update the walking timer
  if (update_timer(walk_timer)) {
    reset_timer(walk_timer);
    player.walk_frame ^= 1;
  }

  player.x += player.dx;
  player.y += player.dy;

  // Bounds checking
  if (player.airborne && player.y > GROUND_Y) {
    player.y = GROUND_Y;
    player.dy = 0;
    player.airborne = 0;
  }

  // Update the sprite graphics
  update_player_sprites();
}


/**
 * Initializes player state and sprite graphics.
 */
void init_player(void) {
  // Initialize player state
  player.x = PLAYER_X_START;
  player.dx = 0;
  player.y = GROUND_Y;
  player.dy = 0;
  player.state = PLAYER_WALKING;
  player.heading = HEADING_RIGHT;
  player.walk_frame = 0;
  player.airborne = 0;
  player.slow_fall = 0;

  // Initialize the walking frame animation timer
  walk_timer.duration = 10;
  reset_timer(walk_timer);

  // Initialize the slow fall timer
  slow_fall_timer.duration = MAX_FALL_SLOW_FRAMES;

  update_player_sprites();
}
