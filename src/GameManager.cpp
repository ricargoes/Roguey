/*
 * Interface.cpp
 *
 *  Created on: Feb 22, 2015
 *      Author: elgatil
 */

#include "GameManager.h"

GameManager::GameManager() {
	HPText=NULL; MPText=NULL; defenseText=NULL; bootsText=NULL;
	swordText=NULL; bowText=NULL; explosionText=NULL; teleportText=NULL; score=NULL;
	lifeIcon=NULL; manaIcon=NULL; defenseIcon=NULL; bootsIcon=NULL;
	swordIcon=NULL; bowIcon=NULL; explosionIcon=NULL; teleportIcon=NULL;

	HPText2=NULL; MPText2=NULL; defenseText2=NULL; bootsText2=NULL;
	swordText2=NULL; bowText2=NULL; explosionText2=NULL; teleportText2=NULL; score2=NULL;
	lifeIcon2=NULL; manaIcon2=NULL; defenseIcon2=NULL; bootsIcon2=NULL;
	swordIcon2=NULL; bowIcon2=NULL; explosionIcon2=NULL; teleportIcon2=NULL;
}


void GameManager::initialize_HUD() {
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	lifeIcon = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-145, 35}, resources->stuffSpriteRects["Life"][0] );
	HPText = new TextElement( NULL, {resources->SCREEN_WIDTH-115, 38} );
	scene->elseComps.push_back(lifeIcon);
	scene->elseComps.push_back(HPText);
	manaIcon = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-145, 65}, resources->stuffSpriteRects["Mana"][0] );
	MPText = new TextElement( NULL, {resources->SCREEN_WIDTH-115, 68} );
	scene->elseComps.push_back(manaIcon);
	scene->elseComps.push_back(MPText);
	defenseIcon = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-145, 95}, resources->stuffSpriteRects["Defense"][0] );
	defenseText = new TextElement( NULL, {resources->SCREEN_WIDTH-115, 98} );
	scene->elseComps.push_back(defenseIcon);
	scene->elseComps.push_back(defenseText);
	bootsIcon = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-80, 95}, resources->stuffSpriteRects["Boots"][0] );
	bootsText = new TextElement( NULL, {resources->SCREEN_WIDTH-55, 98} );
	scene->elseComps.push_back(bootsIcon);
	scene->elseComps.push_back(bootsText);

	swordIcon = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-120, 150}, resources->stuffSpriteRects["Sword"][0] );
	swordText = new TextElement( NULL, {resources->SCREEN_WIDTH-145, 153} );
	scene->elseComps.push_back(swordIcon);
	scene->elseComps.push_back(swordText);
	bowIcon = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-60, 150}, resources->stuffSpriteRects["Bow"][0] );
	bowText = new TextElement( NULL, {resources->SCREEN_WIDTH-85, 153} );
	scene->elseComps.push_back(bowIcon);
	scene->elseComps.push_back(bowText);
	explosionIcon = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-120, 180}, resources->stuffSpriteRects["Explosion"][0] );
	explosionText = new TextElement( NULL, {resources->SCREEN_WIDTH-145, 183} );
	scene->elseComps.push_back(explosionIcon);
	scene->elseComps.push_back(explosionText);
	teleportIcon = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-60, 180}, resources->stuffSpriteRects["Teleport"][0] );
	teleportText = new TextElement( NULL, {resources->SCREEN_WIDTH-85, 183} );
	scene->elseComps.push_back(teleportIcon);
	scene->elseComps.push_back(teleportText);

	score = new TextElement( NULL, {resources->SCREEN_WIDTH-140, 210} );
	scene->elseComps.push_back(score);


	if (scene->hero2){
		lifeIcon2 = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-145, 265}, resources->stuffSpriteRects["Life"][0] );
		HPText2 = new TextElement( NULL, {resources->SCREEN_WIDTH-115, 268} );
		scene->elseComps.push_back(lifeIcon2);
		scene->elseComps.push_back(HPText2);
		manaIcon2 = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-145, 295}, resources->stuffSpriteRects["Mana"][0] );
		MPText2 = new TextElement( NULL, {resources->SCREEN_WIDTH-115, 298} );
		scene->elseComps.push_back(manaIcon2);
		scene->elseComps.push_back(MPText2);
		defenseIcon2 = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-145, 325}, resources->stuffSpriteRects["Defense"][0] );
		defenseText2 = new TextElement( NULL, {resources->SCREEN_WIDTH-115, 328} );
		scene->elseComps.push_back(defenseIcon2);
		scene->elseComps.push_back(defenseText2);
		bootsIcon2 = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-80, 325}, resources->stuffSpriteRects["Boots"][0] );
		bootsText2 = new TextElement( NULL, {resources->SCREEN_WIDTH-55, 328} );
		scene->elseComps.push_back(bootsIcon2);
		scene->elseComps.push_back(bootsText2);

		swordIcon2 = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-120, 380}, resources->stuffSpriteRects["Sword"][0] );
		swordText2 = new TextElement( NULL, {resources->SCREEN_WIDTH-145, 383} );
		scene->elseComps.push_back(swordIcon2);
		scene->elseComps.push_back(swordText2);
		bowIcon2 = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-60, 380}, resources->stuffSpriteRects["Bow"][0] );
		bowText2 = new TextElement( NULL, {resources->SCREEN_WIDTH-85, 383} );
		scene->elseComps.push_back(bowIcon2);
		scene->elseComps.push_back(bowText2);
		explosionIcon2 = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-120, 410}, resources->stuffSpriteRects["Explosion"][0] );
		explosionText2 = new TextElement( NULL, {resources->SCREEN_WIDTH-145, 413} );
		scene->elseComps.push_back(explosionIcon2);
		scene->elseComps.push_back(explosionText2);
		teleportIcon2 = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH-60, 410}, resources->stuffSpriteRects["Teleport"][0] );
		teleportText2 = new TextElement( NULL, {resources->SCREEN_WIDTH-85, 413} );
		scene->elseComps.push_back(teleportIcon2);
		scene->elseComps.push_back(teleportText2);

		score2 = new TextElement( NULL, {resources->SCREEN_WIDTH-140, 440} );
		scene->elseComps.push_back(score2);
	}

}


