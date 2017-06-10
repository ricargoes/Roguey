/*
 * Object.h
 *
 *  Created on: Feb 12, 2015
 *      Author: elgatil
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "InGameComp.h"
//#include "Player.h"
class Character;

class Object: public InGameComp {
public:
	Object( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, Character* objectOwner, bool harm );
	virtual ~Object();

	bool is_harmful(){ return harmful; }
	Character* get_owner(){ return owner; }

protected:
	Character* owner;
	bool harmful;
	int attack;
};

#endif /* OBJECT_H_ */
