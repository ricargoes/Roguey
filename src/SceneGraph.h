/*
 * SceneGraph.h
 *
 *  Created on: Feb 3, 2015
 *      Author: elgatil
 */

#ifndef SCENEGRAPH_H_
#define SCENEGRAPH_H_

#include <vector>
#include <map>

#include "ResourceManager.h"
#include "types.h"
class Room;
class GameComponent;
class Object;
class Character;
class Player;
class HUDElement;

#define SCENEGRAPH_MODE_CREATE 0
#define SCENEGRAPH_MODE_RESET 1
#define SCENEGRAPH_MODE_DELETE 2

#define GAMEMODE_SINGLEPLAYER 0
#define GAMEMODE_COOP 1
#define GAMEMODE_VERSUS 2

#define GAME_ON 0
#define GAME_LEVEL_CLEARED 1
#define GAME_END 2

typedef std::vector<Character*>::iterator charIter;
typedef std::vector<Object*>::iterator objIter;
typedef std::vector<GameComponent*>::iterator elseIter;

class SceneGraph {

public:
	/**
	 * Singleton instance management.
	 * \param instanceMode Concrete request for the instance manager.
	 */

	std::vector<Character*> charComps;
	std::vector<Object*> objectComps;
	std::vector<Object*> newObjectComps;
	std::vector<GameComponent*> elseComps;

	INIConfig lvlLegend;

	int gameMode;

	Room* room;

	Player* hero1;
	int hero1Score;
	Player* hero2;
	int hero2Score;

	int dangerLvl;
	int enemiesLeft;
	const int OFFSET_LVL=7;
	Size tileSize;

	int check_state_of_the_game();

	static SceneGraph* instance(int instanceMode);

	void close();


private:

	/** Private constructor to Singleton isolation. */
	SceneGraph();

	/** Private destructor to Singleton isolation. */
	~SceneGraph();

	/** Copy operator (private because is disabled by default). */
	SceneGraph(const SceneGraph&);

	/** Assing operator (private because is disabled by default). */
	void operator=(const SceneGraph&);
};

#endif /* SCENEGRAPH_H_ */
