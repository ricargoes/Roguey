/*
 * Arrow.h
 *
 *  Created on: Feb 12, 2015
 *      Author: elgatil
 */

#ifndef ARROW_H_
#define ARROW_H_

#include <cmath>

#include "Object.h"
#include "Character.h"

class Arrow: public Object {
public:
	Arrow( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, Character* objectOwner, Point targetPoint );
	virtual ~Arrow();

	void update();

protected:
};

#endif /* ARROW_H_ */
