#include "Rock.h"
#include "resource.h"
#include "Utils.h"
#include "Runner.h"

USING_NS_CC;

const CCSize *Rock::gRockContentSize = NULL;

Rock::Rock()
{

}

/** Constructor
    * @param {CCSpriteBatchNode *}
    * @param {cpSpace *}
    * @param {ccp}
    */
Rock::Rock(CCSpriteBatchNode *spriteSheet, cpSpace *space, CCPoint pos)
{
	this->space = NULL;
	this->sprite = NULL;
	this->shape = NULL;
	this->_map = 0;// which map belong to

	this->space = space;
#if 1
	//石头有两个可根据Y­coordinate的值选择的纹理
	if (pos.y >= (g_groundHight + Runner::getCrouchContentSize()->height)) {
	//if (pos.y >= (g_groundHight + Runner::gRunnerCrouchContentSizeHeight)) {
		this->sprite = PhysicsSprite::createWithSpriteFrameName("hathpace.png");
	} else {
		this->sprite = PhysicsSprite::createWithSpriteFrameName("rock.png");
	}
#endif

	//采取使用静态的body方式来抵消重力
	cpBody *body = cpBodyNewStatic();
	body->p = cpv(pos.x, pos.y);
	this->sprite->setCPBody(body);

	//石头的形状不是circle,而是box
	this->shape = cpBoxShapeNew(body,
		this->sprite->getContentSize().width,
		this->sprite->getContentSize().height);

	this->shape->collision_type = (SpriteTagRock);

	//传感器只是调用碰撞函数,并不会真的产生碰撞
	//Sensors only call collision callbacks, and never generate real collisions
	//shape->setSensor(true);
	this->shape->sensor = true;

	cpSpaceAddStaticShape(this->space, this->shape);
	spriteSheet->addChild(this->sprite);
	// Needed for collision
	//body.setUserData(this);
}

Rock::~Rock()
{

}

int Rock::getMap()
{
	return this->_map;
}

void Rock::setMap(int newMap)
{
	this->_map = newMap;
}

//在ObjectManager.cpp中使用removeFromParent来删除元素
void Rock::removeFromParent()
{
	if ((NULL != this->space)&&(NULL != this->shape))
	{
		cpSpaceRemoveStaticShape(this->space, this->shape);
	}

	this->shape = NULL;
	this->sprite->removeFromParent();
	this->sprite = NULL;
}

cpShape *Rock::getShape()
{
	return this->shape;
}



