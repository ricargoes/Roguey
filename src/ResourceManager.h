/*
 * ResourceManager.h
 *
 *  Created on: Feb 3, 2015
 *      Author: elgatil
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <vector>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "types.h"

#define RESOURCEMANAGER_MODE_INIT 0
#define RESOURCEMANAGER_MODE_RESET 1
#define RESOURCEMANAGER_MODE_CLOSE 2

class ResourceManager {

public:
	/**
	 * Singleton instance management.
	 * \param instanceMode Concrete request for the instance manager.
	 */
	static ResourceManager* instance(int instanceMode);


	//The window we'll be rendering to
	SDL_Window* gameWindow;

	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	//The window renderer
	SDL_Renderer* gameRenderer;

	//Globally used font
	TTF_Font* gameFont = NULL;

	// Tile size
	Size tileSize;


	Image* heroSheet;
	std::map<std::string, std::vector<SDL_Rect> > heroSpriteRects;
	Image* dungeonSheet;
	std::map<std::string, std::vector<SDL_Rect> > dungeonSpriteRects;
	Image* stuffSheet;
	std::map<std::string, std::vector<SDL_Rect> > stuffSpriteRects;

	bool success;

	Image* loadFromFile( std::string path, Uint8 r=0xFF, Uint8 g=0xFF, Uint8 b=0xFF );
	void free(SDL_Texture* texture);
	void render( Image* image, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	void close();

	INIConfig read_INIConfig( std::string filename );

private:

	/** Private constructor to Singleton isolation. */
	ResourceManager();

	/** Private destructor to Singleton isolation. */
	~ResourceManager();

	/** Copy operator (private because is disabled by default). */
	ResourceManager(const ResourceManager&);

	/** Assing operator (private because is disabled by default). */
	void operator=(const ResourceManager&);

	bool init();
	bool loadMedia();
};

#endif /* RESOURCEMANAGER_H_ */
