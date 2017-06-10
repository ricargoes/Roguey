/*
 * InGameComp.h
 *
 *  Created on: Feb 3, 2015
 *      Author: elgatil
 */

#ifndef INGAMECOMP_H_
#define INGAMECOMP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "types.h"
#include "ResourceManager.h"
#include "SceneGraph.h"
#include "Room.h"
#include "GameComponent.h"

#define ACTION_FREE 0
#define ACTION_MOVING 1
#define ACTION_ATTACK 2
#define ACTION_CASTING 3

#define DIR_DOWN 0
#define DIR_LEFT 1
#define DIR_RIGHT 2
#define DIR_UP 3

class InGameComp: public GameComponent {
public:
	InGameComp( SDL_Texture* loadedTexture, Point pos , int nAnimSprites, std::vector<SDL_Rect> spRects );
	virtual ~InGameComp();

	Size get_currentSpriteSize() { return {currentSpriteRect->w, currentSpriteRect->h}; }
	int get_speedMultiplier(){ return speedMultiplier; }
	int get_dir(){ return dir; }
	SDL_Rect get_rect_after_angle();
	int get_actionState(){ return actionState; }

	void set_speedMultiplier(int multiplier){ speedMultiplier=multiplier; }
	void set_action_free(){ actionState=ACTION_FREE; }
	void set_dir( int direction ){ dir=direction; }

	bool check_collision( SDL_Rect& r );
	bool check_wall( Room* room );

	void render();

protected:
	int nAnims; // Number of sprites in each animation
	std::vector<SDL_Rect> spriteRects; // Position of the desired sprites inside the texture
	SDL_Rect* currentSpriteRect;

	int dir;
	int actionState;
	Size stepLength;
	int speedMultiplier;
	int stepsFrames; // Counts how many frames the comp. is moving



};

#endif /* INGAMECOMP_H_ */
