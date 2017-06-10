/*
 * types.h
 *
 *  Created on: Jan 24, 2015
 *      Author: elgatil
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <map>
#include <string>
#include <fstream>

#include <SDL2/SDL.h>

typedef std::map<std::string, int> Group;
typedef std::map<std::string, Group> INIConfig;

struct Point {int x; int y;};
struct Size {int x; int y;};

struct Image {SDL_Texture* texture; Size textSize;};


#endif /* TYPES_H_ */
