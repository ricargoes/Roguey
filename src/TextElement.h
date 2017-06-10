/*
 * TextElement.h
 *
 *  Created on: Feb 11, 2015
 *      Author: elgatil
 */

#ifndef TEXTELEMENT_H_
#define TEXTELEMENT_H_

#include "GameComponent.h"

class TextElement: public GameComponent {
public:
	TextElement( SDL_Texture* loadedTexture, Point pos, std::string initialText="" );
	virtual ~TextElement();

	void set_text( std::string newText ){ text = newText; }

	void update();
	void render();

protected:
	std::string text;
	std::string oldText;
	Size textSize;
};


#endif /* TEXTELEMENT_H_ */