GameManager::~GameManager() {

}


void GameManager::update_HUD(){
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);
	if (scene->hero1){
		HPText->set_text( std::to_string(scene->hero1->get_tempHP())+" / "+std::to_string(scene->hero1->get_HP()) );
		MPText->set_text( std::to_string(scene->hero1->get_tempMP())+" / "+std::to_string(scene->hero1->get_MP()) );
		bootsText->set_text( std::to_string(scene->hero1->get_speedMultiplier())+"x" );
		defenseText->set_text( std::to_string(scene->lvlLegend["defense"][std::to_string(scene->hero1->get_defenseLvl())]) );
		swordText->set_text( "L"+std::to_string(scene->hero1->get_swordLvl()) );
		bowText->set_text( "L"+std::to_string(scene->hero1->get_bowLvl()) );
		explosionText->set_text( "L"+std::to_string(scene->hero1->get_explosionLvl()) );
		teleportText->set_text( "L"+std::to_string(scene->hero1->get_teleportLvl()) );
		score->set_text( std::to_string(scene->hero1->get_points())+" points" );
	}
	if (scene->hero2){
		HPText2->set_text( std::to_string(scene->hero2->get_tempHP())+" / "+std::to_string(scene->hero2->get_HP()) );
		MPText2->set_text( std::to_string(scene->hero2->get_tempMP())+" / "+std::to_string(scene->hero2->get_MP()) );
		bootsText2->set_text( std::to_string(scene->hero2->get_speedMultiplier())+"x" );
		defenseText2->set_text( std::to_string(scene->lvlLegend["defense"][std::to_string(scene->hero2->get_defenseLvl())]) );
		swordText2->set_text( "L"+std::to_string(scene->hero2->get_swordLvl()) );
		bowText2->set_text( "L"+std::to_string(scene->hero2->get_bowLvl()) );
		explosionText2->set_text( "L"+std::to_string(scene->hero2->get_explosionLvl()) );
		teleportText2->set_text( "L"+std::to_string(scene->hero2->get_teleportLvl()) );
		score2->set_text( std::to_string(scene->hero2->get_points())+" points" );
	}
}


