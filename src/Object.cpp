/*
 * Object.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: elgatil
 */

#include "Object.h"

Object::Object( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, Character* objectOwner, bool harm )
	: InGameComp( loadedTexture, pos, nAnimSprites, spRects ) {
	owner = objectOwner;
	attack = 0; // To be rewritten by child class
	harmful = harm;
}


Object::~Object() {

}

