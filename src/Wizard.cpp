/*
 * Wizard.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: elgatil
 */

#include "Wizard.h"

Wizard::Wizard( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, int level )
	:Minion( loadedTexture, pos, nAnimSprites, spRects, 30, 30, level ){
	this->defenseLvl=0;
	switch(minionLvl){
	case 10:
		this->explosionLvl_up();
		/* no break */
	case 9:
		this->add_MP(30);
		/* no break */
	case 8:
		this->teleportLvl_up();
		/* no break */
	case 7:
		this->add_HP(30);
		/* no break */
	case 6:
		this->add_MP(30);
		/* no break */
	case 5:
		this->explosionLvl_up();
		/* no break */
	case 4:
		this->add_MP(30);
		/* no break */
	case 3:
		this->bootsLvl_up();
		/* no break */
	case 2:
		this->teleportLvl_up();
		/* no break */
	case 1:
		this->add_MP(30);
		break;
	}

}

Wizard::~Wizard() {

}


void Wizard::set_cooldown(){
	cooldown=21-minionLvl;
}


void Wizard::update(){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	// Choosing target
	Character* target = this->choose_target();
	if (!target) return;

//	Size distance = { scene->hero1->get_position().x-this->position.x, scene->hero1->get_position().y-this->position.y };
//	Size distanceWallLT = { this->position.x-scene->tileSize.x, this->position.y-scene->tileSize.y };
//	Size distanceWallRB = { scene->room->get_size().x-scene->tileSize.x-(this->position.x+scene->tileSize.x), scene->room->get_size().y-scene->tileSize.y-(this->position.y+scene->tileSize.y) };

	if ( actionState==ACTION_FREE || actionState==ACTION_MOVING ){
		if (cooldown==0){
			if( this->add_tempMP(-1*scene->lvlLegend["explMana"][std::to_string(this->explosionLvl)]) ){
				Explosion* explosion = new Explosion(resources->stuffSheet->texture, {target->get_position().x+3,target->get_position().y+3}, 4, resources->stuffSpriteRects["Explosion"], this);
				scene->newObjectComps.push_back(explosion);
				actionState = ACTION_CASTING;
				this->set_cooldown();
			}
		}
	}

	Character::update();
	cooldown = ( (cooldown-1)>0 ? cooldown-1:0);
}
