/*
 * Swordman.h
 *
 *  Created on: Feb 24, 2015
 *      Author: elgatil
 */

#ifndef SWORDMAN_H_
#define SWORDMAN_H_

#include "Minion.h"

class Swordman: public Minion {
public:
	Swordman( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, int level );
	virtual ~Swordman();

	void set_cooldown();

	void update();
};

#endif /* SWORDMAN_H_ */
