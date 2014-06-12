#include "GameOverLayer.h"
#include "resource.h"
#include "PlayScene.h"

USING_NS_CC;

GameOverLayer::GameOverLayer()
{
	this->init();
}

GameOverLayer::~GameOverLayer()
{

}

// on "init" you need to initialize your instance
bool GameOverLayer::init()
{
	//CCLayerColor *background = CCLayerColor::create(ccc4(0, 0, 0, 180));
	//this->addChild(background);

	//获取屏幕大小
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCPoint centerPos = ccp(size.width/2, size.height/2);

	CCSprite *spriteBG = CCSprite::create(s_HelloBG);
	spriteBG->setPosition(centerPos);
	this->addChild(spriteBG);

	//设置字体大小  
	CCMenuItemFont::setFontSize( 30 );  
	//根据名字设置字体  
	CCMenuItemFont::setFontName("Courier New");  
	//设置能点击  
	setTouchEnabled(true);  

	// 创建一个CCMenuItemSprite   
	CCMenuItemSprite *menuItemRestart = CCMenuItemSprite::create(
		CCSprite::create(s_restart_n),
		CCSprite::create(s_restart_s),
		CC_CALLBACK_1(GameOverLayer::onRestart,this) );

	// create menu, it's an autorelease object
	CCMenu *menu = CCMenu::create(menuItemRestart, NULL);
	menu->setPosition(centerPos);
	this->addChild(menu);

	return true;
}
void GameOverLayer::onRestart(CCObject* pSender)
{
	CCLOG("Restart a new game!!!");
	CCScene *playScene = PlayScene::scene();

	//加载PlayScene
	CCDirector::sharedDirector()->replaceScene(playScene);
}
