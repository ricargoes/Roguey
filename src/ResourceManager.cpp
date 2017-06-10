/*
 * ResourceManager.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: elgatil
 */

#include "ResourceManager.h"


ResourceManager::ResourceManager() {

	//Start up SDL and create window
	if ( !init() ){
		printf( "Failed to initialize!\n" );
		success = false;
		return;
	}

	//Load media
	if ( !loadMedia() ){
		printf( "Failed to load media!\n" );
		success = false;
		return;
	}

	success = true;
}


ResourceManager::~ResourceManager() {

}


// Singleton instance manager.
ResourceManager* ResourceManager::instance(int instanceMode) {

	static ResourceManager *instance;

	if(instance) {
		switch(instanceMode) {
			case RESOURCEMANAGER_MODE_RESET:
				delete instance;
				instance = new ResourceManager();
				break;
			case RESOURCEMANAGER_MODE_CLOSE:
				delete instance;
				break;
			case RESOURCEMANAGER_MODE_INIT:
				break;
			default:
				return 0;
				break;
		}
	} else {
		switch(instanceMode) {
			case RESOURCEMANAGER_MODE_INIT:
				instance = new ResourceManager();
				break;
			case RESOURCEMANAGER_MODE_CLOSE:
			case RESOURCEMANAGER_MODE_RESET:
			default:
				return 0;
				break;
		}
	}
	return instance;
}


void ResourceManager::close(){
	//Free loaded images
	free( heroSheet->texture );
    delete heroSheet;
	free( dungeonSheet->texture );
    delete dungeonSheet;
	free( stuffSheet->texture );
    delete stuffSheet;

	//Free global font
	TTF_CloseFont( gameFont );
	gameFont = NULL;

	//Destroy window
	SDL_DestroyRenderer( gameRenderer );
	SDL_DestroyWindow( gameWindow );
	gameWindow = NULL;
	gameRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


void ResourceManager::free( SDL_Texture* texture ) {
    //Free texture if it exists
    if( texture != NULL ) {
        SDL_DestroyTexture( texture );
        texture = NULL;
    }
}


Image* ResourceManager::loadFromFile( std::string path, Uint8 r, Uint8 g, Uint8 b ){

	//The final image
	Image* image = new Image();

    //Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
		return NULL;
	}

	//Color key image
	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, r, g, b ) );

	//Create texture from surface pixels
	image->texture = SDL_CreateTextureFromSurface( gameRenderer, loadedSurface );
	if( image->texture == NULL ) {
		printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		return NULL;
	}

	//Get image dimensions
	image->textSize.x = loadedSurface->w;
	image->textSize.y = loadedSurface->h;

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );

	return image;
}


void ResourceManager::render(Image* image, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ) {

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, image->textSize.x, image->textSize.y };

	//Set clip rendering dimensions
	if( clip != NULL ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gameRenderer, image->texture, clip, &renderQuad, angle, center, flip );
}


bool ResourceManager::init(){
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}

	//Create window
	gameWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gameWindow == NULL ) {
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}

	//Create renderer for window
	gameRenderer = SDL_CreateRenderer( gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( gameRenderer == NULL ) {
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	SDL_SetRenderDrawColor( gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF ); //Initialize renderer color

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}

	 //Initialize SDL_ttf
	if( TTF_Init() == -1 ) {
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}

	return true;
}


