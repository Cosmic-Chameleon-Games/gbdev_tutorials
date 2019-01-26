#pragma bank 2
#include "main.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
UINT8 bank_SPRITE_PLAYER = 2;

typedef enum {
	NORMAL,		//State 0
	JUMPING 	//State 1
}PLAYER_STATE;

PLAYER_STATE player_state;

INT16 player_accel_y;
INT16 max_accel = 60;
INT8 tile_collision;

void Start_SPRITE_PLAYER() {
	player_state = NORMAL;
	player_accel_y = 0;
}

void Update_SPRITE_PLAYER() {

	UINT8 i;
	struct Sprite* spr;

	switch (player_state)
	{
	case NORMAL:
		Movement();

		if (KEY_TICKED(J_A)) {
			player_accel_y = -50;
			player_state = JUMPING;
		}

		//Check if falling
		if ((player_accel_y >> 4) > 1) {
			player_state = JUMPING;
		}
		break;

	case JUMPING:
		Movement();
		break;
	}
	
	if (player_accel_y < max_accel) {
		player_accel_y += 2;
	}

	tile_collision = TranslateSprite(THIS, 0, player_accel_y >> 4);

	if (!tile_collision && delta_time != 0 && player_accel_y < max_accel) { //Do another iteration if there is no collision
		player_accel_y += 2;
		tile_collision = TranslateSprite(THIS, 0, player_accel_y >> 4);
	}

	if (tile_collision) {
		player_accel_y = 0;
		if (player_state == JUMPING) {
			player_state = NORMAL;
		}
	}

	SPRITEMANAGER_ITERATE(i, spr) {
		if (spr->type == SPRITE_ENEMY) {
			if (CheckCollision(THIS, spr)) {
				SetState(STATE_GAME);
			}
		}
	}
}

void Destroy_SPRITE_PLAYER() {
}

void Movement()
{
	if (KEY_PRESSED(J_LEFT)) {
		tile_collision = TranslateSprite(THIS, -1 << delta_time, 0);
		SPRITE_SET_VMIRROR(THIS);
	}
	if (KEY_PRESSED(J_RIGHT)) {
		tile_collision = TranslateSprite(THIS, 1 << delta_time, 0);
		SPRITE_UNSET_VMIRROR(THIS);
	}
}