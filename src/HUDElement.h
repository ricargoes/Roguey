/*
 * HUDElement.h
 *
 *  Created on: Feb 11, 2015
 *      Author: elgatil
 */

#ifndef HUDELEMENT_H_
#define HUDELEMENT_H_

#include "GameComponent.h"

class HUDElement: public GameComponent {
public:
	HUDElement(SDL_Texture* loadedTexture, Point pos, SDL_Rect spRect, int frameCountdown=-1);
	virtual ~HUDElement();

	bool is_hidden(){ return hidden; }

	void set_countdown( int frameCountdown ){ hideCountdown = frameCountdown; }
	void toggle_hidden(){ hidden = !hidden;}
	void set_spriteRectWidth( int newWidth ){ spriteRect.w = newWidth; }

	void update();
	void render();

protected:
	SDL_Rect spriteRect;
	int hideCountdown;
	int destroyCountdown;
	bool hidden;
};

#endif /* HUDELEMENT_H_ */
