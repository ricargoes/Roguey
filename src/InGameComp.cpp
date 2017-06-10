/*
 * InGameComp.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: elgatil
 */

#include "InGameComp.h"

InGameComp::InGameComp( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects )
	: GameComponent( loadedTexture, pos ) {

	nAnims = nAnimSprites;
	spriteRects = spRects;
	currentSpriteRect = &spriteRects[0];


	dir = DIR_DOWN;
	actionState = ACTION_FREE;
	stepLength.x = 1;
	stepLength.y = 1;
	speedMultiplier = 1;
	stepsFrames = 0;

}


InGameComp::~InGameComp() {
	currentSpriteRect = NULL;
}

SDL_Rect InGameComp::get_rect_after_angle(){
	int leftComp, rightComp, topComp, bottomComp;
	SDL_Point relPivot={this->currentSpriteRect->w/2,this->currentSpriteRect->h/2};
	if (center)
		relPivot=(*center);
	Point globPivot={this->position.x+relPivot.x, this->position.y+relPivot.y};

	if ( (angle>-45 && angle<=45) || (angle>305 && angle<=395) ){
		leftComp = globPivot.x-relPivot.x; rightComp = globPivot.x+(this->currentSpriteRect->w-relPivot.x);
		topComp = globPivot.y-relPivot.y; bottomComp = globPivot.y+(this->currentSpriteRect->h-relPivot.y);
	} else if ((angle>45 && angle<=135) || (angle>-305 && angle<=-215) ){
		leftComp = globPivot.x-(this->currentSpriteRect->h-relPivot.y); rightComp = globPivot.x+relPivot.y;
		topComp = globPivot.y-relPivot.x; bottomComp = globPivot.y+(this->currentSpriteRect->w-relPivot.x);
	} else if ( (angle>135 && angle<=215) || (angle>-215 && angle<=-135) ){
		leftComp = globPivot.x-(this->currentSpriteRect->w-relPivot.x); rightComp = globPivot.x+relPivot.x;
		topComp = globPivot.y-(this->currentSpriteRect->h-relPivot.y); bottomComp = globPivot.y+relPivot.y;
	} else if ( (angle>215 && angle<=305) || (angle>-135 && angle<=-45) ){
		leftComp = globPivot.x-relPivot.y; rightComp = globPivot.x+(this->currentSpriteRect->h-relPivot.y);
		topComp = globPivot.y-(this->currentSpriteRect->w-relPivot.x); bottomComp = globPivot.y+relPivot.x;
	}

	SDL_Rect final = {leftComp, topComp, (rightComp-leftComp), (bottomComp-topComp)};

	return final;
}

bool InGameComp::check_collision( SDL_Rect& b ){
	//The sides of the rectangles

	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	SDL_Rect angled_rect = this->get_rect_after_angle(); // Takes into account the position of the rect of the comp if there has been a rotation
	leftA = angled_rect.x;
	rightA = angled_rect.x + angled_rect.w;
	topA = angled_rect.y;
	bottomA = angled_rect.y + angled_rect.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB ) {
		return false;
	}

	return true;
}


bool InGameComp::check_wall( Room* room ){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);

	int leftRoom, rightRoom, topRoom, bottomRoom;
	leftRoom = room->get_position().x+(resources->tileSize.x); rightRoom = room->get_position().x+(room->get_size().x-resources->tileSize.x);
	topRoom = room->get_position().y+(resources->tileSize.y); bottomRoom = room->get_position().y+(room->get_size().y-resources->tileSize.y);

	int leftComp, rightComp, topComp, bottomComp;
	SDL_Rect angled_rect = this->get_rect_after_angle(); // Takes into account the position of the rect of the comp if there has been a rotation
	leftComp = angled_rect.x;
	rightComp = angled_rect.x + angled_rect.w;
	topComp = angled_rect.y;
	bottomComp = angled_rect.y + angled_rect.h;

	if( bottomComp > bottomRoom || topComp < topRoom || rightComp > rightRoom || leftComp < leftRoom ) {
		return true; // Outside walking zone
	}

	return false;
}

void InGameComp::render(){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);

	SDL_Rect screenPosRect;
	screenPosRect.x = position.x;
	screenPosRect.y = position.y;
	screenPosRect.w = currentSpriteRect->w;
	screenPosRect.h = currentSpriteRect->h;

	//Render to screen
	SDL_RenderCopyEx( resources->gameRenderer, spriteSheet, currentSpriteRect, &screenPosRect, angle, center, flip );
}