int GameManager::choose_game_mode(){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	int gameMode=-1;

	// Clear screen
	SDL_SetRenderDrawColor( resources->gameRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( resources->gameRenderer );
	// Set screen elements
	TextElement* question = new TextElement( NULL, {resources->SCREEN_WIDTH/2-60, resources->SCREEN_HEIGHT/2-80}, "GAMEMODE" );
	TextElement* option1 = new TextElement( NULL, {resources->SCREEN_WIDTH/2-90, resources->SCREEN_HEIGHT/2-30}, "(1)   Singleplayer" );
	TextElement* option2 = new TextElement( NULL, {resources->SCREEN_WIDTH/2-90, resources->SCREEN_HEIGHT/2}, "(2)   Coop" );
	TextElement* option3 = new TextElement( NULL, {resources->SCREEN_WIDTH/2-90, resources->SCREEN_HEIGHT/2+30}, "(3)   Versus" );
	question->render();
	option1->render(); option2->render(); option3->render();
	// Update screen
	SDL_RenderPresent( resources->gameRenderer );
	// Clean Elements
	delete question;
	delete option1; delete option2; delete option3;


	// Sub-game loop
	bool end=false;
	SDL_Event e;
	unsigned int lastTime = 0, currentTime;
	while(!end){

		// Limit frame rate to 30fps
		currentTime = SDL_GetTicks();
		if (currentTime - lastTime < 33)
			SDL_Delay( 33-(currentTime-lastTime) );
		lastTime = currentTime;

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				return -1;
			} else if( e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch( e.key.keysym.sym ) {
					case SDLK_ESCAPE:
						return -1;
						break;
					case SDLK_1:
						gameMode=GAMEMODE_SINGLEPLAYER;
						end = true;
						break;
					case SDLK_2:
						gameMode=GAMEMODE_COOP;
						end = true;
						break;
					case SDLK_3:
						gameMode=GAMEMODE_VERSUS;
						end = true;
						break;
				}
			}
		} // Event loop ends
	}
	return gameMode;
}


