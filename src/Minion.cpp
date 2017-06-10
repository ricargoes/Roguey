/*
 * Minion.cpp
 *
 *  Created on: Jan 30, 2015
 *      Author: elgatil
 */

#include "Minion.h"


Minion::Minion( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, int healthPoints, int manaPoints, int lvl )
	: Character( loadedTexture, pos, nAnimSprites, spRects, healthPoints, manaPoints){
	cooldown=0;
	minionLvl=lvl;
}


Minion::~Minion() {

}


Character* Minion::choose_target(){
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	// Choosing target
	Size distance1, distance2;
	if(scene->hero1) distance1 = { scene->hero1->get_position().x-this->position.x, scene->hero1->get_position().y-this->position.y };
	if(scene->hero2) distance2 = { scene->hero2->get_position().x-this->position.x, scene->hero2->get_position().y-this->position.y };
	Character* target;
	if (scene->hero1 && scene->hero2) target = ( (distance1.x+distance1.y) < (distance1.x+distance1.y) ? scene->hero1:scene->hero2 );
	if (scene->hero1 && !scene->hero2) target = scene->hero1;
	if (!scene->hero1 && scene->hero2) target = scene->hero2;

	return target;
}


void Minion::update(){
	Character::update();

}

