/*
 * Sword.h
 *
 *  Created on: Feb 19, 2015
 *      Author: elgatil
 */

#ifndef SWORD_H_
#define SWORD_H_

#include "Object.h"
#include "Character.h"

class Sword: public Object {
public:
	Sword( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, Character* objectOwner );
	virtual ~Sword();

	void update();

protected:
	int swingState;
};

#endif /* SWORD_H_ */