std::string GameManager::choose_your_hero(std::string subtext){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	std::string heroName;

	// Clear screen
	SDL_SetRenderDrawColor( resources->gameRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( resources->gameRenderer );
	// Set screen elements
	TextElement* question = new TextElement( NULL, {resources->SCREEN_WIDTH/2-100, resources->SCREEN_HEIGHT/2-80}, "Choose your hero:" );
	HUDElement* option1 = new HUDElement( resources->heroSheet->texture, {resources->SCREEN_WIDTH/2-220, resources->SCREEN_HEIGHT/2-40}, resources->heroSpriteRects["ScarfHero"][0] );
	HUDElement* option2 = new HUDElement( resources->heroSheet->texture, {resources->SCREEN_WIDTH/2-88, resources->SCREEN_HEIGHT/2-40}, resources->heroSpriteRects["AshHero"][0] );
	HUDElement* option3 = new HUDElement( resources->heroSheet->texture, {resources->SCREEN_WIDTH/2+44, resources->SCREEN_HEIGHT/2-40}, resources->heroSpriteRects["AshHeroine"][0] );
	HUDElement* option4 = new HUDElement( resources->heroSheet->texture, {resources->SCREEN_WIDTH/2+176, resources->SCREEN_HEIGHT/2-40}, resources->heroSpriteRects["ScarfWhiteHero"][0] );
	TextElement* options = new TextElement( NULL, {resources->SCREEN_WIDTH/2-220, resources->SCREEN_HEIGHT/2}, "(1)         (2)         (3)         (4)" );
	TextElement* subtextElement = new TextElement( NULL, {resources->SCREEN_WIDTH/2-50, resources->SCREEN_HEIGHT/2+30}, subtext );
	question->render();
	option1->render(); option2->render(); option3->render(); option4->render();
	options->render(); subtextElement->render();
	// Update screen
	SDL_RenderPresent( resources->gameRenderer );
	// Clean Elements
	delete question;
	delete option1; delete option2; delete option3; delete option4;
	delete options; delete subtextElement;


	// Sub-game loop
	bool quit=false;
	SDL_Event e;
	unsigned int lastTime = 0, currentTime;
	while(!quit){

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
					case SDLK_1:
						heroName="ScarfHero";
						quit = true;
						break;
					case SDLK_2:
						heroName="AshHero";
						quit = true;
						break;
					case SDLK_3:
						heroName="AshHeroine";
						quit = true;
						break;
					case SDLK_4:
						heroName="ScarfWhiteHero";
						quit = true;
						break;
				}
			}
		} // Event loop ends
	}
	return heroName;
}


bool GameManager::transition(int newLvls){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	// LEVELING UP
	Player* currentHero;
	scene->dangerLvl=0;
	for (int i=1; i<=2; i++){
		if ( i==1 ) currentHero=scene->hero1;
		if ( i==2 ) currentHero=scene->hero2;
		if(currentHero==NULL) continue;
		scene->dangerLvl+=currentHero->get_charLvl()-scene->OFFSET_LVL;

		for(int j=0; j<newLvls; j++){
			if(!level_up(currentHero)) return false;
		}
	}

	// CLEANING THE ROOM
	for(objIter iter = scene->objectComps.begin(); iter!=scene->objectComps.end(); ++iter){
		delete (*iter);
		scene->objectComps.erase(iter);
		--iter;
	}

	// GENERATING ENEMIES
	this->generate_enemies();

	// SETTING HEROES
	if (scene->hero1){
		scene->hero1->set_position(4*resources->tileSize.x, 3*resources->tileSize.y);
		scene->hero1->set_action_free(); scene->hero1->set_dir(DIR_DOWN);
		scene->hero1->initialize_lockOn();
	}
	if (scene->hero2){
		scene->hero2->set_position(7*resources->tileSize.x, 3*resources->tileSize.y);
		scene->hero2->set_action_free(); scene->hero2->set_dir(DIR_DOWN);
		scene->hero2->initialize_lockOn();
	}

	return true;
}


