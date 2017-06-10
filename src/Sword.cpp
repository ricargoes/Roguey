/*
 * Sword.cpp
 *
 *  Created on: Feb 19, 2015
 *      Author: elgatil
 */

#include "Sword.h"

Sword::Sword( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, Character* objectOwner )
	: Object(loadedTexture, pos, nAnimSprites, spRects, objectOwner, true){

	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);
	attack = scene->lvlLegend["sword"][std::to_string(objectOwner->get_swordLvl())];
	speedMultiplier = 1;
	swingState = -1;
	stepLength = {4*(objectOwner->get_swordLvl()/2),4*(objectOwner->get_swordLvl()/2)};
	center = new SDL_Point();
	center->x=0;
	center->y=26;
}


Sword::~Sword() {
	delete center;
}


void Sword::update(){
	if( (stepsFrames-1)==nAnims && destroy==UNBROKEN ){
		destroy = BREAKING;
		owner->set_action_free();
	}
	if (destroy == BREAKING || destroy == BROKEN)
		return;

	// MOVEMENT
	stepsFrames++;
	angle = -89.0+89.0/nAnims*(stepsFrames-1);
	Point swordPos = {owner->get_position().x+15,owner->get_position().y-10};
	switch (owner->get_dir()){
		case DIR_DOWN:
			swordPos.y+=stepLength.y;
			angle+=180;
			break;
		case DIR_LEFT:
			swordPos.x-=stepLength.x;
			angle+=270;
			break;
		case DIR_RIGHT:
			swordPos.x+=stepLength.x;
			angle+=90;
			break;
		case DIR_UP:
			swordPos.y-=stepLength.y;
			angle+=0.0;
			break;
	}
	set_position(swordPos.x, swordPos.y);

	// COLLISIONS
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);
	if (this->check_wall(scene->room)){
		destroy = BREAKING;
		owner->set_action_free();
		return;
	}

	for(charIter iter = scene->charComps.begin(); iter != scene->charComps.end(); ++iter){
		if (owner==(*iter))
			continue;
		SDL_Rect otherCompRect = (*iter)->get_rect_after_angle();
		if ( this->check_collision(otherCompRect) ){
			destroy = BREAKING;
			owner->set_action_free();
			(*iter)->add_tempHP( -1*(attack-scene->lvlLegend["defense"][std::to_string((*iter)->get_defenseLvl())]) );

			if ( (*iter)->get_destroy()==UNBROKEN && (*iter)->check_death() ) owner->add_points(10*(*iter)->get_charLvl());
		}
	}

	for(objIter iter = scene->objectComps.begin(); iter != scene->objectComps.end(); ++iter){
		if (this==(*iter))
			continue;
		SDL_Rect otherCompRect = (*iter)->get_rect_after_angle();
		if ( this->check_collision(otherCompRect) ){
			destroy = BREAKING;
			owner->set_action_free();
			return;
		}
	}
}
