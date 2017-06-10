/*
 * TextElement.cpp
 *
 *  Created on: Feb 11, 2015
 *      Author: elgatil
 */

#include "TextElement.h"

TextElement::TextElement( SDL_Texture* loadedTexture, Point pos, std::string initialText )
	: GameComponent( loadedTexture, pos ) {
	text = initialText;
	oldText = "";
	textSize = { 0, 0 };
	update();
}

TextElement::~TextElement() {

}


void TextElement::update(){

	if (text == oldText){
		return;
	}

	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);

	//Get rid of preexisting texture
	resources->free( spriteSheet );

	//Render text surface
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
	SDL_Surface* textSurface = TTF_RenderText_Solid( resources->gameFont, text.c_str(), textColor );
	if( textSurface == NULL ) {
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
		return;
	}
	//Create texture from surface pixels
	spriteSheet = SDL_CreateTextureFromSurface( resources->gameRenderer, textSurface );
	if( spriteSheet == NULL ) {
		printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		return;
	}
	//Get image dimensions
	textSize.x = textSurface->w;
	textSize.y = textSurface->h;

	text = oldText;

	//Get rid of old surface
	SDL_FreeSurface( textSurface );

}

void TextElement::render(){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);

	SDL_Rect screenPosRect;
	screenPosRect.x = position.x;
	screenPosRect.y = position.y;
	screenPosRect.w = textSize.x;
	screenPosRect.h = textSize.y;

	//Render to screen
	SDL_RenderCopyEx( resources->gameRenderer, spriteSheet, NULL, &screenPosRect, angle, center, flip );
}
