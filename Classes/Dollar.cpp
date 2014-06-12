#include "MainScene.h"
#include "resource.h"

USING_NS_CC;

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
	//获取屏幕大小

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	/////////////////////////////
	// 3. add your codes below...

	CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCSize centerPos = ccp(size.width/2, size.height/2);

	CCSprite *spriteBG = CCSprite::create(s_HelloBG);
	spriteBG->setPosition(centerPos);
	this->addChild(spriteBG);

	//设置字体大小  
	CCMenuItemFont::setFontSize( 60 );  
	//根据名字设置字体  
	CCMenuItemFont::setFontName("Courier New");  
	//设置能点击  
	setTouchEnabled(true);  
	// Font Item  

	// 创建一个CCMenuItemFont   
	CCMenuItemFont *menuItemPlay = CCMenuItemFont::create("Play",this, menu_selector(MainScene::onPlay));
	//menuItemPlay->setFontSizeObj(60);  
	//menuItemPlay->setFontName("Marker Felt");  
	//menuItemPlay->setEnabled(true);

	// create menu, it's an autorelease object
	CCMenu *menu = CCMenu::create(menuItemPlay, NULL);
	menu->setPosition(centerPos);
	this->addChild(menu, 1);

	// add a label shows "Hello World"
	// create and initialize a label
	//CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);

	// position the label on the center of the screen
	//pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
		//origin.y + visibleSize.height - pLabel->getContentSize().height));

	// add the label as a child to this layer
	//this->addChild(pLabel, 1);

	return true;
}
void MainScene::onPlay(CCObject* pSender)
{
	CCLOG("New play a game!!!");
}


void MainScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}
