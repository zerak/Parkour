#include "Coin.h"
#include "resource.h"

USING_NS_CC;

const CCSize *Coin::gCoinContentSize = NULL;

Coin::Coin()
{

}

/** Constructor
    * @param {CCSpriteBatchNode *}
    * @param {cpSpace *}
    * @param {ccp}
    */
Coin::Coin(CCSpriteBatchNode *spriteSheet, cpSpace *space, CCPoint pos)
{
	this->space = NULL;
	this->sprite = NULL;
	this->shape = NULL;
	this->_map = 0;// which map belong to

	this->space = space;

	//初始化金币的动画
	// init runningAction创建一个空白的序列帧动画信息
	CCAnimation* animation = CCAnimation::create();
	//CCSpriteFrame对应的就是帧，将CCSpriteFrame添加到CCAnimation生成动画数据，
	//用CCAnimation生成CCAnimate（就是最终的动画动作），最后可以用CCSprite执行这个动作。
	CCSpriteFrame * frame = NULL;
	// num equal to spriteSheet
	for (unsigned int i = 0; i < 8; i++) {
		char str[100] = {0};
		sprintf(str, "coin%i.png", i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animation->addSpriteFrame(frame);
	}
	//animation = CCAnimation.create(animFrames, 0.1);
	animation->setDelayPerUnit(0.1f);
	//设置动画结束后是否保留动画帧信息
	animation->setRestoreOriginalFrame(false);
	//设置循环播放次数 (-1:无限循环)
	animation->setLoops(-1);
	//由这个动画信息创建一个序列帧动画
	CCAction *action = CCAnimate::create(animation);
	//保存这个动画,这行代码­­­­­retain()将避免CCObject被GC
	//runningAction = CCRepeatForever::create(CCAnimate::create(animation));
	//action->retain();

	this->sprite = PhysicsSprite::createWithSpriteFrameName("coin0.png");
	
	//金币采取使用静态的body方式来抵消重力
	// init physics
	cpFloat radius = 0.95 * sprite->getContentSize().width / 2;

	cpBody *body = cpBodyNewStatic();
	//body->setPos(pos);
	body->p = cpv(pos.x, pos.y);

	sprite->setCPBody(body);

	this->shape = cpCircleShapeNew(body, radius, cpv(0, 0));
	this->shape->collision_type = (SpriteTagCoin);
	//传感器只是调用碰撞函数,并不会真的产生碰撞
	//Sensors only call collision callbacks, and never generate real collisions
	//shape->setSensor(true);
	this->shape->sensor = true;

	cpSpaceAddStaticShape(this->space, this->shape);

	// Needed for collision
	//body.setUserData(this);

	// add sprite to sprite sheet
	this->sprite->runAction(action);
	spriteSheet->addChild(this->sprite, 1);
}

Coin::~Coin()
{

}

int Coin::getMap()
{
	return this->_map;
}

void Coin::setMap(int newMap)
{
	this->_map = newMap;
}

//在ObjectManager.cpp中使用removeFromParent来删除元素
void Coin::removeFromParent()
{
	cpSpaceRemoveStaticShape(this->space, this->shape);
	this->shape = NULL;
	this->sprite->removeFromParent();
	this->sprite = NULL;
}

cpShape *Coin::getShape()
{
	return this->shape;
}



