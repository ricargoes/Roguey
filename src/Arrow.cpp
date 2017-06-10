/*
 * Arrow.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: elgatil
 */

#include "Arrow.h"

Arrow::Arrow( SDL_Texture* loadedTexture, Point pos, int nAnimSprites, std::vector<SDL_Rect> spRects, Character* objectOwner, Point targetPoint )
		: Object(loadedTexture, pos, nAnimSprites, spRects, objectOwner, true){

	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);
	attack = scene->lvlLegend["bow"][std::to_string(objectOwner->get_bowLvl())];
	speedMultiplier = 5+objectOwner->get_bowLvl()/2;
	angle = atan2( targetPoint.y-pos.y, targetPoint.x-pos.x )*( 180.0 / M_PI );
	set_position(position.x+13*cos(angle/( 180.0 / M_PI )),position.y+13*sin(angle/( 180.0 / M_PI )));
}


Arrow::~Arrow() {

}


void Arrow::update(){
	if (destroy == BREAKING || destroy == BROKEN)
		return;
	// MOVEMENT
	set_position(position.x+1*stepLength.x*speedMultiplier*cos(angle/( 180.0 / M_PI )),position.y+1*stepLength.y*speedMultiplier*sin(angle/( 180.0 / M_PI )));

	// COLLISIONS
	SceneGraph* scene = SceneGraph::instance(SCENEGRAPH_MODE_CREATE);
	if (this->check_wall(scene->room)){
		destroy = BREAKING;
		return;
	}

	for(charIter iter = scene->charComps.begin(); iter != scene->charComps.end(); ++iter){
		if (owner==(*iter))
			continue;
		SDL_Rect otherCompRect = (*iter)->get_rect_after_angle();
		if ( this->check_collision(otherCompRect) ){
			destroy = BREAKING;
			(*iter)->add_tempHP( -1*(attack-scene->lvlLegend["defense"][std::to_string((*iter)->get_defenseLvl())]) );

			if ( (*iter)->get_destroy()==UNBROKEN && (*iter)->check_death() ) owner->add_points(10*(*iter)->get_charLvl());
		}
	}

	for(objIter iter = scene->objectComps.begin(); iter != scene->objectComps.end(); ++iter){
		if (this==(*iter))
			continue;
		SDL_Rect otherCompRect = (*iter)->get_rect_after_angle();
		if ( this->check_collision(otherCompRect) ){
			destroy = BREAKING;
			return;
		}
	}
}
