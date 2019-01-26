#pragma bank 2
#include "main.h"
UINT8 bank_STATE_GAME = 2;
UINT8 collision_tiles[] = { 1, 0 };

#include "..\res\src\tiles.h"
#include "..\res\src\map.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

void Start_STATE_GAME() {
	UINT8 i;

	SPRITES_8x16;
	for(i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, 90, 50);
	SpriteManagerAdd(SPRITE_ENEMY, 20, 70);  // <-- Add this line

	InitScrollTiles(0, 2, tiles, 3);
	InitScroll(mapWidth, mapHeight, map, collision_tiles, 0, 3);
	SHOW_BKG;
}

void Update_STATE_GAME() {
}