//#pragma bank 2
//#include "main.h"
//#include "SpriteManager.h"
//UINT8 bank_SPRITE_ENEMY = 2;
//
//struct EnemyInfo {
//	INT8 vy;
//};
//
//void Start_SPRITE_ENEMY() {
//	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
//	data->vy = 1;
//}
//
//void Update_SPRITE_ENEMY() {
//	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
//	if (TranslateSprite(THIS, 0, data->vy))
//	{
//		data->vy = -data->vy;
//	}
//}
//
//void Destroy_SPRITE_ENEMY() {
//}


#pragma bank 2
#include "main.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
UINT8 bank_SPRITE_ENEMY = 2;

struct EnemyInfo {
	INT8 vx;
	INT8 vy;
};

void Start_SPRITE_ENEMY() {
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	data->vx = 1;
	data->vy = 1;
}

//Horizontal Movement
	/*if (TranslateSprite(THIS, data->vx, 0))
	{
		data->vx = -data->vx;
		if (SPRITE_GET_VMIRROR(THIS)) SPRITE_UNSET_VMIRROR(THIS);
		else SPRITE_SET_VMIRROR(THIS);
	}*/

	//Vertical Movement
	/*if (TranslateSprite(THIS, 0, data->vy))
	{
		data->vy = -data->vy;
	}*/

void Update_SPRITE_ENEMY() {
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;

	UINT8 i;
	struct Sprite* spr;
	INT16 diff;

	//Follow the player movement
	SPRITEMANAGER_ITERATE(i, spr) {
		if (spr->type == SPRITE_PLAYER) {

			//we'll set a bounding box with the difference, so that way the 
			//sprite only follows the player when they get close enough
			diff = THIS->x - spr->x;
			if (diff < 10 || diff > -10) {
				if (diff > 0) {
					SPRITE_SET_VMIRROR(THIS);
					data->vx = -1;
				}
				else if (diff < 0) {
					SPRITE_UNSET_VMIRROR(THIS);
					data->vx = 1;
				}
				else {
					data->vx = 0;
				}
			}
		}
	}
	TranslateSprite(THIS, data->vx, 0);
}

void Destroy_SPRITE_ENEMY() {}