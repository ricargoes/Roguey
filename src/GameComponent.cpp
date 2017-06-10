/*
 * GameComponent.cpp
 *
 *  Created on: Jan 29, 2015
 *      Author: elgatil
 */

#include "GameComponent.h"


GameComponent::GameComponent(SDL_Texture* loadedTexture, Point pos) {

	spriteSheet = loadedTexture;
	set_position(pos.x, pos.y);

	angle=0.0;
	center = NULL;
	flip = SDL_FLIP_NONE;

	destroy = false;


}


GameComponent::~GameComponent() {
	spriteSheet = NULL;
}
