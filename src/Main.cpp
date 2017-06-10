
#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "types.h"
#include "SceneGraph.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Minion.h"
#include "Room.h"
#include "HUDElement.h"
#include "TextElement.h"
#include "GameManager.h"

#include "toolbox.h"


int main() {

	// Initialize SDL and load media
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	if( !resources->success ) {
		printf( "Failed to initialize!\n" );
		return -1;
	}

	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	bool quit=false;
	SDL_Event e; //Event handler
	unsigned int lastTime = 0, currentTime;

	std::string hero1Name;
	bool player2bool=false;
	std::string hero2Name;

	GameManager* GM = new GameManager();

	if (!quit){
		scene->gameMode=GM->choose_game_mode();
		if (scene->gameMode==-1) quit=true;
		if (scene->gameMode==GAMEMODE_COOP || scene->gameMode==GAMEMODE_VERSUS ) player2bool=true;
	}
	if (!quit){
		hero1Name = GM->choose_your_hero("Player 1");
		quit = hero1Name.empty();
	}
	if (!quit && player2bool){
		hero2Name = GM->choose_your_hero("Player 2");
		quit = hero2Name.empty();
	}
	if (!quit){ // Room and Heroes initialization
		scene->room = new Room( resources->dungeonSheet->texture, {0, 0}, {15*resources->tileSize.x,15*resources->tileSize.y}, resources->dungeonSpriteRects["Floor"][0], resources->dungeonSpriteRects["Wall"][0],resources->dungeonSpriteRects["FloorVar"], resources->dungeonSpriteRects["WallVar"]);

		scene->hero1 = new Player( resources->heroSheet->texture, {2*resources->tileSize.x, 4*resources->tileSize.y}, 3, resources->heroSpriteRects[hero1Name], 1 );
		scene->charComps.push_back(scene->hero1);
		if (player2bool){
			scene->hero2 = new Player( resources->heroSheet->texture, {1*resources->tileSize.x, 1*resources->tileSize.y}, 3, resources->heroSpriteRects[hero2Name], 2 );
			scene->charComps.push_back(scene->hero2);
		}

		GM->initialize_HUD();

	}
	if (!quit){
		if (scene->gameMode==GAMEMODE_SINGLEPLAYER || scene->gameMode==GAMEMODE_COOP){
			Minion* baddie = new Minion( resources->heroSheet->texture, {1*resources->tileSize.x, 5*resources->tileSize.y}, 3, resources->heroSpriteRects["RedHero"], 30, 10 );
			scene->charComps.push_back(baddie);
			scene->enemiesLeft++;
		} else if (scene->gameMode==GAMEMODE_VERSUS){
			const int manyLevels=8;
			for (int i=0; i<manyLevels; i++){
				GM->level_up(scene->hero1);
				GM->level_up(scene->hero2);
			}
		}
		scene->hero1->initialize_lockOn();
		if(scene->hero2) scene->hero2->initialize_lockOn();
	}

	//Game loop
	while( !quit ) {

		// Limit frame rate to 30fps
		currentTime = SDL_GetTicks();
		if (currentTime - lastTime < 33)
			SDL_Delay( 33-(currentTime-lastTime) );
		lastTime = currentTime;

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				quit = true;
			} else if( e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch( e.key.keysym.sym ) {
					case SDLK_ESCAPE:
					quit = true;
					break;
				}
			}
			for(charIter iter = scene->charComps.begin(); iter != scene->charComps.end(); ++iter){
				(*iter)->manage_input(e);
			}
		} // Event loop ends

		//Clear screen
		SDL_SetRenderDrawColor( resources->gameRenderer, 0x00, 0x00, 0x00, 0x00 );
		SDL_RenderClear( resources->gameRenderer );

		GM->update_HUD();

		scene->room->update();
		for(charIter iter = scene->charComps.begin(); iter!=scene->charComps.end(); ++iter){
			(*iter)->update();
		}
		for(objIter iter = scene->objectComps.begin(); iter!=scene->objectComps.end(); ++iter){
			(*iter)->update();
		}
		for(elseIter iter = scene->elseComps.begin(); iter!=scene->elseComps.end(); ++iter){
			(*iter)->update();
		}

		scene->room->render();
		for(charIter iter = scene->charComps.begin(); iter!=scene->charComps.end(); ++iter){
			(*iter)->render();
		}
		for(objIter iter = scene->objectComps.begin(); iter!=scene->objectComps.end(); ++iter){
			(*iter)->render();
		}
		for(elseIter iter = scene->elseComps.begin(); iter!=scene->elseComps.end(); ++iter){
			(*iter)->render();
		}



		//Update screen
		SDL_RenderPresent( resources->gameRenderer );

		// GameComponents vector Maintenance
		update_components();


		switch(scene->check_state_of_the_game()){
		case GAME_ON:
			break;
		case GAME_LEVEL_CLEARED:
			if( !GM->transition(1) ) quit=true;
			break;
		case GAME_END:
			GM->scores_screen();
			quit=true;
			break;
		}
	} // Gameloop ends

	//Free resources and close SDL
	delete GM;
	scene->close();
	SceneGraph::instance(SCENEGRAPH_MODE_DELETE);
	resources->close();
	ResourceManager::instance(RESOURCEMANAGER_MODE_CLOSE);

	return 0;
}
