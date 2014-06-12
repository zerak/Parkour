#ifndef __ROCK_H__
#define __ROCK_H__

#include "cocos2d.h"
#include "chipmunk.h"
#include "cocos-ext.h"
#include "Utils.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Rock
{
public:
	Rock();
	Rock(CCSpriteBatchNode *spriteSheet, cpSpace *space, CCPoint pos);
	~Rock();

	int getMap();
	void setMap(int newMap);

	void removeFromParent();

	cpShape *getShape();

	// getContentSize是石头类中的一个静态方法,将在ObjectManager.cpp中用来计算坐标
	static const CCSize* getContentSize()
	{
		if (NULL == gRockContentSize)
		{
			PhysicsSprite *sprite = PhysicsSprite::createWithSpriteFrameName("rock.png");        
			gRockContentSize = &sprite->getContentSize();
		}

		return gRockContentSize;
	}

public:
	cpSpace *space;
	PhysicsSprite *sprite;
	cpShape  *shape;// current chipmunk shape
	//石头属于哪个地图,这个值需要在ObjectManager.cpp中进行设置。
	int _map;// which map belong to
	static const CCSize *gRockContentSize;
};
//static const CCSize *gRockContentSize = NULL;

#endif // __ROCK_H__