bool GameManager::level_up(Player* currentHero){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	std::string subtext;
	if (scene->hero1==currentHero) subtext="Player 1"; else if (scene->hero2==currentHero) subtext="Player 2";

	TextElement* question; TextElement* optionsUp; TextElement* optionLvlsUp; TextElement* optionsDown; TextElement* optionLvlsDown; TextElement* subtextElement;
	HUDElement* optionLife; HUDElement* optionMana; HUDElement* optionSword; HUDElement* optionBow;
	HUDElement* optionBoots; HUDElement* optionDefense; HUDElement* optionTeleport; HUDElement* optionExplosion;

	bool end;
	SDL_Event e;
	unsigned int lastTime = 0, currentTime;

	bool lifeCond=currentHero->get_HP()<300; bool manaCond=currentHero->get_MP()<180;
	bool defenseCond=(currentHero->get_defenseLvl()<5); bool bootsCond=currentHero->get_bootsLvl()<3;
	bool swordCond=currentHero->get_swordLvl()<10; bool bowCond=currentHero->get_bowLvl()<10;
	bool teleportCond=currentHero->get_teleportLvl()<3; bool explosionCond=currentHero->get_explosionLvl()<5;

	// Clear screen
	SDL_SetRenderDrawColor( resources->gameRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( resources->gameRenderer );
	// Set screen elements
	subtextElement = new TextElement( NULL, {resources->SCREEN_WIDTH/2-50, resources->SCREEN_HEIGHT/2-160}, subtext );
	question = new TextElement( NULL, {resources->SCREEN_WIDTH/2-50, resources->SCREEN_HEIGHT/2-140}, "LEVEL UP!" );

	optionsUp = new TextElement( NULL, {resources->SCREEN_WIDTH/2-220, resources->SCREEN_HEIGHT/2-100}, "(1)         (2)         (3)         (4)" );
	optionLife = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH/2-217, resources->SCREEN_HEIGHT/2-70}, resources->stuffSpriteRects["Life"][0] );
	optionMana = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH/2-85, resources->SCREEN_HEIGHT/2-70}, resources->stuffSpriteRects["Mana"][0] );
	optionDefense = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH/2+47, resources->SCREEN_HEIGHT/2-70}, resources->stuffSpriteRects["Defense"][0] );
	optionBoots = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH/2+179, resources->SCREEN_HEIGHT/2-70}, resources->stuffSpriteRects["Boots"][0] );
	optionLvlsUp = new TextElement( NULL, {resources->SCREEN_WIDTH/2-215, resources->SCREEN_HEIGHT/2-40}, "L"+std::to_string(currentHero->get_HP()/50)+"          L"+std::to_string(currentHero->get_MP()/30)+"          L"+std::to_string(currentHero->get_defenseLvl())+"          L"+std::to_string(currentHero->get_bootsLvl()) );

	optionsDown = new TextElement( NULL, {resources->SCREEN_WIDTH/2-220, resources->SCREEN_HEIGHT/2+30}, "(5)         (6)         (7)         (8)" );
	optionSword = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH/2-217, resources->SCREEN_HEIGHT/2+60}, resources->stuffSpriteRects["Sword"][0] );
	optionBow = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH/2-85, resources->SCREEN_HEIGHT/2+60}, resources->stuffSpriteRects["Bow"][0] );
	optionTeleport = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH/2+47, resources->SCREEN_HEIGHT/2+60}, resources->stuffSpriteRects["Teleport"][0] );
	optionExplosion = new HUDElement( resources->stuffSheet->texture, {resources->SCREEN_WIDTH/2+179, resources->SCREEN_HEIGHT/2+60}, resources->stuffSpriteRects["Explosion"][0] );
	optionLvlsDown = new TextElement( NULL, {resources->SCREEN_WIDTH/2-215, resources->SCREEN_HEIGHT/2+90}, "L"+std::to_string(currentHero->get_swordLvl())+"          L"+std::to_string(currentHero->get_bowLvl())+"          L"+std::to_string(currentHero->get_teleportLvl())+"          L"+std::to_string(currentHero->get_explosionLvl()) );

	question->render();
	optionLife->render(); optionMana->render(); optionSword->render(); optionBow->render(); optionsUp->render(); optionLvlsUp->render();
	optionBoots->render(); optionDefense->render(); optionTeleport->render(); optionExplosion->render(); optionsDown->render(); optionLvlsDown->render();
	subtextElement->render();
	// Update screen
	SDL_RenderPresent( resources->gameRenderer );
	// Clean Elements
	delete question;
	delete optionLife; delete optionMana; delete optionSword; delete optionBow;	delete optionsUp; delete optionLvlsUp;
	delete optionBoots; delete optionDefense; delete optionTeleport; delete optionExplosion; delete optionsDown; delete optionLvlsDown;
	delete subtextElement;


	// Sub-game loop
	end=false;
	while(!end){

		// Limit frame rate to 30fps
		currentTime = SDL_GetTicks();
		if (currentTime - lastTime < 33)
			SDL_Delay( 33-(currentTime-lastTime) );
		lastTime = currentTime;

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				return false;
			} else if( e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch( e.key.keysym.sym ) {
					case SDLK_ESCAPE:
						return false;
						break;
					case SDLK_1:
						if(lifeCond){
							currentHero->add_HP(50);
							end = true;
						}
						break;
					case SDLK_2:
						if(manaCond){
							currentHero->add_MP(30);
							end = true;
						}
						break;
					case SDLK_3:
						if(defenseCond){
							currentHero->defenseLvl_up();
							end = true;
						}
						break;
					case SDLK_4:
						if(bootsCond){
							currentHero->bootsLvl_up();
							end = true;
						}
						break;
					case SDLK_5:
						if(swordCond){
							currentHero->swordLvl_up();
							end = true;
						}
						break;
					case SDLK_6:
						if(bowCond){
							currentHero->bowLvl_up();
							end = true;
						}
						break;
					case SDLK_7:
						if(teleportCond){
							currentHero->teleportLvl_up();
							end = true;
						}
						break;
					case SDLK_8:
						if(explosionCond){
							currentHero->explosionLvl_up();
							end = true;
						}
						break;
				}
			}
		} // Event loop ends

	} // Sub-game loop ends
	currentHero->add_tempHP(currentHero->get_HP());
	currentHero->add_tempMP(currentHero->get_MP());
	return true;
}


