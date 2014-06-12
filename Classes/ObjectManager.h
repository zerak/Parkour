#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__

#include "cocos2d.h"
#include "chipmunk.h"
#include "cocos-ext.h"
#include <list>
#include "Utils.h"
#include "Rock.h"
#include "Coin.h"


USING_NS_CC;
USING_NS_CC_EXT;

class ObjectManager
{
	CCSpriteBatchNode *spriteSheet;
	cpSpace  *space;
	//objects;//”√list¥Ê
	//std::list<Rock*> m_vecRocksList;
	//std::list<Coin*> m_vecCoinsList;
	std::list<Rock*> m_vecRocksList;
	std::list<Coin*> m_vecCoinsList;

public:
	ObjectManager();
	ObjectManager(CCSpriteBatchNode *spriteSheet, cpSpace  *space);
	~ObjectManager();
	void initObjectOfMap(int map, float mapWidth);

	bool recycleObjectOfMap(int map);

	void removeCoin(Coin *obj);
	void removeRock(Rock *obj);

	Coin * getCoinByShape(cpShape *shape);
	Rock * getRockByShape(cpShape *shape);
};

#endif // __OBJECTMANAGER_H__