bool ResourceManager::loadMedia(){

	// TEXTURES
	//Load sprite sheet texture
	heroSheet = loadFromFile( "media/heroSprite.png" );
	dungeonSheet = loadFromFile( "media/dungeonSpritesMod.gif" );
	stuffSheet = loadFromFile( "media/stuffMod.png", 0x46, 0x6D, 0x6C );
	if( dungeonSheet->texture==NULL || heroSheet->texture==NULL || stuffSheet->texture==NULL ) {
		printf( "Failed to load sprite sheet textures!\n" );
		return false;
	}

	int wDunSp = dungeonSheet->textSize.x/9; // 32px
	int hDunSp = dungeonSheet->textSize.y/10; // 32px

	int wHeroSp = heroSheet->textSize.x/12; // 32px
	int hHeroSp = heroSheet->textSize.y/8; // 32px

	int wStuffSp = stuffSheet->textSize.x/40; // 26px
	int hStuffSp = stuffSheet->textSize.y/30; // 26px


	SDL_Rect dummyRect; // { x, y, width, height }

	for (int i=0; i<0+4; i++){ // Scarf Hero Sprites
		for (int j=0; j<0+3; j++){
			dummyRect = { j*wHeroSp, i*hHeroSp, wHeroSp, hHeroSp }; // { x, y, width, height }
			heroSpriteRects["ScarfHero"].push_back(dummyRect);
		}
	}

	for (int i=0; i<0+4; i++){ // Blue Hero Sprites
		for (int j=3; j<3+3; j++){
			dummyRect = { j*wHeroSp, i*hHeroSp, wHeroSp, hHeroSp }; // { x, y, width, height }
			heroSpriteRects["BlueHero"].push_back(dummyRect);
		}
	}

	for (int i=0; i<0+4; i++){ // Red Hero Sprites
		for (int j=6; j<6+3; j++){
			dummyRect = { j*wHeroSp, i*hHeroSp, wHeroSp, hHeroSp }; // { x, y, width, height }
			heroSpriteRects["RedHero"].push_back(dummyRect);
		}
	}

	for (int i=0; i<0+4; i++){ // Brown Hero Sprites
		for (int j=9; j<9+3; j++){
			dummyRect = { j*wHeroSp, i*hHeroSp, wHeroSp, hHeroSp }; // { x, y, width, height }
			heroSpriteRects["BrownHero"].push_back(dummyRect);
		}
	}

	for (int i=4; i<4+4; i++){ // Ash Hero Sprites
		for (int j=0; j<0+3; j++){
			dummyRect = { j*wHeroSp, i*hHeroSp, wHeroSp, hHeroSp }; // { x, y, width, height }
			heroSpriteRects["AshHero"].push_back(dummyRect);
		}
	}

	for (int i=4; i<4+4; i++){ // Ash Heroine Sprites
		for (int j=3; j<3+3; j++){
			dummyRect = { j*wHeroSp, i*hHeroSp, wHeroSp, hHeroSp }; // { x, y, width, height }
			heroSpriteRects["AshHeroine"].push_back(dummyRect);
		}
	}

	for (int i=4; i<4+4; i++){ // Scarf White Hero Sprites
		for (int j=6; j<6+3; j++){
			dummyRect = { j*wHeroSp, i*hHeroSp, wHeroSp, hHeroSp }; // { x, y, width, height }
			heroSpriteRects["ScarfWhiteHero"].push_back(dummyRect);
		}
	}

	for (int i=4; i<4+4; i++){ // Angel Sprites
		for (int j=9; j<9+3; j++){
			dummyRect = { j*wHeroSp, i*hHeroSp, wHeroSp, hHeroSp }; // { x, y, width, height }
			heroSpriteRects["Angel"].push_back(dummyRect);
		}
	}

	dummyRect = { 0*wDunSp, 5*hDunSp, wDunSp, hDunSp }; // { x, y, width, height }
	dungeonSpriteRects["Wall"].push_back(dummyRect);
	dummyRect = { 2*wDunSp, 5*hDunSp, wDunSp, hDunSp }; // { x, y, width, height }
	dungeonSpriteRects["WallVar"].push_back(dummyRect);
	dummyRect = { 4*wDunSp, 5*hDunSp, wDunSp, hDunSp }; // { x, y, width, height }
	dungeonSpriteRects["WallVar"].push_back(dummyRect);

	dummyRect = { 0*wDunSp, 8*hDunSp, wDunSp, hDunSp }; // { x, y, width, height }
	dungeonSpriteRects["Floor"].push_back(dummyRect);
	dummyRect = { 3*wDunSp, 8*hDunSp, wDunSp, hDunSp }; // { x, y, width, height }
	dungeonSpriteRects["FloorVar"].push_back(dummyRect);

	dummyRect = { 4*wStuffSp, 16*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["Life"].push_back(dummyRect);
	dummyRect = { 5*wStuffSp, 15*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["Mana"].push_back(dummyRect);
	dummyRect = { 10*wStuffSp, 13*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["Defense"].push_back(dummyRect);
	dummyRect = { 16*wStuffSp, 13*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["Boots"].push_back(dummyRect);
	dummyRect = { 31*wStuffSp, 10*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["Sword"].push_back(dummyRect);
	dummyRect = { 19*wStuffSp, 11*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["Bow"].push_back(dummyRect);
	dummyRect = { 35*wStuffSp, 9*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["Arrow"].push_back(dummyRect);
	dummyRect = { 12*wStuffSp, 22*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["Explosion"].push_back(dummyRect);
	dummyRect = { 17*wStuffSp, 22*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["Explosion"].push_back(dummyRect);
	dummyRect = { 20*wStuffSp, 22*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["Explosion"].push_back(dummyRect);
	dummyRect = { 22*wStuffSp, 22*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["Explosion"].push_back(dummyRect);
	dummyRect = { 39*wStuffSp, 2*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["Teleport"].push_back(dummyRect);

	dummyRect = { 2*wStuffSp, 20*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["LockerRed"].push_back(dummyRect);
	dummyRect = { 10*wStuffSp, 20*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["LockerBlue"].push_back(dummyRect);

	dummyRect = { 0*wStuffSp, 29*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["lightRed"].push_back(dummyRect);
	dummyRect = { 1*wStuffSp, 29*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["lightBlue"].push_back(dummyRect);
	dummyRect = { 2*wStuffSp, 29*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["lightGreen"].push_back(dummyRect);
	dummyRect = { 3*wStuffSp, 29*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["lightYellow"].push_back(dummyRect);
	dummyRect = { 0*wStuffSp, 28*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["darkRed"].push_back(dummyRect);
	dummyRect = { 1*wStuffSp, 28*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["darkBlue"].push_back(dummyRect);
	dummyRect = { 2*wStuffSp, 28*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["darkGreen"].push_back(dummyRect);
	dummyRect = { 3*wStuffSp, 28*hStuffSp, wStuffSp, hStuffSp }; // { x, y, width, height }
	stuffSpriteRects["darkYellow"].push_back(dummyRect);

	tileSize.x = dungeonSpriteRects["Floor"][0].w;
	tileSize.y = dungeonSpriteRects["Floor"][0].h;


	// FONTS
	//Open the font
	gameFont = TTF_OpenFont( "media/FreeMono.ttf", 18 );
	if( gameFont == NULL ){
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}



	return true;
}


INIConfig ResourceManager::read_INIConfig( std::string filename ){
	std::ifstream file(filename.c_str());

	std::string s;

	INIConfig Map;
	std::string tempGroupKey;
	Group tempControl;
	std::string tempKey;
	std::string tempValue;

	std::string::size_type i=0;
	std::string::size_type j=0;


	while (getline(file, s)){
		if ((i = s.find('[')) != std::string::npos && (j = s.find(']')) != std::string::npos && (j-i)>1 ){
			if ( !tempGroupKey.empty() )
				Map[tempGroupKey] = tempControl;
			tempGroupKey = s.substr(i+1,j-1-i);
		} else if ( (i = s.find('=')) != std::string::npos ){
			tempKey = s.substr(0,i);
			tempValue = s.substr(i+1);
			tempControl[tempKey] = std::stoi(tempValue);
		}

		Map[tempGroupKey] = tempControl;
	}
	file.close();
	return Map;
}

