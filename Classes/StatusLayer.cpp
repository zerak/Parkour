#include "StatusLayer.h"
#include "resource.h"

USING_NS_CC;

StatusLayer::StatusLayer()
{
	this->init();
}

StatusLayer::StatusLayer(CCLayer *layer)
{
	this->layer = NULL;
	this->labelCoin = NULL;
	this->labelMeter = NULL;
	this->coins = 0;

	this->layer = layer;

	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	//CCLabelTTF::create创建一个文字标签，第一个参数是显示的文字，第二个参数设置字体（可扩展下有那些字体可选择），
	//第三个参数设置字体大小
	this->labelCoin = CCLabelTTF::create("Coins:0", "Helvetica", 20);
	this->labelCoin->setColor(ccc3(0,0,0));//black color
	//this->labelCoin->setAnchorPoint(ccp(0, 0));
	//this->labelCoin->setPosition(ccp(70, winSize.height - 20));
	labelCoin->setPosition(ccp(70, 300));

	//layer->addChild(this->labelCoin);

	this->labelMeter = CCLabelTTF::create("0M", "Helvetica", 20);
	//this->labelMeter->setPosition(ccp(winSize.width - 70, winSize.height - 20));
	//labelMeter->setAnchorPoint(ccp(0, 0));

	this->labelMeter->setPosition(ccp(300, 300));

	//layer->addChild(this->labelMeter);
}

StatusLayer::~StatusLayer()
{

}

// on "init" you need to initialize your instance
bool StatusLayer::init()
{
	//CCLayer::onEnter();//务必调用
	// PlayLayer will get StatusLayer by tag
	this->setTag(1);
	this->layer = NULL;
	this->labelCoin = NULL;
	this->labelMeter = NULL;
	this->coins = 0;

	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	//CCLabelTTF::create创建一个文字标签，第一个参数是显示的文字，第二个参数设置字体（可扩展下有那些字体可选择），
	//第三个参数设置字体大小
	this->labelCoin = CCLabelTTF::create("Coins:0", "Helvetica", 25);
	this->labelCoin->setColor(ccc3(0,0,0));//black color
	//this->labelCoin->setAnchorPoint(ccp(0, 0));
	this->labelCoin->setPosition(ccp(70, winSize.height - 20));
	//labelCoin->setPosition(ccp(70, 300));
	this->addChild(this->labelCoin);

	this->labelMeter = CCLabelTTF::create("0M", "Helvetica", 25);
	//this->labelMeter->setPosition(ccp(winSize.width - 70, winSize.height - 20));
	//labelMeter->setAnchorPoint(ccp(0, 0));
	this->labelMeter->setPosition(ccp(300, 300));
	this->addChild(this->labelMeter);

	return true;
}

void StatusLayer::addCoin(int num)
{
	coins += num;
	this->labelCoin->setString("Coins:" + coins);
}

void StatusLayer::updateMeter(float px)
{
	char meter[100] = {0};
	sprintf(meter, "%iM", int(px / 10));

	this->labelMeter->setString(meter);
}


