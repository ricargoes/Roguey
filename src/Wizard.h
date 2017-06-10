/*
 * Wizard.h
 *
 *  Created on: Feb 24, 2015
 *      Author: elgatil
 */

#ifndef WIZARD_H_
#define WIZARD_H_

#include "Minion.h"

class Wizard: public Minion {
public:
	Wizard( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, int level );
	virtual ~Wizard();

	void set_cooldown();

	void update();
};

#endif /* WIZARD_H_ */
