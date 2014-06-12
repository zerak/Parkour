#include "Map.h"
#include "resource.h"
#include "Utils.h"

namespace Parkour{

Map::~Map()
{

}

Map::Map()
{

}

/** Constructor
    * @param {cc.Layer *}
    * @param {cp.Space *}
    */

Map::Map(CCLayer *layer, cpSpace *space)
{
	this->layer = NULL;
	this->space = NULL;
	//MapCount应等于在资源文件夹中的文件数量。并应不少于两个
	this->mapCount = 2;
	this->spriteWidth = 0;
	this->map0 = NULL;
	this->map1 = NULL;
	this->ground0 = NULL;
	this->ground1 = NULL;
	this->curMap = 0;

	this->layer = layer;
	this->space = space;

	// init bg map for the first time
	//地图的上半部分是一个锚点改为(0,0)的精灵,用更改锚点来简化坐标的计算
	map0 = CCSprite::create("res/Map00.png");
	map0->setAnchorPoint(ccp(0, 0));
	map0->setPosition(ccp(0, 0));
	layer->addChild(map0);

	//上层部分跟下层部分的不同之处是它们的位置坐标,将下层部分Y轴坐标设置为 
	//g_groundHight – ground0->getContentSize().height来确保游戏角色的脚是踏在地面上的。
	ground0 = CCSprite::create("res/Ground00.png");
	ground0->setAnchorPoint(ccp(0, 0));
	CCSize size = ground0->getContentSize();
	ground0->setPosition(ccp(0, g_groundHight - size.height));
	layer->addChild(ground0);

	spriteWidth = map0->getContentSize().width;

	map1 = CCSprite::create("res/Map01.png");
	map1->setAnchorPoint(ccp(0, 0));
	// 第二张地图的开始位置是背景的宽度
	map1->setPosition(ccp(spriteWidth, 0));
	layer->addChild(map1);

	ground1 = CCSprite::create("res/Ground01.png");
	ground1->setAnchorPoint(ccp(0, 0));
	ground1->setPosition(ccp(spriteWidth, g_groundHight - size.height));
	layer->addChild(ground1);
}

/**
    * @return width of the map sprite.
    */ 
float Map::getMapWidth()
{
	return spriteWidth;
}

/**
    * @return which map of the runner current run on.
    */ 
int Map::getCurMap() {
    return this->curMap;
}

/**
    * @param {float} X-coordinate of the eye of camera of PlayLayer
    */
bool Map::checkAndReload(float eyeX) {
	//用这种方式计算地图坐标
	int newCur = int(eyeX / spriteWidth);

    if (curMap == newCur) {
        return false;
    }

    CCSprite * map;
    CCSprite * ground;

    if (0 == newCur % 2) {
        // change mapSecond
        map = this->map1;
        ground = this->ground1;
    } else {
        // change mapFirst
        map = this->map0;
        ground = this->ground0;
    }

    CCLOG("==load map:%d", (newCur + 1));

    this->curMap = newCur;

	//在一张背景跑完之后需要切换一张新的图片
    // load curMap + 1
    //var fileName = "res/Map" + FormatNumberLength((newCur + 1) % mapCount, 2) + ".png";

	//char fileMapName[100] = {0};
	//sprintf(fileName, "res/Map%i.png", i);
	//fileMapName = "res/Map" + FormatNumberLength((newCur + 1) % mapCount, 2) + ".png";
	//CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(fileMapName);

	//暂时简化,待扩展
	std::string fileMapName;
	if ((newCur + 1) % mapCount)
	{
		fileMapName = "res/Map00.png";
	} 
	else
	{
		fileMapName = "res/Map01.png";
	}

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(fileMapName.c_str());

    map->setTexture(texture);
    map->setPositionX(this->spriteWidth * (newCur + 1));

    // load ground
#if 0
	var fileGroundName = "res/Ground" + FormatNumberLength((newCur + 1) % mapCount, 2) + ".png";
	CCTexture2D *textureGround = CCTextureCache::sharedTextureCache()->addImage(fileGroundName);
	ground->setTexture(textureGround);
	ground->setPositionX(this->spriteWidth * (newCur + 1));

#else
	std::string fileGroundName;
	if ((newCur + 1) % mapCount)
	{
		fileGroundName = "res/Ground00.png";
	} 
	else
	{
		fileGroundName = "res/Ground01.png";
	}
	CCTexture2D *textureGround = CCTextureCache::sharedTextureCache()->addImage(fileGroundName.c_str());

	ground->setTexture(textureGround);
	ground->setPositionX(this->spriteWidth * (newCur + 1));
#endif

    return true;
}
}