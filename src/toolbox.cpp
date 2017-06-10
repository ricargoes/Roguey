/*
 * toolBox.cpp
 *
 *  Created on: Feb 18, 2015
 *      Author: elgatil
 */

#include "toolbox.h"

void update_components(){
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);

	// CLEANING
	for(charIter iter = scene->charComps.begin(); iter!=scene->charComps.end(); ++iter){
		switch((*iter)->get_destroy()){
		case UNBROKEN:
			break;
		case BREAKING:
			(*iter)->advance_destroy();
			break;
		case BROKEN:
			if( (*iter)!=scene->hero1 && (*iter)!=scene->hero2 ) scene->enemiesLeft--;
			// DESTROYING HEORES
			if ( (*iter)==scene->hero1 ){
				scene->hero1Score=scene->hero1->get_points();
				scene->hero1 = NULL;
			}
			if ( (*iter)==scene->hero2 ){
				scene->hero2Score=scene->hero2->get_points();
				scene->hero2 = NULL;
			}
			delete (*iter);
			scene->charComps.erase(iter);
			--iter;
			break;
		}
	}
	for(objIter iter = scene->objectComps.begin(); iter!=scene->objectComps.end(); ++iter){
		switch((*iter)->get_destroy()){
		case UNBROKEN:
			break;
		case BREAKING:
			(*iter)->advance_destroy();
			break;
		case BROKEN:
			delete (*iter);
			scene->objectComps.erase(iter);
			--iter;
			break;
		}
	}
	for(elseIter iter = scene->elseComps.begin(); iter!=scene->elseComps.end(); ++iter){
		switch((*iter)->get_destroy()){
		case UNBROKEN:
			break;
		case BREAKING:
			(*iter)->advance_destroy();
			break;
		case BROKEN:
			delete (*iter);
			scene->elseComps.erase(iter);
			--iter;
			break;
		}
	}

	// ADDING NEW COMPONENTS
	for(objIter iter=scene->newObjectComps.begin(); iter!=scene->newObjectComps.end(); ++iter){
		scene->objectComps.push_back((*iter));
	}
	scene->newObjectComps.clear();
}



