/*
 * Room.h
 *
 *  Created on: Jan 24, 2015
 *      Author: elgatil
 */

#ifndef ROOM_H_
#define ROOM_H_

#include <string>
#include <vector>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "types.h"
#include "ResourceManager.h"
#include "SceneGraph.h"
#include "GameComponent.h"

class Room: public GameComponent {

public:
	Room(SDL_Texture* loadedTexture, Point pos, Size size, SDL_Rect floorSprite, SDL_Rect wallSprite, std::vector<SDL_Rect> floorVarSprites={}, std::vector<SDL_Rect> wallVarSprites={});
	Size get_size(){ return roomSize; }

	void update();
	void render();

private:
	Size roomSize; // Size of the room in pixels
	SDL_Rect floorSpriteRect;
	std::vector<SDL_Rect> floorVarSpriteRects;
	SDL_Rect wallSpriteRect;
	std::vector<SDL_Rect> wallVarSpriteRects;

};
#endif /* ROOM_H_ */
