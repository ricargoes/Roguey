/*
 * Character.cpp
 *
 *  Created on: Jan 29, 2015
 *      Author: elgatil
 */

#include "Character.h"

Character::Character( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, int hp, int mp  )
	: InGameComp( loadedTexture, pos, nAnimSprites, spRects ) {

	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	HP = hp;
	tempHP = hp;
	MP = mp;
	tempMP = mp;
	manaCooldown=0;
	bootsLvl = 1;
	speedMultiplier=bootsLvl;
	defenseLvl = 1;
	swordLvl = 1;
	bowLvl = 1;
	explosionLvl = 1;
	teleportLvl = 1;

	gamePoints = 0;

	SDL_Rect lifeBarRect = {resources->stuffSpriteRects["lightRed"][0].x, resources->stuffSpriteRects["lightRed"][0].y, resources->stuffSpriteRects["lightRed"][0].w*tempHP/HP, 2 };
	lifeBar = new HUDElement( resources->stuffSheet->texture, {this->position.x+3, this->position.y-2}, lifeBarRect );
	lifeBar->toggle_hidden(); scene->elseComps.push_back(lifeBar);
	SDL_Rect lifeBarRemainRect = {resources->stuffSpriteRects["darkRed"][0].x, resources->stuffSpriteRects["darkRed"][0].y, resources->stuffSpriteRects["darkRed"][0].w*(HP-tempHP)/HP, 2 };
	lifeBarRemain = new HUDElement( resources->stuffSheet->texture, {this->position.x+3+resources->stuffSpriteRects["darkRed"][0].w*tempHP/HP, this->position.y-2}, lifeBarRemainRect );
	lifeBarRemain->toggle_hidden(); scene->elseComps.push_back(lifeBarRemain);
}

Character::~Character() {
	lifeBar->advance_destroy();
	lifeBarRemain->advance_destroy();
}


void Character::add_tempHP(int deltaTempHP){
	tempHP+=deltaTempHP;
	if(tempHP>HP) tempHP=HP;
	if(tempHP<0) tempHP=0;
	this->show_lifeBar();
}


bool Character::add_tempMP(int deltaTempMP){
	if(-1*deltaTempMP>tempMP)
		return false;
	tempMP+=deltaTempMP;
	if(tempMP>MP) tempMP=MP;
	return true;
}


void Character::show_lifeBar(){
	if (lifeBar->is_hidden()) lifeBar->toggle_hidden();
	lifeBar->set_countdown(20);
	if (lifeBarRemain->is_hidden()) lifeBarRemain->toggle_hidden();
	lifeBarRemain->set_countdown(20);
}


bool Character::check_death(){
	if (this->tempHP<=0){
		return true;
	}
	return false;
}


void Character::teleport(){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);
	if ( this->get_tempMP() < scene->lvlLegend["teleMana"][std::to_string(this->teleportLvl)] ) return;
	this->add_tempMP(-1*scene->lvlLegend["teleMana"][std::to_string(this->teleportLvl)]);

	Size jump={0,0};
	switch(dir){
	case DIR_UP:
		jump.y=-1;
		break;
	case DIR_DOWN:
		jump.y=1;
		break;
	case DIR_LEFT:
		jump.x=-1;
		break;
	case DIR_RIGHT:
		jump.x=1;
		break;
	}
	HUDElement* blink = new HUDElement( resources->stuffSheet->texture, this->position, resources->stuffSpriteRects["Teleport"][0], 20 );
	scene->elseComps.push_back(blink);
	this->set_position(this->position.x+jump.x*(1+scene->lvlLegend["teleJump"][std::to_string(this->teleportLvl)]), this->position.y+jump.y*(1+scene->lvlLegend["teleJump"][std::to_string(this->teleportLvl)]));

	// COLLISIONS
	if(this->check_wall(scene->room))
		position=oldPos;
	for(charIter iter = scene->charComps.begin(); iter != scene->charComps.end(); ++iter){
		if (this==(*iter))
			continue;
		SDL_Rect otherCompRect = (*iter)->get_rect_after_angle();
		if ( this->check_collision(otherCompRect) ){
			position = oldPos;
		}
	}
}


void Character::update(){
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);
	//CHECK DEATH
	if (this->check_death() && destroy==UNBROKEN){
		destroy=BREAKING;
	}

	// MANA REGEN;
	if (manaCooldown==0){
		this->add_tempMP((this->get_MP()-1)/60+1);
		manaCooldown=30;
	} else {
		manaCooldown--;
	}

	// MOVEMENT
	if ( actionState==ACTION_MOVING || (stepsFrames % 4) != 0 ){
		switch (dir){
			case DIR_DOWN:
				set_position(position.x,position.y+1*stepLength.y*speedMultiplier);
				stepsFrames++;
				break;
			case DIR_LEFT:
				set_position(position.x-1*stepLength.x*speedMultiplier,position.y);
				stepsFrames++;
				break;
			case DIR_RIGHT:
				set_position(position.x+1*stepLength.x*speedMultiplier,position.y);
				stepsFrames++;
				break;
			case DIR_UP:
				set_position(position.x,position.y-1*stepLength.y*speedMultiplier);
				stepsFrames++;
				break;
		}
	} else {
		stepsFrames = 0;
	}


	// COLLISIONS
	if(this->check_wall(scene->room))
		position=oldPos;
	for(charIter iter = scene->charComps.begin(); iter != scene->charComps.end(); ++iter){
		if (this==(*iter))
			continue;
		SDL_Rect otherCompRect = (*iter)->get_rect_after_angle();
		if ( this->check_collision(otherCompRect) ){
			position = oldPos;
		}
	}

	// SELECTING FRAME
	int deltaAnim;
	switch (stepsFrames/6 % 4){
	case 0:
	case 2:
		deltaAnim = 1; // dir*nAnims+1 gives the standing sprite of the character
		break;
	case 1:
		deltaAnim = 0;
		break;
	case 3:
		deltaAnim = 2;
		break;
	}
	currentSpriteRect = &spriteRects[dir*nAnims+deltaAnim];

	// UPDATING LIFEBAR
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	if ( !lifeBar->is_hidden() && !lifeBarRemain->is_hidden() ){
		lifeBar->set_position(this->position.x+3,this->position.y-2);
		lifeBar->set_spriteRectWidth(resources->stuffSpriteRects["lightRed"][0].w*tempHP/HP);
		lifeBarRemain->set_position(this->position.x+3+resources->stuffSpriteRects["darkRed"][0].w*tempHP/HP, this->position.y-2);
		lifeBarRemain->set_spriteRectWidth(resources->stuffSpriteRects["darkRed"][0].w*(HP-tempHP)/HP);
	}
}
