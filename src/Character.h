/*
 * Character.h
 *
 *  Created on: Jan 29, 2015
 *      Author: elgatil
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "InGameComp.h"
#include "types.h"
#include "HUDElement.h"

class Character: public InGameComp {
protected:
	int HP;
	int tempHP;
	HUDElement* lifeBar;
	HUDElement* lifeBarRemain;
	int MP;
	int tempMP;
	int manaCooldown;
	int bootsLvl;
	int defenseLvl;
	int swordLvl;
	int bowLvl;
	int explosionLvl;
	int teleportLvl;

	int gamePoints;

public:
	Character( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, int HP, int MP);
	virtual ~Character();

	// GETTERS
	int get_HP(){ return HP; }
	int get_tempHP(){ return tempHP; }
	int get_MP(){ return MP; }
	int get_tempMP(){ return tempMP; }
	int get_bootsLvl(){ return bootsLvl; }
	int get_defenseLvl(){ return defenseLvl; }
	int get_swordLvl(){ return swordLvl; }
	int get_bowLvl(){ return bowLvl; }
	int get_explosionLvl(){ return explosionLvl; }
	int get_teleportLvl(){ return teleportLvl; }
	virtual int get_charLvl(){ return (get_HP()/50+get_MP()/30+get_bootsLvl()+get_defenseLvl()+get_swordLvl()+get_bowLvl()+get_explosionLvl()+get_teleportLvl()); }
	int get_points(){ return gamePoints; }


	// SETTERS
	void add_HP(int newHP){ HP+=newHP; tempHP=HP; }
	void add_tempHP(int deltaTempHP);
	void add_MP(int newMP){ MP+=newMP; tempMP=MP; }
	bool add_tempMP(int deltaTempMP);
	void bootsLvl_up(){ bootsLvl++; speedMultiplier=bootsLvl; }
	void defenseLvl_up(){ defenseLvl++; }
	void swordLvl_up(){ swordLvl++; }
	void bowLvl_up(){ bowLvl++; }
	void explosionLvl_up(){ explosionLvl++; }
	void teleportLvl_up(){ teleportLvl++; }
	void add_points(int newPoints){ gamePoints+=newPoints; }


	virtual void update();

	void show_lifeBar();
	bool check_death();
	void teleport();

};

#endif /* CHARACTER_H_ */
