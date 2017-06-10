/*
 * Interface.h
 *
 *  Created on: Feb 22, 2015
 *      Author: elgatil
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <vector>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <algorithm>

#include <SDL2/SDL.h>

#include "ResourceManager.h"
#include "SceneGraph.h"
#include "GameComponent.h"
#include "Character.h"
#include "Object.h"
#include "Player.h"
#include "Swordman.h"
#include "Archer.h"
#include "Wizard.h"
#include "HUDElement.h"
#include "TextElement.h"

class GameManager {
public:
	GameManager();
	virtual ~GameManager();

	void initialize_HUD();
	void update_HUD();

	int choose_game_mode();
	std::string choose_your_hero(std::string subtext="");
	bool transition(int levels);
	void scores_screen();

	bool level_up(Player* currentHero);
	void generate_enemies();

private:
	TextElement* HPText; TextElement* MPText; TextElement* defenseText; TextElement* bootsText;
	TextElement* swordText; TextElement* bowText; TextElement* explosionText; TextElement* teleportText; TextElement* score;
	HUDElement* lifeIcon; HUDElement* manaIcon; HUDElement* defenseIcon; HUDElement* bootsIcon;
	HUDElement* swordIcon; HUDElement* bowIcon; HUDElement* explosionIcon; HUDElement* teleportIcon;

	TextElement* HPText2; TextElement* MPText2; TextElement* defenseText2; TextElement* bootsText2;
	TextElement* swordText2; TextElement* bowText2; TextElement* explosionText2; TextElement* teleportText2; TextElement* score2;
	HUDElement* lifeIcon2; HUDElement* manaIcon2; HUDElement* defenseIcon2; HUDElement* bootsIcon2;
	HUDElement* swordIcon2; HUDElement* bowIcon2; HUDElement* explosionIcon2; HUDElement* teleportIcon2;
};

#endif /* INTERFACE_H_ */
