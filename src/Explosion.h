/*
 * Explosion.h
 *
 *  Created on: Feb 20, 2015
 *      Author: elgatil
 */

#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "Object.h"
#include "Character.h"

class Explosion: public Object {
public:
	Explosion( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, Character* objectOwner );
	virtual ~Explosion();

	void update();

protected:
	const int explosionAnimLapse=6;
};

#endif /* EXPLOSION_H_ */
