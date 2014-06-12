#ifndef __MAP_H__
#define __MAP_H__

#include "cocos2d.h"
#include "chipmunk.h"
#include "cocos-ext.h"
#include "Utils.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace Parkour{
class Map 
{
	CCLayer *layer;
	cpSpace *space;
	float spriteWidth;

	int mapCount;// total map of resource
	CCSprite *map0;
	CCSprite *map1;
	CCSprite *ground0;
	CCSprite *ground1;
	int curMap;// [0, n]

public:
	Map();
	Map(CCLayer *layer, cpSpace *space);
	~Map();
	float getMapWidth();

	int getCurMap();

	bool Map::checkAndReload(float eyeX);
};
}

#endif // __MAP_H__
