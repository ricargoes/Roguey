/*
 * Minion.h
 *
 *  Created on: Jan 30, 2015
 *      Author: elgatil
 */

#ifndef MINION_H_
#define MINION_H_

#include "Character.h"
#include "Player.h"
#include "Arrow.h"

class Minion: public Character {
public:
	Minion( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, int healthPoints, int manaPoints, int lvl=0 );
	virtual ~Minion();

	int get_charLvl(){ return (get_HP()/30+get_MP()/30+get_bootsLvl()+get_defenseLvl()+get_swordLvl()+get_bowLvl()+get_explosionLvl()+get_teleportLvl()); }

	Character* choose_target();
	void update();

protected:
	int cooldown;
	int minionLvl;
};

#endif /* MINION_H_ */
