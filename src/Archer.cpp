/*
 * Archer.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: elgatil
 */

#include "Archer.h"

Archer::Archer( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, int level )
	:Minion( loadedTexture, pos, nAnimSprites, spRects, 40, 20, level ){
	switch(minionLvl){
	case 10:
		this->bowLvl_up();
		/* no break */
	case 9:
		this->bowLvl_up();
		/* no break */
	case 8:
		this->bootsLvl_up();
		/* no break */
	case 7:
		this->bowLvl_up();
		/* no break */
	case 6:
		this->teleportLvl_up();
		/* no break */
	case 5:
		this->bowLvl_up();
		/* no break */
	case 4:
		this->add_HP(40);
		/* no break */
	case 3:
		this->defenseLvl_up();
		/* no break */
	case 2:
		this->bowLvl_up();
		/* no break */
	case 1:
		this->bowLvl_up();
		break;
	}

}

Archer::~Archer() {

}


void Archer::set_cooldown(){
	cooldown=21-minionLvl;
}


void Archer::update(){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	// Choosing target
	Character* target = this->choose_target();
	if (!target) return;

	Size distance = { target->get_position().x-this->position.x, target->get_position().y-this->position.y };
	Size distanceWallLT = { this->position.x-scene->tileSize.x, this->position.y-scene->tileSize.y };
	Size distanceWallRB = { scene->room->get_size().x-scene->tileSize.x-(this->position.x+scene->tileSize.x), scene->room->get_size().y-scene->tileSize.y-(this->position.y+scene->tileSize.y) };

	if ( actionState==ACTION_FREE || actionState==ACTION_MOVING ){
		if (cooldown==0){
			actionState = ACTION_ATTACK;
			Arrow* arrow = new Arrow(resources->stuffSheet->texture, position, 1, resources->stuffSpriteRects["Arrow"], this, {target->get_position().x+3,target->get_position().y+3});
			scene->newObjectComps.push_back(arrow);
			actionState = ACTION_FREE;
			this->set_cooldown();
		}

		if (cooldown!=0) {
			if ( abs(distance.x)>abs(distance.y) ){
				if ( distance.x>0 ){

					if (distanceWallLT.x>scene->tileSize.x){
						dir = DIR_LEFT;  actionState=ACTION_MOVING;
					} else {
						if ( distance.y>0 ){
							if( distanceWallLT.y>scene->tileSize.y ){
								dir = DIR_UP; actionState=ACTION_MOVING;
							} else {
								dir = DIR_RIGHT; actionState=ACTION_FREE;
							}
						} else {
							if( distanceWallRB.y>scene->tileSize.y ){
								dir = DIR_DOWN; actionState=ACTION_MOVING;
							} else {
								dir = DIR_RIGHT; actionState=ACTION_FREE;
							}
						}
					}

				} else {

					if (distanceWallRB.x>scene->tileSize.x){
						dir = DIR_RIGHT; actionState=ACTION_MOVING;
					} else {
						if ( distance.y>0 ){
							if( distanceWallLT.y>scene->tileSize.y ){
								dir = DIR_UP; actionState=ACTION_MOVING;
							} else {
								dir = DIR_LEFT; actionState=ACTION_FREE;
							}
						} else {
							if( distanceWallRB.y>scene->tileSize.y ){
								dir = DIR_DOWN; actionState=ACTION_MOVING;
							} else {
								dir = DIR_LEFT; actionState=ACTION_FREE;
							}
						}
					}

				}
			} else {
				if ( distance.y>0 ){

					if (distanceWallLT.y>scene->tileSize.y){
						dir = DIR_UP; actionState=ACTION_MOVING;
					} else {
						if ( distance.x>0 ){
							if( distanceWallLT.x>scene->tileSize.x ){
								dir = DIR_LEFT; actionState=ACTION_MOVING;
							} else {
								dir = DIR_DOWN; actionState=ACTION_FREE;
							}
						} else {
							if( distanceWallRB.x>scene->tileSize.x ){
								dir = DIR_RIGHT; actionState=ACTION_MOVING;
							} else {
								dir = DIR_DOWN; actionState=ACTION_FREE;
							}
						}
					}

				} else {

					if (distanceWallRB.y>scene->tileSize.y){
						dir = DIR_DOWN; actionState=ACTION_MOVING;
					} else {
						if ( distance.x>0 ){
							if( distanceWallLT.x>scene->tileSize.x ){
								dir = DIR_LEFT; actionState=ACTION_MOVING;
							} else {
								dir = DIR_UP; actionState=ACTION_FREE;
							}
						} else {
							if( distanceWallRB.x>scene->tileSize.x ){
								dir = DIR_RIGHT; actionState=ACTION_MOVING;
							} else {
								dir = DIR_UP; actionState=ACTION_FREE;
							}
						}
					}

				}
			}

		}

	}


	Character::update();
	cooldown = ( (cooldown-1)>0 ? cooldown-1:0);
}

