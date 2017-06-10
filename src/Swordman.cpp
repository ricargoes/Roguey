/*
 * Swordman.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: elgatil
 */

#include "Swordman.h"

Swordman::Swordman( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, int level )
	:Minion( loadedTexture, pos, nAnimSprites, spRects, 50, 10, level ){
	switch(minionLvl){
	case 10:
		this->defenseLvl_up();
		/* no break */
	case 9:
		this->swordLvl_up();
		/* no break */
	case 8:
		this->teleportLvl_up();
		/* no break */
	case 7:
		this->add_HP(50);
		/* no break */
	case 6:
		this->swordLvl_up();
		/* no break */
	case 5:
		this->defenseLvl_up();
		/* no break */
	case 4:
		this->swordLvl_up();
		/* no break */
	case 3:
		this->add_HP(50);
		/* no break */
	case 2:
		this->swordLvl_up();
		/* no break */
	case 1:
		this->bootsLvl_up();
		break;
	}
}


Swordman::~Swordman() {

}


void Swordman::set_cooldown(){
	cooldown=21-minionLvl;
}


void Swordman::update(){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	// Choosing target
	Character* target = this->choose_target();
	if (!target) return;

	Size distance = { target->get_position().x-this->position.x, target->get_position().y-this->position.y };
	if ( actionState==ACTION_FREE || actionState==ACTION_MOVING ){

		// Close range behaviour
		if( sqrt(pow(distance.x,2)+pow(distance.y,2))<=1.5*scene->tileSize.x && cooldown==0){
			if ( abs(distance.x)>abs(distance.y) ){
				if ( distance.x>0 ){
					dir = DIR_RIGHT;
				} else {
					dir = DIR_LEFT;
				}
			} else {
				if ( distance.y>0 ){
					dir = DIR_DOWN;
				} else {
					dir = DIR_UP;
				}
			}
			actionState=ACTION_ATTACK;
			Sword* sword = new Sword(resources->stuffSheet->texture, position, 10, resources->stuffSpriteRects["Sword"], this);
			scene->newObjectComps.push_back(sword);
			this->set_cooldown();
		}

		// Long range behaviour
		if( sqrt(pow(distance.x,2)+pow(distance.y,2))>1.5*scene->tileSize.x){
			if ( abs(distance.x)>abs(distance.y) ){
				if ( distance.x>0 ){
					dir = DIR_RIGHT;
				} else {
					dir = DIR_LEFT;
				}
			} else {
				if ( distance.y>0 ){
					dir = DIR_DOWN;
				} else {
					dir = DIR_UP;
				}
			}
			actionState=ACTION_MOVING;
		}
	}

	Character::update();
	cooldown = ( (cooldown-1)>0 ? cooldown-1:0);
}

