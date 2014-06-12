#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class BackgroundLayer : public cocos2d::CCLayer
{
	CCTMXTiledMap *map00;
	CCTMXTiledMap *map01;
	float mapWidth;
	int mapIndex;

public:
	BackgroundLayer(void);
	~BackgroundLayer(void);

	virtual bool init();  
	bool checkAndReload(float eyeX);
};

#endif // __BACKGROUND_LAYER_H__
