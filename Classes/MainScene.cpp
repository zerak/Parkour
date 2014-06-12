#include "MainScene.h"
#include "resource.h"
#include "PlayScene.h"

USING_NS_CC;

MainScene::~MainScene() {
	//CC_SAFE_RELEASE(_jamMove);
}

CCScene* MainScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MainScene *layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize size = CCDirector::getInstance()->getWinSize();
	CCPoint centerPos = ccp(size.width/2, size.height/2);

	CCSprite *spriteBG = CCSprite::create(s_HelloBG);
	spriteBG->setPosition(centerPos);
	this->addChild(spriteBG);

	CCMenuItemSprite *menuItemPlay = CCMenuItemSprite::create(
		CCSprite::create(s_start_n),
		CCSprite::create(s_start_s),
		CC_CALLBACK_1(MainScene::onPlay,this) );

	// create menu, it's an autorelease object
	CCMenu *menu = CCMenu::create(menuItemPlay, NULL);
	menu->setPosition(centerPos);
	this->addChild(menu);

	return true;
}

void MainScene::onPlay(cocos2d::Ref* pSender)
{
	CCLOG("Start a new game!!!");

	CCScene *playScene = PlayScene::scene();

	CCDirector::sharedDirector()->replaceScene(playScene);
}

