/*
 * SceneGraph.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: elgatil
 */

#include "SceneGraph.h"

SceneGraph::SceneGraph() {
	ResourceManager* resources = ResourceManager::instance(RESOURCEMANAGER_MODE_INIT);

	room = NULL;
	hero1 = NULL;
	hero1Score=0;
	hero2 = NULL;
	hero2Score=0;
	lvlLegend = resources->read_INIConfig("levels.ini");
	dangerLvl=0;
	enemiesLeft=0;
	gameMode=-1;
	tileSize = resources->tileSize;

}

SceneGraph::~SceneGraph() {
	// TODO Auto-generated destructor stub
}


// Singleton instance manager.
SceneGraph* SceneGraph::instance(int instanceMode) {

	static SceneGraph *instance;

	if(instance) {
		switch(instanceMode) {
			case SCENEGRAPH_MODE_RESET:
				delete instance;
				instance = new SceneGraph();
				break;
			case SCENEGRAPH_MODE_DELETE:
				delete instance;
				break;
			case SCENEGRAPH_MODE_CREATE:
				break;
			default:
				return 0;
				break;
		}
	} else {
		switch(instanceMode) {
			case SCENEGRAPH_MODE_CREATE:
				instance = new SceneGraph();
				break;
			case SCENEGRAPH_MODE_DELETE:
			case SCENEGRAPH_MODE_RESET:
			default:
				return 0;
				break;
		}
	}

	return instance;
}


void SceneGraph::close(){

	delete room;
	for(elseIter iter = elseComps.begin(); iter!=elseComps.end(); ++iter){
		delete (*iter);
	}
	for(charIter iter = charComps.begin(); iter!=charComps.end(); ++iter){
		delete (*iter);
	}
	for(objIter iter = objectComps.begin(); iter!=objectComps.end(); ++iter){
		delete (*iter);
	}
	hero1 = NULL;
	hero2 = NULL;
}


int SceneGraph::check_state_of_the_game(){
	if ( ( !hero1 && !hero2 ) || ( gameMode==GAMEMODE_VERSUS && (!hero1 || !hero2) ) )
		return GAME_END;
	if (gameMode!=GAMEMODE_VERSUS && enemiesLeft==0) return GAME_LEVEL_CLEARED;
	return GAME_ON;
}
