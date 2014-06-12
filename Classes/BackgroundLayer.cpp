#include "BackgroundLayer.h"
#include "resource.h"


BackgroundLayer::BackgroundLayer()
{
	this->init();
}

BackgroundLayer::~BackgroundLayer()
{
	
}

// on "init" you need to initialize your instance
bool BackgroundLayer::init()
{
	map00 = CCTMXTiledMap::create(s_map00);
	this->addChild(map00);

	mapWidth = map00->getContentSize().width;

	map01 = CCTMXTiledMap::create(s_map01);
	map01->setPosition(ccp(mapWidth, 0));
	this->addChild(map01);

	return true;
}

/**
    * @param {float} X-coordinate of the eye of camera of PlayLayer
    */
bool BackgroundLayer::checkAndReload(float eyeX) {
	//用这种方式计算地图坐标
	int newMapIndex = int(eyeX / mapWidth);

    if (mapIndex == newMapIndex) {
        return false;
    }

	if (0 == newMapIndex % 2) {
		// change mapSecond
		map01->setPositionX(mapWidth * (newMapIndex + 1));
	} else {
		// change mapFirst
		map00->setPositionX(mapWidth * (newMapIndex + 1));
	}

	mapIndex = newMapIndex;

	return true;
}

