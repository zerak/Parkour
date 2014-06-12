#ifndef __PLAYSCENE_SCENE_H__
#define __PLAYSCENE_SCENE_H__

#include "cocos2d.h"
#include "chipmunk.h"
#include "cocos-ext.h"
#include "Runner.h"
#include "SimpleRecognizer.h"
#include "GeometricRecognizer.h"
#include "Map.h"
#include "BackgroundLayer.h"
#include "ObjectManager.h"
#include "StatusLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace DollarRecognizer;

enum GameStat
{
	GameStatNormal,
	GameStatOver,
};

class PlayScene : public cocos2d::CCLayer
{
public:
	PlayScene();
	~PlayScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(PlayScene);

	//void onEnter();
	static int collisionCoinBegin(cpArbiter *arb, cpSpace *space, void *unused);
	static int collisionRockBegin(cpArbiter *arb, cpSpace *space, void *unused);


	void onEnter();

	void onEnterTransitionDidFinish();

	void onExit();

	void initPhysics();

	void cleanScreen();
	
	void initStatusLayer();

	void createResetButton();
	void reset(CCObject* sender);

	void addNewSpriteAtPosition(CCPoint p);
	void update(float dt);
	void toggleDebugCallback(CCObject* pSender);
	
	virtual bool onTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void onTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void onTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void onTouchCancelled(CCTouch* touch, CCEvent* event);

	//virtual void didAccelerate(CCAcceleration* pAccelerationValue);

public:
	Parkour::Map *map;
	BackgroundLayer *backgroundLayer;

	static StatusLayer *statusLayer;

	float lastEyeX;				//1.定义新的类成员变量

	static Runner *runner;
	
	cpSpace* space;				// chipmunk space定义类成员

	SimpleRecognizer *recognizer;

	GeometricRecognizer* geometricRecognizer;
	Path2D p_2dPath;

	//dollar;
	ObjectManager *objectManager;
	static std::vector<cpShape> shapesToRemove;

	static GameStat gameStat;
	CCSpriteBatchNode *spriteSheet;

	//cpShape* wallBottom;			//跑酷用的地面

	CCLabelTTF *labelCoin;
	CCLabelTTF *labelMeter;
	int coins;

};

#endif // __PLAYSCENE_SCENE_H__