void GameManager::generate_enemies(){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	srand (time(NULL));
	Swordman* swordy; Archer* arch; Wizard* wiz; Size roomS = scene->room->get_size();
	int n = scene->dangerLvl; int midLevel;
	int picker; int nLoop=0; Point posEnemy;
	while(n!=0){
		midLevel = 1 + std::rand()%(n<=10 ? n:10);
		n -= midLevel;
		posEnemy = {roomS.x-(2+3*(nLoop/3))*resources->tileSize.x, roomS.y-(8-3*(nLoop % 3))*resources->tileSize.y};
		picker = (std::rand()%100);
		if (picker<=40){
			swordy= new Swordman( resources->heroSheet->texture, posEnemy, 3, resources->heroSpriteRects["RedHero"],1 );
			scene->charComps.push_back(swordy);
		} else if (picker<=75){
			arch= new Archer( resources->heroSheet->texture, posEnemy, 3, resources->heroSpriteRects["BrownHero"],1 );
			scene->charComps.push_back(arch);
		} else {
			wiz= new Wizard( resources->heroSheet->texture, posEnemy, 3, resources->heroSpriteRects["BlueHero"],1 );
			scene->charComps.push_back(wiz);
		}
		scene->enemiesLeft++;
		nLoop++;
	}
}


