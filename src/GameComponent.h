/*
 * GameComponent.h
 *
 *  Created on: Jan 29, 2015
 *      Author: elgatil
 */

#ifndef GAMECOMPONENT_H_
#define GAMECOMPONENT_H_

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "types.h"
#include "ResourceManager.h"

#define UNBROKEN 0
#define BREAKING 1
#define BROKEN 2

class GameComponent {
public:
	GameComponent(SDL_Texture* loadedTexture, Point pos);
	virtual ~GameComponent();

	// Getters
	Point get_position(){ return position; }
	int get_destroy(){ return destroy; }

	//Setters
	void set_position(int x, int y){  oldPos = position; position = {x, y};}
	void advance_destroy(){ destroy++; }

	virtual void render(){ };
	virtual void update(){ }
	virtual void manage_input( SDL_Event e ){ }

protected:

	SDL_Texture* spriteSheet;


	Point position = {64, 64};
	Point oldPos = {0,0};

	// Rotation and reflexion
	double angle;
	SDL_Point* center;
	SDL_RendererFlip flip;

	int destroy;

};

#endif /* GAMECOMPONENT_H_ */
