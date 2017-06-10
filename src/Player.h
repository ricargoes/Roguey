/*
 * Player.h
 *
 *  Created on: Jan 29, 2015
 *      Author: elgatil
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include "types.h"
#include "Sword.h"
#include "Arrow.h"
#include "Explosion.h"
#include "HUDElement.h"

class Player: public Character {
public:
	Player( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, int nPlayer = 1 );
	virtual ~Player();

	void initialize_lockOn();
	void cycle_lockOn();

	void manage_input( SDL_Event e );
	void update();

private:
	charIter lockOn;
	HUDElement* lockHUD;

	int playerNumber;
	Group controlBindings;
};

#endif /* PLAYER_H_ */