void GameManager::scores_screen(){
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	// Clear screen
	SDL_SetRenderDrawColor( resources->gameRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( resources->gameRenderer );
	// Set screen elements
	TextElement* title; TextElement* playerScore; std::fstream scoresFile; std::string s; std::vector<int> scoresRanking;
	int i;

	switch(scene->gameMode){
	case GAMEMODE_SINGLEPLAYER:
		title= new TextElement( NULL, {resources->SCREEN_WIDTH/2-50, resources->SCREEN_HEIGHT/2-80}, "SCORES" );
		playerScore = new TextElement( NULL, {resources->SCREEN_WIDTH/2-85, resources->SCREEN_HEIGHT/2-50}, "Your score: "+std::to_string(scene->hero1Score) );
		playerScore->render(); delete playerScore;

		scoresFile.open("./singleplayer_scores.ini");
		while (getline(scoresFile, s)){
			scoresRanking.push_back(std::stoi(s));
		}
		scoresFile.close();
		scoresRanking.push_back(scene->hero1Score);
		std::sort(scoresRanking.begin(), scoresRanking.end(), std::greater<int>());
		scoresFile.open("./singleplayer_scores.ini");
		if (scoresFile.is_open()) {
			i=0;
			for (std::vector<int>::iterator iter = scoresRanking.begin(); iter!=scoresRanking.begin()+3; iter++){
				scoresFile << std::to_string((*iter))+"\n";
				switch(i){
				case 0: s="1st: "; break;
				case 1: s="2nd: "; break;
				case 2: s="3rd: "; break;
				}
				TextElement* scoreEntry = new TextElement( NULL, {resources->SCREEN_WIDTH/2-55, resources->SCREEN_HEIGHT/2-20+20*i}, s+std::to_string((*iter)) );
				scoreEntry->render(); delete scoreEntry;
				i++;
			}
		}
		scoresFile.close();
		break;
	case GAMEMODE_COOP:
		title= new TextElement( NULL, {resources->SCREEN_WIDTH/2-50, resources->SCREEN_HEIGHT/2-80}, "SCORES" );
		// Player 1 Scores
		playerScore = new TextElement( NULL, {resources->SCREEN_WIDTH/2-180, resources->SCREEN_HEIGHT/2-60}, "Hero 1: "+std::to_string(scene->hero1Score) );
		playerScore->render(); delete playerScore;
		// Player 2 Scores
		playerScore = new TextElement( NULL, {resources->SCREEN_WIDTH/2+60, resources->SCREEN_HEIGHT/2-60}, "Hero 2: "+std::to_string(scene->hero2Score) );
		playerScore->render(); delete playerScore;
		// Total Scores
		playerScore = new TextElement( NULL, {resources->SCREEN_WIDTH/2-100, resources->SCREEN_HEIGHT/2-30}, "Total score: "+std::to_string(scene->hero1Score+scene->hero2Score) );
		playerScore->render(); delete playerScore;

		scoresFile.open("./coop_scores.ini");
				while (getline(scoresFile, s)){
					scoresRanking.push_back(std::stoi(s));
				}
				scoresFile.close();
				scoresRanking.push_back(scene->hero1Score+scene->hero2Score);
				std::sort(scoresRanking.begin(), scoresRanking.end(), std::greater<int>());
				scoresFile.open("./coop_scores.ini");
				if (scoresFile.is_open()) {
					i=0;
					for (std::vector<int>::iterator iter = scoresRanking.begin(); iter!=scoresRanking.begin()+3; iter++){
						scoresFile << std::to_string((*iter))+"\n";
						switch(i){
						case 0: s="1st: "; break;
						case 1: s="2nd: "; break;
						case 2: s="3rd: "; break;
						}
						TextElement* scoreEntry = new TextElement( NULL, {resources->SCREEN_WIDTH/2-55, resources->SCREEN_HEIGHT/2-00+20*i}, s+std::to_string((*iter)) );
						scoreEntry->render(); delete scoreEntry;
						i++;
					}
				}
				scoresFile.close();
		break;
	case GAMEMODE_VERSUS:
		std::string winner = (scene->hero2==NULL ? "Player 1":"Player 2");
		title= new TextElement( NULL, {resources->SCREEN_WIDTH/2-70, resources->SCREEN_HEIGHT/2-80}, winner+" won" );
		break;
	}

	title->render();
	delete title;
	TextElement* instruction = new TextElement( NULL, {resources->SCREEN_WIDTH/2-130, resources->SCREEN_HEIGHT/2+80}, "(Press any key to exit)" );
	instruction->render();
	delete instruction;
	// Update screen
	SDL_RenderPresent( resources->gameRenderer );
	// Clean Elements


	// Sub-game loop
	SDL_Event e;
	unsigned int lastTime = 0, currentTime;
	while(true){

		// Limit frame rate to 30fps
		currentTime = SDL_GetTicks();
		if (currentTime - lastTime < 33)
			SDL_Delay( 33-(currentTime-lastTime) );
		lastTime = currentTime;

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				return;
			} else if( e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				return;
			}
		} // Event loop ends
	}

}
