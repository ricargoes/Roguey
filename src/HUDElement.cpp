/*
 * HUDElement.cpp
 *
 *  Created on: Feb 11, 2015
 *      Author: elgatil
 */

#include "HUDElement.h"

HUDElement::HUDElement( SDL_Texture* loadedTexture, Point pos, SDL_Rect spRect, int frameCountdown )
	: GameComponent( loadedTexture, pos ) {
	spriteRect = spRect;
	destroyCountdown = frameCountdown;
	hideCountdown=-1;
	hidden=false;

}

HUDElement::~HUDElement() {

}


void HUDElement::update(){
	if (hideCountdown>0) hideCountdown--;
	if ( (hideCountdown==0) ) hidden = true;

	if (destroyCountdown>0) destroyCountdown--;
	if ( (destroyCountdown==0) && (destroy==UNBROKEN) ) destroy = BREAKING;
}


void HUDElement::render(){
	if (hidden) return;

	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);

	SDL_Rect screenPosRect;
	screenPosRect.x = position.x;
	screenPosRect.y = position.y;
	screenPosRect.w = spriteRect.w;
	screenPosRect.h = spriteRect.h;

	//Render to screen
	SDL_RenderCopyEx( resources->gameRenderer, spriteSheet, &spriteRect, &screenPosRect, angle, center, flip );
}
