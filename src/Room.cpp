/*
 * Room.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: elgatil
 */

#include "Room.h"

Room::Room( SDL_Texture* loadedTexture, Point pos, Size size, SDL_Rect floorSprite, SDL_Rect wallSprite, std::vector<SDL_Rect> floorVarSprites, std::vector<SDL_Rect> wallVarSprites)
	: GameComponent( loadedTexture, pos ) {

	roomSize = size;
	floorSpriteRect = floorSprite;
	floorVarSpriteRects = floorVarSprites;
	wallSpriteRect = wallSprite;
	wallVarSpriteRects = wallVarSprites;
}

void Room::update(){

}


void Room::render(){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	SDL_Rect screenPosRect;
	screenPosRect.w = floorSpriteRect.w;
	screenPosRect.h = floorSpriteRect.h;

	Point ini = position;
	Point end = {position.x+roomSize.x,position.y+roomSize.y};
	SDL_Rect currentSpriteRect;

	std::vector<SDL_Rect>::size_type sizeVarFloor = floorVarSpriteRects.size();
	std::vector<SDL_Rect>::size_type sizeVarWall = wallVarSpriteRects.size();
	std::vector<SDL_Rect>::size_type delta;
	srand (scene->dangerLvl);
	for(int y=ini.y; y<end.y; y+=resources->tileSize.y){
		for(int x=ini.x; x<end.x; x+=resources->tileSize.x){ // Rendering background
			if(y==ini.y || x==ini.x || y>=(end.y-1*resources->tileSize.x) || x>=(end.x-1*resources->tileSize.x)){
				if (sizeVarWall!=0 && (delta=std::rand()%(sizeVarWall*10))<sizeVarWall ){ // Render a wall variation with a 10% probability
					currentSpriteRect = wallVarSpriteRects[delta];
				}else{
					currentSpriteRect = wallSpriteRect;
				}
			}else{
				if (sizeVarFloor!=0 && (delta=std::rand()%(sizeVarFloor*10))<sizeVarFloor ){ // Render a floor variation with a 10% probability
					currentSpriteRect = floorVarSpriteRects[delta];
				}else{
					currentSpriteRect = floorSpriteRect;
				}
			}
			screenPosRect.x = x;
			screenPosRect.y = y;
			SDL_RenderCopyEx( resources->gameRenderer, spriteSheet, &currentSpriteRect, &screenPosRect, angle, center, flip );
		}
	}

}
