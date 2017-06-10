/*
 * Player.cpp
 *
 *  Created on: Jan 29, 2015
 *      Author: elgatil
 */

#include "Player.h"


Player::Player( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, int nPlayer )
	: Character( loadedTexture, pos, nAnimSprites, spRects, 50, 30){

	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	INIConfig map = resources->read_INIConfig( "controls.ini" );
	playerNumber = nPlayer;
	switch ( playerNumber ){
		case 1:
			controlBindings = map["player1"];
			break;
		case 2:
			controlBindings = map["player2"];
			break;
	}

	lockOn = scene->charComps.begin();

	lockHUD = new HUDElement( resources->stuffSheet->texture, {-100, -100}, resources->stuffSpriteRects["LockerRed"][0] );
	scene->elseComps.push_back(lockHUD);
}


Player::~Player() {
	lockHUD->set_countdown(0);
}


void Player::manage_input(SDL_Event e){

	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0){ //Pressing Keys
		if(actionState==ACTION_FREE || actionState==ACTION_MOVING){
			if(e.key.keysym.sym == controlBindings["up"]){
				if(dir != DIR_UP)
					dir = DIR_UP;
				actionState = ACTION_MOVING;
			} else if(e.key.keysym.sym == controlBindings["down"]){
				if(dir != DIR_DOWN)
					dir = DIR_DOWN;
				actionState = ACTION_MOVING;
			} else if(e.key.keysym.sym == controlBindings["left"]){
				if(dir != DIR_LEFT)
					dir = DIR_LEFT;
				actionState = ACTION_MOVING;
			} else if(e.key.keysym.sym == controlBindings["right"]){
				if(dir != DIR_RIGHT)
					dir = DIR_RIGHT;
				actionState = ACTION_MOVING;
			}else if(e.key.keysym.sym == controlBindings["teleport"]){
				this->teleport();
			}
		}
		if(actionState==ACTION_FREE || actionState==ACTION_MOVING){
			if(e.key.keysym.sym == controlBindings["sword"]){
				actionState = ACTION_ATTACK;
				Sword* sword = new Sword(resources->stuffSheet->texture, position, 10, resources->stuffSpriteRects["Sword"], this);
				scene->newObjectComps.push_back(sword);
			} else if(e.key.keysym.sym == controlBindings["arrow"]){
				if (lockOn != scene->charComps.end()){
					actionState = ACTION_ATTACK;
					Arrow* arrow = new Arrow(resources->stuffSheet->texture, position, 1, resources->stuffSpriteRects["Arrow"], this, {(*lockOn)->get_position().x+3,(*lockOn)->get_position().y+3});
					scene->newObjectComps.push_back(arrow);
					actionState = ACTION_FREE;
				}
			} else if(e.key.keysym.sym == controlBindings["explosion"]){
				if (lockOn != scene->charComps.end()){
					if( this->add_tempMP(-1*scene->lvlLegend["explMana"][std::to_string(this->explosionLvl)]) ){
						Explosion* explosion = new Explosion(resources->stuffSheet->texture, {(*lockOn)->get_position().x+3,(*lockOn)->get_position().y+3}, 4, resources->stuffSpriteRects["Explosion"], this);
						scene->newObjectComps.push_back(explosion);
						actionState = ACTION_CASTING;
					}
				}
			}
		}
		if(e.key.keysym.sym == controlBindings["lock"]){
			this->cycle_lockOn();
		}

	} else if( e.type == SDL_KEYUP ){ // Releasing Keys
		if (actionState==ACTION_MOVING){
			if(e.key.keysym.sym == controlBindings["up"]){
				if(dir == DIR_UP)
					this->set_action_free();
			} else if(e.key.keysym.sym == controlBindings["down"]){
				if(dir == DIR_DOWN)
					this->set_action_free();
			} else if(e.key.keysym.sym == controlBindings["left"]){
				if(dir == DIR_LEFT)
					this->set_action_free();
			} else if(e.key.keysym.sym == controlBindings["right"]){
				if(dir == DIR_RIGHT)
					this->set_action_free();
			}
		}
	}
}

void Player::initialize_lockOn(){
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);
	lockOn = scene->charComps.begin();
}


void Player::cycle_lockOn(){
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);
	if ( ((scene->charComps.begin()+1)==scene->charComps.end()) ) {
		lockOn = scene->charComps.end();
		return;
	}
	if (lockOn != scene->charComps.end())
			++lockOn;
	if (lockOn == scene->charComps.end())
			lockOn = scene->charComps.begin();

	if (lockOn != scene->charComps.end() && (*lockOn)==this) ++lockOn;
}


void Player::update(){
	Character::update();
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	// Rendering lockHUD
	Point lockOnPos;
	if (lockOn != scene->charComps.end()) lockOnPos = {(*lockOn)->get_position().x+3,(*lockOn)->get_position().y-5}; else lockOnPos = {-100, -100};
	lockHUD->set_position(lockOnPos.x, lockOnPos.y);

	// lockOn iterator out-of-range protection
	for(charIter iter = scene->charComps.begin(); iter != scene->charComps.end(); ++iter){
		if ( (*iter)->get_destroy()==BREAKING || (*iter)->get_destroy()==BROKEN ){
				lockOn = scene->charComps.begin();
		}
	}

	if (lockOn == scene->charComps.end() && ((scene->charComps.begin()+1)!=scene->charComps.end()) )
		lockOn = scene->charComps.begin();
	if (lockOn != scene->charComps.end() && (*lockOn)==this) ++lockOn;


}
