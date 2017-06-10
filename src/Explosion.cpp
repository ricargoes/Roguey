/*
 * Explosion.cpp
 *
 *  Created on: Feb 20, 2015
 *      Author: elgatil
 */

#include "Explosion.h"

Explosion::Explosion( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, Character* objectOwner )
		: Object(loadedTexture, pos, nAnimSprites, spRects, objectOwner, true){

	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);
	attack = scene->lvlLegend["explDmg"][std::to_string(objectOwner->get_explosionLvl())];
}


Explosion::~Explosion() {

}


void Explosion::update(){
	if (destroy == BREAKING || destroy == BROKEN)
		return;

	stepsFrames++;
	if ( (stepsFrames-1)==(explosionAnimLapse*nAnims) )
		destroy = BREAKING;

	// COLLISIONS
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);
	for(charIter iter = scene->charComps.begin(); iter != scene->charComps.end(); ++iter){
		SDL_Rect otherCompRect = (*iter)->get_rect_after_angle();
		if ( this->check_collision(otherCompRect) ){
			(*iter)->add_tempHP( -1*(attack) );

			if ( (*iter)->get_destroy()==UNBROKEN && (*iter)->check_death() ) owner->add_points(10*(*iter)->get_charLvl());
		}
	}

	// SELECTING FRAME
	if (owner->get_actionState()==ACTION_CASTING){
		if ((stepsFrames-1)>=(explosionAnimLapse*nAnims)){
			owner->set_action_free(); // Hero can react after explosion has ended
		} else if ((stepsFrames % 4)==0){
			int ownerDir=owner->get_dir();
			if(ownerDir==DIR_UP) ownerDir=DIR_RIGHT; else if(ownerDir==DIR_RIGHT) ownerDir=DIR_DOWN; else if(ownerDir==DIR_DOWN) ownerDir=DIR_LEFT; else if(ownerDir==DIR_LEFT) ownerDir=DIR_UP;
			owner->set_dir(ownerDir);
		}
	}
	int deltaAnim = stepsFrames/explosionAnimLapse;
	currentSpriteRect = &spriteRects[deltaAnim];
}
