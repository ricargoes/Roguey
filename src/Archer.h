/*
 * Archer.h
 *
 *  Created on: Feb 24, 2015
 *      Author: elgatil
 */

#ifndef ARCHER_H_
#define ARCHER_H_

#include "Minion.h"

class Archer: public Minion {
public:
	Archer( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, int level );
	virtual ~Archer();

	void set_cooldown();

	void update();
};

#endif /* ARCHER_H_ */
